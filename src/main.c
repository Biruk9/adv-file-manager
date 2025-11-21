#include <stdio.h>
#include "../include/file_ops.h"

int main()
{
    // system("cls");
    int input;

    do
    {

        printf("======ADVANCED FILE MANAGER =======\n");

        printf("1.create file .\n");
        printf("2.delete file .\n");
        printf("3.Rename file .\n");
        printf("4.File info .\n");
        printf("5.Copy file\n");
        printf("0.Exit .\n");
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
        case 0:
            printf("Exiting ....");
        default:
            printf("invalid info");
            break;
        }
    } while (input != 0);

    return 0;
}