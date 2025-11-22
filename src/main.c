#include <stdio.h>
#include "../include/file_ops.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

int main()
{

    char theme[20];
    char default_dir[200];
    int logging;

    // system("cls");
    int input;

    do
    {

        printf(BLUE "======ADVANCED FILE MANAGER =======\n");

        printf(GREEN "1.create file \n");
        printf(GREEN "2.delete file \n");
        printf(GREEN "3.Rename file \n");
        printf(GREEN "4.File info \n");
        printf(GREEN "5.Copy file\n");
        printf(GREEN "6.Move File \n");
        printf(GREEN "7. List Files\n");
        printf(GREEN "8. create folder\n");
        printf(GREEN "9 delete folder \n");
        printf(GREEN "10. Help Menu\n" RESET);

        printf(RED "0.Exit \n" RESET);
        printf(" Choose what you would like to do:.\n");

        scanf("%d", &input);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (input)

        {
        case 1:
            create_file();

            break;
        case 2:
            delete_file();
            break;
        case 3:
            rename_file();
            break;

        case 4:
            file_info();
            break;
        case 5:
            copy_file();
            break;
        case 6:
            move_file();
            break;
        case 7:
            list_files();
            break;
        case 8:
            create_folder();
            break;
        case 9:
            delete_folder();
            break;
        case 10:
            Help_Menu();
            break;
        case 0:
            printf("Exiting ....");
        default:
            printf("invalid info");
            break;
        }
    } while (input != 0);

    Write_log("program started");
    create_default_config();
    load_config(theme, default_dir, &logging);

    return 0;
}