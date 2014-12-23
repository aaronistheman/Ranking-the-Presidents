#ifndef PRESIDENTS_RANKINGDATA_HPP
#define PRESIDENTS_RANKINGDATA_HPP

#include <string>


// Contains the rankings data for a president.
// For use in RankingsState.
struct RankingData
{
  int number;
  std::string name;
  int rank;
  int peaceRating;
  int prosperityRating;
  int libertyRating;
  int totalScore;
};

#endif // PRESIDENTS_RANKINGDATA_HPP