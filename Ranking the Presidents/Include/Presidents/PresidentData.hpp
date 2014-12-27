#ifndef PRESIDENTS_PRESIDENTDATA_HPP
#define PRESIDENTS_PRESIDENTDATA_HPP

#include <string>


struct PresidentData
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

// For reading a president's category from the file
std::ifstream& operator>>(std::ifstream& ist, 
                          PresidentData::Category& category);

#endif // PRESIDENTS_DESCRIPTIONDATA_HPP