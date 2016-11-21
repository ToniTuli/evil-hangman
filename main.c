#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string = NULL;
	MY_STRING hMy_string1 = NULL;
	char c;
	
	hMy_string = my_string_init_c_string("Hello this is sprta");
	hMy_string1 = my_string_init_c_string(" and we are...");

	//hMy_string1 = my_string_init_c_string("Hello");

	my_string_insertion(hMy_string, stdout);
	printf("\n---\n");
	my_string_insertion(hMy_string1, stdout);
	printf("\n---\n");
	my_string_push_back(hMy_string, 'A');
	my_string_insertion(hMy_string, stdout);
	my_string_concat(hMy_string, hMy_string);
	my_string_insertion(hMy_string, stdout);
	printf("\n---\n");


	my_string_destroy(&hMy_string);
	return 0;
}
