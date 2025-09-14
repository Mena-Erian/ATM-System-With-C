
#ifndef MYUTILS_H
#define MYUTILS_H

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

struct Config create_default_config();

FILE* create_config_file(struct Config* config_file);

struct Config read_config_file();

typedef enum {
	RUNNING,
	STOPPED,
	APP_STATUS_LEN
} APP_STATUS;

static char* app_status_type[APP_STATUS_LEN] = {
   "RUNNING",
   "STOPPED"
};

void check_app_status(APP_STATUS app_status);

APP_STATUS read_app_status();

bool ping(char serverip[20]);

void print_ping_status(bool is_reachable);

#endif // !MYUTILS_H
