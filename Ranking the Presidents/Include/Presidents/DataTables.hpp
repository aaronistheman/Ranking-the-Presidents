#ifndef PRESIDENTS_DATATABLES_HPP
#define PRESIDENTS_DATATABLES_HPP

#include <Presidents/DescriptionData.hpp>
#include <Presidents/RankingData.hpp>

#include <vector>

// Each of these functions closes the file it reads from
std::vector<DescriptionData> initializeDescriptionData();
std::vector<RankingData> initializeRankingData();

#endif // PRESIDENTS_DATATABLES_HPP