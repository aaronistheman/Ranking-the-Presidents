#include <Presidents/DataTables.hpp>

#include <cassert>
#include <fstream>


// This number excludes William Henry Harrison and James Garfield.
// It does not count Grover Cleveland twice.
// const int numberOfRankings = 41;
const int numberOfRankings = 41;

void readName(PresidentData& presidentData, std::ifstream& ist)
{
  char characterInput = ' ';
  std::string stringInput = "";

  // Holds number of names (first, middle, etc.) that have
  // been input for a specific president
  int nameCount = 0;
  
  // Input a (opening) quotation
  ist >> characterInput;

  // Prohibit file formatting issues; the issue of reaching the end of the
  // file is addressed in the while loop below
  assert(characterInput == '"' || ist.eof());

  characterInput = ' ';

  // Input names until:
  // an ending quotation is encountered OR
  // the end of the file has been reached
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

  // Prohibit file formatting issues; the issue of reaching the end of the
  // file is addressed in the while loop below
  assert(characterInput == '"' || ist.eof());

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

    // Add the pair only if the president's data has less than two pairs
    // (which is the maximum)
    if (presidentData.yearsInOfficePairs.size() < 2)
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
  std::vector<PresidentData> data;

  std::string filePath = "DataTables/PresidentData.txt";
  std::ifstream ist(filePath.c_str());
  assert(!ist.fail());  // check that file reading did not fail
  
  PresidentData presidentData;
  presidentData.Reset();

  for (int presidentNumber = 1; presidentNumber <= numberOfRankings; 
       ++presidentNumber)
  {
    // Input number
    presidentData.number = presidentNumber;

    readName(presidentData, ist);

    // Read the president's rank
    ist >> presidentData.rank;

    // Read the president's category
    ist >> presidentData.category;

    // Read the president's party
    ist >> presidentData.party;

    // Read the president's years in office
    readYearsInOffice(presidentData, ist);

    data.push_back(presidentData);

    presidentData.Reset();
  }

  // stop file reading
  ist.close();

  return data;
}