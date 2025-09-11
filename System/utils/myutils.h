
#ifndef MYUTILS_H
#define MYUTILS_H

//by this way it saved in heap 
/// struct Config {
/// 	char* srver_ip;
/// 	char* middleware;
/// 	char* software_varsion;
/// };

struct Config {
	char srver_ip[20];
	char middleware[20];
	char software_varsion[20];
};

struct Config create_default_config();

FILE* create_config_file(struct Config* config_file);

FILE* create_file(char* file_name, char* input);

struct Config read_config_file();

bool is_file_exist(char* file_name_with_path);

#endif // !MYUTILS_H
