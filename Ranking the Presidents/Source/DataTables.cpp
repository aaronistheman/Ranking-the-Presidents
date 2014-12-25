#include <Presidents/DataTables.hpp>

#include <fstream>


// This number excludes William Henry Harrison and James Garfield.
// It does not count Grover Cleveland twice.
const int numberOfRankings = 41;

std::vector<DescriptionData> initializeDescriptionData()
{
  std::vector<DescriptionData> data(numberOfRankings);

  std::string filePath = "DataTables/DescriptionData.txt";
  std::ifstream ist(filePath.c_str());

  return data;
}

std::vector<RankingData> initializeRankingData()
{
  std::vector<RankingData> data(numberOfRankings);

  std::string filePath = "DataTables/RankingData.txt";
  std::ifstream ist(filePath.c_str());

  char characterInput = ' ';
  std::string stringInput = "";
  int integerInput = 0;

  // Keeps track of the number of the president in the sequence of
  // all ranked presidents (ex: John Adams corresponds to 2)
  int presidentNumber = 1;

  // Holds number of names (first, middle, etc.) that have
  // been input for a specific president
  int nameCount = 0;

  for (auto itr = data.begin(); itr != data.end() && !ist.eof(); ++itr)
  {
    // Read until a (opening) quotation is encountered
    while (characterInput != '"')
    {
      ist >> characterInput;
    }

    characterInput = ' ';

    // Input names until a (closing) quotation is encountered
    while (characterInput != '"')
    {
      ist >> stringInput;
        
      // Do not let the closing quotation be treated as part of the
      // president's last name
      if (stringInput.back() == '"')
      {
        characterInput = '"';
        stringInput.pop_back();
      }

      // If a name other than the president's first name is being input,
      // add a space to the ranking data's name field
      if (nameCount > 0)
        itr->name += ' ';
        
      // Attach the name to the ranking data's name field
      itr->name += stringInput;
      nameCount++;
    }

    // Input number and update presidentNumber
    itr->number = presidentNumber;
    ++presidentNumber;

    // Input rank
    ist >> integerInput;
    itr->rank = integerInput;

    // Reset reading-helper variables
    characterInput = ' ';
    stringInput = "";
    integerInput = 0;
    nameCount = 0;
  }

  // stop file reading
  ist.close();

  return data;
}