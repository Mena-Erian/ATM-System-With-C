 
#ifndef MYUTILS_H
#define MYUTILS_H

//#include <stdio.h>
//#include <stdbool.h>



FILE* create_config_file(char* srver_ip, char* middle_Ware, char* software_varsion);

FILE* create_file(char* file_name, char* input);

bool is_file_exist(char* file_name_with_path);

#endif // !MYUTILS_H
