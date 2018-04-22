#ifndef LAUNCHERMARKETPLACE
#define LAUNCHERMARKETPLACE

namespace UnrealatedLauncher{

	class Launcher_MarketTab : public Gtk::Grid{
	public:
		Launcher_MarketTab();
		virtual ~Launcher_MarketTab();

		void AddPageTask(){v_tasks++;} // Increments the number of tasks the page is performing.
		void RemovePageTask(){
			v_tasks--;
			if(v_tasks < 0) { v_tasks == 0; } // Ensure tasks never goes below 0.
		} // Decrements the number of tasks the page is performing.
		void SetPageTaskPercent(double p_progress){ v_taskProgress = p_progress; }; // Sets the task progress to the given value.
		int GetPageTasks(){return v_tasks;} // Gets the current number of tasks the page is performing.
		double GetPageTaskProgress(){return v_taskProgress;} // Gets the current task progress.  Not used if more than one task is running.
		
	protected:
		int v_tasks = 0; // Number of tasks in progress; If higher than 1, pulse is used.
		double v_taskProgress; // Used to update page progress bar.
		//
	}; // END - Launcher_MarketTab class

} // Unrealated launcher Namespace
#endif
