#ifndef PRESIDENTS_RANKINGDATA_HPP
#define PRESIDENTS_RANKINGDATA_HPP

#include <string>


// Contains the rankings data for a president.
// For use in RankingsState.
struct RankingData
{
  int           number;
  std::string   name;
  int           rank;
};

#endif // PRESIDENTS_RANKINGDATA_HPP