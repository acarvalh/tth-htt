import FWCore.ParameterSet.Config as cms
import os
from tthAnalysis.HiggsToTauTau.recommendedMEtFilters_cfi import recommendedMEtFilters

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(''),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_hadTopTagger.root')
)

process.analyze_hadTopTagger = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string('ttH'),

    histogramDir = cms.string('hadTopTagger_gen'),

    era = cms.string('2017'),

    # Xanda:  entries for the triggers:
    # https://github.com/HEP-KBFI/tth-htt/blob/master/python/analysisSettings.py
    triggers_1e = cms.vstring('HLT_Ele32_WPTight_Gsf', 'HLT_Ele35_WPTight_Gsf'),
    use_triggers_1e = cms.bool(True),
    triggers_2e = cms.vstring('HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL', 'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ'),
    use_triggers_2e = cms.bool(True),
    triggers_3e = cms.vstring('HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL'),
    use_triggers_3e = cms.bool(True),

    triggers_1mu = cms.vstring('HLT_IsoMu24', 'HLT_IsoMu27'),
    use_triggers_1mu = cms.bool(True),
    triggers_2mu = cms.vstring('HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ', 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8'),
    use_triggers_2mu = cms.bool(True),
    triggers_3mu = cms.vstring('HLT_TripleMu_12_10_5'),
    use_triggers_3mu = cms.bool(True),

    triggers_1e1mu = cms.vstring('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL', 'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
          'HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',),
    use_triggers_1e1mu = cms.bool(True),
    triggers_1e1tau = cms.vstring('HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1'),
    use_triggers_1e1tau = cms.bool(True),
    triggers_1mu1tau = cms.vstring('HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1'),
    use_triggers_1mu1tau = cms.bool(True),

    triggers_2e1mu = cms.vstring('HLT_Mu8_DiEle12_CaloIdL_TrackIdL'),
    use_triggers_2e1mu = cms.bool(True),
    triggers_1e2mu = cms.vstring('HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ'),
    use_triggers_1e2mu = cms.bool(True),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),

    apply_offline_e_trigger_cuts_3e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_3mu = cms.bool(True),

    leptonFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_lep_ttH_mva_2016_data.root"),
        histogramName_e = cms.string("FR_mva075_el_data_comb"),
        histogramName_mu = cms.string("FR_mva075_mu_data_comb"),
    ),

    hadTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root"),
        lead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True),
        ),
        sublead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True),
        ),
    ),

    leptonSelection = cms.string('Tight'),
    apply_leptonGenMatching = cms.bool(False),
    leptonChargeSelection = cms.string('SS'),

    hadTauSelection = cms.string('Tight|dR03mvaMedium'),
    apply_hadTauGenMatching = cms.bool(False),

    chargeSumSelection = cms.string('OS'),

    use_HIP_mitigation_mediumMuonId = cms.bool(False),

    apply_lepton_and_hadTauCharge_cut = cms.bool(True),

    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_genWeight = cms.bool(True),
    apply_trigger_bits = cms.bool(True),
    apply_met_filters = cms.bool(True),
    cfgMEtFilter = recommendedMEtFilters,

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('Tau'),
    branchName_jets = cms.string('Jet'),
    branchName_jetsHTTv2 = cms.string('HTTV2'),
    branchName_subjetsHTTv2 = cms.string('HTTV2Subjets'),
    branchName_jetsAK12 = cms.string('FatJetAK12'),
    branchName_subjetsAK12 = cms.string('SubJetAK12'),
    branchName_jetsAK8 = cms.string('FatJet'),
    branchName_subjetsAK8 = cms.string('SubJet'),
    branchName_met = cms.string('MET'),

    branchName_genLeptons = cms.string('GenLep'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genJets = cms.string('GenJet'),
    redoGenMatching = cms.bool(True),

    branchName_genTopQuarks = cms.string('GenTop'),
    branchName_genBJets = cms.string('GenBQuarkFromTop'),
    branchName_genWBosons = cms.string('GenVbosons'),
    branchName_genWJets = cms.string('GenWZQuark'),
    branchName_genQuarkFromTop = cms.string('GenQuarkFromTop'),

    selEventsFileName_input = cms.string(''),
    ##selEventsFileName_input = cms.string('/home/veelken/CMSSW_9_4_4/src/tthAnalysis/HiggsToTauTau/test/selEvents_hadTopTagger_gen.txt'),
    ##selEventsFileName_output = cms.string('')
    selEventsFileName_output = cms.string('/home/acaan/VHbbNtuples_8_0_x/CMSSW_9_4_6_patch1/src/tthAnalysis/HiggsToTauTau/selEvents_hadTopTagger.txt'),
    selEventsFileName_output_1l_2tau = cms.string('/home/acaan/VHbbNtuples_8_0_x/CMSSW_9_4_6_patch1/src/tthAnalysis/HiggsToTauTau/selEvents_hadTopTagger_1l_2tau.txt'),
    selEventsFileName_output_2lss_1tau = cms.string('/home/acaan/VHbbNtuples_8_0_x/CMSSW_9_4_6_patch1/src/tthAnalysis/HiggsToTauTau/selEvents_hadTopTagger_2lss_1tau.txt'),
    selEventsFileName_output_2los_1tau = cms.string('/home/acaan/VHbbNtuples_8_0_x/CMSSW_9_4_6_patch1/src/tthAnalysis/HiggsToTauTau/selEvents_hadTopTagger_2los_1tau.txt'),
    selEventsFileName_output_2lss = cms.string('/home/acaan/VHbbNtuples_8_0_x/CMSSW_9_4_6_patch1/src/tthAnalysis/HiggsToTauTau/selEvents_hadTopTagger_2lss.txt'),
    selEventsFileName_output_3l = cms.string('/home/acaan/VHbbNtuples_8_0_x/CMSSW_9_4_6_patch1/src/tthAnalysis/HiggsToTauTau/selEvents_hadTopTagger_3l.txt'),
    selEventsFileName_output_summary = cms.string('/home/acaan/VHbbNtuples_8_0_x/CMSSW_9_4_6_patch1/src/tthAnalysis/HiggsToTauTau/selEvents_hadTopTagger_summary.txt'),

    selectBDT = cms.bool(True),
    isDEBUG = cms.bool(False),
    hasLHE = cms.bool(True),
)
