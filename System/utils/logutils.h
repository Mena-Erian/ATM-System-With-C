
#ifndef LOGSUTILS_H
#define LOGSUTILS_H


typedef enum FileMode
{
	WRITE = 1 << 0,		//0001 = 1
	READ = 1 << 1,		//0010 = 2
	APPEND = 1 << 2,	//0100 = 4
	N_WRITEREAD = 1 << 3,	//1000 = 8

	// mode = READ | WRITE; << will to be read and write
}FileMode;

typedef enum LogFileMode
{
	NEWFILE = N_WRITEREAD,// w
	FILEEXISTED = WRITE | READ,// r+
	//CHECKING = READ
}LogFileMode;

bool is_this_file_name_exist(char* file_name_with_path);

bool is_file_exist(FILE* fptr);

void log_error(char* msg, char* details);

FILE* log_into(char* file_name_with_path, char* input);

FILE* open_file(char* file_name_with_path, FileMode mode);

#endif // !LOGSUTILS_H
