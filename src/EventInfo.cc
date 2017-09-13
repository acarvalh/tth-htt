#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys

#include <cmath> // std::fabs()

#define EPS 1E-2

const std::map<std::string, GENHIGGSDECAYMODE_TYPE> EventInfo::decayMode_idString =
{
  { "ttH_hww", static_cast<GENHIGGSDECAYMODE_TYPE>(24) },
  { "ttH_hzz", static_cast<GENHIGGSDECAYMODE_TYPE>(23) },
  { "ttH_htt", static_cast<GENHIGGSDECAYMODE_TYPE>(15) }
};

EventInfo::EventInfo()
  : EventInfo(false, false)
{}

EventInfo::EventInfo(bool is_signal,
                     bool is_mc)
  : run(0)
  , lumi(0)
  , event(0)
  , genHiggsDecayMode(-1)
  , genWeight(1.)
  , pileupWeight(1.)
  , is_signal_(is_signal)
  , is_mc_(is_mc)
{}

bool
EventInfo::is_signal() const
{
  return is_signal_;
}

bool
EventInfo::is_mc() const
{
  return is_mc_;
}

bool
EventInfo::is_initialized() const
{
  return run != 0 && lumi != 0 && event != 0;
}

std::string
EventInfo::getDecayModeString() const
{
  if(! is_signal())
  {
    throw cms::Exception("EventInfo")
      << "The event " << *this << " is not a signal event => request "
         "for a decay mode as a string is not applicable\n";
  }
  for(const auto & kv: EventInfo::decayMode_idString)
  {
    if(std::fabs(genHiggsDecayMode - kv.second) < EPS)
    {
      return kv.first;
    }
  }
  return ""; // unrecognizable decay mode
}

std::vector<std::string>
EventInfo::getDecayModes()
{
  std::vector<std::string> decayModes;
  decayModes.reserve(EventInfo::decayMode_idString.size());
  boost::copy(
    EventInfo::decayMode_idString | boost::adaptors::map_keys, std::back_inserter(decayModes)
  );
  return decayModes;
}

std::ostream &
operator<<(std::ostream & os,
           const EventInfo & info)
{
  os << info.run << ':' << info.lumi << ':' << info.event;
  return os;
}