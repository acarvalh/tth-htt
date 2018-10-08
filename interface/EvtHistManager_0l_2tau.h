#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_0l_2tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_0l_2tau_h

/** \class EvtHistManager_0l_2tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 0l_2tau category
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_0l_2tau
  : public HistManagerBase
{
public:
  EvtHistManager_0l_2tau(const edm::ParameterSet & cfg);
  ~EvtHistManager_0l_2tau() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(int numElectrons,
                 int numMuons,
                 int numHadTaus,
                 int numJets,
                 int numBJets_loose,
                 int numBJets_medium,
                 int num_HTTv2,
                 double mvaOutput_0l_2tau_ttbar,
		 double mvaOutput_0l_2tau_HTT_tt,
		 double mvaOutput_0l_2tau_HTT_ttv,
		 double mvaOutput_0l_2tau_HTT_sum,
		 float mvaDiscr_0l_2tau_HTT,
     //
     double mva_oldVar, double mva_Updated,
     double mva_Boosted_AK8_noISO,  double mva_Boosted_AK8,
     double mva_Boosted_AK12_noISO, double mva_Boosted_AK12,
     double mva_Boosted_AK12_basic, double mva_Boosted_AK8_basic,
     //
                 double mTauTauVis,
                 double mTauTau,
                 double evtWeight);

  const TH1 *
  getHistogram_EventCounter() const;

private:
  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numHTTv2_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  // CV: used to check loss in signal efficiency in case events with
  // high jet and b-jet multiplicity are vetoed to avoid overlap with ttH, H->bb analysis
  // (alternative: ttH, H->bb analysis adds hadronic tau veto)
  TH2 * histogram_numBJets_loose_vs_numJets_;
  TH2 * histogram_numBJets_medium_vs_numJets_;

  TH1 * histogram_mvaOutput_0l_2tau_ttbar_;

  TH1 * histogram_mvaOutput_0l_2tau_HTT_tt_;
  TH1 * histogram_mvaOutput_0l_2tau_HTT_ttv_;
  TH1 * histogram_mvaOutput_0l_2tau_HTT_sum_;
  TH1 * histogram_mvaDiscr_0l_2tau_HTT_;

  TH1 * histogram_mva_oldVar_;
  TH1 * histogram_mva_Updated_;
  TH1 * histogram_mva_Boosted_AK8_noISO_;
  TH1 * histogram_mva_Boosted_AK8_;
  TH1 * histogram_mva_Boosted_AK12_noISO_;
  TH1 * histogram_mva_Boosted_AK12_;
  TH1 * histogram_mva_Boosted_AK12_basic_;
  TH1 * histogram_mva_Boosted_AK8_basic_;


  TH1 * histogram_mTauTauVis_;
  TH1 * histogram_mTauTau_;

  TH1 * histogram_EventCounter_;
};

#endif
