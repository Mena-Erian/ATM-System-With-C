#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "./myutils.h"



#define CONFIG_FILE_PATH "./configs/atm_config.txt"

struct Config create_default_config()
{
	struct Config df;

	 strcpy(df.srver_ip, "192.168.1.1");
	 strcpy(df.middleware, "Up");
	 strcpy(df.software_varsion, "1.0.0");

	/*df.srver_ip = "192.168.1.1";
	df.middleware = "Up";
	df.software_varsion = "1.0.0";*/

	return df;
}

FILE* create_config_file(struct Config* config)
{
	FILE* fconfig_ptr = fopen(CONFIG_FILE_PATH, "w");

	if (fconfig_ptr != NULL)
	{
		fprintf(fconfig_ptr,
			"ServerIP = %s\nMiddlewareState = %s\nSoftwareVersion = %s",
			config->srver_ip,
			config->middleware,
			config->software_varsion
		);
	}
	return  fconfig_ptr;
	//exsit(1);
}

FILE* create_file(char* file_name, char* input)
{
	FILE* fptr = fopen("./atm_config.txt", "w");

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

struct Config read_config_file()
{
	FILE* fptr = fopen(CONFIG_FILE_PATH, "r");

	if (fptr == NULL)  return;

	struct Config config;
	char _[20];

	//i will back to handle erros :)
	(void)fscanf(fptr, "%s = %s", _, config.srver_ip);
	(void)fscanf(fptr, "%s = %s", _, config.middleware);
	(void)fscanf(fptr, "%s = %s", _, config.software_varsion);

	/// printf("%s\n", _, config.srver_ip);
	/// printf("%s\n", _, config.middleware);
	/// printf("%s\n", _, config.software_varsion);

	fclose(fptr);
	return config;
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
