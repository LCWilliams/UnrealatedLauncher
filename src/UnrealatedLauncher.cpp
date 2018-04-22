#include <headers/UnrealatedLauncherWindow.h>

using namespace std;

int main(int argc, char *argv[]){
	
	// Initialise XThreads:
//	XInitThreads();
	
	// FUNCTION VARIABLES:
	CSimpleIniCaseA ini;
	string iniFileDir = "./config/UnrealatedLauncher.ini";
	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str());
	bool useSysTheme = false; // Pre-set as false as quicker error handling.
	
	
	// Create configuration directories.
	mkdir("config", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./config/engines", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./config/projects", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	//Create default folders:
	mkdir("launcherRepo", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("engines", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./engines/install", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./engines/source", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	// If Config file was loaded, set bool to userpreference; else, create preferences.
	if(temp_errorCheck == 0){
		useSysTheme = ini.GetBoolValue("General", "UseSystemTheme");
	} else{
		cout << "Creating settings file..." << endl;
		// DUPLICATE FROM UNREALATEDLAUNCHERSETTINGS.CPP :: RESET
		string dataString;
		// Write General:
		ini.SetBoolValue("General", "FirstRun", true);
		ini.SetBoolValue("General", "UseSystemTheme", false);
		ini.SetBoolValue("General", "utilityBarOpen", true);
		ini.SetBoolValue("General", "UtilBar_ShowLauncherRepoStatus", true);
		ini.SetBoolValue("General", "UtilBar_ShowLatestCommit", true);
		ini.SetDoubleValue("General", "DefaultPage", 1);
			
		// Write Projects:
		
		
		// Write Engines:
		ini.SetBoolValue("Engines", "BackgroundRepoSync", true);
		ini.SetDoubleValue("Engines", "BackgroundRepoSyncInterval", 10);
		
		ini.SetValue("Engines", "launcherRepo", "./launcherRepo");
		ini.SetValue("Engines", "defaultInstallDir", "./engines/install");
		ini.SetValue("Engines", "defaultSourceDir", "./engines/source");
		
		ini.SetDoubleValue("Engines", "maxBranches", 30);
		ini.SetDoubleValue("Engines", "maxCommits", 150);
		ini.SetBoolValue("Engines", "defaultShowBranches", true);
		ini.SetDoubleValue("Engines", "commitWrap", 3);
		// Write Market:
		
		// Write Community:
		
		// Save & Close Tab:
		temp_errorCheck = ini.Save(dataString);
		if(temp_errorCheck < 0) exit(-1);
		
		temp_errorCheck = ini.SaveFile(iniFileDir.c_str());
		if(temp_errorCheck < 0) exit(-1);
	}

	Glib::RefPtr<Gtk::Application> UnrealatedLauncherApplication = Gtk::Application::create(argc, argv, "LCWilliams.UnrealatedLauncher");
	UnrealatedLauncher::UnrealatedLauncherWindow window;

	// Themes:
	// If use system theme is false, apply custom theme...
	if(!useSysTheme){
		Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
		cssProvider->load_from_path("../themes/unrealatedLauncher.css");
		
		Glib::RefPtr<Gtk::StyleContext> styleContext = Gtk::StyleContext::create();
		
		//get default screen
		Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
		
		//add provider for screen in all application
		styleContext->add_provider_for_screen(screen, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
	} // END - Custom theme IF.

	return  UnrealatedLauncherApplication->run(window);
} // END - Main Function.
