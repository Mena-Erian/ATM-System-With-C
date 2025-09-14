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
	struct Config config;
	APP_STATUS app_status;

	config = read_config_file();

	if (strcmp(config.middleware, "Up") == 0)
	{
		char choise;
		do
		{
			print_menu_admin();

			int operation_number = 0;
			scanf_s("%i", &operation_number);
			switch (operation_number)
			{
			case 1: // Network Check
				if (ping(config.serverip)) printf("\nYour in good Network Connection :)");
				else printf("\nError: Network Failure :(\n");
				break;
			case 2: // App Health Check
				app_status = read_app_status();
				if (check_app_status(app_status) == true) printf("\nYour App Statis is: %s.", app_status_type[RUNNING]);
				break;
			case 3: // Read Logs Error
				(void)print_loged_errors(ERROR_FILE_PATH);
				break;
			case 4:	//Check Version
				check_software_version(config);
				break;
			
			default:
				system("cls");
				printf("Your Input Was Not Valid, try again..\n");
			}

			printf("\n\nTo show menu again press any key Enter and to exit click Esc\n");
			while ((getchar()) != '\n'); // flush leftover newline
			choise = getchar(); //

			//getchar();
			//scanf(" %c", &choise);   // note the SPACE before %c -> skips \n, \t, etc.

		} while ((int)choise != 27);
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