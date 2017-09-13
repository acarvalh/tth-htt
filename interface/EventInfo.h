#ifndef EventInfo_H
#define EventInfo_H

#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // *_TYPE, *_KEY

#include <iostream> // std::ostream
#include <string> // std::string
#include <map> // std::map<,>

class EventInfo
{
public:
  EventInfo();
  EventInfo(bool is_signal,
            bool is_mc);

  RUN_TYPE               run;               ///< run number
  LUMI_TYPE              lumi;              ///< luminosity
  EVT_TYPE               event;             ///< event number
  GENHIGGSDECAYMODE_TYPE genHiggsDecayMode; ///< Higgs decay mode (only if MC signal)
  GENWEIGHT_TYPE         genWeight;         ///< generator-level weight (only if MC)
  PUWEIGHT_TYPE          pileupWeight;      ///< pile-up weight (only if MC)

  bool
  is_signal() const;

  bool
  is_mc() const;

  bool
  is_initialized() const;

  std::string
  getDecayModeString() const;

  static std::vector<std::string>
  getDecayModes();

  friend std::ostream &
  operator<<(std::ostream & os,
             const EventInfo & info);

private:
  const bool is_signal_;
  const bool is_mc_;

  static const std::map<std::string, GENHIGGSDECAYMODE_TYPE> decayMode_idString;
};

#endif // EventInfo_H