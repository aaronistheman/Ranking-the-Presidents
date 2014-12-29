#include <Presidents/PresidentData.hpp>

#include <cassert>
#include <fstream>


void PresidentData::Reset()
{
  number = 0;
  name = "";
  rank = 0;
  category = PresidentData::NoCategory;
  party = PresidentData::NoParty;
}

std::ifstream& operator>>(std::ifstream& ist, 
                          PresidentData::Category& category)
{
  std::string s = "";
  if (ist >> s)
  {
    if (s == "Excellent")
      category = PresidentData::Excellent;
    else if (s == "Good")
      category = PresidentData::Good;
    else if (s == "Average")
      category = PresidentData::Average;
    else if (s == "Poor")
      category = PresidentData::Poor;
    else if (s == "Bad")
      category = PresidentData::Bad;

    else
    {
      // Terminate because something went wrong with the file and that
      // data could be crucial to the program
      assert(false);
    }
  }

  return ist;
}

std::ifstream& operator>>(std::ifstream& ist, PresidentData::Party& party)
{
  std::string s = "";
  if (ist >> s)
  {
    if (s == "Federalist")
      party = PresidentData::Federalist;
    else if (s == "Democrat")
      party = PresidentData::Democrat;
    else if (s == "Whig")
      party = PresidentData::Whig;
    else if (s == "Republican")
      party = PresidentData::Republican;

    else
    {
      // Terminate because something went wrong with the file and that
      // data could be crucial to the program
      assert(false);
    }
  }

  return ist;
}