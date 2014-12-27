#include <Presidents/PresidentData.hpp>

#include <cassert>
#include <fstream>


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