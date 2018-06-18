# Unrealated Launcher
An Unofficial Unreal Engine Launcher for Linux

# Pre-Warnings:
At its current stage, it's very rough around the edges; some things don't work, aren't hooked up, or it may just crash when it feels like it.

The launcher makes use of Libgit2.

You need to make sure that your EpicGames and Github accounts are connected.  Follow step "1" from here: https://docs.unrealengine.com/en-us/Platforms/Linux/BeginnerLinuxDeveloper/SettingUpAnUnrealWorkflow

Steps 2 onwards are what the Launcher does for you!

# Installing Engines:
Installing engines using the launcher is completed in three stages: downloading the source code repository; setting up an engine installation; and performing the install.

## 1: Downloading the repository
1. Click on the Launcher Menu drop down.
2. Click on "Repo Manager":  the repo manager will open.
3. Enter your GITHUB login details, and click "login".  
**WARNING**: Enabling "remember login details" will save your login to a plain text within your home directory.  Use at your own risk!
4. You can now click on "Get New Repository".  The repository is approximately 2.5GB big.
5. Once finished, click "Generate Lists".  The lists are used by the launcher to show you the commits from the repository.
### Notes:
- SSH Authentication Support is planned.
- "Update All" will perform steps 4 and 5.

## 2: Adding an Engine
1. Click on the large "ENGINES" tab.
2. On the bottom tool bar, click "Add Engine".  The sidebar will open.
3. If you want the installation process to start after you're finished, check "Start Install after finishing".
4. Press "Refresh Lists".  
**NOTE:** The UI will freeze up after pressing, the duration of which will depend on the "max commits" values in settings.
4. Ensure "Show Tagged Commits" is selected.
4. From the Tagged Commit selector, choose the engine version you wish to install.
5. Choose your installation folder and Engine Label.
**NOTE:** By default, the engine label is appended to the install folder directory.
**WARNING:** Avoid spaces in the directory path!  They cause havoc and break things.
6. Choose a custom image, if you wish to use one.  Currently, the end size is 300x300.
7. Check the details, then click CONFIRM.

### Notes:
- "Show Commits" will show all the commits linearly;
- Enabling "show commits after tagged commit" will show the commits from the chosen tagged commit:  currently, this feature works in reverse to its intended direction (shows commits before).
- If adding an existing Engine, make sure the chosen folder is the root of the installation:
`/path/to/the/install/Folder[Choose This Folder]/Engine/Binaries/Linux/UE4Editor`

## 3: Installation
This stage is almost completely automated.
If you are stuck on the 2nd stage "Running Setup.sh, Check the terminal for sudo prompts", you're stuck on a sudo prompt for missing dependancies (the script is asking for software it needs to be installed).  Please close and re-launch the Launcher from a terminal:  you'll be able to enter your password and continue as normal.

### Notes:
The installation stage is currently coded in a way that works in a rudamentary way: I'm working on improving this.

# GENERAL NOTES:
Please remember that this is **NOT FINISHED**, It's also the first time I have personally created software.
This project will have an associated Patreon and KoFi/BuyMeCoffee for monetary support; the more of which means the more time I can dedicate to improving the launcher; which is nessecary for...

# PLANNED FEATURES:
These are planned, but whether or not they make it into the launcher are another matter.
- SSH Authentification for Github.
- Project Blocks (project version of installed engines).
- Marketplace Support.
- Functioning Community tab.
