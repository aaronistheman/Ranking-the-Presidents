#include <Presidents/DataTables.hpp>


std::vector<RankingData> initializeRankingData()
{
  std::vector<RankingData> data(2);

  data[0].number = 1;
  data[0].name = "George Washington";
  data[0].rank = 7;
  data[0].peaceRating = 16;
  data[0].prosperityRating = 12;
  data[0].libertyRating = 20;
  data[0].totalScore = data[0].peaceRating + data[0].prosperityRating
                     + data[0].libertyRating;

  data[1].number = 2;
  data[1].name = "John Adams";
  data[1].rank = 22;
  data[1].peaceRating = 16;
  data[1].prosperityRating = 9;
  data[1].libertyRating = 3;
  data[1].totalScore = data[1].peaceRating + data[1].prosperityRating
                     + data[1].libertyRating;

  return data;
}