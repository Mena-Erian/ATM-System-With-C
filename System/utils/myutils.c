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

void check_config_file_member_key(char* finput, APP_CONFIG_FILE_MEMBERS member)
{
	if (_stricmp(finput, app_config_file_type[member]) == 0)
	{
		return member;
	}

	char err_dtls[150] = "";
	sprintf(err_dtls, "Cannot Read %s From Config file", app_config_file_type[member]);
	printf(err_dtls);
	log_error(error_log_type[LOG_CONFIG_ERROR], err_dtls);
	exit(1);
};

struct Config read_config_file()
{
	FILE* fptr = fopen(CONFIG_FILE_PATH, "r");

	if (fptr == NULL) {
		perror("Cannot Read Config file");
		log_error(error_log_type[LOG_CONFIG_ERROR], "Cannot Read Config file");
		exit(1);
	}


	struct Config config;
	char config_key[20];
	int temp_check;

	//i will back to handle erros :)
	temp_check = fscanf(fptr, "%s = %s", config_key, config.serverip);
	if (temp_check == 1)
	{
		printf("Cannot Read Server ip from Config file");
		log_error(error_log_type[LOG_CONFIG_ERROR], "Cannot Read Server ip from Config file");
		exit(1);
	};
	check_config_file_member_key(config_key, CONF_SERVERIP);

	temp_check = -1;
	temp_check = fscanf(fptr, "%s = %s", config_key, config.middleware);
	if (temp_check == 1)
	{
		printf("Cannot Read Middleware from Config file");
		log_error(error_log_type[LOG_CONFIG_ERROR], "Cannot Read Middleware from Config file");
		exit(1);
	};

	check_config_file_member_key(config_key, CONF_MIDDLEWARESTATE);

	temp_check = -1;
	temp_check = fscanf(fptr, "%s = %s", config_key, config.software_version);
	if (temp_check == 1)
	{
		printf("Cannot Read Software Version from Config file");
		log_error(error_log_type[LOG_CONFIG_ERROR], "Cannot Read Software Version from Config file");
		exit(1);
	};
	check_config_file_member_key(config_key, CONF_SOFTWARE_VERSION);

	/// printf("%s\n", _, config.srver_ip);
	/// printf("%s\n", _, config.middleware);
	/// printf("%s\n", _, config.software_version);

	fclose(fptr);
	return config;
}

void check_software_version(struct Config config)
{
	printf("Software Version Check...");

	char temp_buffer[250];
	double version = strtod(config.software_version, &temp_buffer);
	//printf("%.2f\n", version);
	*temp_buffer = "";
	sprintf(temp_buffer, "The Present Version is %.2f ", version);
	if (version < 2.0)
	{
		printf("Update Required\n");
		log_error(error_log_type[LOG_UPDATE_REQUIRED], &temp_buffer);
	}
}

void check_app_status(APP_STATUS app_status)
{
	printf("App Helth Check...");
	if (app_status == STOPPED)
	{
		printf("Application Down...");
		log_error(error_log_type[LOG_APP_STOPPED], "Application Down");
		exit(1);
	}
	system("cls");
}

APP_STATUS read_app_status()
{
	// that just default value maybe we should change it in the future (based on business)
	APP_STATUS app_status = STOPPED;
	FILE* fptr = open_file(STATUS_FILE_PATH, READ);
	char buffer[10] = "";

	if (fscanf(fptr, "%s", buffer) == 1)
	{
		//printf("%s", buffer);
		if (_stricmp(buffer, app_status_type[RUNNING]) == 0)
		{
			app_status = RUNNING;
			return app_status;
		}
		else if (_stricmp(buffer, app_status_type[STOPPED]) == 0)
		{
			app_status = STOPPED;
			return app_status;
		}
	}
	return app_status;
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
		printf("Network Checking...\n");
		if (strstr(buffer, "Reply from") != '\0')
		{
			is_reachable = true;
			//print_ping_status(is_reachable); // if needed
			break;
		}
		is_reachable = false;
	}
	system("cls");
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


