#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

#include "../include/file_ops.h"

void Help_Menu()
{
    printf(CYAN "====== HELP MENU ======\n" RESET);
    printf(GREEN "1. Create File: " RESET "Creates a new empty file.\n");
    printf(GREEN "2. Delete File: " RESET "Deletes a file by specifying its name.\n");
    printf(GREEN "3. Rename File: " RESET "Renames an existing file.\n");
    printf(GREEN "4. File Info: " RESET "Shows size and last modified date of a file.\n");
    printf(GREEN "5. Copy File: " RESET "Copies a file to a new location.\n");
    printf(GREEN "6. Move File: " RESET "Moves a file to a new location.\n");
    printf(GREEN "7. List Files: " RESET "Lists all files and folders in a directory with details.\n");
    printf(GREEN "8. Create Folder: " RESET "Creates a new folder.\n");
    printf(GREEN "9. Delete Folder: " RESET "Deletes a folder (including all files/subfolders).\n");
    printf(GREEN "0. Exit: " RESET "Exits the application.\n");
    printf(YELLOW "Press Enter to return to the main menu..." RESET);
    getchar();
}

void create_file()
{

#define MAX_PATH 256
    char filename[MAX_PATH];
    char folderpath[100];
    char logmsg[200];

    printf(YELLOW "Enter the name of the file to create:" RESET);
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf(RED "Error creating file '%s'\n" RESET, filename);
    }
    else
    {
        printf(GREEN "File '%s' created successfully ! \n" RESET, filename);
        fclose(fp);
        sprintf(logmsg, "Created  a File : %s", filename);
        Write_log(logmsg);
    }
}
void delete_file()
{
#define MAX_PATH 256
    char filename[MAX_PATH];
    char choice;

    char folderpath[100];
    char logmsg[200];

    printf(YELLOW "Enter the name of file to delete: " RESET);
    fgets(filename, sizeof(filename), stdin);

    filename[strcspn(filename, "\n")] = 0;
    printf(RED "Are you sure you want to delete this folder (Y/N)\n" RESET);
    scanf(" %c", &choice);
    getchar();
    if (choice == 'Y' || choice == 'y')
    {
        if (remove(filename) == 0)
        {
            printf(GREEN "file '%s' deleted successfully !  \n" RESET, filename);
            sprintf(logmsg, "Deleted a File : %s", filename);
            Write_log(logmsg);
        }
        else
        {

            perror(RED "error deleting file\n" RESET);
        }
    }
    else
    {
        printf(RED "Operation canceled\n" RESET);
    }
}
void rename_file()
{
    char oldname[100];
    char newname[100];

    char folderpath[100];
    char logmsg[200];

    printf(YELLOW "Enter the file name to rename :" RESET);
    fgets(oldname, sizeof(oldname), stdin);
    oldname[strcspn(oldname, "\n")] = 0;

    printf(YELLOW "Enter the new name:" RESET);
    fgets(newname, sizeof(newname), stdin);
    newname[strcspn(newname, "\n")] = 0;

    if (rename(oldname, newname) == 0)
    {
        printf(GREEN "File renamed successfully!\n" RESET);

        sprintf(logmsg, "A File renamed : %s", newname);
        Write_log(logmsg);
    }
    else
    {
        perror(RED "Rrror renaming file" RESET);
    }
}
void file_info()
{
    char filename[100];
    printf(YELLOW "enter the file name you want information of:" RESET);
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    struct stat fileStat;
    if (stat(filename, &fileStat) == 0)
    {
        printf(GREEN "File size :%ld bytes \n" RESET, fileStat.st_size);
        printf(GREEN "last modified : %s" RESET, ctime(&fileStat.st_mtime));
    }
    else
    {

        perror(RED "Error getting file info" RESET);
    }
}

void copy_file()
{
    char originalfile[100];
    char copyfile[100];
    char buffer[1024];

    char folderpath[100];
    char logmsg[200];

    size_t bytes;

    printf(YELLOW "Enter the source file name : " RESET);
    fgets(originalfile, sizeof(originalfile), stdin);
    originalfile[strcspn(originalfile, "\n")] = 0;

    FILE *fo = fopen(originalfile, "rb");
    if (fo == NULL)
    {
        printf(RED "cannot open source file!\n" RESET);
        return;
    }

    printf(YELLOW "Enter the destination file name : " RESET);
    fgets(copyfile, sizeof(copyfile), stdin);
    copyfile[strcspn(copyfile, "\n")] = 0;

    FILE *fc = fopen(copyfile, "wb");
    if (fc == NULL)
    {
        printf(RED "cannot create destination file!\n" RESET);
        fclose(fo);
        return;
    }
    while ((bytes = fread(buffer, 1, sizeof(buffer), fo)) > 0)
    {
        fwrite(buffer, 1, bytes, fc);
    }
    printf(GREEN "File coppied successfully!!!!\n" RESET);
    sprintf(logmsg, "File coppied : %s", copyfile);
    Write_log(logmsg);
    fclose(fo);
    fclose(fc);
}
void move_file()
{
    char sourceFile[100];
    char destinationPath[100];

    char folderpath[100];
    char logmsg[200];

    printf(YELLOW "Enter source file path: " RESET);
    fgets(sourceFile, sizeof(sourceFile), stdin);
    sourceFile[strcspn(sourceFile, "\n")] = 0;

    printf(YELLOW "Enter the destination file (include filename): " RESET);
    fgets(destinationPath, sizeof(destinationPath), stdin);
    destinationPath[strcspn(destinationPath, "\n")] = 0;

    if (rename(sourceFile, destinationPath) == 0)
    {

        printf(GREEN "File Moved successfully \n" RESET);

        sprintf(logmsg, GREEN "File moved : %s" RESET, destinationPath);

        Write_log(logmsg);
    }
    else
    {
        perror(RED "Move Faild \n" RESET);
    }
}

