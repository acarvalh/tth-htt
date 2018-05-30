#!/usr/bin/env python
import os, logging, sys, getpass
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_4l import analyzeConfig_4l
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_4l.py -v 2017Dec13 -m default -e 2017

mode_choices         = [ 'default', 'forBDTtraining', 'sync', 'sync_wMEM' ]
sys_choices          = [ 'central', 'full', 'extended' ]
systematics.full     = systematics.an_common
systematics.extended = systematics.an_extended

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_preselect()
parser.add_rle_select()
parser.add_nonnominal()
parser.add_hlt_filter()
parser.add_files_per_job()
parser.add_use_home()
args = parser.parse_args()

# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
resubmission_limit = args.resubmission_limit
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_input_files  = args.check_input_files
debug              = args.debug
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
mode              = args.mode
systematics_label = args.systematics
use_preselected   = args.use_preselected
rle_select        = os.path.expanduser(args.rle_select)
use_nonnominal    = args.original_central
hlt_filter        = args.hlt_filter
files_per_job     = args.files_per_job
use_home          = args.use_home

# Use the arguments
central_or_shift = getattr(systematics, systematics_label)
do_sync          = mode.startswith('sync')

chargeSumSelections = [ "OS", "SS" ]

if mode == "default":
  if use_preselected:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_preselected import samples_2017
  else:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017
elif mode == "forBDTtraining":
  if use_preselected:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_BDT_preselected import samples_2017
  else:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_BDT import samples_2017
  chargeSumSelections = [ "OS" ]
elif mode == "sync_wMEM":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_addMEM_sync import samples_2017
elif mode == "sync":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_sync import samples_2017
else:
  raise ValueError("Internal logic error")

if era == "2017":
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
  samples = samples_2017
else:
  raise ValueError("Invalid era: %s" % era)

for sample_name, sample_info in samples.items():
  if sample_name.startswith('/Tau/Run'):
    sample_info["use_it"] = False

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shift)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(resubmission_limit):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_4l(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      executable_analyze                    = "analyze_4l",
      cfgFile_analyze                       = "analyze_4l_cfg.py",
      samples                               = samples,
      applyFakeRateWeights                  = "4lepton",
      chargeSumSelections                   = chargeSumSelections,
      central_or_shifts                     = central_or_shift,
      max_files_per_job                     = files_per_job,
      era                                   = era,
      use_lumi                              = True,
      lumi                                  = lumi,
      check_input_files                     = check_input_files,
      running_method                        = running_method,
      num_parallel_jobs                     = num_parallel_jobs,
      executable_addBackgrounds             = "addBackgrounds",
      executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes",
      histograms_to_fit                     = [
        "EventCounter",
        "numJets"
      ],
      select_rle_output                     = True,
      select_root_output                    = False,
      verbose                               = idx_job_resubmission > 0,
      dry_run                               = dry_run,
      do_sync                               = do_sync,
      isDebug                               = debug,
      rle_select                            = rle_select,
      use_nonnominal                        = use_nonnominal,
      hlt_filter                            = hlt_filter,
      use_home                              = use_home,
    )

    if mode.find("forBDTtraining") != -1:
      analysis.set_BDT_training(hadTau_selection_relaxed, hadTauFakeRateWeight_inputFileName)

    job_statistics = analysis.create()
    for job_type, num_jobs in job_statistics.items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
    job_statistics_summary[idx_job_resubmission] = job_statistics

    if idx_job_resubmission == 0:
      if auto_exec:
        run_analysis = True
      elif no_exec:
        run_analysis = False
      else:
        run_analysis = query_yes_no("Start jobs ?")
    if run_analysis:
      analysis.run()
    else:
      sys.exit(0)

    if job_statistics['analyze'] == 0:
      is_last_resubmission = True

  for idx_job_resubmission in job_statistics_summary.keys():
    logging.info("Job (re)submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
