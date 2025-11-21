#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "../include/file_ops.h"

void create_file()
{
    char filename[100]; // buffer to store filename
    printf("enter the name of the file to create:");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("error creating file '%s'\n", filename);
    }
    else
    {
        printf("file '%s' created successfully ! \n", filename);
        fclose(fp);
    }
}
void delete_file()
{
    char filename[100];
    printf("enter the name of file to delete: ");
    fgets(filename, sizeof(filename), stdin);
    // remove trailing newline
    filename[strcspn(filename, "\n")] = 0;

    if (remove(filename) == 0)
    {
        printf("file '%s' deleted successfully ! \n", filename);
    }
    else
    {

        perror("error deleting file");
    }
}
void rename_file()
{
    char oldname[100];
    char newname[100];
    printf("enter the file name to rename :");
    fgets(oldname, sizeof(oldname), stdin);
    oldname[strcspn(oldname, "\n")] = 0;

    printf(" enter the new name:");
    fgets(newname, sizeof(newname), stdin);
    newname[strcspn(newname, "\n")] = 0;

    if (rename(oldname, newname) == 0)
    {
        printf("file named successfully!\n ");
    }
    else
    {
        perror("error rnaming file");
    }
}
void file_info()
{
    char filename[100];
    printf("enter the file name you want information of:");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    struct stat fileStat;
    if (stat(filename, &fileStat) == 0)
    {
        printf("File size :%ld bytes \n", fileStat.st_size);
        printf("last modified : %s", ctime(&fileStat.st_mtime));
    }
    else
    {

        perror("Error getting file info");
    }
}

void copy_file()
{
    char originalfile[100];
    char copyfile[100];
    char buffer[1024];
    size_t bytes;

    printf("enter the source file name : ");
    fgets(originalfile, sizeof(originalfile), stdin);
    originalfile[strcspn(originalfile, "\n")] = 0;

    FILE *fo = fopen(originalfile, "rb");
    if (fo == NULL)
    {
        printf("cannot open source file!\n");
        return;
    }

    printf("enter the destination file name : ");
    fgets(copyfile, sizeof(copyfile), stdin);
    copyfile[strcspn(copyfile, "\n")] = 0;

    FILE *fc = fopen(copyfile, "wb");
    if (fc == NULL)
    {
        printf("cannot create destination file!\n");
        fclose(fo);
        return;
    }
    while ((bytes = fread(buffer, 1, sizeof(buffer), fo)) > 0)
    {
        fwrite(buffer, 1, bytes, fc);
    }
    printf("file coppied succesfully!!!!\n");

    fclose(fo);
    fclose(fc);
}