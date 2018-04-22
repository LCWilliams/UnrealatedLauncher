 DEPRECATED: TO BE REMOVED!!
 DEPRECATED: TO BE REMOVED!!

#ifndef ENGINES_ADDASSISTANTS
#define ENGINES_ADDASSISTANTS

// REMOVE[Tag]: clean up after finishing movement to sidebar.

#include <gtkmm/assistant.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/border.h>
//#include <gtkmm/combobox.h>
#include <gtkmm/comboboxtext.h> // Remove
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/spinner.h>

#include <headers/Engines_Block.h>

#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

namespace UnrealatedLauncher{

	class EngineAddAssistant_New : public Gtk::Assistant{
	public:
		EngineAddAssistant_New();
		virtual ~EngineAddAssistant_New();

		vector<EngineBlock*> v_EngineBlockArray; // A vectorArray of EngineBlocks for recursive checks.
	private:
		Gtk::Grid page_engineSelect, page_Directories, page_Customisation, page_confirm;
		
		Gtk::ComboBoxText v_engineSelector;
		Gtk::Entry v_customLabelEntry;
		Gtk::Label installDirectoryLabel, installDirectoryExampleLabel, sourceDirectoryLabel, sourceDirectoryExampleLabel, txt_customLabelWarning,
		// Page 2 Labels:
		txt_versionToInstallLabel, txt_versionToInstall, txt_installDirLabel, txt_installDir, txt_sourceDirLabel, txt_sourceDir, txt_customLabelLabel, txt_customLabelConfirm, txt_customImageLabel, txt_customImageStatus;
		Gtk::Image img_customImage;
		Gtk::FileChooserButton btn_installSelectFolder, btn_sourceSelectFolder, btn_customImageSelector;
		
		string str_selectedEngine, str_installDir, str_sourceDir;
		
		// FUNCTIONS:
		void closeAssistant();
		// Utility
		void populateEngineSelector();
		void populateConfirmationPage();
		int directoryNotUsed(string p_directoryToCheck); // Returns 0 if directory is not used. 1 If it's an install Dir, 2 if it's a source dir.
		string removeFileFromString(string p_stringToModify); // Removes "File:/" from a string.
		void checkDirectories(); // Error checking for entries.
		void requireCustomLabel(); // Returns true if a custom label is required. Will also return true if a custom label matches an existing custom label.
		
		//Signal Responders:
		void engineSelectorUpdated();
		void directoryEntryUpdated();
		void sourceEntryUpdated();
		void btn_ToConfirmPage_clicked();
		void btn_applyClicked();

		
	}; // END - New Add assistant.



	class EngineAdd : public Gtk::Grid{
	public:
		EngineAdd();
		virtual ~EngineAdd();
		vector<EngineBlock*> v_engineBlockArray;
		
	private:
		// GTK Elements:
		Gtk::ComboBoxText v_engineSelector;
		Gtk::Label txt_label_version, txt_label_versionStatus;
		Gtk::Button btn_cancel, btn_confirm;
		Gtk::ButtonBox v_confirmCancelButtonBox;
		Gtk::Border v_border;
		Gtk::Spinner v_populateSpinner;
		
		// Functions: Buttons & Signal Responders
		void btn_Cancel_clicked();
		void btn_Confirm_clicked();
		void v_engineSelector_changed();
		
		// Functions: Utility
		void PopulateSelector(); // Populates the selector.
		void CheckCanConfirm(); // Checks all input is valid before allowing Confirm to be sensitive.
		
	};

	class EngineAddAssistant_Existing : public Gtk::Assistant{
	public:
		EngineAddAssistant_Existing();
		virtual ~EngineAddAssistant_Existing();

	private:
		// FUNCTIONS:
		void closeAssistant();
	}; // END - Existing add assistant.


	class EngineAddAssistant_OneClickAdd : public Gtk::Assistant{
	public:
		EngineAddAssistant_OneClickAdd();
		virtual ~EngineAddAssistant_OneClickAdd();

	private:
		
		// FUNCTIONS:
		void closeAssistant();
	}; // END - One Click Add assistant.

} // END - Unrealated launcher namespace.


#endif
