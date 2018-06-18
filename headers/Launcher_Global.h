// COPYRIGHT © 2018
// AUTHOR(S):	Lee Connor Williams
// All Rights Reserved

// Global contains variables used throughout the application, stored here to prevent repetative/unessecary code.


#ifndef LAUNCHER_GLOBAL
#define LAUNCHER_GLOBAL

#include <string>
#include <gtkmm/application.h>

namespace UnrealatedLauncherGlobal{
	
	extern std::string	launcherHomeDir;			// Launchers associated folder within the users home directory.  Should only be set once, within the main loop.
	extern std::string	launcherConfig;				// Path to the launcher ini configuration file.
	extern std::string	launcherRepositoryDir;		// Path to the launcher repository directory.
	extern bool			repoManagerRememberLogin;	// Bool that determines whether the user wants to save their details.
	extern std::string	repoManagerLoginFile;		// Path to a file containing login information.
	
} // END - Global launcher namespace.

#endif