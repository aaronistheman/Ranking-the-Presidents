#include <Presidents/DataTables.hpp>


std::vector<RankingData> initializeRankingData()
{
  std::vector<RankingData> data(2);

  data[0].number = 1;
  data[0].name = "George Washington";
  data[0].rank = 7;

  data[1].number = 2;
  data[1].name = "John Adams";
  data[1].rank = 22;

  return data;
}