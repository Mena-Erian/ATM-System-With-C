
#ifndef LOGSUTILS_H
#define LOGSUTILS_H

#define CONFIG_FILE_PATH "./configs/atm_config.txt"
#define ERROR_FILE_PATH "./logs/atm_error.log"
#define STATUS_FILE_PATH "./status/atm_app_status.txt"

typedef enum FileMode
{
	WRITE = 1 << 0,		//0001 = 1
	READ = 1 << 1,		//0010 = 2
	APPEND = 1 << 2,	//0100 = 4
	N_WRITEREAD = 1 << 3,	//1000 = 8

	// mode = READ | WRITE; << will to be read and write
}FileMode;
/*
and that i taken this idea when i maked in c# with flag attribute
[flags]
enum Permission
{
	Write = 1, Read = 2, Execute = 4,.. and so on.
	// 3 is to read and write
}
*/
typedef enum LogFileMode
{
	NEWFILE = N_WRITEREAD,// w
	FILEEXISTED = WRITE | READ,// r+
	//CHECKING = READ
}LogFileMode;

typedef enum {
	LOG_NETWORK_FAILURE,
	LOG_APP_STOPPED,
	LOG_CONFIG_ERROR,
	LOG_UPDATE_REQUIRED,
	LOG_ERROR_LEN
} LOG_ERROR_TYPE;

static char* error_log_type[LOG_ERROR_LEN] = {
	"network failure",
	"app stopped",
	"config error",
	"update required"
};

bool is_file_exist(char* file_name_with_path);

bool is_null(FILE* fptr);

void log_error(char* msg, char* details);

FILE* log_into(char* file_name_with_path, char* input);

void print_loged_errors(char* file_name_with_path);

FILE* open_file(char* file_name_with_path, FileMode mode);

#endif // !LOGSUTILS_H
