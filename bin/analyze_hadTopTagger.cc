// latest

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include <TChain.h> // TChain
#include <TTree.h> // TTree
#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TMatrixD.h> // TMatrixD
#include <TError.h> // gErrorAbortLevel, kError
#include <TMath.h> // TMath::Pi()
#include <TLorentzVector.h>

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h" // RecoJetAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h" // RecoJetAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderHTTv2.h" // RecoJetReaderHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK12.h" // RecoJetReaderAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h" // RecoJetReaderAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorHTTv2.h" // RecoJetSelectorHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK12.h" // RecoJetSelectorAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK8.h" // RecoJetSelectorAK8
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerHTTv2.h" // JetHistManagerHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerAK12.h" // JetHistManagerAK12
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow2d
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTaggerFill.h" // HadTopTaggerFill

#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <math.h> // acos, sqrt
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <numeric> // iota

#include <iostream>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

enum { kGen_bWj1Wj2, kGen_bWj1, kGen_bWj2, kGen_Wj1Wj2, kGen_b, kGen_Wj1, kGen_Wj2, kGen_none };
bool inAK12 = true;
bool loopB = true;
bool cleanLep = false;
size_t cutJetCombo = 20;

const int hadTauSelection_antiElectron_lead = -1; // not applied
const int hadTauSelection_antiMuon_lead = -1; // not applied
const int hadTauSelection_antiElectron_sublead = -1; // not applied
const int hadTauSelection_antiMuon_sublead = -1; // not applied

double square(double x)
{
  return x*x;
}

int main(int argc, char* argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_hadTopTagger>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_hadTopTagger");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_hadTopTagger")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_hadTopTagger");
  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;
  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2017" ) era = kEra_2017;
  else throw cms::Exception("analyze_hadTopTagger")
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::cout << "triggerNames_1e " ;
  for (auto i: triggerNames_1e) std::cout << i << " ";
  std::cout << std::endl;
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e, "triggers_2e");
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggerNames_1e1tau = cfg_analyze.getParameter<vstring>("triggers_1e1tau");
  std::vector<hltPath*> triggers_1e1tau = create_hltPaths(triggerNames_1e1tau);
  bool use_triggers_1e1tau = cfg_analyze.getParameter<bool>("use_triggers_1e1tau");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::cout << "triggerNames_1mu " ;
  for (auto i: triggerNames_1mu) std::cout << i << " ";
  std::cout << std::endl;
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu, "triggers_2mu");
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  vstring triggerNames_1mu1tau = cfg_analyze.getParameter<vstring>("triggers_1mu1tau");
  std::vector<hltPath*> triggers_1mu1tau = create_hltPaths(triggerNames_1mu1tau);
  std::cout << "triggers_1mu1tau " ;
  for (auto i: triggerNames_1mu1tau) std::cout << i << " ";
  std::cout << std::endl;
  bool use_triggers_1mu1tau = cfg_analyze.getParameter<bool>("use_triggers_1mu1tau");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  std::cout << "triggers_1e1mu " ;
  for (auto i: triggerNames_1e1mu) std::cout << i << " ";
  std::cout << std::endl;
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");
  // triple lepton triggers
  vstring triggerNames_3e = cfg_analyze.getParameter<vstring>("triggers_3e");
  std::vector<hltPath*> triggers_3e = create_hltPaths(triggerNames_3e, "triggers_3e");
  bool use_triggers_3e = cfg_analyze.getParameter<bool>("use_triggers_3e");
  vstring triggerNames_2e1mu = cfg_analyze.getParameter<vstring>("triggers_2e1mu");
  std::vector<hltPath*> triggers_2e1mu = create_hltPaths(triggerNames_2e1mu, "triggers_2e1mu");
  bool use_triggers_2e1mu = cfg_analyze.getParameter<bool>("use_triggers_2e1mu");
  vstring triggerNames_1e2mu = cfg_analyze.getParameter<vstring>("triggers_1e2mu");
  std::vector<hltPath*> triggers_1e2mu = create_hltPaths(triggerNames_1e2mu, "triggers_1e2mu");
  bool use_triggers_1e2mu = cfg_analyze.getParameter<bool>("use_triggers_1e2mu");
  vstring triggerNames_3mu = cfg_analyze.getParameter<vstring>("triggers_3mu");
  std::vector<hltPath*> triggers_3mu = create_hltPaths(triggerNames_3mu, "triggers_3mu");
  bool use_triggers_3mu = cfg_analyze.getParameter<bool>("use_triggers_3mu");

  /*
  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1e1tau = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1tau");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_1mu1tau = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu1tau");

  bool apply_offline_e_trigger_cuts_3e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3e");
  bool apply_offline_e_trigger_cuts_2e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e1mu");
  bool apply_offline_e_trigger_cuts_1e2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e2mu");
  bool apply_offline_e_trigger_cuts_3mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3mu");
  */

  // read leptons and hadronic taus to do cleaning
  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection").data();
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"                                                      ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" || leptonSelection_string == "Fakeable_mcClosure" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"                                                      ) leptonSelection = kTight;
  else throw cms::Exception("analyze_HTT")
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions = getLeptonGenMatch_definitions_1lepton(apply_leptonGenMatching);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  int hadTauSelection = -1;
  if      ( hadTauSelection_part1 == "Loose"                                                     ) hadTauSelection = kLoose;
  else if ( hadTauSelection_part1 == "Fakeable" || hadTauSelection_part1 == "Fakeable_mcClosure" ) hadTauSelection = kFakeable;
  else if ( hadTauSelection_part1 == "Tight"                                                     ) hadTauSelection = kTight;
  else throw cms::Exception("analyze_HTT")
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_2tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  //enum { kOS, kSS };
  //std::string hadTauChargeSelection_string = cfg_analyze.getParameter<std::string>("hadTauChargeSelection");
  //int hadTauChargeSelection = -1;
  //if      ( hadTauChargeSelection_string == "OS" ) hadTauChargeSelection = kOS;
  //else if ( hadTauChargeSelection_string == "SS" ) hadTauChargeSelection = kSS;
  //else throw cms::Exception("analyze_1l_2tau")
  //  << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool isMC_tH = ( process_string == "tH" ) ? true : false;
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits");
  bool apply_met_filters = cfg_analyze.getParameter<bool>("apply_met_filters");
  edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);
  //bool apply_hlt_filter = cfg_analyze.getParameter<bool>("apply_hlt_filter");

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;
  const int jetPt_option     = getJet_option       (central_or_shift, isMC);
  const int jetBtagSF_option = getBTagWeight_option(central_or_shift, isMC);
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift, isMC);
  const int jetToTauFakeRate_option    = getJetToTauFR_option   (central_or_shift, isMC);
  const int met_option   = getMET_option(central_or_shift, isMC);

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
  leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
  cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight, jetToTauFakeRate_option);

  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_jetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_jetsHTTv2");
  std::string branchName_subjetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_subjetsHTTv2");
  std::string branchName_jetsAK12 = cfg_analyze.getParameter<std::string>("branchName_jetsAK12");
  std::string branchName_subjetsAK12 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK12");
  std::string branchName_jetsAK8 = cfg_analyze.getParameter<std::string>("branchName_jetsAK8");
  std::string branchName_subjetsAK8 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK8");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");
  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");
  std::string branchName_genQuarkFromTop = cfg_analyze.getParameter<std::string>("branchName_genQuarkFromTop");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");

  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::string selEventsFileName_output_1l_2tau = cfg_analyze.getParameter<std::string>("selEventsFileName_output_1l_2tau");
  std::string selEventsFileName_output_2lss_1tau = cfg_analyze.getParameter<std::string>("selEventsFileName_output_2lss_1tau");
  std::string selEventsFileName_output_2los_1tau = cfg_analyze.getParameter<std::string>("selEventsFileName_output_2los_1tau");
  std::string selEventsFileName_output_2lss = cfg_analyze.getParameter<std::string>("selEventsFileName_output_2lss");
  std::string selEventsFileName_output_3l = cfg_analyze.getParameter<std::string>("selEventsFileName_output_3l");
  std::string selEventsFileName_output_summary = cfg_analyze.getParameter<std::string>("selEventsFileName_output_summary");

  fwlite::InputSource inputFiles(cfg);
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);
  const int hadTauPt_option            = getHadTauPt_option     (central_or_shift, isMC);

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron_lead", hadTauSelection_antiElectron_lead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon_lead", hadTauSelection_antiMuon_lead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron_sublead", hadTauSelection_antiElectron_sublead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon_sublead", hadTauSelection_antiMuon_sublead);

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  std::cout << "Here before RecoMuonReader" << std::endl;
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, isDEBUG);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  electronReader->readUncorrected(false); // it is always MC
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.05, isDEBUG);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);
  // assume apply_offline_e_trigger_cuts* alwyas true
  fakeableElectronSelector.disable_offline_e_trigger_cuts();
  tightElectronSelector.disable_offline_e_trigger_cuts();

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector.set(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoHadTauCollectionSelectorTight looseHadTauSelector(era);
  looseHadTauSelector.set("dR03mvaLoose");
  looseHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  looseHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  tightHadTauSelector.set("dR03mvaMedium");
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  //RecoHadTauSelectorTight looseHadTauFilter(era);
  //looseHadTauFilter.set("dR03mvaLoose");
  //looseHadTauFilter.set_min_antiElectron(hadTauSelection_antiElectron);
  //looseHadTauFilter.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoHadTauSelectorTight tightHadTauFilter(era);
  tightHadTauFilter.set("dR03mvaMedium");
  tightHadTauFilter.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauFilter.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);
  RecoJetCollectionCleaner jetCleaner(0.6, isDEBUG); //to clean against AK12
  RecoJetCollectionCleaner jetCleanerLep(0.2, isDEBUG); //to clean against leptons and hadronic taus

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters);
  inputTree -> registerReader(metFilterReader);

  /*
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    if ( ! readGenObjects ) {
      if ( branchName_genLeptons != "" ) {
        genLeptonReader = new GenLeptonReader(branchName_genLeptons);
        inputTree -> registerReader(genLeptonReader);
      }
      if ( branchName_genHadTaus != "" ) {
        genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
        inputTree -> registerReader(genHadTauReader);
      }
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree -> registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree -> registerReader(lheInfoReader);
  }
  */


  RecoJetReaderHTTv2* jetReaderHTTv2 = new RecoJetReaderHTTv2(era, branchName_jetsHTTv2, branchName_subjetsHTTv2);
  inputTree -> registerReader(jetReaderHTTv2);
  RecoJetCollectionSelectorHTTv2 jetSelectorHTTv2(era);
  RecoJetHTTv2CollectionCleaner jetCleanerHTTv2(0.75, isDEBUG); //to clean against leptons and hadronic taus

  RecoJetReaderAK12* jetReaderAK12 = new RecoJetReaderAK12(era, branchName_jetsAK12, branchName_subjetsAK12);
  inputTree -> registerReader(jetReaderAK12);
  RecoJetCollectionSelectorAK12 jetSelectorAK12(era);
  RecoJetAK12CollectionCleaner jetCleanerAK12(0.6, isDEBUG); //to clean against leptons and hadronic taus

  RecoJetReaderAK8* jetReaderAK8 = new RecoJetReaderAK8(era, branchName_jetsAK8, branchName_subjetsAK8);
  inputTree -> registerReader(jetReaderAK8);
  RecoJetCollectionSelectorAK8 jetSelectorAK8(era);
  RecoJetAK8CollectionCleaner jetCleanerAK8(0.4, isDEBUG); //to clean against leptons and hadronic taus

