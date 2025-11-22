Advanced File Manager 🗂️

Version: v1.0.0
Language: C
Platform: Windows

A simple yet powerful command-line file and folder management tool built in C. Manage files and directories with ease, featuring logging, configuration, and a user-friendly colored interface.

Features 

File Operations:

Create, delete, rename, copy, and move files

View file info (size, last modified date)

Folder Operations:

Create new folders

Delete folders recursively (including all files/subfolders)

List folder contents with details

User Interface:

Color-coded output for better readability

Help menu for guidance

Confirmation prompts to prevent accidental deletions

Logging System:

All operations are logged with timestamps

Logs saved in logs/log.txt

Configuration System:


Default directory and theme options in setting.cfg

Automatically creates default configuration if none exists.


Installation & Compilation 💻

Requirements: GCC compiler

Clone the repository:

git clone <your-repo-url>
cd adv-file-manager/src


Compile the project:

gcc main.c file_ops.c -o filemanager.exe


Run the program:
.\filemanager.exe     # Windows

Usage 📝

Launch the program and choose from the menu options:

Create File

Delete File

Rename File

File Info

Copy File

Move File

List Files

Create Folder

Delete Folder

Exit

Logs are automatically saved in logs/log.txt.

Configuration settings are loaded from setting.cfg.

Example Config (setting.cfg) 

theme=on
default_dir=.
logging=on

Notes & Future Improvements 

Add undo functionality for accidental deletions.

Implement search and filter for large directories.

Add multi-platform compatibility checks.

Extend test mode for automated demonstrations

Author ✍️

Biruk Aklilu Ambaye

GitHub: Biruk9

Email:akibiruk39@gmail.com