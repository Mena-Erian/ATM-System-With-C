#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//#include "./utils/myutils.h"

extern bool is_file_exist(char* file_name_with_path);



int main()
{
	/*
		check if config file exist
			if true:
				read
				false:
				make one with default values
	*/
	

	if (is_file_exist("./../configs/atm_config.txt"))
	{
		printf("file exist");
	}
	else {
		printf("file not exist");

	}

	/*
		Network Check


	*/



	return 0;
}