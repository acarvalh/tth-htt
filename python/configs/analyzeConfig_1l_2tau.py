import logging

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

def get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight):
  lepton_and_hadTau_selection_and_frWeight = lepton_and_hadTau_selection
  if lepton_and_hadTau_selection.startswith("Fakeable"):
    if lepton_and_hadTau_frWeight == "enabled":
      lepton_and_hadTau_selection_and_frWeight += "_wFakeRateWeights"
    elif lepton_and_hadTau_frWeight == "disabled":
      lepton_and_hadTau_selection_and_frWeight += "_woFakeRateWeights"
  lepton_and_hadTau_selection_and_frWeight = lepton_and_hadTau_selection_and_frWeight.replace("|", "_")
  return lepton_and_hadTau_selection_and_frWeight

def getHistogramDir(hadTau_selection, hadTau_frWeight, hadTau_charge_selection):
  hadTau_selection_part1 = hadTau_selection
  for separator in [ "|" ]:
    if hadTau_selection_part1.find(separator) != -1:
      hadTau_selection_part1 = hadTau_selection_part1[:hadTau_selection_part1.find(separator)]
  histogramDir = "1l_2tau_%s_%s" % (hadTau_charge_selection, hadTau_selection_part1)
  if hadTau_selection_part1.find("Fakeable") != -1:
    if hadTau_frWeight == "enabled":
      histogramDir += "_wFakeRateWeights"
    elif hadTau_frWeight == "disabled":
      histogramDir += "_woFakeRateWeights"
  return histogramDir