//--- declare generator level information
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree -> registerReader(genJetReader);
      }
    //}
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree -> registerReader(lheInfoReader);
  }

  GenParticleReader* genTopQuarkReader = new GenParticleReader(branchName_genTopQuarks);
  GenParticleReader* genBJetReader = new GenParticleReader(branchName_genBJets);
  GenParticleReader* genWBosonReader = new GenParticleReader(branchName_genWBosons);
  GenParticleReader* genWJetReader = new GenParticleReader(branchName_genWJets);
  GenParticleReader* genQuarkFromTopReader = new GenParticleReader(branchName_genQuarkFromTop);

  if ( isMC ) {
    inputTree->registerReader(genTopQuarkReader);
    inputTree->registerReader(genBJetReader);
    inputTree->registerReader(genWBosonReader);
    inputTree->registerReader(genWJetReader);
    inputTree->registerReader(genQuarkFromTopReader);
  }

  HadTopTaggerFill* hadTopTaggerFill = new HadTopTaggerFill();

  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
       makeHistManager_cfg(process_string, Form("%s/evtntuple", histogramDir.data()), "central")
       );
    bdt_filler->register_variable<float_type>(
      ///* // computed by (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2);
      "m_bWj1Wj2", "m_Wj1Wj2", "m_bWj1", "m_bWj2",
      //"m_Wj1Wj2_div_m_bWj1Wj2",
      "pT_b", //"eta_b", //"phi_b", "mass_b",
      "kinFit_pT_b", //"kinFit_eta_b", //"kinFit_phi_b", "kinFit_mass_b",
      "pT_Wj1", //"eta_Wj1", //"phi_Wj1", "mass_Wj1",
      "kinFit_pT_Wj1", //"kinFit_eta_Wj1", //"kinFit_phi_Wj1", "kinFit_mass_Wj1",
      "pT_Wj2", //"eta_Wj2", //"phi_Wj2", "mass_Wj2",
      "kinFit_pT_Wj2", //"kinFit_eta_Wj2", //"kinFit_phi_Wj2", "kinFit_mass_Wj2",
      //"cosTheta_leadWj_restTop","cosTheta_subleadWj_restTop",
      //"cosTheta_Kin_leadWj_restTop","cosTheta_Kin_subleadWj_restTop",
      //"cosTheta_leadEWj_restTop","cosTheta_subleadEWj_restTop",
      //"cosTheta_Kin_leadEWj_restTop","cosTheta_Kin_subleadEWj_restTop",
      "cosThetaW_rest","cosThetaKinW_rest", //"cosThetaW_lab","cosThetaKinW_lab",
      //"cosThetab_rest","cosThetaKinb_rest", //"cosThetab_lab","cosThetaKinb_lab",
      //"Dphi_Wj1_Wj2_lab","Dphi_KinWj1_KinWj2_lab",
      "Dphi_Wb_rest", //"Dphi_KinWb_rest","Dphi_Wb_lab","Dphi_KinWb_lab",
      "cosThetaWj1_restW", "cosThetaKinWj_restW",
      "dR_bWj1", "dR_bWj2", "dR_Wj1Wj2", "dR_bW",
      "statusKinFit", "nllKinFit", "alphaKinFit", //"logPKinFit", "logPErrKinFit",
      "pT_bWj1Wj2", "pT_Wj1Wj2", "pT_Wj1Wj2_kin",
      //*/
      "tau32Top", "massTop",
      "tau21W", "massW_SD",
      "genFatPtAll", "genFatEtaAll",
      "drT_gen", "drB_gen", "drW_gen", "drWj1_gen", "drWj2_gen",
      "etaB_gen",  "etaWj1_gen", "etaWj2_gen",
      "ptB_gen",  "ptWj1_gen", "ptWj2_gen",
      "dr_b_wj1", "dr_b_wj2", "dr_wj1_wj2",
      "dr_b_wj1_gen", "dr_b_wj2_gen", "dr_wj1_wj2_gen", "drT_genTriplet", "drT_genJ_max",
      "btagDisc", "qg_Wj1", "qg_Wj2",
      "HTTv2_area", "HTTv2_Ropt", "HTTv2_RoptCalc",
      "genTopMassFromW", "genTopMassFromWj", "genWMassFromWj",
      "genAntiTopMassFromW", "genAntiTopMassFromWj", "genAntiWMassFromWj",
      "genWMass", "genAntiWMass","genWeight",
      //
      "weight_fakeRate_3L", "weight_fakeRate_4L", "weight_fakeRate_2L"
    );


    bdt_filler->register_variable<int_type>(
      "typeTop", "collectionSize", "bjet_tag_position", "bWj1Wj2_isGenMatched", "counter",
      "fatjet_isGenMatched", "b_isGenMatched", "Wj1_isGenMatched", "Wj2_isGenMatched",
      "passJetSel","passJetMassSel",
      "passHadGenHadW",
      "pass_3l", "pass_2lss", "pass_1l_2tau", "pass_2lss_1tau", "pass_2los_1tau"
      //"b_isGenMatched", "Wj1_isGenMatched", "Wj2_isGenMatched",
      //"bWj1Wj2_isGenMatched"
    );
	//bdt_filler->register_variable<int_type>("mvaOutput_hadTopTagger");
    bdt_filler->bookTree(fs);
	}

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;
  std::ostream* selEventsFile_1l_2tau = ( selEventsFileName_output_1l_2tau != "" ) ? new std::ofstream(selEventsFileName_output_1l_2tau.data(), std::ios::out) : 0;
  std::ostream* selEventsFile_2lss_1tau = ( selEventsFileName_output_2lss_1tau != "" ) ? new std::ofstream(selEventsFileName_output_2lss_1tau.data(), std::ios::out) : 0;
  std::ostream* selEventsFile_2los_1tau = ( selEventsFileName_output_2los_1tau != "" ) ? new std::ofstream(selEventsFileName_output_2los_1tau.data(), std::ios::out) : 0;
  std::ostream* selEventsFile_2lss = ( selEventsFileName_output_2lss != "" ) ? new std::ofstream(selEventsFileName_output_2lss.data(), std::ios::out) : 0;
  std::ostream* selEventsFile_3l = ( selEventsFileName_output_3l != "" ) ? new std::ofstream(selEventsFileName_output_3l.data(), std::ios::out) : 0;

  int countFatTop = 0;
  int countFatTopPt200 = 0;
  int countFatTopbmatch = 0;
  int countFatTopWj1match = 0;
  int countFatTopWj2match = 0;
  int countFatW = 0;
  int countFatWjets = 0;
  int countFatWpt130 = 0;

  int countpassJetSel = 0;

  int countFatAK8 = 0;
  int countFatAK12 = 0;
  int countResolved = 0;
  int hadtruth1 = 0; // counter for diagnosis
  int hadtruth2 = 0; // counter for diagnosis
  int hadtruth3 = 0; // counter for diagnosis
  int ca1_cat2 = 0;
  int cat2_cat3 = 0;
  int cat3_cat1 = 0 ;
  int cat3_cat2_cat1 = 0;

  int count_pass_3l = 0;
  int count_pass_2lss = 0;
  int count_pass_1l_2tau = 0;
  int count_pass_2lss_1tau = 0;
  int count_pass_2los_1tau = 0;

  int pass_3l_0 = 0;
  int pass_3l_1 = 0;
  int pass_3l_2 = 0;
  int pass_3l_3 = 0;
  int pass_3l_4 = 0;
  int pass_3l_5 = 0;
  int pass_3l_6 = 0;
  int pass_3l_7 = 0;

  std::ostream* selEventsFile_summary = ( selEventsFileName_output_summary != "" ) ? new std::ofstream(selEventsFileName_output_summary.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output_summary = " << selEventsFileName_output_summary << std::endl;

  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    //if (countFatTop > 50) continue;
    if ( isDEBUG ) {
      std::cout << "processing run = " << eventInfo.run << ", ls = " << eventInfo.lumi << ", event = " << eventInfo.event << std::endl;
    }

    if(inputTree -> canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1)
                << " (" << eventInfo
                << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    //if (analyzedEntries > 100) break;
    std::cout << "processing entry  = " << analyzedEntries << std::endl;
    histogram_analyzedEntries->Fill(0.);

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    //--- build collections of electrons, muons and hadronic taus;
    //    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons, isHigherConePt);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons, isHigherConePt);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons, isHigherConePt);
    std::vector<const RecoMuon*> selMuons;
    if      ( leptonSelection == kLoose    ) selMuons = preselMuons;
    else if ( leptonSelection == kFakeable ) selMuons = fakeableMuons;
    else if ( leptonSelection == kTight    ) selMuons = tightMuons;
    else assert(0);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons, isHigherConePt);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons, isHigherConePt);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons, isHigherConePt);
    std::vector<const RecoElectron*> selElectrons;
    if      ( leptonSelection == kLoose    ) selElectrons = preselElectrons;
    else if ( leptonSelection == kFakeable ) selElectrons = fakeableElectrons;
    else if ( leptonSelection == kTight    ) selElectrons = tightElectrons;
    else assert(0);

    std::vector<const RecoLepton*> preselLeptonsFull = mergeLeptonCollections(preselElectrons, preselMuons, isHigherConePt);
    std::vector<const RecoLepton*> fakeableLeptonsFull = mergeLeptonCollections(fakeableElectrons, fakeableMuons, isHigherConePt);
    std::vector<const RecoLepton*> tightLeptonsFull = mergeLeptonCollections(tightElectrons, tightMuons, isHigherConePt);

    std::vector<const RecoLepton*> preselLeptons = pickFirstNobjects(preselLeptonsFull, 3);
    std::vector<const RecoLepton*> fakeableLeptons = pickFirstNobjects(fakeableLeptonsFull, 3);
    std::vector<const RecoLepton*> tightLeptons = getIntersection(fakeableLeptons, tightLeptonsFull, isHigherConePt);
    std::vector<const RecoLepton*> selLeptons = selectObjects(leptonSelection, preselLeptons, fakeableLeptons, tightLeptons);

    bool passesTight_lepton_lead = false;
    if (selLeptons.size() > 0) passesTight_lepton_lead = isMatched(*selLeptons[0], tightElectrons) || isMatched(*selLeptons[0], tightMuons);
    bool passesTight_lepton_sublead = false;
    if (selLeptons.size() > 1) passesTight_lepton_sublead = isMatched(*selLeptons[1], tightElectrons) || isMatched(*selLeptons[1], tightMuons);

    // Xanda: I am not sure we need this in this code on the HTT
    double prob_fake_lepton_lead = 1.;
    double prob_fake_lepton_sublead = 1.;
    if(leptonFakeRateInterface) {
      if (selLeptons.size() > 0) {
        if      ( std::abs(selLeptons[0]->pdgId()) == 11 )
          prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(selLeptons[0]->cone_pt(), selLeptons[0]->absEta());
        else if ( std::abs(selLeptons[0]->pdgId()) == 13 )
          prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(selLeptons[0]->cone_pt(), selLeptons[0]->absEta());
        else assert(0);
      }
      if (selLeptons.size() > 1) {
        if      ( std::abs(selLeptons[1]->pdgId()) == 11 )
          {prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(selLeptons[1]->cone_pt(), selLeptons[1]->absEta());}
        else if ( std::abs(selLeptons[1]->pdgId()) == 13 )
          {prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(selLeptons[1]->cone_pt(), selLeptons[1]->absEta());}
        else assert(0);
      }
    }

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTausFull = preselHadTauSelector(cleanedHadTaus, isHigherPt);
    std::vector<const RecoHadTau*> fakeableHadTausFull = fakeableHadTauSelector(preselHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> tightHadTausFull = tightHadTauSelector(fakeableHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> looseHadTausFull = looseHadTauSelector(fakeableHadTausFull, isHigherPt);

    std::vector<const RecoHadTau*> preselHadTaus = pickFirstNobjects(preselHadTausFull, 2);
    std::vector<const RecoHadTau*> fakeableHadTaus = pickFirstNobjects(fakeableHadTausFull, 2);
    std::vector<const RecoHadTau*> tightHadTaus = getIntersection(fakeableHadTaus, tightHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> looseHadTaus = getIntersection(fakeableHadTaus, looseHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> selHadTaus = selectObjects(hadTauSelection, preselHadTaus, fakeableHadTaus, tightHadTaus);

    bool passesTight_hadTau_lead = false;
    if ( selHadTaus.size() > 0) passesTight_hadTau_lead = isMatched(*selHadTaus[0], tightHadTaus);
    bool passesTight_hadTau_sublead = false;
    if ( selHadTaus.size() > 1) passesTight_hadTau_sublead = isMatched(*selHadTaus[1], tightHadTaus);

    double prob_fake_hadTau_lead = 1.;
    double prob_fake_hadTau_sublead = 1.;
    if(jetToTauFakeRateInterface) {
    if ( selHadTaus.size() > 0) prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTaus[0]->pt(), selHadTaus[0]->absEta());
    if ( selHadTaus.size() > 1) prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTaus[1]->pt(), selHadTaus[1]->absEta());
    }

    //std::cout << "before load jets"  << std::endl;
//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> selJets;
    if (cleanLep && (fakeableMuons.size() + fakeableElectrons.size() + preselHadTaus.size()) > 0) {
      std::vector<const RecoJet*> cleanedJetsAK4 = jetCleanerLep(jet_ptrs, fakeableMuons, fakeableElectrons, preselHadTaus);
      selJets = jetSelector(cleanedJetsAK4, isHigherPt);
    } else selJets = jetSelector(jet_ptrs, isHigherPt);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(selJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(selJets);
//--- build collections of jets reconstructed by hep-top-tagger (HTTv2) algorithm
    std::vector<RecoJetHTTv2> jetsHTTv2 = jetReaderHTTv2->read();
    std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2raw = convert_to_ptrs(jetsHTTv2);
    std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2;
    if (cleanLep && (fakeableMuons.size() + fakeableElectrons.size() + preselHadTaus.size()) > 0) {
      std::vector<const RecoJetHTTv2*> cleanedJetsHTTv2 = jetCleanerHTTv2(jet_ptrsHTTv2raw, fakeableMuons, fakeableElectrons, preselHadTaus);
      jet_ptrsHTTv2 =  jetSelectorHTTv2(cleanedJetsHTTv2, isHigherPt);
    } else jet_ptrsHTTv2 =  jetSelectorHTTv2(jet_ptrsHTTv2raw, isHigherPt);
    //std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2 = jetSelectorHTTv2(jet_ptrsHTTv2raw, isHigherPt);
//--- build collections of jets reconstructed by anti-kT algorithm with dR=1.2 (AK12)
    std::vector<RecoJetAK12> jetsAK12 = jetReaderAK12->read();
    std::vector<const RecoJetAK12*> jet_ptrsAK12raw = convert_to_ptrs(jetsAK12);
    std::vector<const RecoJetAK12*> jet_ptrsAK12;
    if (cleanLep && (fakeableMuons.size() + fakeableElectrons.size() + preselHadTaus.size()) > 0) {
    std::vector<const RecoJetAK12*> cleanedJetsAK12 = jetCleanerAK12(jet_ptrsAK12raw, fakeableMuons, fakeableElectrons, preselHadTaus);
    jet_ptrsAK12 = jetSelectorAK12(cleanedJetsAK12, isHigherPt);
    } else jet_ptrsAK12 = jetSelectorAK12(jet_ptrsAK12raw, isHigherPt);
//--- build collections of jets reconstructed by anti-kT algorithm with dR=0.8 (AK8)
    std::vector<RecoJetAK8> jetsAK8 = jetReaderAK8->read();
    std::vector<const RecoJetAK8*> jet_ptrsAK8raw = convert_to_ptrs(jetsAK8);
    std::vector<const RecoJetAK8*> jet_ptrsAK8;
    if (cleanLep && (fakeableMuons.size() + fakeableElectrons.size() + preselHadTaus.size()) > 0) {
      std::vector<const RecoJetAK8*> cleanedJetsAK8 = jetCleanerAK8(jet_ptrsAK8raw, fakeableMuons, fakeableElectrons, preselHadTaus);
      jet_ptrsAK8 = jetSelectorAK8(cleanedJetsAK8, isHigherPt);
    } else jet_ptrsAK8 = jetSelectorAK8(jet_ptrsAK8raw , isHigherPt);

    // cleaned RecoJet collection from AK12 as well -- to keep b-tag ordering consistent in cat2
    std::vector<const RecoJet*> cleanedJets;
    if (inAK12 && jet_ptrsAK12.size() > 0) cleanedJets = jetCleaner(selJets, jet_ptrsAK12);
    else cleanedJets = jetCleaner(selJets, jet_ptrsAK8);

    if (selJets.size() < 3 && jet_ptrsHTTv2.size() < 1 && jet_ptrsAK12.size() < 1 && cleanedJets.size() < 1 ) continue;

    // natural selection of all ttH(multilepton categories)
    bool passJetSel = false;
    if ( selJets.size() >= 3 &&  (selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1)) {passJetSel = true; countpassJetSel++; } //else continue;

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    std::vector<GenJet> genJets;
    if ( isMC && redoGenMatching ) {
      if ( genJetReader ) {
				genJets = genJetReader->read();
      }
    }

//--- match reconstructed to generator level particles
    if ( isMC && redoGenMatching ) {
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.4);
    }

    if ( isMC ) {
      lheInfoReader->read();
    }

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e1tau = hltPaths_isTriggered(triggers_1e1tau) || (isMC && !apply_trigger_bits);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1mu1tau = hltPaths_isTriggered(triggers_1mu1tau) || (isMC && !apply_trigger_bits);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_1e1tau = use_triggers_1e1tau && isTriggered_1e1tau;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_1mu1tau = use_triggers_1mu1tau && isTriggered_1mu1tau;

    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e) || (isMC && !apply_trigger_bits);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu) || (isMC && !apply_trigger_bits);

    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;

    bool isTriggered_3e = hltPaths_isTriggered(triggers_3e) || (isMC && !apply_trigger_bits);
    bool isTriggered_2e1mu = hltPaths_isTriggered(triggers_2e1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e2mu = hltPaths_isTriggered(triggers_1e2mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_3mu = hltPaths_isTriggered(triggers_3mu) || (isMC && !apply_trigger_bits);

    bool selTrigger_3e = use_triggers_3e && isTriggered_3e;
    bool selTrigger_2e1mu = use_triggers_2e1mu && isTriggered_2e1mu;
    bool selTrigger_1e2mu = use_triggers_1e2mu && isTriggered_1e2mu;
    bool selTrigger_3mu = use_triggers_3mu && isTriggered_3mu;

    bool passtrigger_1l_2tau = (selTrigger_1e || selTrigger_1mu); // || selTrigger_1e1tau || selTrigger_1mu1tau
    bool passtrigger_2l = (selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu || selTrigger_1e1mu) ;
    bool passtrigger_3l = (selTrigger_1e || selTrigger_1mu ||
     selTrigger_2e || selTrigger_1e1mu || selTrigger_2mu   ||
     selTrigger_3e || selTrigger_2e1mu || selTrigger_1e2mu || selTrigger_3mu);

    /////////////////////////////////////////////////////
    // add analyses flags

    double weight_fakeRate_3L = getWeight_3L(
      prob_fake_lepton_lead, passesTight_lepton_lead,
      prob_fake_hadTau_lead, passesTight_hadTau_lead,
      prob_fake_hadTau_sublead, passesTight_hadTau_sublead);

    double weight_fakeRate_4L = getWeight_4L(
        prob_fake_lepton_lead, passesTight_lepton_lead,
        prob_fake_lepton_sublead, passesTight_lepton_sublead,
        prob_fake_hadTau_lead, passesTight_hadTau_lead,
        prob_fake_hadTau_sublead, passesTight_hadTau_sublead
      );

    double weight_fakeRate_2L = getWeight_2L(
        prob_fake_lepton_lead, passesTight_lepton_lead,
        prob_fake_lepton_sublead, passesTight_lepton_sublead
      );

    bool pass_3l = true;
    bool pass_2lss = true;
    bool pass_1l_2tau = true;
    bool pass_2lss_1tau = true;
    bool pass_2los_1tau = true;

    if (!passtrigger_3l) pass_3l = false;
    if (!passtrigger_2l) {pass_2lss = false; pass_2lss_1tau = false; pass_2los_1tau = false;}
    if (!passtrigger_1l_2tau) pass_1l_2tau = false;

    // require that trigger paths match event category (with event category based on fakeableLeptons)
    if ( !((fakeableElectrons.size() >= 1 && (selTrigger_1e  || selTrigger_1e1tau )) ||
           (fakeableMuons.size()     >= 1 && (selTrigger_1mu || selTrigger_1mu1tau))) ) {pass_1l_2tau = false;}

    if ( !((fakeableElectrons.size() >= 3 &&                              (selTrigger_3e    || selTrigger_2e  || selTrigger_1e                                      )) ||
	   (fakeableElectrons.size() >= 2 && fakeableMuons.size() >= 1 && (selTrigger_2e1mu || selTrigger_2e  || selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (fakeableElectrons.size() >= 1 && fakeableMuons.size() >= 2 && (selTrigger_1e2mu || selTrigger_2mu || selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                                 fakeableMuons.size() >= 3 && (selTrigger_3mu   || selTrigger_2mu || selTrigger_1mu                                     ))) ) pass_3l = false;

     // require that trigger paths match event category (with event category based on fakeableLeptons)
    if ( !((fakeableElectrons.size() >= 2 && (selTrigger_2e || selTrigger_1e )) ||
	   (fakeableElectrons.size() >= 1 && fakeableMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (fakeableMuons.size() >= 2 && (selTrigger_2mu   || selTrigger_1mu))) ) {pass_2lss_1tau = false; pass_2los_1tau = false; pass_2lss = false;}

    //bool isTriggered_SingleElectron = isTriggered_1e;
    //bool isTriggered_SingleMuon = isTriggered_1mu;

    //bool selTrigger_SingleElectron = selTrigger_1e;
    //bool selTrigger_SingleMuon = selTrigger_1mu;
    //bool selTrigger_Tau = selTrigger_1e1tau || selTrigger_1mu1tau;

    //const bool isGenMatched = isMC &&
    //    ((apply_leptonGenMatching && selLepton_genMatch.numGenMatchedJets_ == 0) || ! apply_leptonGenMatching) &&
    //    ((apply_hadTauGenMatching && selHadTau_genMatch.numGenMatchedJets_ == 0) || ! apply_hadTauGenMatching)
    //  ;

    // there are no tau triggers now
    //bool selTrigger_Tau = selTrigger_1e1tau || selTrigger_1mu1tau;
    std::cout<<" before trigger      "<<pass_3l<< " "<<pass_2lss<< " "<<pass_1l_2tau<< " "<<pass_2lss_1tau<< " "<<pass_2los_1tau<<std::endl;

    std::cout<<" before minimum jets "<<pass_3l<< " "<<pass_2lss<< " "<<pass_1l_2tau<< " "<<pass_2lss_1tau<< " "<<pass_2los_1tau<< " " << (int)selJets.size() << std::endl;
    if (!((int)selJets.size() >= 4)){pass_2lss = false;}
    if (!((int)selJets.size() >= 3)){pass_2lss_1tau = false; pass_2los_1tau = false; pass_1l_2tau = false;}
    if (!((int)selJets.size() >= 2)){pass_3l = false;}

    //if (!hltFilter(trigger_bits, selLeptons, selHadTaus)){pass_1l_2tau = false;}
    //if (!hltFilter(trigger_bits, selLeptons, {})) {pass_3l = false; pass_2lss = false;}

    if ( apply_met_filters )
    {
      if ( !metFilterSelector(metFilters) )
      {
        pass_3l = false;
        pass_2lss = false;
        pass_1l_2tau = false;
        pass_2lss_1tau = false;
        pass_2los_1tau = false;
      }
    }
    std::cout<<" MET filters          "<<pass_3l<< " "<<pass_2lss<< " "<<pass_1l_2tau<< " "<<pass_2lss_1tau<< " "<<pass_2los_1tau <<std::endl;

    bool passAnalysis = (pass_3l || pass_2lss || pass_2lss_1tau || pass_2los_1tau || pass_1l_2tau);

    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptonsFull.begin();
      lepton1 != preselLeptonsFull.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
        lepton2 != preselLeptonsFull.end(); ++lepton2 ) {
        double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
        if ( mass < 12. ) {
          failsLowMassVeto = true;
        }
      }
    }

    if (!failsLowMassVeto)
    {
      pass_3l = false;
      pass_2lss = false;
      pass_1l_2tau = false;
      pass_2lss_1tau = false;
      pass_2los_1tau = false;
    }

    if (!(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1))
    {
      pass_3l = false;
      pass_2lss = false;
      pass_1l_2tau = false;
      pass_2lss_1tau = false;
      pass_2los_1tau = false;
    }

    const double minPt_lead = 25.;
    const double minPt_sublead = 15.;
    const double maxAbsEta_lept = 2.1;

    std::cout<<" before count analysis "
    <<pass_3l<< " "<<pass_2lss<< " "<<pass_1l_2tau<< " "<<pass_2lss_1tau<< " "<<pass_2los_1tau << " "
    << selLeptons.size() << " " << failsLowMassVeto << " " << selBJets_loose.size() << " " << selBJets_medium.size() << " " <<
    (selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) << " " << passAnalysis << " " <<
    (selLeptons.size() >= 1 && !failsLowMassVeto  && (selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) &&  passAnalysis) <<std::endl;

    if (pass_3l) pass_3l_0++;
    if (
      selLeptons.size() >= 1 && passAnalysis // one of the channels passed trigger and minimum jets selection
    )
    {

      const RecoLepton* selLepton_lead = selLeptons[0];
      const leptonGenMatchEntry& selLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, selLepton_lead);

      if (
        selLepton_lead->cone_pt() > minPt_lead &&
        ((apply_leptonGenMatching && selLepton_genMatch.numGenMatchedJets_ == 0) || ! apply_leptonGenMatching)
      )
      {
        if (tightHadTausFull.size() >= 2)
        {
          const RecoHadTau* selHadTau_lead = tightHadTausFull[0];
          const RecoHadTau* selHadTau_sublead = tightHadTausFull[1];
          const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead);
          if ( (apply_hadTauGenMatching && selHadTau_genMatch.numGenMatchedJets_ == 0) || ! apply_hadTauGenMatching)
          {
            const double minPt_hadTau_lead    = 30.;
            const double minPt_hadTau_sublead = 20.;
            if (selHadTau_lead->charge()*selHadTau_sublead->charge() > 0) {pass_1l_2tau = false;}
            else if ( !(selHadTau_lead->pt() > minPt_hadTau_lead) ) {pass_1l_2tau = false;}
            else if ( !(selHadTau_sublead->pt() > minPt_hadTau_sublead) ) {pass_1l_2tau = false;}
            else if ( !(selHadTau_sublead->absEta() < maxAbsEta_lept) ) {pass_1l_2tau = false;}
            else if ( !(selHadTau_lead->absEta() < maxAbsEta_lept) ) {pass_1l_2tau = false;}
          } else {pass_1l_2tau = false;}

          if ( (tightLeptonsFull.size() <= 1) && pass_1l_2tau)
          { // require exactly one lepton passing tight selection criteria, to avoid overlap with other channels
            // only on 1l_2tau
            const double minPt_lead_E_1l_2tau = 30.;
            if (selLepton_lead->is_electron() && !(selLepton_lead->cone_pt() > minPt_lead_E_1l_2tau)) {pass_1l_2tau = false;}
            else if (!(selLepton_lead->absEta() < maxAbsEta_lept))  {pass_1l_2tau = false;}
          } else
          {
            pass_1l_2tau = false;
            // add the 2l2t
          }

        } else {pass_1l_2tau = false;} // add 2l2t

        if ( selLeptons.size() >= 2 )
        {
          RecoMEt met = metReader->read();
          Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, {}, selJets);
          double met_LD = compMEt_LD(met.p4(), mht_p4);

          bool failsTightChargeCut = false;
          for ( std::vector<const RecoLepton*>::const_iterator lepton = fakeableLeptons.begin();
          lepton != fakeableLeptons.end(); ++lepton )
          {
            if ( (*lepton)->is_electron() )
            {
              const RecoElectron* electron = dynamic_cast<const RecoElectron*>(*lepton);
              assert(electron);
              if ( electron->tightCharge() < 2 ) failsTightChargeCut = true;
            }
            if ( (*lepton)->is_muon() )
            {
              const RecoMuon* muon = dynamic_cast<const RecoMuon*>(*lepton);
              assert(muon);
              if ( muon->tightCharge() < 2 ) failsTightChargeCut = true;
            }
          }
          if ( failsTightChargeCut ){pass_2lss = false; pass_2lss_1tau = false;}
          std::cout<<" tight charge      "<<pass_3l<< " "<<pass_2lss<< " "<<pass_1l_2tau<< " "<<pass_2lss_1tau<< " "<<pass_2los_1tau<<std::endl;
          if (pass_3l) pass_3l_2++;

          const RecoLepton* selLepton_sublead = selLeptons[1];
          const leptonGenMatchEntry& selLepton_sublead_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, selLepton_sublead);

          if (!((apply_leptonGenMatching && selLepton_sublead_genMatch.numGenMatchedJets_ == 0) || ! apply_leptonGenMatching)) {pass_3l = false; pass_2lss = false; pass_2lss_1tau = false; pass_2los_1tau = false; }
          else if (!(selLepton_sublead->cone_pt() > minPt_sublead))
          {
            std::cout<<" not pass sub lep pt "<<pass_3l<< " "<<pass_2lss<< " "<<pass_1l_2tau<< " "<<pass_2lss_1tau<< " "<<pass_2los_1tau<< " " << selLepton_sublead->cone_pt() << std::endl;
            pass_3l = false;
            pass_2lss = false;
            const double minPt_sublead_E_2l_1tau = 10.;
            if (looseHadTausFull.size() >= 1)
            {
              if (selLepton_sublead->is_electron()) { pass_2lss_1tau = false; pass_2los_1tau = false; }
              else if ( !(selLepton_sublead->cone_pt() > minPt_sublead_E_2l_1tau) ) { pass_2lss_1tau = false; pass_2los_1tau = false; }
              if (looseHadTausFull[0]->charge()*selLepton_sublead->charge() > 0) pass_2lss_1tau = false;
            } else { pass_2lss_1tau = false; pass_2los_1tau = false; }
            if (tightHadTausFull.size() > 1) { pass_2lss_1tau = false; pass_2los_1tau = false; }
          }

          bool isLeptonCharge_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;
          if ( isLeptonCharge_OS ) {pass_2lss = false; pass_2lss_1tau = false;}
          else pass_2los_1tau = false;

          if ( selLeptons.size() != 2 ) pass_2lss = false;
          if ( looseHadTausFull.size() > 0 ) {pass_2lss = false; pass_3l = false;}
          if (pass_3l) pass_3l_3++;
          //if (selHadTaus.size() > 1)  {pass_2los_1tau = false; pass_2lss_1tau = false;}
          // not more than one medium -- to add



          //if (!(fakeableHadTausFull.size() >= 1)) {pass_2los_1tau = false; pass_2lss_1tau = false;}
          //if ( (selLeptons.size() >= 2) )
          //if ( !(selHadTaus.size() >= 1) )

          if ( !(tightLeptonsFull.size() <= 2) ) {pass_2lss = false; pass_2lss_1tau = false; pass_2los_1tau = false;}

          if ( pass_2lss || pass_2lss_1tau || pass_2los_1tau )
          {
            if ((selLepton_lead->is_electron() && selLepton_sublead->is_electron()) && !(met_LD >= 0.2)) {pass_2lss = false; pass_2lss_1tau = false; pass_2los_1tau = false;}

            bool failsZbosonMassVeto = false;
            for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptonsFull.begin();
                 lepton1 != preselLeptonsFull.end(); ++lepton1 ) {
             for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
                   lepton2 != preselLeptonsFull.end(); ++lepton2 ) {
               double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
               if ( (*lepton1)->is_electron() && (*lepton2)->is_electron() && std::fabs(mass - z_mass) < z_window ) {
                 failsZbosonMassVeto = true;
               }
             }
            }
            std::cout<<" testing Zmass veto "<< failsZbosonMassVeto << " "<< z_window<<std::endl;
             if ( failsZbosonMassVeto ) {pass_2lss = false; pass_2lss_1tau = false; pass_2los_1tau = false;}
          } // close if nor fail Z mass cut on leptons

          std::cout<<" testing 3l "<< tightLeptonsFull.size() << " "<< selLeptons.size() <<std::endl;
          //if ( !(tightLeptonsFull.size() <= 3) ) pass_3l = false;
          if ( (selLeptons.size() == 3) && pass_3l)
          {
            if (pass_3l) pass_3l_4++;
            // require exactly three leptons passing tight selection criteria, to avoid overlap with 4l channel
            const RecoLepton* selLepton_third = selLeptons[2];
            const leptonGenMatchEntry& selLepton_third_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, selLepton_third);
            if (!((apply_leptonGenMatching && selLepton_third_genMatch.numGenMatchedJets_ == 0) || ! apply_leptonGenMatching)) {pass_3l = false;}

            double minPt_third = 10.;
            if ( !(selLepton_third->cone_pt() > minPt_third) ) pass_3l = false;
            else
            {
              int sumLeptonCharge = selLepton_lead->charge() + selLepton_sublead->charge() + selLepton_third->charge();
              if ( !(std::abs(sumLeptonCharge) == 1) ) pass_3l = false;
            }
            if (pass_3l) pass_3l_5++;

            if (pass_3l)
            {
              bool isSameFlavor_OS = false;
              double massSameFlavor_OS = -1.;
              for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptonsFull.begin();
              lepton1 != preselLeptonsFull.end(); ++lepton1 ) {
                for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
                lepton2 != preselLeptonsFull.end(); ++lepton2 ) {
                	if ( (*lepton1)->pdgId() == -(*lepton2)->pdgId() ) { // pair of same flavor leptons of opposite charge
                	  isSameFlavor_OS = true;
                	  double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
                	  if ( std::fabs(mass - z_mass) < std::fabs(massSameFlavor_OS - z_mass) ) massSameFlavor_OS = mass;
                	}
                }
              }
              bool failsZbosonMassVeto = isSameFlavor_OS && std::fabs(massSameFlavor_OS - z_mass) < z_window;
              if ( failsZbosonMassVeto ) {pass_3l = false; if (pass_3l) pass_3l_6++;}
              else
              {
                double met_LD_cut = 0.;
                if      ( selJets.size() >= 4 ) met_LD_cut = -1.; // MET LD cut not applied
                else if ( isSameFlavor_OS     ) met_LD_cut =  0.3;
                else                            met_LD_cut =  0.2;
                if ( met_LD_cut > 0 && met_LD < met_LD_cut ) pass_3l = false;
              }
            }
            if (pass_3l) pass_3l_7++;

            ///*
            bool failsHtoZZVeto = false;
            for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptonsFull.begin();
            lepton1 != preselLeptonsFull.end(); ++lepton1 )
            {
              for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
              lepton2 != preselLeptonsFull.end(); ++lepton2 )
              {
                if ( (*lepton1)->pdgId() == -(*lepton2)->pdgId() )
                { // first pair of same flavor leptons of opposite charge
                  for ( std::vector<const RecoLepton*>::const_iterator lepton3 = preselLeptonsFull.begin();
                  lepton3 != preselLeptonsFull.end(); ++lepton3 )
                  {
                    if ( (*lepton3) == (*lepton1) || (*lepton3) == (*lepton2) ) continue;
                    for ( std::vector<const RecoLepton*>::const_iterator lepton4 = lepton3 + 1;
                    lepton4 != preselLeptonsFull.end(); ++lepton4 )
                    {
                      if ( (*lepton4) == (*lepton1) || (*lepton4) == (*lepton2) ) continue;
                      if ( (*lepton3)->pdgId() == -(*lepton4)->pdgId() )
                      { // second pair of same flavor leptons of opposite charge
                        double mass = ((*lepton1)->p4() + (*lepton2)->p4() + (*lepton3)->p4() + (*lepton4)->p4()).mass();
                        if ( mass < 140. ) failsHtoZZVeto = true;
                      }
                    }
                  }
                }
              }
            }
            if ( failsHtoZZVeto ) pass_3l = false;
            //*/
            } else pass_3l = false; // has 3l

        } else // close on two tight leptons
        {
          pass_3l = false;
          pass_2lss = false;
          pass_2lss_1tau = false;
          pass_2los_1tau = false;
        }
      } else // clse if leading lep passes
      {
        pass_3l = false;
        pass_2lss = false;
        pass_1l_2tau = false;
        pass_2lss_1tau = false;
        pass_2los_1tau = false;
      }
    } else // close if basic analysis passes
    {
      pass_3l = false;
      pass_2lss = false;
      pass_1l_2tau = false;
      pass_2lss_1tau = false;
      pass_2los_1tau = false;
    }
    int SUM_AnBits =  pass_3l+pass_2lss+pass_1l_2tau+pass_2lss_1tau+pass_2los_1tau;
    std::cout<<" pass all analysis  "<<pass_3l<< " "<<pass_2lss<< " "<<pass_1l_2tau<< " "<<pass_2lss_1tau<< " "<<pass_2los_1tau<<
     " SUM "<< SUM_AnBits <<std::endl;
     if (SUM_AnBits > 1) throw cms::Exception("analyze_HTT")
       << "The signal region of 2 analyses overlaped = " << hadTauSelection_string << " !!\n";

    std::cout<<"  ------------------------   "<<std::endl;
    if (pass_3l) {
      count_pass_3l++;
      if ( selEventsFile_3l ) (*selEventsFile_3l) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }
    if (pass_2lss) {
      count_pass_2lss++;
      if ( selEventsFile_2lss ) (*selEventsFile_2lss) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }
    if (pass_1l_2tau) {
      count_pass_1l_2tau++;
      if ( selEventsFile_1l_2tau ) (*selEventsFile_1l_2tau) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }
    if (pass_2lss_1tau) {
      count_pass_2lss_1tau++;
      if ( selEventsFile_2lss_1tau ) (*selEventsFile_2lss_1tau) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }
    if (pass_2los_1tau) {
      count_pass_2los_1tau++;
      if ( selEventsFile_2los_1tau ) (*selEventsFile_2los_1tau) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }

    // problably missing according to gitlab
    //2lss: (muon: (muon.muonBestTrack()->ptError() / muon.muonBestTrack()->pt()) < 0.2,
    //     electron: (isGsfCtfScPixChargeConsistent() + isGsfScPixChargeConsistent()) > 1)
    //2lss1tau: At least 1 tau passing "byLooseIsolationMVArun2v1DBdR03oldDMwLT", at most one tau passing "byMediumIsolationMVArun2v1DBdR03oldDMwLT" (to avoid overlap with the 2l+2tau channel)
    //In MC, require MC matching of the Teptons

		//;
    //std::cout << "Size of jet collections "
    //  <<jet_ptrsHTTv2.size()<< " "<< jet_ptrsAK8.size() << " "<< jet_ptrsAK12.size() << " " << cleanedJets.size() << " " << selJets.size() << std::endl;

    //--- build collections of generator level particles
    std::vector<GenParticle> genTopQuarks = genTopQuarkReader->read();
    std::vector<GenParticle> genBJets = genBJetReader->read();
    std::vector<GenParticle> genWBosons = genWBosonReader->read();
    std::vector<GenParticle> genWJets = genWJetReader->read();
    std::vector<GenParticle> genQuarkFromTop = genQuarkFromTopReader->read();

    //std::cout << "Size of genjet collections "
    //  <<genQuarkFromTop.size()<< " "<< genWJets.size() << " " << genWBosons.size() << std::endl;
    bool passHadGenHadW = false;
    if (genQuarkFromTop.size() < 2) passHadGenHadW = true; // put a flag here instead

    Particle::LorentzVector unfittedHadTopP4, selBJet, selWJet1, selWJet2 ;
    bool isGenMatched = false;
		bool fatjet_isGenMatched = false;
    bool b_isGenMatched = false;
    bool wj1_isGenMatched = false;
    bool wj2_isGenMatched = false;
    double genFatPtAll = -1.;
    double drT_gen = -1.;
    double drW_gen = -1.;
    double drB_gen = -1.;
    double drWj1_gen = -1.;
    double drWj2_gen = -1.;
    double genFatEtaAll = -2.5;
    double etaB_gen = -1;
    double etaWj1_gen = -1;
    double etaWj2_gen = -1;
    double ptB_gen = -1;
    double ptWj1_gen = -1;
    double ptWj2_gen = -1;
    double drb_wj1_gen = -1;
    double drb_wj2_gen = -1;
    double drwj1_wj2_gen = -1;
    double drT_genTriplet = -1;
    double drT_genJ_max = -1;
    double HTTv2_area = -1;
    double HTTv2_Ropt = -1;
    double HTTv2_RoptCalc = -1;
    double genTopMassFromW = -1;
    double genTopMassFromWj = -1;
    double genWMassFromWj = -1;
    double genAntiTopMassFromW = -1;
    double genAntiTopMassFromWj = -1;
    double genAntiWMassFromWj = -1;
    double genAntiWMass = -1.;
    double genWMass = -1.;
    //
    bool cat1 = false;
    bool cat2 = false;
    bool cat3 = false;
    bool passJetMassSel = false;

    // it returns the gen-triplets organized in top/anti-top
    std::map<int, Particle::LorentzVector> genVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenTop); // genWJets,
    std::map<int, Particle::LorentzVector> genVarAnti = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenAntiTop); // genWJets,

    if (genQuarkFromTop.size() == 2 ) {
      //&& genVar[kGenTopWj1].pt() > 0 && genVar[kGenTopWj2] > 0
      double diff_Top = (genVar[kGenTopWj1]+genVar[kGenTopWj2]+genVar[kGenTopB]).mass() - genVar[kGenTop].mass();
      double diff_AntiTop = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]+genVarAnti[kGenTopB]).mass() - genVarAnti[kGenTop].mass();
      if( diff_Top < diff_AntiTop && genVar[kGenTopWj1].px() > 0) {
        genTopMassFromW = (genVar[kGenTopW]+genVar[kGenTopB]).mass();
        genTopMassFromWj = (genVar[kGenTopWj1]+genVar[kGenTopWj2]+genVar[kGenTopB]).mass();
        genWMassFromWj = (genVar[kGenTopWj1]+genVar[kGenTopWj2]).mass();
        genWMass = genVar[kGenTopW].mass();
        //std::cout<<" mass W/T  "<< genVar[kGenTop].mass() << " "<< (genVar[kGenTopW]+genVar[kGenTopB]).mass() << " (" << genVar[kGenTopW].mass() <<") " << " (" << genWMassFromWj <<") " <<std::endl;
      } else if (genVarAnti[kGenTopWj1].px() > 0){
        genAntiTopMassFromW = (genVarAnti[kGenTopW]+genVarAnti[kGenTopB]).mass();
        genAntiTopMassFromWj = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]+genVarAnti[kGenTopB]).mass();
        genAntiWMassFromWj = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]).mass();
        genAntiWMass = genVarAnti[kGenTopW].mass();
        //std::cout<<" mass anti W/T  "<< genVarAnti[kGenTop].mass() << " "<< (genVarAnti[kGenTopW]+genVarAnti[kGenTopB]).mass() << " (" << genVarAnti[kGenTopW].mass() <<") " << " (" << genAntiWMassFromWj <<") "  <<std::endl;
      }
    } else if (genQuarkFromTop.size() == 4) {

      if ( genVar[kGenTopWj1].px() > 0 ) {
        genTopMassFromW = (genVar[kGenTopW]+genVar[kGenTopB]).mass();
        genTopMassFromWj = (genVar[kGenTopWj1]+genVar[kGenTopWj2]+genVar[kGenTopB]).mass();
        genWMassFromWj = (genVar[kGenTopWj1]+genVar[kGenTopWj2]).mass();
        //std::cout<<" mass W/T  "<< genVar[kGenTop].mass() << " "<< (genVar[kGenTopW]+genVar[kGenTopB]).mass() << " (" << genVar[kGenTopW].mass() << ") " << " (" << genWMassFromWj << ") "  <<std::endl;
      }

      if ( genVarAnti[kGenTopWj1].px() > 0 ) {
        genAntiTopMassFromW = (genVarAnti[kGenTopW]+genVarAnti[kGenTopB]).mass();
        genAntiTopMassFromWj = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]+genVarAnti[kGenTopB]).mass();
        genAntiWMassFromWj = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]).mass();
      //std::cout<<" mass anti W/T  "<< genVarAnti[kGenTop].mass() << " "<< (genVarAnti[kGenTopW]+genVarAnti[kGenTopB]).mass() << " (" << genVarAnti[kGenTopW].mass() << ") " << " (" << genAntiWMassFromWj << ") "<<std::endl;
      }

    } else std::cout<<" unusual genQuarkFromTop.size()  "<< genQuarkFromTop.size() <<std::endl;
    //if (genAntiTopMassFromWj > 0 && (genAntiWMassFromWj > 125.)) throw cms::Exception("analyze_hadTopTagger")
    //  <<"            mass anti W/T  "<< genVarAnti[kGenTop].mass() << "                "<< (genVarAnti[kGenTopW]+genVarAnti[kGenTopB]).mass() << " " << genAntiTopMassFromWj << "      (" << genVarAnti[kGenTopW].mass() << ") " << " (" << genAntiWMassFromWj << ") " << genQuarkFromTop.size() << " !!\n";


    // to be used at analysis level
    int typeTop = -1; // 1 - FatTop; 2 - countFatAK8 ? countFatAK12; 3- countResolved;
    //if (inAK12) typeTop = getType(jet_ptrsHTTv2.size(), jet_ptrsAK12.size(), selJets.size());
    //else typeTop = getType(jet_ptrsHTTv2.size(), jet_ptrsAK8.size(), selJets.size());
    // start loops in jets
    //if (typeTop == 1) {

      if (jet_ptrsHTTv2.size() > 0 ) countFatTop++;
      typeTop = 1;
      int counter = 0;
      for ( std::vector<const RecoJetHTTv2*>::const_iterator jetIter = jet_ptrsHTTv2.begin();
        jetIter != jet_ptrsHTTv2.end(); ++jetIter ) {
          genFatPtAll = -1.;
          genFatEtaAll = -2.5;
          unfittedHadTopP4 = (*jetIter)->p4();
          if ( unfittedHadTopP4.M() > 95 && unfittedHadTopP4.M() < 225 ) passJetMassSel = true;
          HTTv2_area = (*jetIter)->area();
          HTTv2_Ropt = (*jetIter)->Ropt();
          HTTv2_RoptCalc = (*jetIter)->RoptCalc();

          const RecoSubjetHTTv2* recSubJet[3];
          recSubJet[0] = (*jetIter)->subJet1();
          recSubJet[1] = (*jetIter)->subJet2();
          recSubJet[2] = (*jetIter)->subJet3();
          double btag_orderType1 = -1;
          double btag_discType1 = -1;

          // loop on bjetCandidate version 1 :
          //bool foundtruth = false;
          //for (int bb = 0; bb < 3; bb++) {
          //  if (foundtruth) continue;
          //  for (int wj1 = 0; wj1 < 3; wj1++) {
          //   if (bb == wj1) continue;
          //    for (int wj2 = 0; wj2 < 3; wj2++) {
          //      if (bb == wj2 || wj1 == wj2 || foundtruth) continue;
          //        selBJet = recSubJet[bb]->p4();
          //        selWJet1 = recSubJet[wj1]->p4();
          //        selWJet2 = recSubJet[wj2]->p4();
          //        std::vector<double> btag_disc1 = {recSubJet[bb]->BtagCSV(), recSubJet[wj1]->BtagCSV(), recSubJet[wj2]->BtagCSV()};
          //  auto btag_order1 = calRank(btag_disc1);
          //  btag_orderType1 = btag_order1[0];
          //  btag_discType1 = btag_disc1[0];
          //  std::cout<<" btag position of bjet "<< btag_order1[0] <<" value "<< btag_disc1[0] <<std::endl;

          ////////////
          // loop on bjetCandidate version 2 :
          //int perm [5] = { 0, 1, 2, 0, 1 }; // I do not care about the ordering of wj1/2 so no fancy permutation solution is required
          //for (int bb = 0; bb < 3; bb++) {
          //  if (foundtruth) continue;
          //  selBJet = recSubJet[perm[bb]]->p4();
          //  selWJet1 = recSubJet[perm[bb+1]]->p4();
          //  selWJet2 = recSubJet[perm[bb+2]]->p4();
          //  std::vector<double> btag_disc1 = {recSubJet[perm[bb]]->BtagCSV(), recSubJet[perm[bb+1]]->BtagCSV(), recSubJet[perm[bb+2]]->BtagCSV()};
            // checking btag ordering
          //  auto btag_order1 = calRank(btag_disc1);
          //  btag_orderType1 = btag_order1[0];
          //  btag_discType1 = recSubJet[perm[bb]]->BtagCSV();
          //  std::cout<<"btag discr  ";
          //  for (auto i: btag_disc1) std::cout << i << " ";
          //  std::cout<<" btag ordering  ";
          //  for (auto i: btag_order1) std::cout << i << " ";
          //  std::cout<<" typeTop = "<<typeTop << " b-tag discrim: " << recSubJet[perm[bb]]->BtagCSV() << " on position " << btag_order1[0] <<std::endl;

            // Just take the subjet with highest b-tag score to be the b-candidate
            std::vector<double> btag_disc = {recSubJet[0]->BtagCSV(), recSubJet[1]->BtagCSV(), recSubJet[2]->BtagCSV()};
            auto btag_order = sort_indexes(btag_disc);
            selBJet = recSubJet[btag_order[0]]->p4();
            selWJet1 = recSubJet[btag_order[1]]->p4();
            selWJet2 = recSubJet[btag_order[2]]->p4();
            btag_orderType1 = 1;
            btag_discType1 = recSubJet[btag_order[0]]->BtagCSV();
            //std::cout<<"btag discr  ";
            //for (auto i: btag_disc) std::cout << i << " ";
            //std::cout<<" position of highest  "<< btag_order[0] << " (" << btag_discType1 <<") "<< foundtruth <<std::endl;

            std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
              selBJet, selWJet1, selWJet2,
              genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
              kGenTop, typeTop, unfittedHadTopP4
            );
            std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
              selBJet, selWJet1, selWJet2,
              genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
              kGenAntiTop, typeTop, unfittedHadTopP4
            );

            isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
            fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
            b_isGenMatched = (genMatchingTop[kGenMatchedBJet] || genMatchingAntiTop[kGenMatchedBJet]);
            wj1_isGenMatched = (genMatchingTop[kGenMatchedWJet1] || genMatchingAntiTop[kGenMatchedWJet1]);
            wj2_isGenMatched = (genMatchingTop[kGenMatchedWJet2] || genMatchingAntiTop[kGenMatchedWJet2]);
            //if (b_isGenMatched) foundtruth = true; // if loop on subjets
            if (isGenMatched) {hadtruth1++; cat1 = true; } // foundtruth = true;
          //}}} // end loop on subjets version 1
          //} // end loop on subjets version 2
          // debug gen-matching

          double minT = deltaR(selBJet, genVar[kGenTopB]) + deltaR(selWJet1+selWJet2, genVar[kGenTopWj2]);//std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2])) + std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
          double minAntiT = deltaR(selBJet, genVarAnti[kGenTopB]) + deltaR(selWJet1+selWJet2, genVarAnti[kGenTopWj2]);//std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2])) + std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));

          if ( minT < minAntiT ){
            genFatPtAll = genVar[kGenTopVar].pt();
            genFatEtaAll = genVar[kGenTopVar].eta();
            drT_gen = deltaR(unfittedHadTopP4, genVar[kGenTop]);
            drT_genTriplet = deltaR(unfittedHadTopP4, genVar[kGenTopWj1]+genVar[kGenTopWj1]+genVar[kGenTopB]);
            drT_genJ_max = std::max(deltaR(unfittedHadTopP4, genVar[kGenTopB]),std::max(deltaR(unfittedHadTopP4, genVar[kGenTopWj1]),deltaR(unfittedHadTopP4, genVar[kGenTopWj2])));
            drB_gen = deltaR(selBJet, genVar[kGenTopB]);
            drWj1_gen = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2]));
            drWj2_gen = std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
            etaB_gen = genVar[kGenTopB].eta();
            etaWj1_gen = genVar[kGenTopWj1].eta();
            etaWj2_gen = genVar[kGenTopWj2].eta();
            ptB_gen = genVar[kGenTopB].pt();
            ptWj1_gen = genVar[kGenTopWj1].pt();
            ptWj2_gen = genVar[kGenTopWj2].pt();
            drb_wj1_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj1]);
            drb_wj2_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj2]);
            drwj1_wj2_gen = deltaR(genVar[kGenTopWj1], genVar[kGenTopWj2]);
            drW_gen = deltaR(selWJet1 + selWJet2 , genVar[kGenTopW]);
          } else {
            genFatPtAll = genVarAnti[kGenTopVar].pt();
            genFatEtaAll = genVarAnti[kGenTopVar].eta();
            drT_gen = deltaR(unfittedHadTopP4, genVarAnti[kGenTop]);
            drT_genTriplet = deltaR(unfittedHadTopP4, genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj1]+genVarAnti[kGenTopB]);
            drT_genJ_max = std::max(deltaR(unfittedHadTopP4, genVarAnti[kGenTopB]),std::max(deltaR(unfittedHadTopP4, genVarAnti[kGenTopWj1]),deltaR(unfittedHadTopP4, genVarAnti[kGenTopWj2])));
            drB_gen = deltaR(selBJet, genVarAnti[kGenTopB]);
            drWj1_gen = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2]));
            drWj2_gen = std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
            etaB_gen = genVarAnti[kGenTopB].eta();
            etaWj1_gen = genVarAnti[kGenTopWj1].eta();
            etaWj2_gen = genVarAnti[kGenTopWj2].eta();
            ptB_gen = genVarAnti[kGenTopB].pt();
            ptWj1_gen = genVarAnti[kGenTopWj1].pt();
            ptWj2_gen = genVarAnti[kGenTopWj2].pt();
            drb_wj1_gen = deltaR(genVarAnti[kGenTopB], genVarAnti[kGenTopWj1]);
            drb_wj2_gen = deltaR(genVarAnti[kGenTopB], genVar[kGenTopWj2]);
            drwj1_wj2_gen = deltaR(genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2]);
            drW_gen = deltaR(selWJet1 + selWJet2 , genVarAnti[kGenTopW]);
          }
          if ( genFatPtAll > 200 && (genVarAnti[kGenTopB]+genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]).eta() < 2.4 && counter == 0 && drT_gen < 0.75) {
            countFatTopPt200++; counter++;
          }
          if ( counter == 1 && b_isGenMatched && selBJet.pt() > 30 ) {
            countFatTopbmatch++;
            if ( wj1_isGenMatched && selWJet1.pt() > 30) {
              countFatTopWj1match++;
              if ( wj2_isGenMatched && selWJet2.pt() > 30) countFatTopWj2match++;
            }
          }

          if ( bdt_filler ) {
            (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2); // calculates the quantities that take only kinematics
            const std::map<std::string, double>& mvaInputs =  hadTopTaggerFill->mvaInputs();
            for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
              mvaInput != mvaInputs.end(); ++mvaInput ) {
              bdt_filler->operator()(mvaInput->first, mvaInput->second);
            }
            bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
            ("typeTop",              typeTop)
            ("tau32Top",             (*jetIter)->tau3()/(*jetIter)->tau2())
            ("massTop",              unfittedHadTopP4.mass())
            ("tau21W",               -1.)
            ("massW_SD",             -1.)
            ("btagDisc",             btag_discType1)
            ("qg_Wj1",                -1.)
            ("qg_Wj2",                -1.)
            ("genFatPtAll", genFatPtAll)
            ("genFatEtaAll",         std::fabs(genFatEtaAll))
            ("drT_gen",       drT_gen)
            ("drT_genTriplet",  drT_genTriplet)
            ("drT_genJ_max", drT_genJ_max)
            ("drB_gen", drB_gen)
            ("drW_gen", drW_gen)
            ("drWj1_gen", drWj1_gen)
            ("drWj2_gen", drWj2_gen)
            ("etaB_gen", etaB_gen)
            ("etaWj1_gen", etaWj1_gen)
            ("etaWj2_gen", etaWj2_gen)
            ("ptB_gen", ptB_gen)
            ("ptWj1_gen", ptWj1_gen)
            ("ptWj2_gen", ptWj2_gen)
            ("dr_b_wj1", deltaR(selBJet, selWJet1))
            ("dr_b_wj2", deltaR(selBJet, selWJet2))
            ("dr_wj1_wj2", deltaR(selWJet1, selWJet2))
            ("dr_b_wj1_gen", drb_wj1_gen)
            ("dr_b_wj2_gen", drb_wj2_gen)
            ("dr_wj1_wj2_gen", drwj1_wj2_gen)
            ("collectionSize",       jet_ptrsHTTv2.size())
            ("bjet_tag_position",    btag_orderType1)
            ("bWj1Wj2_isGenMatched", isGenMatched)
            ("fatjet_isGenMatched",  fatjet_isGenMatched)
            ("b_isGenMatched",       b_isGenMatched)
            ("Wj1_isGenMatched", wj1_isGenMatched)
            ("Wj2_isGenMatched", wj2_isGenMatched)
            ("counter",        analyzedEntries)
            ("passJetSel", passJetSel)
            ("passJetMassSel", passJetMassSel)
            ("HTTv2_area", HTTv2_area)
            ("HTTv2_Ropt", HTTv2_Ropt)
            ("HTTv2_RoptCalc", HTTv2_RoptCalc)
            ("genTopMassFromW", genTopMassFromW )
            ("genTopMassFromWj", genTopMassFromWj )
            ("genWMassFromWj", genWMassFromWj )
            ("genAntiTopMassFromW", genAntiTopMassFromW )
            ("genAntiTopMassFromWj", genAntiTopMassFromWj )
            ("genAntiWMassFromWj", genAntiWMassFromWj )
            ("genWMass", genWMass)
            ("genAntiWMass", genAntiWMass)
            ("genWeight", eventInfo.genWeight) // to count nevents with neg weights
            ("weight_fakeRate_3L", weight_fakeRate_3L)
            ("weight_fakeRate_4L", weight_fakeRate_4L)
            ("weight_fakeRate_2L", weight_fakeRate_2L)
            ("passHadGenHadW", passHadGenHadW)
            ("pass_3l", pass_3l)
            ("pass_2lss", pass_2lss)
            ("pass_1l_2tau", pass_1l_2tau)
            ("pass_2lss_1tau", pass_2lss_1tau)
            ("pass_2los_1tau", pass_2los_1tau)
                .fill();
          }
        } // end typeTop == 1
    //} else if (typeTop!=-1) {
    // store b-tag classification of cleaned jet collection
    if (cleanedJets.size()>0) {
    std::vector<double> btag_disc = getBdiscr(cleanedJets);
    auto btag_order = calRank(btag_disc);
    unsigned int bToLoop = cleanedJets.size();
    if (!loopB) bToLoop = 1;
    //std::cout<<std::endl;
    //std::cout<<"btag ordering  ";
    //for (auto i: btag_order) std::cout << i << " ";
    // classify between 2 and 3
    if (inAK12) { // typeTop == 2 and
      if (jet_ptrsAK12.size() > 0 && cleanedJets.size() > 0) {countFatAK12++; typeTop = 2;}
      //std::cout<<" typeTop = "<<typeTop<<std::endl;
      for ( std::vector<const RecoJetAK12*>::const_iterator jetIter = jet_ptrsAK12.begin();
        jetIter != jet_ptrsAK12.end(); ++jetIter ) {
          for ( unsigned int bjetCandidate = 0; bjetCandidate < bToLoop; bjetCandidate++ ) { // cleanedJets.size()
              unfittedHadTopP4 = (*jetIter)->p4() + (*cleanedJets[bjetCandidate]).p4();
              if ( unfittedHadTopP4.M() > 95 && unfittedHadTopP4.M() < 225 ) passJetMassSel = true;
              selBJet = (*cleanedJets[bjetCandidate]).p4();
              if((*jetIter)->subJet1() && (*jetIter)->subJet2()) {
              selWJet1 = (*jetIter)->subJet1()->p4();
              selWJet2 = (*jetIter)->subJet2()->p4();
              // calculate matching
              std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
                selBJet, selWJet1, selWJet2,
                genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
                kGenTop, typeTop, (*jetIter)->p4()
              );
              std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
                selBJet, selWJet1, selWJet2,
                genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
                kGenAntiTop, typeTop, (*jetIter)->p4()
              );

              isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
              fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
              b_isGenMatched = (genMatchingTop[kGenMatchedBJet] || genMatchingAntiTop[kGenMatchedBJet]);
              wj1_isGenMatched = (genMatchingTop[kGenMatchedWJet1] || genMatchingAntiTop[kGenMatchedWJet1]);
              wj2_isGenMatched = (genMatchingTop[kGenMatchedWJet2] || genMatchingAntiTop[kGenMatchedWJet2]);
              if (btag_order[bjetCandidate] > cutJetCombo) continue;
              if (isGenMatched) {hadtruth2++; cat2 = true;}

              double minT;
              double minAntiT;
              if (loopB) {
                minT = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2])) + std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                minAntiT = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2])) + std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
              } else {
                minT = deltaR(selBJet, genVar[kGenTopB]);
                minAntiT = deltaR(selBJet, genVarAnti[kGenTopB]);
              }
              if ( minT < minAntiT ){
                genFatPtAll = genVar[kGenTopW].pt();
                genFatEtaAll = genVar[kGenTopW].pt();
                drT_gen = deltaR(unfittedHadTopP4, genVar[kGenTop]);
                drT_genTriplet = deltaR(unfittedHadTopP4, genVar[kGenTopWj1]+genVar[kGenTopWj1]+genVar[kGenTopB]);
                drB_gen = deltaR(selBJet, genVar[kGenTopB]);
                drWj1_gen = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2]));
                drWj2_gen = std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                etaB_gen = genVar[kGenTopB].eta();
                etaWj1_gen = genVar[kGenTopWj1].eta();
                etaWj2_gen = genVar[kGenTopWj2].eta();
                ptB_gen = genVar[kGenTopB].pt();
                ptWj1_gen = genVar[kGenTopWj1].pt();
                ptWj2_gen = genVar[kGenTopWj2].pt();
                drb_wj1_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj1]);
                drb_wj2_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj2]);
                drwj1_wj2_gen = deltaR(genVar[kGenTopWj1], genVar[kGenTopWj2]);
                drW_gen = deltaR(unfittedHadTopP4 , genVar[kGenTopW]);
              } else {
                genFatPtAll = genVarAnti[kGenTopW].pt();
                genFatEtaAll = genVarAnti[kGenTopW].pt();
                drT_gen = deltaR(unfittedHadTopP4, genVarAnti[kGenTop]);
                drT_genTriplet = deltaR(unfittedHadTopP4, genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj1]+genVarAnti[kGenTopB]);
                drB_gen = deltaR(selBJet, genVarAnti[kGenTopB]);
                drWj1_gen = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2]));
                drWj2_gen = std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                etaB_gen = genVarAnti[kGenTopB].eta();
                etaWj1_gen = genVarAnti[kGenTopWj1].eta();
                etaWj2_gen = genVarAnti[kGenTopWj2].eta();
                ptB_gen = genVarAnti[kGenTopB].pt();
                ptWj1_gen = genVarAnti[kGenTopWj1].pt();
                ptWj2_gen = genVarAnti[kGenTopWj2].pt();
                drb_wj1_gen= deltaR(genVarAnti[kGenTopB], genVarAnti[kGenTopWj1]);
                drb_wj2_gen = deltaR(genVarAnti[kGenTopB], genVar[kGenTopWj2]);
                drwj1_wj2_gen = deltaR(genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2]);
                drW_gen = deltaR(unfittedHadTopP4 , genVarAnti[kGenTopW]);
              }
              if (genFatPtAll > 130) {
                countFatWpt130++;
                if (wj1_isGenMatched && wj2_isGenMatched) countFatWjets++;
                if (fatjet_isGenMatched) countFatW++;
              }

              if ( bdt_filler ) {
                (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2);
                const std::map<std::string, double>& mvaInputs =  hadTopTaggerFill->mvaInputs();
                for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
                  mvaInput != mvaInputs.end(); ++mvaInput ) {
                  bdt_filler->operator()(mvaInput->first, mvaInput->second);
                }
                bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
                ("typeTop",              typeTop)
                ("tau32Top",             -1.)
                ("massTop",              unfittedHadTopP4.mass())
                ("tau21W",               (*jetIter)->tau2()/(*jetIter)->tau1())
                ("massW_SD",             (*jetIter)->msoftdrop())
                ("btagDisc",             (*cleanedJets[bjetCandidate]).BtagCSV())
                ("qg_Wj1",                -1.)
                ("qg_Wj2",                -1.)
                ("genFatPtAll", genFatPtAll)
                ("genFatEtaAll",         std::fabs(genFatEtaAll))
                ("drT_gen",       drT_gen)
                ("drT_genTriplet",  drT_genTriplet)
                ("drT_genJ_max", drT_genJ_max)
                ("drB_gen", drB_gen)
                ("drW_gen", drW_gen)
                ("drWj1_gen", drWj1_gen)
                ("drWj2_gen", drWj2_gen)
                ("etaB_gen", etaB_gen)
                ("etaWj1_gen", etaWj1_gen)
                ("etaWj2_gen", etaWj2_gen)
                ("ptB_gen", ptB_gen)
                ("ptWj1_gen", ptWj1_gen)
                ("ptWj2_gen", ptWj2_gen)
                ("dr_b_wj1", deltaR(selBJet, selWJet1))
                ("dr_b_wj2", deltaR(selBJet, selWJet2))
                ("dr_wj1_wj2", deltaR(selBJet, selWJet2))
                ("dr_b_wj1_gen", drb_wj1_gen)
                ("dr_b_wj2_gen", drb_wj2_gen)
                ("dr_wj1_wj2_gen", drwj1_wj2_gen)
                ("collectionSize",       jet_ptrsAK12.size())
                ("bjet_tag_position",    btag_order[bjetCandidate])
                ("bWj1Wj2_isGenMatched", isGenMatched)
                ("fatjet_isGenMatched",  fatjet_isGenMatched)
                ("b_isGenMatched",       b_isGenMatched)
                ("Wj1_isGenMatched", wj1_isGenMatched)
                ("Wj2_isGenMatched", wj2_isGenMatched)
                ("counter",       analyzedEntries)
                ("passJetSel", passJetSel)
                ("passJetMassSel", passJetMassSel)
                ("HTTv2_area", HTTv2_area)
                ("HTTv2_Ropt", HTTv2_Ropt)
                ("HTTv2_RoptCalc", HTTv2_RoptCalc)
                ("genTopMassFromW", genTopMassFromW )
                ("genTopMassFromWj", genTopMassFromWj )
                ("genWMassFromWj", genWMassFromWj )
                ("genAntiTopMassFromW", genAntiTopMassFromW )
                ("genAntiTopMassFromWj", genAntiTopMassFromWj )
                ("genAntiWMassFromWj", genAntiWMassFromWj )
                ("genWMass", genWMass)
                ("genAntiWMass", genAntiWMass)
                ("genWeight", eventInfo.genWeight) // to count nevents with neg weights
                ("weight_fakeRate_3L", weight_fakeRate_3L)
                ("weight_fakeRate_4L", weight_fakeRate_4L)
                ("weight_fakeRate_2L", weight_fakeRate_2L)
                ("passHadGenHadW", passHadGenHadW)
                ("pass_3l", pass_3l)
                ("pass_2lss", pass_2lss)
                ("pass_1l_2tau", pass_1l_2tau)
                ("pass_2lss_1tau", pass_2lss_1tau)
                ("pass_2los_1tau", pass_2los_1tau)
                    .fill();
              }
            } else { std::cout<<" type2 akt12 did not had subjets "<<std::endl; continue;}
            }
        } // end typeTop == 2 ak12 loop
    } else { // if (typeTop == 2)
        if (jet_ptrsAK8.size() > 0 && cleanedJets.size() > 0) {countFatAK8++; typeTop = 2;}
        for ( std::vector<const RecoJetAK8*>::const_iterator jetIter = jet_ptrsAK8.begin();
          jetIter != jet_ptrsAK8.end(); ++jetIter ) {
            for ( unsigned int bjetCandidate = 0; bjetCandidate < bToLoop; bjetCandidate++ ) { // cleanedJets.size()
                unfittedHadTopP4 = (*jetIter)->p4() + (*cleanedJets[bjetCandidate]).p4();
                if ( unfittedHadTopP4.M() > 95 && unfittedHadTopP4.M() < 225 ) passJetMassSel = true;
                selBJet = (*cleanedJets[bjetCandidate]).p4();
                if((*jetIter)->subJet1() && (*jetIter)->subJet2()) {
                selWJet1 = (*jetIter)->subJet1()->p4();
                selWJet2 = (*jetIter)->subJet2()->p4();

                std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
                  selBJet, selWJet1, selWJet2,
                  genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
                  kGenTop, typeTop, (*jetIter)->p4()
                );
                std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
                  selBJet, selWJet1, selWJet2,
                  genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
                  kGenAntiTop, typeTop, (*jetIter)->p4()
                );

                isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
                fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
                b_isGenMatched = (genMatchingTop[kGenMatchedBJet] || genMatchingAntiTop[kGenMatchedBJet]);
                wj1_isGenMatched = (genMatchingTop[kGenMatchedWJet1] || genMatchingAntiTop[kGenMatchedWJet1]);
                wj2_isGenMatched = (genMatchingTop[kGenMatchedWJet2] || genMatchingAntiTop[kGenMatchedWJet2]);
                if (btag_order[bjetCandidate] > cutJetCombo) continue;
                if (isGenMatched) {hadtruth2++; cat2 = true;}

                double minT;
                double minAntiT;
                if (loopB) {
                  minT = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2])) + std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                  minAntiT = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2])) + std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                } else {
                  minT = deltaR(selBJet, genVar[kGenTopB]);
                  minAntiT = deltaR(selBJet, genVarAnti[kGenTopB]);
                }

                if ( minT < minAntiT ){
                  genFatPtAll = genVar[kGenTopW].pt();
                  genFatEtaAll = genVar[kGenTopW].pt();
                  drT_gen = deltaR(unfittedHadTopP4, genVar[kGenTop]);
                  drB_gen = deltaR(selBJet, genVar[kGenTopB]);
                  drWj1_gen = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2]));
                  drWj2_gen = std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                  etaB_gen = genVar[kGenTopB].eta();
                  etaWj1_gen = genVar[kGenTopWj1].eta();
                  etaWj2_gen = genVar[kGenTopWj2].eta();
                  ptB_gen = genVar[kGenTopB].pt();
                  ptWj1_gen = genVar[kGenTopWj1].pt();
                  ptWj2_gen = genVar[kGenTopWj2].pt();
                  drb_wj1_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj1]);
                  drb_wj2_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj2]);
                  drwj1_wj2_gen = deltaR(genVar[kGenTopWj1], genVar[kGenTopWj2]);
                  drW_gen = deltaR(unfittedHadTopP4 , genVar[kGenTopW]);
                } else {
                  genFatPtAll = genVarAnti[kGenTopW].pt();
                  genFatEtaAll = genVarAnti[kGenTopW].pt();
                  drT_gen = deltaR(unfittedHadTopP4, genVarAnti[kGenTop]);
                  drB_gen = deltaR(selBJet, genVarAnti[kGenTopB]);
                  drWj1_gen = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2]));
                  drWj2_gen = std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                  etaB_gen = genVarAnti[kGenTopB].eta();
                  etaWj1_gen = genVarAnti[kGenTopWj1].eta();
                  etaWj2_gen = genVarAnti[kGenTopWj2].eta();
                  ptB_gen = genVarAnti[kGenTopB].pt();
                  ptWj1_gen = genVarAnti[kGenTopWj1].pt();
                  ptWj2_gen = genVarAnti[kGenTopWj2].pt();
                  drb_wj1_gen= deltaR(genVarAnti[kGenTopB], genVarAnti[kGenTopWj1]);
                  drb_wj2_gen = deltaR(genVarAnti[kGenTopB], genVar[kGenTopWj2]);
                  drwj1_wj2_gen = deltaR(genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2]);
                  drW_gen = deltaR(unfittedHadTopP4 , genVarAnti[kGenTopW]);
                }

                if ( bdt_filler ) {
                  (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2);
                  const std::map<std::string, double>& mvaInputs =  hadTopTaggerFill->mvaInputs();
                  for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
                    mvaInput != mvaInputs.end(); ++mvaInput ) {
                    bdt_filler->operator()(mvaInput->first, mvaInput->second);
                  }
                  bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
                  ("typeTop",              typeTop)
                  ("tau32Top",             -1.)
                  ("massTop",              unfittedHadTopP4.mass())
                  ("tau21W",               (*jetIter)->tau2()/(*jetIter)->tau1())
                  ("massW_SD",             (*jetIter)->msoftdrop())
                  ("btagDisc",             (*cleanedJets[bjetCandidate]).BtagCSV())
                  ("qg_Wj1",                -1.)
                  ("qg_Wj2",                -1.)
                  ("genFatPtAll", genFatPtAll)
                  ("genFatEtaAll",         std::fabs(genFatEtaAll))
                  ("drT_gen",       drT_gen)
                  ("drT_genTriplet",  drT_genTriplet)
                  ("drT_genJ_max", drT_genJ_max)
                  ("drB_gen", drB_gen)
                  ("drW_gen", drW_gen)
                  ("drWj1_gen", drWj1_gen)
                  ("drWj2_gen", drWj2_gen)
                  ("etaB_gen", etaB_gen)
                  ("etaWj1_gen", etaWj1_gen)
                  ("etaWj2_gen", etaWj2_gen)
                  ("ptB_gen", ptB_gen)
                  ("ptWj1_gen", ptWj1_gen)
                  ("ptWj2_gen", ptWj2_gen)
                  ("dr_b_wj1", deltaR(selBJet, selWJet1))
                  ("dr_b_wj2", deltaR(selBJet, selWJet2))
                  ("dr_wj1_wj2", deltaR(selBJet, selWJet2))
                  ("dr_b_wj1_gen", drb_wj1_gen)
                  ("dr_b_wj2_gen", drb_wj2_gen)
                  ("dr_wj1_wj2_gen", drwj1_wj2_gen)
                  ("collectionSize",       jet_ptrsAK8.size())
                  ("bjet_tag_position",    btag_order[bjetCandidate])
                  ("bWj1Wj2_isGenMatched", isGenMatched)
                  ("fatjet_isGenMatched",  fatjet_isGenMatched)
                  ("b_isGenMatched",       b_isGenMatched)
                  ("Wj1_isGenMatched", wj1_isGenMatched)
                  ("Wj2_isGenMatched", wj2_isGenMatched)
                  ("counter",        analyzedEntries)
                  ("passJetSel", passJetSel)
                  ("passJetMassSel", passJetMassSel)
                  ("HTTv2_area", HTTv2_area)
                  ("HTTv2_Ropt", HTTv2_Ropt)
                  ("HTTv2_RoptCalc", HTTv2_RoptCalc)
                  ("genTopMassFromW", genTopMassFromW )
                  ("genTopMassFromWj", genTopMassFromWj )
                  ("genWMassFromWj", genWMassFromWj )
                  ("genAntiTopMassFromW", genAntiTopMassFromW )
                  ("genAntiTopMassFromWj", genAntiTopMassFromWj )
                  ("genAntiWMassFromWj", genAntiWMassFromWj )
                  ("genWMass", genWMass)
                  ("genAntiWMass", genAntiWMass)
                  ("genWeight", eventInfo.genWeight) // to count nevents with neg weights
                  ("weight_fakeRate_3L", weight_fakeRate_3L)
                  ("weight_fakeRate_4L", weight_fakeRate_4L)
                  ("weight_fakeRate_2L", weight_fakeRate_2L)
                  ("passHadGenHadW", passHadGenHadW)
                  ("pass_3l", pass_3l)
                  ("pass_2lss", pass_2lss)
                  ("pass_1l_2tau", pass_1l_2tau)
                  ("pass_2lss_1tau", pass_2lss_1tau)
                  ("pass_2los_1tau", pass_2los_1tau)
                      .fill();
                }
              } else { std::cout<<" type2 akt8 did not had subjets "<<std::endl; continue;}
            }
          } // end typeTop == 2 ak8 loop
        } //end if (inAK12) //else if (typeTop == 3) {
        } // end if enough cleanJets.size()
          // store b-tag classification
          //std::cout<<std::endl;
          //std::cout<<"btag ordering  ";
          //for (auto i: btag_order_selJets) std::cout << i << " ";
          //std::cout<<" typeTop = "<<typeTop<<" collectionSize "<< collectionSize <<std::endl;
          if (selJets.size() > 2) {
          std::vector<double> btag_disc = getBdiscr(selJets);
          auto btag_order_selJets = calRank(btag_disc);
          typeTop = 3;
          //std::cout<<" typeTop = "<<typeTop<<std::endl;
          countResolved++;
          for ( unsigned int bjetCandidate = 0; bjetCandidate < selJets.size(); bjetCandidate++ )  {
            for ( std::vector<const RecoJet*>::const_iterator selWJet1Candidate = selJets.begin();
              selWJet1Candidate != selJets.end(); ++selWJet1Candidate ) {
               if ( (*selWJet1Candidate)->pt() == (*selJets[bjetCandidate]).pt() ) continue;
               for ( std::vector<const RecoJet*>::const_iterator selWJet2Candidate = selWJet1Candidate + 1;
                 selWJet2Candidate != selJets.end(); ++selWJet2Candidate ) {
                  //std::cout<<" bjetCandidate = "<<bjetCandidate<<std::endl;
                  if ( (*selWJet2Candidate)->pt() == (*selJets[bjetCandidate]).pt() ) continue;
                  if ( (*selWJet2Candidate)->pt() == (*selWJet1Candidate)->pt() ) continue;
                  selBJet = (*selJets[bjetCandidate]).p4();
                  selWJet1 = (*selWJet1Candidate)->p4();
                  selWJet2 = (*selWJet2Candidate)->p4();

                  std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
                    selBJet, selWJet1, selWJet2,
                    genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
                    kGenTop
                  );
                  std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
                    selBJet, selWJet1, selWJet2,
                    genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
                    kGenAntiTop
                  );

                  isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
                  fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
                  b_isGenMatched = (genMatchingTop[kGenMatchedBJet] || genMatchingAntiTop[kGenMatchedBJet]);
                  wj1_isGenMatched = (genMatchingTop[kGenMatchedWJet1] || genMatchingAntiTop[kGenMatchedWJet1]);
                  wj2_isGenMatched = (genMatchingTop[kGenMatchedWJet2] || genMatchingAntiTop[kGenMatchedWJet2]);
                  //std::cout<<" done loading flags "<<std::endl;
                  if (btag_order_selJets[bjetCandidate] > cutJetCombo) continue;
                  if (isGenMatched) {hadtruth3++; cat3 = true;}
                  //std::cout<<"btag position = "<< btag_order[bjetCandidate] <<std::endl;

                  // debug gen-matching
                  std::map<int, Particle::LorentzVector> genVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenTop);
                  std::map<int, Particle::LorentzVector> genVarAnti = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop);
                  double minT = deltaR(selBJet, genVar[kGenTopB]) + std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2])) + std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                  double minAntiT = deltaR(selBJet, genVarAnti[kGenTopB]) + std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2])) + std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                  if ( minT < minAntiT ){
                    genFatPtAll = genVar[kGenTopW].pt();
                    genFatEtaAll = genVar[kGenTopW].pt();
                    drB_gen = deltaR(selBJet, genVar[kGenTopB]);
                    drWj1_gen = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2]));
                    drWj2_gen = std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                    etaB_gen = genVar[kGenTopB].eta();
                    etaWj1_gen = genVar[kGenTopWj1].eta();
                    etaWj2_gen = genVar[kGenTopWj2].eta();
                    ptB_gen = genVar[kGenTopB].pt();
                    ptWj1_gen = genVar[kGenTopWj1].pt();
                    ptWj2_gen = genVar[kGenTopWj2].pt();
                    drb_wj1_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj1]);
                    drb_wj2_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj2]);
                    drwj1_wj2_gen = deltaR(genVar[kGenTopWj1], genVar[kGenTopWj2]);
                  } else {
                    genFatPtAll = genVarAnti[kGenTopW].pt();
                    genFatEtaAll = genVarAnti[kGenTopW].pt();
                    drB_gen = deltaR(selBJet, genVarAnti[kGenTopB]);
                    drWj1_gen = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2]));
                    drWj2_gen = std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                    etaB_gen = genVarAnti[kGenTopB].eta();
                    etaWj1_gen = genVarAnti[kGenTopWj1].eta();
                    etaWj2_gen = genVarAnti[kGenTopWj2].eta();
                    ptB_gen = genVarAnti[kGenTopB].pt();
                    ptWj1_gen = genVarAnti[kGenTopWj1].pt();
                    ptWj2_gen = genVarAnti[kGenTopWj2].pt();
                    drb_wj1_gen= deltaR(genVarAnti[kGenTopB], genVarAnti[kGenTopWj1]);
                    drb_wj2_gen = deltaR(genVarAnti[kGenTopB], genVar[kGenTopWj2]);
                    drwj1_wj2_gen = deltaR(genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2]);
                  }

                  unfittedHadTopP4 = selBJet+selWJet1+selWJet2;
                  if ( unfittedHadTopP4.M() > 95 && unfittedHadTopP4.M() < 225 ) passJetMassSel = true;

                  if ( bdt_filler ) {
                    (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2);
                    const std::map<std::string, double>& mvaInputs =  hadTopTaggerFill->mvaInputs();
                    for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
                      mvaInput != mvaInputs.end(); ++mvaInput ) {
                      bdt_filler->operator()(mvaInput->first, mvaInput->second);
                    }
                    //std::cout<<" pass fill kin "<<std::endl;
                  bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
                  ("typeTop",              typeTop)
                  ("tau32Top",              -1.)
                  ("massTop",              -1.) // should be the one calculated with the groomed jet
                  ("tau21W",                -1.)
                  ("massW_SD",             -1.) // maybe add the kinfitted mass here
                  ("btagDisc",             (*selJets[bjetCandidate]).BtagCSV())
                  ("qg_Wj1",               (*selWJet1Candidate)->QGDiscr())
                  ("qg_Wj2",               (*selWJet2Candidate)->QGDiscr())
                  ("genFatPtAll", genFatPtAll)
                  ("genFatEtaAll",         std::fabs(genFatEtaAll))
                  ("drT_gen",       drT_gen)
                  ("drT_genTriplet",  drT_genTriplet)
                  ("drT_genJ_max", drT_genJ_max)
                  ("drB_gen", drB_gen)
                  ("drW_gen", drW_gen)
                  ("drWj1_gen", drWj1_gen)
                  ("drWj2_gen", drWj2_gen)
                  ("etaB_gen", etaB_gen)
                  ("etaWj1_gen", etaWj1_gen)
                  ("etaWj2_gen", etaWj2_gen)
                  ("ptB_gen", ptB_gen)
                  ("ptWj1_gen", ptWj1_gen)
                  ("ptWj2_gen", ptWj2_gen)
                  ("dr_b_wj1", deltaR(selBJet, selWJet1))
                  ("dr_b_wj2", deltaR(selBJet, selWJet2))
                  ("dr_wj1_wj2", deltaR(selBJet, selWJet2))
                  ("dr_b_wj1_gen", drb_wj1_gen)
                  ("dr_b_wj2_gen", drb_wj2_gen)
                  ("dr_wj1_wj2_gen", drwj1_wj2_gen)
                  ("collectionSize",       selJets.size())
                  ("bjet_tag_position",    btag_order_selJets[bjetCandidate])
                  ("bWj1Wj2_isGenMatched", isGenMatched)
                  ("fatjet_isGenMatched",  false)
                  ("b_isGenMatched",       b_isGenMatched)
                  ("Wj1_isGenMatched", wj1_isGenMatched)
                  ("Wj2_isGenMatched", wj2_isGenMatched)
                  ("counter",         analyzedEntries)
                  ("passJetSel", passJetSel)
                  ("passJetMassSel", passJetMassSel)
                  ("HTTv2_area", HTTv2_area)
                  ("HTTv2_Ropt", HTTv2_Ropt)
                  ("HTTv2_RoptCalc", HTTv2_RoptCalc)
                  ("genTopMassFromW", genTopMassFromW )
                  ("genTopMassFromWj", genTopMassFromWj )
                  ("genWMassFromWj", genWMassFromWj )
                  ("genAntiTopMassFromW", genAntiTopMassFromW )
                  ("genAntiTopMassFromWj", genAntiTopMassFromWj )
                  ("genAntiWMassFromWj", genAntiWMassFromWj )
                  ("genWMass", genWMass)
                  ("genAntiWMass", genAntiWMass)
                  ("genWeight", eventInfo.genWeight) // to count nevents with neg weights
                  ("weight_fakeRate_3L", weight_fakeRate_3L)
                  ("weight_fakeRate_4L", weight_fakeRate_4L)
                  ("weight_fakeRate_2L", weight_fakeRate_2L)
                  ("passHadGenHadW", passHadGenHadW)
                  ("pass_3l", pass_3l)
                  ("pass_2lss", pass_2lss)
                  ("pass_1l_2tau", pass_1l_2tau)
                  ("pass_2lss_1tau", pass_2lss_1tau)
                  ("pass_2los_1tau", pass_2los_1tau)
                      .fill();
                 }
              }
            }
          } // end typeTop == 3 loop
        } // end if has 3 jets
      //<< "Does not fall in any category " << " !!\n";
  //}

		++selectedEntries;
    //selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
    if (cat1 && cat2 && !cat3) ca1_cat2++;
    if (cat2 && cat3 && !cat1) cat2_cat3++;
    if (cat3 && cat1 && !cat2) cat3_cat1++ ;
    if (cat3 && cat2 && cat1) cat3_cat2_cat1++;
  }
  //if(bdt_filler) bdt_filler->write();

  std::cout << "AK8 separation = " << countFatTop << " " << countFatAK8 << " " << countResolved<< " " << countFatTop+countFatAK8+countResolved<<std::endl;
  std::cout << "AK12 separation = " << countFatTop << " " << countFatAK12 << " " << countResolved<< " " << countFatTop+countFatAK12+countResolved<<std::endl;
  std::cout << "truth counters = "<<hadtruth1 << " "<<hadtruth2 << " "<<hadtruth3 << std::endl;
  std::cout << "overlaps = "<< ca1_cat2 << " "<< cat2_cat3 << " "<< cat3_cat1 << " " << cat3_cat2_cat1 << std::endl;

  std::cout << "HTTv2 > 0  " << countFatTop <<std::endl;
  std::cout << "+ closest genTop > 200 " << countFatTopPt200 << " " << countFatTopbmatch << " " << countFatTopWj1match << " " << countFatTopWj2match <<std::endl;

  std::cout << countFatWpt130 << "fatW  " << countFatWjets << " " << " " << countFatW <<std::endl;


  std::cout <<std::endl<< "pass_3l  " << count_pass_3l <<std::endl;
  std::cout << "pass_2lss  " << count_pass_2lss <<std::endl;
  std::cout << "pass_1l_2tau  " << count_pass_1l_2tau <<std::endl;
  std::cout << "pass_2lss_1tau  " << count_pass_2lss_1tau <<std::endl;
  std::cout << "2los_1tau  " << count_pass_2los_1tau <<std::endl;

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n"
            << "cut-flow table" << std::endl;

  if ( selEventsFile_summary ) {
    (*selEventsFile_summary) << "AK8 separation = " << countFatTop << " " << countFatAK8 << " " << countResolved<< " " << countFatTop+countFatAK8+countResolved<< '\n';
    (*selEventsFile_summary) << "AK12 separation = " << countFatTop << " " << countFatAK12 << " " << countResolved<< " " << countFatTop+countFatAK12+countResolved<< '\n';
    (*selEventsFile_summary) << "truth counters = "<<hadtruth1 << " "<<hadtruth2 << " "<<hadtruth3 << '\n';
    (*selEventsFile_summary) << "overlaps = "<< ca1_cat2 << " "<< cat2_cat3 << " "<< cat3_cat1 << " " << cat3_cat2_cat1 <<  '\n';

    (*selEventsFile_summary) << "HTTv2 > 0  " << countFatTop << '\n';
    (*selEventsFile_summary) << "+ closest genTop > 200 " << countFatTopPt200 << " " << countFatTopbmatch << " " << countFatTopWj1match << " " << countFatTopWj2match << '\n';

    (*selEventsFile_summary) << countFatWpt130 << "fatW  " << countFatWjets << " " << " " << countFatW << '\n';


    (*selEventsFile_summary) << '\n' << "pass_3l  " << count_pass_3l << '\n';
    (*selEventsFile_summary) << "pass_2lss  " << count_pass_2lss << '\n';
    (*selEventsFile_summary) << "pass_1l_2tau  " << count_pass_1l_2tau << '\n';
    (*selEventsFile_summary) << "pass_2lss_1tau  " << count_pass_2lss_1tau << '\n';
    (*selEventsFile_summary) << "2los_1tau  " << count_pass_2los_1tau << '\n';

    (*selEventsFile_summary) << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
              << " (limited by " << maxEvents << ") processed in "
              << inputTree -> getProcessedFileCount() << " file(s) (out of "
              << inputTree -> getFileCount() << ")\n"
              << " analyzed = " << analyzedEntries << '\n'
              << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n"
              << '\n';

    // Cut flow 3l = 542 427 405 374 248 0 0
    // Cut flow 3l = 542 427 405 374 248 248 0 202
    (*selEventsFile_summary) << "Cut flow 3l = "
              << pass_3l_0
              << " " << pass_3l_1
              << " " << pass_3l_2
              << " " << pass_3l_3
              << " " << pass_3l_4
              << " " << pass_3l_5
              << " " << pass_3l_6
              << " " << pass_3l_7
              << '\n';

  }
  std::cout << "selEventsFileName_output_summary = " << selEventsFileName_output_summary << std::endl;

  delete jetReader;
  delete genJetReader;
  delete lheInfoReader;
  delete hadTopTaggerFill;
  delete inputTree;
  std::cout << "delete 1"  << std::endl;

  //delete dataToMCcorrectionInterface;

  delete leptonFakeRateInterface;
  delete jetToTauFakeRateInterface;

  delete run_lumi_eventSelector;

  delete selEventsFile;
  delete selEventsFile_summary;
  delete selEventsFile_1l_2tau;
  delete selEventsFile_2lss_1tau;
  delete selEventsFile_2los_1tau;
  delete selEventsFile_2lss;
  delete selEventsFile_3l;

  delete bdt_filler;
  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete metReader;
  delete metFilterReader;

  //delete genLeptonReader;
  //delete genHadTauReader;
  //delete genJetReader;
  //delete lheInfoReader;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_3e);
  hltPaths_delete(triggers_3mu);
  hltPaths_delete(triggers_1e2mu);
  hltPaths_delete(triggers_2e1mu);

  //hltPaths_delete(triggers_2tau);
  hltPaths_delete(triggers_1e1tau);
  hltPaths_delete(triggers_1mu1tau);

  clock.Show("analyze_hadTopTagger");

  return EXIT_SUCCESS;
}
