

#include <stdio.h>
#include <stdbool.h>

#include "./myutils.h"

FILE* create_config_file(char* srver_ip, char* middle_Ware, char* software_varsion)
{
	FILE* fconfig_ptr = fopen("./atm_config.txt", "w+");

	//char* srver_ip = "Server IP = 192.163.1.200";
	//char* middle_Ware = "Middleware state = Up";
	//char* software_varsion = "Software Version = 1.1";

	fprintf(fconfig_ptr, "Server IP = %s\nMiddleware state = %s\nSoftware Version = %s", srver_ip, middle_Ware, software_varsion);
	return  fconfig_ptr;
}

FILE* create_file(char* file_name, char* input)
{

	FILE* fptr = fopen("./atm_config.txt", "w+");

	//char* srver_ip = "Server IP = 192.163.1.200";
	//char* middle_Ware = "Middleware state = Up";
	//char* software_varsion = "Software Version = 1.1";

	fprintf(fptr, "%s", input);

	return  fptr;
}

bool is_file_exist(char* file_name_with_path)
{
	FILE* file = fopen(file_name_with_path, "r");
	
	if (file == NULL) return false;

	fclose(file);

	return true;
}


/*
| Mode   | File Exists?                    | File Not Exists?     | Write Behavior with `fprintf`                                               |
| ------ | ------------------------------- | -------------------- | --------------------------------------------------------------------------- |
| `"w"`  | **Clears file** (old data lost) | **Creates new file** | Overwrites from start.                                                      |
| `"w+"` | **Clears file**                 | **Creates new file** | Can read & write. Writing overwrites from start.                            |
| `"a"`  | Opens at **end of file**        | Creates new file     | Always appends new data at the end. Old data kept.                          |
| `"a+"` | Opens at **end of file**        | Creates new file     | Can read & write, but writes always go to end.                              |
| `"r"`  | Opens existing                  | Error (NULL)         | **Cannot write** (read-only).                                               |
| `"r+"` | Opens existing                  | Error (NULL)         | Can read & write. Writing starts at beginning (overwrites unless you seek). |
*/
