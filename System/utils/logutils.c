#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "logutils.h"
#include "myutils.h"

bool is_this_file_name_exist(char* file_name_with_path)
{
	FILE* file = fopen(file_name_with_path, "r");

	if (file == NULL) return false;

	fclose(file);

	return true;
}

bool is_file_exist(FILE* fptr)
{
	if (fptr == NULL) return false;
	return true;
}

void log_error(char* msg, char* details) {

	char final_msg[250];
	
	/*
		get number of err from file to increment it and Record
	*/

	time_t now = time(NULL); // get Time In Secondes
	struct tm* time = localtime(&now);
	char str_time[20];
	// timestamp =>
	strftime(str_time, sizeof(str_time), "%Y-%m-%d %H:%M:%S", time);

	sprintf(final_msg, "E%d: %s Message: %s %s",errno,str_time, msg, details);

	(void)log_into(ERROR_FILE_PATH, final_msg);
	//perror("Failed to Log The Error");
}

// Maybe Retrun NULL !!
FILE* log_into(char* file_name_with_path, char* input)
{
	FILE* fptr = open_file(file_name_with_path, APPEND | READ);

	if (is_file_exist(fptr))
	{
		fprintf(fptr, input);
		return fptr;
	}
	else perror(input);
	return fptr;
}

FILE* open_file(char* file_name_with_path, FileMode mode)
{
	FILE* fptr;
	switch (mode)
	{
	case WRITE:
		return fopen(file_name_with_path, "w"); // write only, make override if file is exist.
		break;
	case READ:
		return fopen(file_name_with_path, "r"); // read only
		break;
	case APPEND:
		return fopen(file_name_with_path, "a"); // append only
		break;
	case WRITE | READ:
		return fopen(file_name_with_path, "r+"); // read/write (if not exist return NULL)
		break;
	case APPEND | READ:
		return fopen(file_name_with_path, "a+"); // read/append 
	case N_WRITEREAD:
		return fopen(file_name_with_path, "w+"); // read/write, make override if file is exist.
	default:
		return NULL;
	}

	return  fptr;
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