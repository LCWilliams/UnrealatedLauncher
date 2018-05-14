#include <headers/UnrealatedLauncherWindow.h>

using namespace std;

int main(int argc, char *argv[]){
	
	// Initialise XThreads:
//	XInitThreads();
	
	
	
	// Create configuration directories.
	mkdir("config", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./config/engines", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./config/projects", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	//Create default folders:
	mkdir("launcherRepo", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("engines", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./engines/install", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./engines/source", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	// Folder for user specific items:
	system("mkdir -p ~/.unrealatedLauncher");
	
// SET GLOBAL VARIABLES:
	string temp_directory; // Will be used to concancate path + subfolder.
	string temp_homeName = getenv("HOME");
	if(!temp_homeName.empty()){
		temp_directory = temp_homeName + "/.unrealatedLauncher";
	} else{
		cerr << "WARN:	" << "Home directory not found.  Using subfolder of launcher directory." << endl;
		temp_directory = "/.launcher";
	} // END - Check Home name.
	
	UnrealatedLauncherGlobal::launcherHomeDir = temp_directory;
	UnrealatedLauncherGlobal::repoManagerLoginFile = temp_directory + "/.repoManagerLogin";
	
		cout << "DEBUG:	Directories:" << endl 
		<< "		> Launcher Homedir: " << UnrealatedLauncherGlobal::launcherHomeDir << endl
		<< "		> RepoManagerLogin: " << UnrealatedLauncherGlobal::repoManagerLoginFile << endl;

	// setup directory for ini file:
	temp_directory += "/UnrealatedLauncher.ini";
	UnrealatedLauncherGlobal::launcherConfig = temp_directory;

	// FUNCTION VARIABLES:
	CSimpleIniCaseA ini;
	SI_Error temp_errorCheck = ini.LoadFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
	bool useSysTheme = false; // Pre-set as false as quicker error handling.
	
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
		ini.SetBoolValue("General", "RememberGitLogin", UnrealatedLauncherGlobal::repoManagerRememberLogin); // False
			
		// Write Projects:
		
		
		// Write Engines:
		ini.SetBoolValue("Engines", "BackgroundRepoSync", true);
		ini.SetDoubleValue("Engines", "BackgroundRepoSyncInterval", 10);
		ini.SetBoolValue("Engines", "BackgroundRepoSync_RegenList", true);
		
		ini.SetValue("Engines", "launcherRepo", "./launcherRepo");
		ini.SetValue("Engines", "defaultInstallDir", "./engines/install");
		ini.SetValue("Engines", "defaultSourceDir", "./engines/source");
		
		ini.SetDoubleValue("Engines", "maxTaggedCommits", 30);
		ini.SetDoubleValue("Engines", "maxCommits", 150);
		ini.SetBoolValue("Engines", "defaultShowTaggedCommits", true);
		ini.SetDoubleValue("Engines", "commitWrap", 3);
		// Write Market:
		
		// Write Community:
		
		// Save & Close Tab:
		temp_errorCheck = ini.Save(dataString);
		if(temp_errorCheck < 0) exit(-1);
		
		temp_errorCheck = ini.SaveFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
		if(temp_errorCheck < 0) exit(-1);
	}// END - else/Create settings file.

	Glib::RefPtr<Gtk::Application> UnrealatedLauncherApplication = Gtk::Application::create(argc, argv, "LCWilliams.UnrealatedLauncher");
	UnrealatedLauncher::UnrealatedLauncherWindow window;
	window.ref_application = UnrealatedLauncherApplication;

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
