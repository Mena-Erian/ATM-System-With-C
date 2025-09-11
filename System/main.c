#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "./utils/myutils.h"
#include "./utils/logutils.h"


int main()
{
	/*
		check if config file exist
			if true:
				read
				false:
				make one with default values
	*/

	FILE* fconfig;
	struct Config config;
	char command[100];
	if (!is_file_exist("./configs/atm_config.txt"))
	{
		config = create_default_config();
		fconfig = create_config_file(&config);
	}
	else config = read_config_file();

	/*
		Network Check
	*/
	sprintf(command, "ping -n 1 %s", config.srver_ip);

	if (system(command) == 0)
	{
		printf("success");
	}
	else
	{
		printf("Un reachable");

	}

	//fclose(fconfig);
	return 0;
}