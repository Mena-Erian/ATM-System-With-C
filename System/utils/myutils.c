#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "./myutils.h"
#include "./logutils.h"


struct Config create_default_config()
{
	struct Config df;
	strcpy(df.serverip, "192.168.1.1");
	strcpy(df.middleware, "Up");
	strcpy(df.software_version, "1.0.0");

	/*df.srver_ip = "192.168.1.1";
	df.middleware = "Up";
	df.software_version = "1.0.0";*/

	return df;
}

FILE* create_config_file(struct Config* config)
{
	FILE* fconfig_ptr = fopen(CONFIG_FILE_PATH, "w");

	if (fconfig_ptr != NULL)
	{
		fprintf(fconfig_ptr,
			"ServerIP = %s\nMiddlewareState = %s\nSoftwareVersion = %s",
			config->serverip,
			config->middleware,
			config->software_version
		);
	}
	return  fconfig_ptr;
	//exsit(1);
}



struct Config read_config_file()
{
	FILE* fptr = fopen(CONFIG_FILE_PATH, "r");

	if (fptr == NULL)  return;

	struct Config config;
	char _[20];

	//i will back to handle erros :)
	(void)fscanf(fptr, "%s = %s", _, config.serverip);
	(void)fscanf(fptr, "%s = %s", _, config.middleware);
	(void)fscanf(fptr, "%s = %s", _, config.software_version);

	/// printf("%s\n", _, config.srver_ip);
	/// printf("%s\n", _, config.middleware);
	/// printf("%s\n", _, config.software_varsion);

	fclose(fptr);
	return config;
}

bool ping(char serverip[20])
{
	FILE* fcmd_output;
	char command[50];
	char buffer[200];
	bool is_reachable = false;

	sprintf(command, "ping %s", serverip);

	fcmd_output = _popen(command, "r");// may we can use here system() // put i used this to 
	if (fcmd_output == NULL)
	{
		perror("Popen Failed");
		return false;
	}

	while (fgets(buffer, sizeof(buffer), fcmd_output) != NULL)
	{
		//printf("%s", buffer); // to see the output of ping in console
		if (strstr(buffer, "Reply from") != '\0')
		{
			is_reachable = true;
			//print_ping_status(is_reachable); // if needed
			break;
		}
		is_reachable = false;
	}

	if (is_reachable == false)
	{
		log_error(error_log_type[LOG_NETWORK_FAILURE], NULL);
		return false;
	}

	_pclose(fcmd_output);
	return true;
}

void print_ping_status(bool is_reachable)
{

	if (is_reachable)
	{
		printf("success");
	}
	else
	{
		printf("Un reachable");
	}
}


