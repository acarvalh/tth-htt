#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_1tau_h

/** \class EvtHistManager_2lss_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 2lss_1tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_2lss_1tau.h" // MEMOutput_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

class EvtHistManager_2lss_1tau
  : public HistManagerBase
{
 public:
  EvtHistManager_2lss_1tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_2lss_1tau() {}

  void bookHistograms(TFileDirectory& dir);
  void integralHistograms(TFileDirectory& dir);
  void fillHistograms(
    std::vector<const RecoElectron*>::size_type numElectrons,
    std::vector<const RecoMuon*>::size_type numMuons,
    std::vector<const RecoHadTau*>::size_type numHadTaus,
    std::vector<const RecoJet*>::size_type numJets,
    std::vector<const RecoJet*>::size_type numBJets_loose,
    std::vector<const RecoJet*>::size_type numBJets_medium,
    double evtWeight,
    //
    double mvaOutput_2lss_ttV,
    double mvaOutput_2lss_ttbar,
    double mvaDiscr_2lss,
    double mvaOutput_2lss_1tau_ttV,
    double mvaOutput_2lss_1tau_ttbar,
    double mvaDiscr_2lss_1tau,
    double mvaOutput_2lss_1tau_ttV_wMEM,
    double mvaOutput_2lss_1tau_ttbar_wMEM,
    double mvaDiscr_2lss_1tau_wMEM,
    double mvaOutput_Hj_tagger,
    double mvaOutput_Hjj_tagger,
    double mTauTauVis1,
    double mTauTauVis2,
    double memOutput_LR, //const MEMOutput_2lss_1tau* memOutput_2lss_1tau,
    double memDiscr,
    // XGB training 1D
    double mvaOutput_2lss_oldVarA_tt,
    double mvaOutput_2lss_oldVarA_ttV,
    double mvaOutput_2lss_noHTT_tt,
    double mvaOutput_2lss_noHTT_ttV,
    double mvaOutput_2lss_HTT_tt,
    double mvaOutput_2lss_HTTMEM_tt,
    double mvaOutput_2lss_HTTMEM_ttV,
    double mvaOutput_2lss_HTTMEM_SUM_M,
    double mvaOutput_2lss_HTTMEM_SUM_T,
    double mvaOutput_2lss_HTT_LepID_tt,
    double mvaOutput_2lss_HTTMEM_1B_M,
    double mvaOutput_2lss_HTTMEM_1B_T,
    double mvaOutput_2lss_HTT_1B_M,
    double mvaOutput_2lss_HTT_1B_T,
    double mvaOutput_2lss_noHTT_1B_M,
    double mvaOutput_2lss_noHTT_1B_T,
    double mvaOutput_2lss_oldVarA_1B,
    double mvaOutput_2lss_oldVarA_2MEM,
    double mvaOutput_2lss_noHTT_2MEM,
    double mvaOutput_2lss_noHTT_2HTT
    );

  const TH1* getHistogram_EventCounter() const { return histogram_EventCounter_; }

 private:
  int era_;

  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH2* histogram_numBJets_loose_vs_numJets_;  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  TH2* histogram_numBJets_medium_vs_numJets_; //     to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)

  TH1* histogram_mvaOutput_2lss_ttV_;
  TH1* histogram_mvaOutput_2lss_ttbar_;
  TH1* histogram_mvaDiscr_2lss_;

  TH1* histogram_mvaOutput_2lss_1tau_ttV_;
  TH1* histogram_mvaOutput_2lss_1tau_ttbar_;
  TH1* histogram_mvaDiscr_2lss_1tau_;
  TH1* histogram_mvaOutput_2lss_1tau_ttV_wMEM_;
  TH1* histogram_mvaOutput_2lss_1tau_ttbar_wMEM_;
  TH1* histogram_mvaDiscr_2lss_1tau_wMEM_;

  TH1* histogram_mvaOutput_Hj_tagger_;
  TH1* histogram_mvaOutput_Hjj_tagger_;

  TH1* histogram_mTauTauVis1_;
  TH1* histogram_mTauTauVis_;
  TH1* histogram_mTauTauVis2_;
  TH1* histogram_memOutput_LR_;
  TH1* histogram_memDiscr_;

  TH1* histogram_EventCounter_;

  TH1* histogram_mvaOutput_2lss_oldVarA_tt_;
  TH1* histogram_mvaOutput_2lss_oldVarA_ttV_;
  TH1* histogram_mvaOutput_2lss_noHTT_tt_;
  TH1* histogram_mvaOutput_2lss_noHTT_ttV_;
  TH1* histogram_mvaOutput_2lss_HTT_tt_;
  TH1* histogram_mvaOutput_2lss_HTTMEM_tt_;
  TH1* histogram_mvaOutput_2lss_HTTMEM_ttV_;
  TH1* histogram_mvaOutput_2lss_HTT_LepID_tt_;

  //const int & nstart =2;
  //const int & ntarget =6;
  //TH1* hist_HTT_2D_[2][6];
  //TH1* hist_noHTT_2D_[2][6];
  //TH1* hist_HTTMEM_2D_[2][6];
  //TH1* hist_oldVarA_2D_[2][6];

  TH1* histogram_mvaOutput_2lss_HTTMEM_SUM_T_;
  TH1* histogram_mvaOutput_2lss_HTTMEM_SUM_M_;

  TH1* histogram_mvaOutput_2lss_HTTMEM_1B_T_;
  TH1* histogram_mvaOutput_2lss_HTTMEM_1B_M_;

  TH1* histogram_mvaOutput_2lss_HTT_1B_T_;
  TH1* histogram_mvaOutput_2lss_HTT_1B_M_;

  TH1* histogram_mvaOutput_2lss_noHTT_1B_T_;
  TH1* histogram_mvaOutput_2lss_noHTT_1B_M_;

  TH1* histogram_mvaOutput_2lss_oldVarA_1B_;

  TH1* histogram_mvaOutput_2lss_oldVarA_2MEM_;
  TH1* histogram_mvaOutput_2lss_noHTT_2MEM_;
  TH1* histogram_mvaOutput_2lss_noHTT_2HTT_;

  std::vector<TH1*> hist_oldVarA_2D_;
  std::vector<TH1*> hist_HTT_2D_;
  std::vector<TH1*> hist_HTTMEM_2D_;
  std::vector<TH1*> hist_noHTT_2D_;

  std::vector<TH1*> histograms_;
};

#endif