void list_files()
{

    char directoryPath[200];
    char fullPath[300];

    printf(YELLOW "Enter the directory path you want list of \n" RESET);
    fgets(directoryPath, sizeof(directoryPath), stdin);
    directoryPath[strcspn(directoryPath, "\n")] = 0;

    DIR *dir = opendir(directoryPath);
    if (dir == NULL)
    {

        printf(RED "directory not found" RESET);
        return;
    }
    struct dirent *entry;
    printf(BLUE "File is in %s : \n" RESET, directoryPath);
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            sprintf(fullPath, "%s/%s", directoryPath, entry->d_name);

            struct stat fileStat;
            if (stat(fullPath, &fileStat) == 0)
            {
                printf(YELLOW "%-30s %101d bytes %s" RESET, entry->d_name, fileStat.st_size, ctime(&fileStat.st_mtime));

                if (S_ISDIR(fileStat.st_mode))
                    printf(BLUE "[DIR]\n" RESET);
                else
                    printf(GREEN "[FILE]\n" RESET);
            }
        }
    }
    closedir(dir);
}
void create_folder()
{
    char createfolder[100];

    char folderpath[100];
    char logmsg[200];

    printf(YELLOW "Enter the name of the folder you want create\n" RESET);
    fgets(createfolder, sizeof(createfolder), stdin);
    createfolder[strcspn(createfolder, "\n")] = 0;

    if (mkdir(createfolder) == 0)
    {
        printf(GREEN "folder created successfully \n" RESET);
        sprintf(logmsg, GREEN "A folder created : %s" RESET, createfolder);
        Write_log(logmsg);
    }
    else
    {
        perror(RED "Error creating folder \n" RESET);
    }
}

int delete_folder_recursive(const char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (!dir)
        return -1;
    char fullpath[512];
    while ((entry = readdir(dir)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        struct stat statbuf;
        if (stat(fullpath, &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
            {
                delete_folder_recursive(fullpath);
            }
            else
            {
                remove(fullpath);
            }
        }
    }
    closedir(dir);
    return rmdir(path);
}
void delete_folder()
{
    char folderpath[100];
    char logmsg[200];

    char choice;

    printf(YELLOW "Enter the folder path you want to delete:\n" RESET);
    fgets(folderpath, sizeof(folderpath), stdin);
    folderpath[strcspn(folderpath, "\n")] = 0;

    printf(RED "Are you sure you want to delete this folder (Y/N)\n" RESET);
    scanf(" %c", &choice);
    getchar();

    if (choice == 'Y' || choice == 'y')
    {

        if (delete_folder_recursive(folderpath) == 0)
        {
            printf(GREEN "Folder deleted succesfully\n" RESET);
            sprintf(logmsg, GREEN "A folder deleted : %s" RESET, folderpath);
            Write_log(logmsg);
        }
        else
        {
            perror(RED "Folder not found\n" RESET);
        }
    }
    else
    {
        printf("Operation cancelled");
    }
}

void Write_log(const char *message)
{
    mkdir("logs");
    FILE *log = fopen("logs/log.txt", "a");
    if (!log)
        return;

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strcspn(time_str, "\n")] = 0;

    fprintf(log, "[%s] %s\n", time_str, message);
    fclose(log);
}

void load_config(char *theme, char *default_dir, int *logging)
{
    FILE *config = fopen("setting.cfg", "r");
    if (!config)
        return;

    char line[100];
    while (fgets(line, sizeof(line), config))
    {
        line[strcspn(line, "\n")] = 0; // remove newline

        if (strstr(line, "theme="))
            sscanf(line, "theme=%s", theme);

        else if (strstr(line, "default_dir="))
            sscanf(line, "default_dir=%s", default_dir);

        else if (strstr(line, "logging="))
        {
            char value[10];
            sscanf(line, "logging=%s", value);
            *logging = (strcmp(value, "on") == 0);
        }
    }
    fclose(config);
}
void create_default_config()
{
    FILE *config = fopen("setting.cfg", "r");
    if (config)
    {
        fclose(config); // file exists, nothing to do
        return;
    }

    config = fopen("setting.cfg", "w");
    if (!config)
        return;

    fprintf(config, "theme=on\n");
    fprintf(config, "default_dir=.\n");
    fprintf(config, "logging=on\n");

    fclose(config);
}
