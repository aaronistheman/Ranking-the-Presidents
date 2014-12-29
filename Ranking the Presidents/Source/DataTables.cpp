#include <Presidents/DataTables.hpp>

#include <cassert>
#include <fstream>


// This number excludes William Henry Harrison and James Garfield.
// It does not count Grover Cleveland twice.
// const int numberOfRankings = 41;
const int numberOfRankings = 2;

void readName(PresidentData& presidentData, std::ifstream& ist)
{
  char characterInput = ' ';
  std::string stringInput = "";

  // Holds number of names (first, middle, etc.) that have
  // been input for a specific president
  int nameCount = 0;
  
  // Input a (opening) quotation
  ist >> characterInput;
  if (ist.eof())
    return;
  assert(characterInput == '"');

  characterInput = ' ';

  // Input names until a (closing) quotation is encountered;
  // Skip if end of file
  while (characterInput != '"' && !ist.eof())
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
      presidentData.name += ' ';
        
    // Attach the name to the ranking data's name field
    presidentData.name += stringInput;
    nameCount++;
  }
}

void readYearsInOffice(PresidentData& presidentData, std::ifstream& ist)
{
  char characterInput = ' ';
  int integerInput = 0;

  // Input a (opening) quotation
  ist >> characterInput;
  if (ist.eof())
    return;
  assert(characterInput == '"');

  characterInput = ' ';

  // Input pairs of beginning and ending years in office until:
  // an ending quotation is encountered OR
  // the end of the file has been reached
  while (characterInput != '"' && !ist.eof())
  {
    YearsInOfficePair yearsInOfficePair;
    
    // Input beginning year
    ist >> yearsInOfficePair.termBeginning;

    // Input the dash in between a pair of years
    ist >> characterInput;
    assert(characterInput == '-');

    // Input ending year
    ist >> yearsInOfficePair.termEnd;
    presidentData.yearsInOfficePairs.push_back(yearsInOfficePair);

    // If a quotation is inputted, the loop will end;
    // If a semi-colon is inputted, another pair of years will
    // be inputted
    ist >> characterInput;
    assert(characterInput == ';' || characterInput == '"');
  }
}

std::vector<PresidentData> initializeDescriptionData()
{
  std::vector<PresidentData> data(numberOfRankings);

  std::string filePath = "DataTables/PresidentData.txt";
  std::ifstream ist(filePath.c_str());
  
  // Keeps track of the number of the president in the sequence of
  // all ranked presidents (ex: John Adams corresponds to 2)
  int presidentNumber = 1;

  for (auto itr = data.begin(); itr != data.end() && !ist.eof(); ++itr)
  {
    // Input number and update presidentNumber
    itr->number = presidentNumber;
    ++presidentNumber;

    readName(*itr, ist);

    // Read the president's rank
    ist >> itr->rank;

    // Read the president's category
    ist >> itr->category;

    // Read the president's party
    ist >> itr->party;

    // Read the president's years in office
    readYearsInOffice(*itr, ist);
  }

  // stop file reading
  ist.close();

  return data;
}