class analyzeConfig_1l_2tau(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  Args specific to analyzeConfig_1l_2tau:
    hadTau_selection: either `Tight`, `Loose` or `Fakeable`
    hadTau_charge_selection: either `OS` or `SS` (opposite-sign or same-sign)

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.

  """
  def __init__(self,
        configDir,
        outputDir,
        executable_analyze,
        cfgFile_analyze,
        samples,
        lep_mva_wp,
        hadTau_selection,
        hadTau_charge_selections,
        applyFakeRateWeights,
        central_or_shifts,
        max_files_per_job,
        era,
        use_lumi,
        lumi,
        check_input_files,
        running_method,
        num_parallel_jobs,
        executable_addBackgrounds,
        executable_addBackgroundJetToTauFakes,
        histograms_to_fit,
        select_rle_output = False,
        do_sync           = False,
        verbose           = False,
        dry_run           = False,
        isDebug           = False,
        rle_select        = '',
        use_nonnominal    = False,
        hlt_filter        = False,
        use_home          = True,
      ):
    analyzeConfig.__init__(self,
      configDir          = configDir,
      outputDir          = outputDir,
      executable_analyze = executable_analyze,
      channel            = "1l_2tau",
      lep_mva_wp         = lep_mva_wp,
      central_or_shifts  = central_or_shifts,
      max_files_per_job  = max_files_per_job,
      era                = era,
      use_lumi           = use_lumi,
      lumi               = lumi,
      check_input_files  = check_input_files,
      running_method     = running_method,
      num_parallel_jobs  = num_parallel_jobs,
      histograms_to_fit  = histograms_to_fit,
      triggers           = [ '1e', '1e1tau', '1mu', '1mu1tau' ],
      do_sync            = do_sync,
      verbose            = verbose,
      dry_run            = dry_run,
      isDebug            = isDebug,
      use_home           = use_home,
    )

    self.samples = samples

    ##self.lepton_and_hadTau_selections = [ "Tight", "Fakeable", "Fakeable_mcClosure" ]
    self.lepton_and_hadTau_selections = [ "Tight", "Fakeable" ]
    self.lepton_and_hadTau_frWeights = [ "enabled", "disabled" ]
    self.hadTau_selection_part2 = hadTau_selection
    self.hadTau_charge_selections = hadTau_charge_selections
    self.applyFakeRateWeights = applyFakeRateWeights

    self.lepton_genMatches = [ "1l0g0j", "0l1g0j", "0l0g1j" ]
    self.hadTau_genMatches = [ "2t0e0m0j", "1t1e0m0j", "1t0e1m0j", "1t0e0m1j", "0t2e0m0j", "0t1e1m0j", "0t1e0m1j", "0t0e2m0j", "0t0e1m1j", "0t0e0m2j" ]

    self.apply_leptonGenMatching = None
    self.apply_hadTauGenMatching = None
    self.lepton_and_hadTau_genMatches_nonfakes = []
    self.lepton_and_hadTau_genMatches_conversions = []
    self.lepton_and_hadTau_genMatches_fakes = []
    if self.applyFakeRateWeights == "3L":
      self.apply_leptonGenMatching = True
      self.apply_hadTauGenMatching = True
      for lepton_genMatch in self.lepton_genMatches:
        for hadTau_genMatch in self.hadTau_genMatches:
          lepton_and_hadTau_genMatch = "&".join([ lepton_genMatch, hadTau_genMatch ])
          if lepton_genMatch.endswith("0g0j") and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_nonfakes.append(lepton_and_hadTau_genMatch)
          elif lepton_genMatch.endswith("0j") and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_conversions.append(lepton_and_hadTau_genMatch)
          else:
            self.lepton_and_hadTau_genMatches_fakes.append(lepton_and_hadTau_genMatch)
    elif applyFakeRateWeights == "2tau":
      self.apply_leptonGenMatching = True
      self.apply_hadTauGenMatching = True
      for lepton_genMatch in self.lepton_genMatches:
        for hadTau_genMatch in self.hadTau_genMatches:
          if lepton_genMatch.find("0g") != -1 and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_nonfakes.append(hadTau_genMatch)
          elif hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_conversions.append(hadTau_genMatch)
          else:
            self.lepton_and_hadTau_genMatches_fakes.append(hadTau_genMatch)
    else:
      raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % applyFakeRateWeights)

    self.executable_addBackgrounds = executable_addBackgrounds
    self.executable_addFakes = executable_addBackgroundJetToTauFakes

    self.nonfake_backgrounds = [ "TT", "TTW", "TTZ", "TTWW", "EWK", "Rares", "tH", "VH" ]

    self.prep_dcard_processesToCopy = [ "data_obs" ] + self.nonfake_backgrounds + [ "conversions", "fakes_data", "fakes_mc" ]
    ##self.make_plots_backgrounds = self.nonfake_backgrounds + [ "fakes_data" ]
    self.make_plots_backgrounds = [ "TTW", "TTZ", "TTWW", "EWK", "Rares", "tH" ] + [ "conversions", "fakes_data" ]

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)
    self.histogramDir_prep_dcard = "1l_2tau_OS_Tight"
    self.histogramDir_prep_dcard_SS = "1l_2tau_SS_Tight"
    self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_1l_2tau_cfg.py")
    self.cfgFile_make_plots_mcClosure = os.path.join(self.template_dir, "makePlots_mcClosure_1l_2tau_cfg.py")

    self.select_rle_output = select_rle_output
    self.rle_select = rle_select
    self.use_nonnominal = use_nonnominal
    self.hlt_filter = hlt_filter

  def set_BDT_training(self, hadTau_selection_relaxed):
    """Run analysis with loose selection criteria for leptons and hadronic taus,
       for the purpose of preparing event list files for BDT training.
    """
    self.lepton_and_hadTau_selections = [ "forBDTtraining" ]
    self.lepton_and_hadTau_frWeights  = [ "disabled" ]
    super(analyzeConfig_1l_2tau, self).set_BDT_training(hadTau_selection_relaxed)

  def createCfg_analyze(self, jobOptions, sample_info):
    """Create python configuration file for the analyze_1l_2tau executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_1l_2tau.cc
    """
    lines = []
    hadTau_frWeight = "disabled" if jobOptions['applyFakeRateWeights'] == "disabled" else "enabled"
    jobOptions['histogramDir'] = getHistogramDir(
      jobOptions['hadTauSelection'], hadTau_frWeight, jobOptions['hadTauChargeSelection']
    )

    jobOptions['leptonFakeRateWeight.inputFileName'] = self.leptonFakeRateWeight_inputFile
    jobOptions['leptonFakeRateWeight.histogramName_e'] = self.leptonFakeRateWeight_histogramName_e
    jobOptions['leptonFakeRateWeight.histogramName_mu'] = self.leptonFakeRateWeight_histogramName_mu

    jobOptions['hadTauFakeRateWeight.inputFileName'] = self.hadTauFakeRateWeight_inputFile
    graphName = 'jetToTauFakeRate/%s/$etaBin/jetToTauFakeRate_mc_hadTaus_pt' % self.hadTau_selection_part2
    jobOptions['hadTauFakeRateWeight.lead.graphName'] = graphName
    jobOptions['hadTauFakeRateWeight.sublead.graphName'] = graphName
    fitFunctionName = 'jetToTauFakeRate/%s/$etaBin/fitFunction_data_div_mc_hadTaus_pt' % self.hadTau_selection_part2
    jobOptions['hadTauFakeRateWeight.lead.fitFunctionName'] = fitFunctionName
    jobOptions['hadTauFakeRateWeight.sublead.fitFunctionName'] = fitFunctionName
    if jobOptions['hadTauSelection'].find("mcClosure") != -1:
      jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = False
      jobOptions['hadTauFakeRateWeight.applyFitFunction_sublead'] = False
    if jobOptions['hadTauSelection'].find("Tight") != -1 and self.applyFakeRateWeights not in [ "3L", "2tau" ] and not self.isBDTtraining:
      jobOptions['hadTauFakeRateWeight.applyGraph_lead'] = False
      jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = True
      jobOptions['hadTauFakeRateWeight.applyGraph_sublead'] = False
      jobOptions['hadTauFakeRateWeight.applyFitFunction_sublead'] = True
      jobOptions['apply_hadTauFakeRateSF'] = True

    lines = super(analyzeConfig_1l_2tau, self).createCfg_analyze(jobOptions, sample_info)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def createCfg_makePlots_mcClosure(self, jobOptions):
    """Fills the template of python configuration file for making control plots

    Args:
      histogramFile: name of the input ROOT file
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.makePlots_mcClosure.outputFileName = cms.string('%s')" % jobOptions['outputFile'])
    lines.append("process.makePlots_mcClosure.processesBackground = cms.vstring(%s)" % self.make_plots_backgrounds)
    lines.append("process.makePlots_mcClosure.processSignal = cms.string('%s')" % self.make_plots_signal)
    lines.append("process.makePlots_mcClosure.categories = cms.VPSet(")
    lines.append("  cms.PSet(")
    lines.append("    signal = cms.string('%s')," % self.histogramDir_prep_dcard)
    lines.append("    sideband = cms.string('%s')," % self.histogramDir_prep_dcard.replace("Tight", "Fakeable_mcClosure_wFakeRateWeights"))
    lines.append("    label = cms.string('%s')" % self.channel)
    lines.append("  )")
    lines.append(")")
    create_cfg(self.cfgFile_make_plots_mcClosure, jobOptions['cfgFile_modified'], lines)

  def addToMakefile_backgrounds_from_data(self, lines_makefile):
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds", self.sbatchFile_addBackgrounds, self.jobOptions_addBackgrounds)
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds_sum", self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
    self.addToMakefile_hadd_stage1_5(lines_makefile)
    self.addToMakefile_addFakes(lines_makefile)

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for lepton_and_hadTau_selection in self.lepton_and_hadTau_selections:
        for lepton_and_hadTau_frWeight in self.lepton_and_hadTau_frWeights:
          if lepton_and_hadTau_frWeight == "enabled" and not lepton_and_hadTau_selection.startswith("Fakeable"):
            continue
          lepton_and_hadTau_selection_and_frWeight = get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight)
          for hadTau_charge_selection in self.hadTau_charge_selections:
            key_dir = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
            for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES, DKEY_SYNC ]:
              initDict(self.dirs, [ key_dir, dir_type ])
              if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
                  "_".join([ lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection ]), process_name)
              else:
                self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                  "_".join([ lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection ]), process_name)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT, DKEY_SYNC ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
        self.dirs[dir_type] = os.path.join(self.configDir, dir_type, self.channel)
      else:
        self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)
    ##print "self.dirs = ", self.dirs

    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        for dir_type in self.dirs[key].keys():
          create_if_not_exists(self.dirs[key][dir_type])
      else:
        create_if_not_exists(self.dirs[key])

    inputFileLists = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      logging.info("Checking input files for sample %s" % sample_info["process_name_specific"])
      inputFileLists[sample_name] = generateInputFileList(sample_info, self.max_files_per_job, self.check_input_files)

    for lepton_and_hadTau_selection in self.lepton_and_hadTau_selections:
      lepton_selection = lepton_and_hadTau_selection
      if self.applyFakeRateWeights == "2tau":
        lepton_selection = "Tight"
      hadTau_selection = "|".join([ lepton_and_hadTau_selection, self.hadTau_selection_part2 ])

      if lepton_and_hadTau_selection == "forBDTtraining":
        lepton_selection = "Tight"
        hadTau_selection = "Tight|%s" % self.hadTau_selection_relaxed

      for lepton_and_hadTau_frWeight in self.lepton_and_hadTau_frWeights:
        if lepton_and_hadTau_frWeight == "enabled" and not lepton_and_hadTau_selection.startswith("Fakeable"):
          continue
        if lepton_and_hadTau_frWeight == "disabled" and not lepton_and_hadTau_selection in [ "Tight", "forBDTtraining" ]:
          continue
        lepton_and_hadTau_selection_and_frWeight = get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight)

        for hadTau_charge_selection in self.hadTau_charge_selections:

          for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
              continue
            process_name = sample_info["process_name_specific"]
            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))

            sample_category = sample_info["sample_category"]
            is_mc = (sample_info["type"] == "mc")
            is_signal = (sample_category == "signal")

            for central_or_shift in self.central_or_shifts:

              inputFileList = inputFileLists[sample_name]
              for jobId in inputFileList.keys():
                if central_or_shift != "central":
                  isFR_shape_shift = False
                  for FR_shape_shift in [
                    "CMS_ttHl_FRe_shape",
                    "CMS_ttHl_FRm_shape",
                    "CMS_ttHl_FRjt_norm",
                    "CMS_ttHl_FRjt_shape" ]:
                    if central_or_shift.find(FR_shape_shift) != -1:
                      isFR_shape_shift = True
                  if not ((lepton_and_hadTau_selection == "Fakeable" and hadTau_charge_selection == "OS" and isFR_shape_shift) or
                          (lepton_and_hadTau_selection == "Tight"    and hadTau_charge_selection == "OS")):
                    continue
                  if not is_mc and not isFR_shape_shift:
                    continue
                if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
                  continue
                if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
                  continue
                if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
                  continue
                ##print "processing sample %s: jobId = %i, central_or_shift = '%s'" % (process_name, jobId, central_or_shift)

                # build config files for executing analysis code
                key_dir = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
                key_analyze_job = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection, central_or_shift, jobId)
                ntupleFiles = inputFileList[jobId]
                if len(ntupleFiles) == 0:
                  print "Warning: ntupleFiles['%s'] = %s --> skipping job !!" % (key_file, ntupleFiles)
                  continue

                syncOutput = ''
                syncTree = ''
                syncRequireGenMatching = False
                if self.do_sync:
                  if lepton_and_hadTau_selection_and_frWeight == 'Tight' and hadTau_charge_selection == 'OS':
                    syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s_SR.root' % self.channel)
                    syncTree   = 'syncTree_%s_SR' % self.channel.replace('_', '')
                    syncRequireGenMatching = True
                  elif lepton_and_hadTau_selection_and_frWeight == 'Fakeable_wFakeRateWeights' and hadTau_charge_selection == 'OS':
                    syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s_Fake.root' % self.channel)
                    syncTree   = 'syncTree_%s_Fake' % self.channel.replace('_', '')
                  else:
                    continue

                syncRLE = ''
                if self.do_sync and self.rle_select:
                  syncRLE = self.rle_select % syncTree
                  if not os.path.isfile(syncRLE):
                    logging.warning("Input RLE file for the sync is missing: %s; skipping the job" % syncRLE)
                    continue

                if syncOutput:
                  self.inputFiles_sync['sync'].append(syncOutput)

                cfg_key = getKey(
                  self.channel, process_name, lepton_and_hadTau_selection_and_frWeight,
                  hadTau_charge_selection, central_or_shift, jobId
                )
                cfgFile_modified_path = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_cfg.py" % cfg_key)
                logFile_path = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s.log" % cfg_key)
                rleOutputFile_path = os.path.join(self.dirs[key_dir][DKEY_RLES], "rle_%s.txt" % cfg_key) \
                                     if self.select_rle_output else ""
                histogramFile_path = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s.root" % key_analyze_job)
                applyFakeRateWeights = self.applyFakeRateWeights \
                  if self.isBDTtraining or not (lepton_selection == "Tight" and hadTau_selection.find("Tight") != -1) \
                  else "disabled"

                self.jobOptions_analyze[key_analyze_job] = {
                  'ntupleFiles'              : ntupleFiles,
                  'cfgFile_modified'         : cfgFile_modified_path,
                  'histogramFile'            : histogramFile_path,
                  'logFile'                  : logFile_path,
                  'selEventsFileName_output' : rleOutputFile_path,
                  'leptonSelection'          : lepton_selection,
                  'lep_mva_cut'              : self.lep_mva_cut,
                  'apply_leptonGenMatching'  : self.apply_leptonGenMatching,
                  'hadTauSelection'          : hadTau_selection,
                  'apply_hadTauGenMatching'  : self.apply_hadTauGenMatching,
                  'hadTauChargeSelection'    : hadTau_charge_selection,
                  'applyFakeRateWeights'     : applyFakeRateWeights,
                  'central_or_shift'         : central_or_shift,
                  'selectBDT'                : self.isBDTtraining,
                  'syncOutput'               : syncOutput,
                  'syncTree'                 : syncTree,
                  'syncRLE'                  : syncRLE,
                  'syncRequireGenMatching'   : syncRequireGenMatching,
                  'apply_hlt_filter'         : self.hlt_filter,
                  'useNonNominal'            : self.use_nonnominal,
                  'fillGenEvtHistograms'     : True,
                }
                self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)

                # initialize input and output file names for hadd_stage1
                key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
                if not key_hadd_stage1 in self.inputFiles_hadd_stage1:
                  self.inputFiles_hadd_stage1[key_hadd_stage1] = []
                self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
                self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s_%s_%s.root" % \
                    (self.channel, process_name, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))

            if self.isBDTtraining or self.do_sync:
              continue

            if is_mc:
              logging.info("Creating configuration files to run 'addBackgrounds' for sample %s" % process_name)

              sample_categories = [ sample_category ]
              if is_signal:
                sample_categories = [ "signal", "ttH", "ttH_htt", "ttH_hww", "ttH_hzz" ]
              for sample_category in sample_categories:
                # sum non-fake and fake contributions for each MC sample separately
                genMatch_categories = [ "nonfake", "conversions", "fake" ]

                for genMatch_category in genMatch_categories:
                  key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
                  key_addBackgrounds_job = None
                  processes_input = None
                  process_output = None
                  cfgFile_modified = None
                  outputFile = None
                  if genMatch_category == "nonfake":
                    # sum non-fake contributions for each MC sample separately
                    # input processes: TT1l0g0j&2t0e0m0j, TT1l0g0j&1t1e0m0j, TT1l0g0j&1t0e1m0j, TT1l0g0j&0t2e0m0j, TT1l0g0j&0t1e1m0j, TT1l0g0j&0t0e2m0j; ...
                    # output processes: TT; ...
                    if sample_category in [ "signal" ]:
                      lepton_and_hadTau_genMatches = []
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_nonfakes)
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_conversions)
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_fakes)
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in lepton_and_hadTau_genMatches ]
                    elif sample_category in [ "ttH" ]:
                      lepton_and_hadTau_genMatches = []
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_nonfakes)
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_conversions)
                      processes_input = []
                      processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in lepton_and_hadTau_genMatches ])
                      processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in lepton_and_hadTau_genMatches ])
                      processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in lepton_and_hadTau_genMatches ])
                    else:
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_nonfakes ]
                    process_output = sample_category
                    key_addBackgrounds_job = getKey(process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
                    cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_%s_%s_%s_%s_cfg.py" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))
                    outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_%s_%s_%s_%s.root" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))
                  if genMatch_category == "conversions":
                    # sum conversion background contributions for each MC sample separately
                    # input processes: TT2l1g0j,...
                    # output processes: TT_conversions; ...
                    if sample_category in [ "signal" ]:
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ]
                    elif sample_category in [ "ttH" ]:
                      processes_input = []
                      processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ])
                      processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ])
                      processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ])
                    else:
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ]
                    process_output = "%s_conversion" % sample_category
                    key_addBackgrounds_job = getKey(process_name, "%s_conversion" % sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
                    cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_conversions_%s_%s_%s_%s_cfg.py" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))
                    outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_conversions_%s_%s_%s_%s.root" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))
                  elif genMatch_category == "fake":
                    # sum fake background contributions for each MC sample separately
                    # input processes: TT1l0g0j&1t0e0m1j, TT1l0g0j&0t1e0m1j, TT1l0g0j&0t0e1m1j, TT1l0g0j&0t0e0m2j; ...
                    # output processes: TT_fake; ...
                    if sample_category in [ "signal" ]:
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ]
                    elif sample_category in [ "ttH" ]:
                      processes_input = []
                      processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ])
                      processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ])
                      processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ])
                    else:
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ]
                    process_output = "%s_fake" % sample_category
                    key_addBackgrounds_job = getKey(process_name, "%s_fake" % sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
                    cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_fakes_%s_%s_%s_%s_cfg.py" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))
                    outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_fakes_%s_%s_%s_%s.root" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))
                  if processes_input:
                    logging.info(" ...for genMatch option = '%s'" % genMatch_category)
                    self.jobOptions_addBackgrounds[key_addBackgrounds_job] = {
                      'inputFile' : self.outputFile_hadd_stage1[key_hadd_stage1],
                      'cfgFile_modified' : cfgFile_modified,
                      'outputFile' : outputFile,
                      'logFile' : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(cfgFile_modified).replace("_cfg.py", ".log")),
                      'categories' : [ getHistogramDir(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight, hadTau_charge_selection) ],
                      'processes_input' : processes_input,
                      'process_output' : process_output
                    }
                    self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds[key_addBackgrounds_job])

                    # initialize input and output file names for hadd_stage1_5
                    key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
                    if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
                      self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
                    self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.jobOptions_addBackgrounds[key_addBackgrounds_job]['outputFile'])
                    self.outputFile_hadd_stage1_5[key_hadd_stage1_5] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_5_%s_%s_%s.root" % \
                     (self.channel, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))

            if self.isBDTtraining or self.do_sync:
              continue

            # add output files of hadd_stage1 for data to list of input files for hadd_stage1_5
            if not is_mc:
              key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
              key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
              if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
                self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
              self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.outputFile_hadd_stage1[key_hadd_stage1])

          if self.isBDTtraining or self.do_sync:
            continue

          # sum fake background contributions for the total of all MC sample
          # input processes: TT1l0g0j&1t0e0m1j, TT1l0g0j&0t1e0m1j, TT1l0g0j&0t0e1m1j, TT1l0g0j&0t0e0m2j; ...
          # output process: fakes_mc
          key_addBackgrounds_job_fakes = getKey(lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection, "fakes")
          sample_categories = []
          sample_categories.extend(self.nonfake_backgrounds)
          sample_categories.extend([ "signal" ])
          processes_input = []
          for sample_category in sample_categories:
            processes_input.append("%s_fake" % sample_category)
          self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes] = {
            'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_fakes_mc_%s_%s_cfg.py" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)),
            'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_fakes_mc_%s_%s.root" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)),
            'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_%s_fakes_mc_%s_%s.log" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)),
            'categories' : [ getHistogramDir(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight, hadTau_charge_selection) ],
            'processes_input' : processes_input,
            'process_output' : "fakes_mc"
          }
          self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes])

          # sum conversion background contributions for the total of all MC sample
          # input processes: TT0l1g0j&2t0e0m0j, TT0l1g0j&2t0e0m0j, TT0l1g0j&1t1e0m0j, TT0l1g0j&1t0e1m0j; ...
          # output process: conversions
          key_addBackgrounds_job_conversions = getKey(lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection, "conversions")
          sample_categories = []
          sample_categories.extend(self.nonfake_backgrounds)
          sample_categories.extend([ "signal" ])
          processes_input = []
          for sample_category in sample_categories:
            processes_input.append("%s_conversion" % sample_category)
          self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions] = {
            'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_conversions_%s_%s_cfg.py" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)),
            'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_conversions_%s_%s.root" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)),
            'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_%s_conversions_%s_%s.log" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)),
            'categories' : [ getHistogramDir(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight, hadTau_charge_selection) ],
            'processes_input' : processes_input,
            'process_output' : "conversions"
          }
          self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions])

          # initialize input and output file names for hadd_stage2
          key_hadd_stage2 = getKey(lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
          if not key_hadd_stage2 in self.inputFiles_hadd_stage2:
            self.inputFiles_hadd_stage2[key_hadd_stage2] = []
          if lepton_and_hadTau_selection == "Tight":
            self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes]['outputFile'])
            self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions]['outputFile'])
          key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection)
          self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
          self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2_%s_%s_%s.root" % \
            (self.channel, lepton_and_hadTau_selection_and_frWeight, hadTau_charge_selection))

    if self.isBDTtraining or self.do_sync:
      if self.is_sbatch:
        logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
        self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
        if self.isBDTtraining:
          self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
        elif self.do_sync:
          self.createScript_sbatch_syncNtuple(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating Makefile")
      lines_makefile = []
      if self.isBDTtraining:
        self.addToMakefile_analyze(lines_makefile)
        self.addToMakefile_hadd_stage1(lines_makefile)
      elif self.do_sync:
        self.addToMakefile_syncNtuple(lines_makefile)
        outputFile_sync_path = os.path.join(self.outputDir, DKEY_SYNC, '%s.root' % self.channel)
        self.outputFile_sync['sync'] = outputFile_sync_path
        self.targets.append(outputFile_sync_path)
        self.addToMakefile_hadd_sync(lines_makefile)
      else:
        raise ValueError("Internal logic error")
      self.createMakefile(lines_makefile)
      logging.info("Done")
      return self.num_jobs

    logging.info("Creating configuration files to run 'addBackgroundFakes'")
    for hadTau_charge_selection in self.hadTau_charge_selections:
      key_addFakes_job = getKey("fakes_data", hadTau_charge_selection)
      key_hadd_stage1_5 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Fakeable", "enabled"), hadTau_charge_selection)
      category_sideband = None
      if self.applyFakeRateWeights == "3L":
        category_sideband = "1l_2tau_%s_Fakeable_wFakeRateWeights" % hadTau_charge_selection
      elif self.applyFakeRateWeights == "2tau":
        category_sideband = "1l_2tau_%s_Fakeable_wFakeRateWeights" % hadTau_charge_selection
      else:
        raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % applyFakeRateWeights)
      self.jobOptions_addFakes[key_addFakes_job] = {
        'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgroundLeptonFakes_%s_%s_cfg.py" % \
          (self.channel, hadTau_charge_selection)),
        'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgroundLeptonFakes_%s_%s.root" % \
          (self.channel, hadTau_charge_selection)),
        'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgroundLeptonFakes_%s_%s.log" % \
          (self.channel, hadTau_charge_selection)),
        'category_signal' : "1l_2tau_%s_Tight" % hadTau_charge_selection,
        'category_sideband' : category_sideband
      }
      self.createCfg_addFakes(self.jobOptions_addFakes[key_addFakes_job])
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), hadTau_charge_selection)
      self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])

    logging.info("Creating configuration files to run 'prepareDatacards'")
    for histogramToFit in self.histograms_to_fit:
      key_prep_dcard_job = getKey(histogramToFit)
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "OS")
      self.jobOptions_prep_dcard[key_prep_dcard_job] = {
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_%s_%s_cfg.py" % (self.channel, histogramToFit)),
        'datacardFile' : os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s_%s.root" % (self.channel, histogramToFit)),
        'histogramDir' : self.histogramDir_prep_dcard,
        'histogramToFit' : histogramToFit,
        'label' : None
      }
      self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])
      if "SS" in self.hadTau_charge_selections:
        key_prep_dcard_job = getKey(histogramToFit, "SS")
        key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "SS")
        self.jobOptions_prep_dcard[key_prep_dcard_job] = {
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_%s_SS_%s_cfg.py" % (self.channel, histogramToFit)),
          'datacardFile' : os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s_SS_%s.root" % (self.channel, histogramToFit)),
          'histogramDir' : self.histogramDir_prep_dcard_SS,
          'histogramToFit' : histogramToFit,
          'label' : 'SS'
        }
        self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

    logging.info("Creating configuration files to run 'makePlots'")
    key_makePlots_job = getKey("OS")
    key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "OS")
    self.jobOptions_make_plots[key_makePlots_job] = {
      'executable' : self.executable_make_plots,
      'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
      'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_%s_cfg.py" % self.channel),
      'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_%s.png" % self.channel),
      'histogramDir' : self.histogramDir_prep_dcard,
      'label' : None,
      'make_plots_backgrounds' : self.make_plots_backgrounds
    }
    self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
    if "SS" in self.hadTau_charge_selections:
      key_makePlots_job = getKey("SS")
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "SS")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_%s_SS_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_%s_SS.png" % self.channel),
        'histogramDir' : self.histogramDir_prep_dcard_SS,
        'label' : "SS",
        'make_plots_backgrounds' : self.make_plots_backgrounds
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
    if "Fakeable_mcClosure" in self.lepton_and_hadTau_selections:
      key_makePlots_job = getKey("OS")
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "OS")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots_mcClosure,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_mcClosure_%s_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_mcClosure_%s.png" % self.channel)
      }
      self.createCfg_makePlots_mcClosure(self.jobOptions_make_plots[key_makePlots_job])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addBackgrounds)
      self.sbatchFile_addBackgrounds = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addBackgrounds, self.sbatchFile_addBackgrounds, self.jobOptions_addBackgrounds)
      self.sbatchFile_addBackgrounds_sum = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_sum_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addBackgrounds, self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addFakes)
      self.sbatchFile_addFakes = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addFakes_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addFakes, self.sbatchFile_addFakes, self.jobOptions_addFakes)

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done")

    return self.num_jobs
