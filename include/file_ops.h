#ifndef FILE_OPS_H
#define FILE_OPS_H

void create_file();
void delete_file();
void rename_file();
void copy_file();
void file_info();
void move_file();
void list_files();
void create_folder();
void delete_folder();
void Help_Menu();
void Write_log(const char *message);
void load_config(char *theme, char *default_dir, int *logging);
void create_default_config();
#endif