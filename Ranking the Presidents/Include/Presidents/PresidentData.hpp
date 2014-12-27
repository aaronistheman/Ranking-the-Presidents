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

  enum Party
  {
    Federalist,
    Democrat,
    Whig,
    Republican
  };

  int           number;
  std::string   name;
  int           rank;
  Category      category;
  Party         party;
};

// For reading a president's category from the file
std::ifstream& operator>>(std::ifstream& ist, 
                          PresidentData::Category& category);

// For reading a president's party from the file
std::ifstream& operator>>(std::ifstream& ist, PresidentData::Party& party);

#endif // PRESIDENTS_DESCRIPTIONDATA_HPP