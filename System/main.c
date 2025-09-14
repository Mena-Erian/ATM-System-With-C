#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



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

	// FILE* fconfig;
	// FILE* fcmd_output;
	struct Config config;
	APP_STATUS app_status;

	config = read_config_file();
	// Network Check
	if (strcmp(config.middleware, "Up") == 0)
	{
		if (ping(config.serverip) == false)
		{
			printf("Error: Network Failure\n");
			//exit(1);
		}
		app_status = read_app_status();
		check_app_status(app_status);
		check_software_version(config);
	}

	/// FILE* fp;
	/// char buffer[1024];
	/// 
	/// // Execute the 'ls -l' command and read its output
	/// fp = _popen("ping 8.8.8.8 -t", "r");
	/// if (fp == NULL) {
	/// 	perror("popen failed");
	/// 	return 1;
	/// }
	/// 
	/// // Read and print the output line by line
	/// while (fgets(buffer, sizeof(buffer), fp) != NULL) {
	/// 	printf("%s", buffer);
	/// }
	/// 
	/// // Close the pipe
	/// _pclose(fp);

	//fclose(fconfig);

	return 0;
}