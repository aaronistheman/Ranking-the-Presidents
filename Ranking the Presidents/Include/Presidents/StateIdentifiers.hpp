#ifndef PRESIDENTS_STATEIDENTIFIERS_HPP
#define PRESIDENTS_STATEIDENTIFIERS_HPP


// Menu layout:
// MainMenu
// --Profiles
//   --PresidentialProfiles
//   --Rankings
// --About
// --Exit (has no ID)
//
// User can trigger Help state in any other state besides About 
// and Exit.

namespace States
{
	enum ID
	{
		None,
		MainMenu,
		Profiles,
    PresidentialProfiles,
    Rankings,
    About,
    Help
	};
}

#endif // PRESIDENTS_STATEIDENTIFIERS_HPP
