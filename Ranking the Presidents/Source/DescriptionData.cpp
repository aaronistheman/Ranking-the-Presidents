#include <Presidents/DescriptionData.hpp>

#include <cassert>
#include <fstream>


std::ifstream& operator>>(std::ifstream& ist, 
                          DescriptionData::Category& category)
{
  std::string s = "";
  if (ist >> s)
  {
    if (s == "Excellent")
      category = DescriptionData::Excellent;
    else if (s == "Good")
      category = DescriptionData::Good;
    else if (s == "Average")
      category = DescriptionData::Average;
    else if (s == "Poor")
      category = DescriptionData::Poor;
    else if (s == "Bad")
      category = DescriptionData::Bad;

    else
    {
      // Terminate because something went wrong with the file and that
      // data could be crucial to the program
      assert(false);
    }
  }

  return ist;
}