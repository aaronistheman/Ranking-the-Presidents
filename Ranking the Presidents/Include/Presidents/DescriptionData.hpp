#ifndef PRESIDENTS_DESCRIPTIONDATA_HPP
#define PRESIDENTS_DESCRIPTIONDATA_HPP

#include <string>


// Contains the description data for a president.
// For use in DescriptionsState.
struct DescriptionData
{
  enum Category 
  {
    Excellent,
    Good,
    Average,
    Poor,
    Bad
  };

  int           number;
  std::string   name;
  int           rank;
  Category      category;
};

#endif // PRESIDENTS_DESCRIPTIONDATA_HPP