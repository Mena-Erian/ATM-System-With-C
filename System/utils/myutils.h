
#ifndef MYUTILS_H
#define MYUTILS_H

#define CONFIG_FILE_PATH "./configs/atm_config.txt"
#define ERROR_FILE_PATH "./logs/atm_error.log"

//by this way it saved in heap 
/// struct Config {
/// 	char* srver_ip;
/// 	char* middleware;
/// 	char* software_version;
/// };


struct Config {
	char serverip[20];
	char middleware[20];
	char software_version[20];
};


/*
and that i taken this idea when i maked in c# with flag attribute
[flags]
enum Permission
{
	Write = 1, Read = 2, Execute = 4,.. and so on.
	// 3 is to read and write
}
*/

struct Config create_default_config();

FILE* create_config_file(struct Config* config_file);

struct Config read_config_file();

bool ping(char serverip[20]);

void print_ping_status(bool is_reachable);

#endif // !MYUTILS_H
