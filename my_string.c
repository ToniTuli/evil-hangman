#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

struct string
{
	int capacity;
	int size;
	char* char_arr;
};
typedef struct string String;

//Precondition: None
//Postcondition: Allocate space for a string object that represents the empty
//   string.  The string will have capacity 7 and size 0 by default. A copy of
//   the address of the opaque object will be returned on success and NULL on
//   failure.
MY_STRING my_string_init_default(void)
{
	String* pMy_string;
	pMy_string = (String*)malloc(sizeof(String));

	if (pMy_string != NULL)
	{
		pMy_string->size = 0;
		pMy_string->capacity = 7;
		pMy_string->char_arr = (char*)malloc(sizeof(char)*pMy_string->capacity);
		if (pMy_string->char_arr == NULL)
		{
			free(pMy_string);
			pMy_string = NULL;
		}
	}

	return (MY_STRING)pMy_string;
}

//Precondtion: c_string is a valid null terminated c-string.
//Postcondition: Allocate space for a string object that represents a string
//   with the same value as the given c-string.  The capacity of the string
//   object will be set to be one greater than is required to hold the string.
//   As an example, the string "the" would set capacity at 4 instead of 3. A
//   copy of the address of the opaque object will be returned on success and
//   NULL on failure.
MY_STRING my_string_init_c_string(const char* c_string)
{
	int i = 0, j=0;
	char *copy;
	String* pMy_string;
	pMy_string = (String*)malloc(sizeof(String));

	if (pMy_string == NULL)
	{
		printf("Fail tochar_arr malloc!.\n");
		free(pMy_string);
		exit(1);
	}

	//malloc for array;
	pMy_string->char_arr = (char*)malloc(sizeof(char*)*pMy_string->capacity);
	if (pMy_string == NULL)
	{
		printf("Failed to malloc!\n");
		free(pMy_string);
		exit(1);
	}

	//get size of str;
	//copy str to array;
	while (c_string[i] != '\0')
	{
		pMy_string->char_arr[i] = c_string[i];
		i++;

		if (i == pMy_string->capacity)
		{
			copy = (char*)malloc(sizeof(char) * pMy_string->capacity);
			for (j = 0; j < pMy_string->size; j++)
				copy[j] = pMy_string->char_arr[j];
			free(pMy_string->char_arr);

			pMy_string->capacity = pMy_string->capacity * 2;
			pMy_string->char_arr = (char*)malloc(sizeof(char) * pMy_string->capacity);
			for (j = 0; j < pMy_string->size; j++)
				pMy_string->char_arr[j] = copy[j];
			free(copy);
		}
	}

	//for(i=0; c_string != '\0'; ++i)
		//pMy_string->char_arr[i] = c_string[i];

	pMy_string->char_arr[i] = '\0';
	pMy_string->capacity = i + 1;
	pMy_string->size = i;

	//return
	return (MY_STRING)pMy_string;
}

//Precondition: phMy_string holds the address of a valid handle to a MY_STRING
//   object.
//Postcondition: The memory used for the MY_STRING object has be reclaimed by
//   the system and the handle referred to by the pointer phMy_string has been
//   set to NULL.
void my_string_destroy(MY_STRING* phMy_string)
{
	String* pMy_string = (String*)*phMy_string;
	free(pMy_string->char_arr);

	free(*phMy_string);
	*phMy_string = NULL;
}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's capacity
int my_string_get_capacity(MY_STRING hMy_string)
{
	String* pMy_string = (String*)hMy_string;
	return pMy_string->capacity;
}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's size.
int my_string_get_size(MY_STRING hMy_string)
{
	String* pMy_string = (String*)hMy_string;
	return pMy_string->size;
}

//Precondition: str1 and str2 are valid My_string objects.
//Postcondition: returns an integer less than zero if the string represented
//   by hLeft_string is lexicographically smaller than hRight_string.  If
//   one string is a prefix of the other string then the shorter string is
//   considered to be the smaller one. (app is less than apple).  Returns
//   0 if the strings are the same and returns a number greater than zero
//   if the string represented by hLeft_string is bigger than hRight_string.
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	String* pStr1 = (String*)hLeft_string;
	String* pStr2 = (String*)hRight_string;
	int i;

	if (pStr1->size < pStr2->size)
	{
		return -1;
	}
	else if (pStr1->size > pStr2->size)
	{
		return 1;
	}
	else
	{
		for (i = 0; i< pStr1->capacity; i++)
		{
			if (pStr1->char_arr[i] > pStr2->char_arr[i])
				return 1;
			if (pStr1->char_arr[i] < pStr2->char_arr[i])
				return -1;
		}
	}
	return 0;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: hMy_string will be the handle of a string object that contains
//   the next string from the file stream fp according to the following rules.
//   1) Leading whitespace will be ignored.
//   2) All characters (after the first non-whitespace character is obtained
//      and included) will be added to the string until a stopping condition
//       is met.  The capacity of the string will continue to grow as needed
//       until all characters are stored.
//   3) A stopping condition is met if we read a whitespace character after
//      we have read at least one non-whitespace character or if we reach
//      the end of the file.
//   Function will return SUCCESS if a non-empty string is read successfully.
//   and failure otherwise.  Remember that the incoming string may aleady
//   contain some data and this function should replace the data but not
//   necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	String* pMy_string = (String*)hMy_string;
	char c, *copy;
	int i = 0;

	pMy_string->char_arr = (char*)malloc(sizeof(char*)*pMy_string->capacity);

	if (fp == NULL)
	{
		printf("Failed to read the file\n");
		return FAILURE;
	}

	pMy_string->size = 0;

	while (fscanf(fp, "%c", &c) != -1)
	{
		if (c == ' ' || c == '\n')
		{
			if (pMy_string->size != 0)
			{
				ungetc(c, fp);
				return SUCCESS;
				i++;
				break;
			}
		}
		else
		{
			pMy_string->char_arr[i] = c;
			i++;
			pMy_string->size = i;
		}

		if (i == pMy_string->capacity)
		{
			copy = (char*)malloc(sizeof(char) * pMy_string->capacity);
			for (i = 0; i < pMy_string->size; i++)
				copy[i] = pMy_string->char_arr[i];
			free(pMy_string->char_arr);

			pMy_string->capacity = pMy_string->capacity * 2;
			pMy_string->char_arr = (char*)malloc(sizeof(char) * pMy_string->capacity);
			for (i = 0; i < pMy_string->size; i++)
				pMy_string->char_arr[i] = copy[i];
			free(copy);
		}
	}

	return FAILURE;

}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Writes the characters contained in the string object indicated
//   by the handle hMy_string to the file stream fp.
//   Function will return SUCCESS if it successfully writes the string and
//   FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	String* pMy_string = (String*)hMy_string;
	int i;

	for (i = 0; i<pMy_string->size; i++)
		fprintf(fp, "%c", pMy_string->char_arr[i]);
	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: If successful, places the character item at the end of the
//   string and returns SUCCESS.  If the string does not have enough room and
//   cannot resize to accomodate the new character then the operation fails
//   and FAILURE is returned.  The resize operation will attempt to amortize
//   the cost of a resize by making the string capacity somewhat larger than
//   it was before (up to 2 times bigger).
Status my_string_push_back(MY_STRING hMy_string, char item)
{
	String* pMy_string = (String*)hMy_string;
	char c, *copy;
	int i = 0;

	if (pMy_string->size >= pMy_string->capacity)
	{
		copy = (char*)malloc(sizeof(char) * pMy_string->capacity);
		for (i = 0; i < pMy_string->size; i++)
			copy[i] = pMy_string->char_arr[i];
		free(pMy_string->char_arr);

		pMy_string->capacity = pMy_string->capacity * 2;
		pMy_string->char_arr = (char*)malloc(sizeof(char) * pMy_string->capacity);
		for (i = 0; i < pMy_string->size; i++)
			pMy_string->char_arr[i] = copy[i];
		free(copy);
	}
	if (pMy_string->size >= pMy_string->capacity)
	{
		printf("Failed to resize the capacity of String.\n");
		return FAILURE;
	}

	pMy_string->char_arr[pMy_string->size] = item;
	pMy_string->size++;

	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Removes the last character of a string in constant time.
//  Guaranteed to not cause a resize operation of the internal data.  Returns
//  SUCCESS on success and FAILURE if the string is empty.
Status my_string_pop_back(MY_STRING hMy_string)
{
	String* pMy_string = (String*)hMy_string;

	if (my_string_get_size(pMy_string) == 0)
		return FAILURE;
	
	pMy_string->size--;
	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition:  Returns the address of the character located at the given
//   index if the index is in bounds but otherwise returns NULL.  This address
//   is not usable as a c-string since the data is not NULL terminated and is
//   intended to just provide access to the element at that index.
char* my_string_at(MY_STRING hMy_string, int index)
{
	String* pMy_string = (String*)hMy_string;

	if (index <= pMy_string->size)
	{
		return (char*)pMy_string->char_arr[index];
	}
	else
	{
		return NULL;
	}
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the first element of the string object
//   for use as a c-string.  The resulting c-string is guaranteed to be NULL
//   terminated and the memory is still maintained by the string object though
//   the NULL is not actually counted as part of the string (in size).
char* my_string_c_str(MY_STRING hMy_string)
{
	String* pMy_string = (String*)hMy_string;
	char *c;
	int i = 0;
	c = (char*)malloc(sizeof(char*)*pMy_string->capacity);

	while (i < pMy_string->size)
	{
		c[i] = pMy_string->char_arr[i];
		i++;
	}

	return c;
}

//Precondition: hResult and hAppend are handles to valid My_string objects.
//Postcondition:  hResult is the handle of a string that contains the original
//   hResult object followed by the hAppend object concatenated together. This
//   function should guarantee no change to the hAppend object and return
//   SUCCESS if they operation is successful and FAILURE if the hResult object
//   is unable to accomodate the characters in the hAppend string perhaps
//   because of a failed resize operation.  On FAILURE, no change to either
//   string shouldbe made.
/*Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	String* phResult = (String*)hResult;
	String* phAppend = (String*)hAppend;

	int i, j;
	char *copy;

	for (j = 0; j < phAppend->size; j++)
	{
		phResult->char_arr[phResult->size + j] = phAppend->char_arr[j];

		if (phResult->size >= phResult->capacity)
		{
			copy = (char*)malloc(sizeof(char) * phResult->capacity);
			for (i = 0; i < phResult->size; i++)
				copy[i] = phResult->char_arr[i];
			free(phResult->char_arr);

			phResult->capacity = phResult->capacity * 2;
			phResult->char_arr = (char*)malloc(sizeof(char) * phResult->capacity);
			for (i = 0; i < phResult->size; i++)
				phResult->char_arr[i] = copy[i];
			free(copy);
		}

		if (phResult->size >= phResult->capacity)
			return FAILURE;
	}

	phResult->char_arr[phResult->size + j] = '\0';

	return SUCCESS;
}*/
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	String* phAppend = (String*)hAppend;
	int i = 0;

	while (i < phAppend->size)
	{
		my_string_push_back(hResult, phAppend->char_arr[i]);
		i++;
	}

	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns an enumerated type with value TRUE if the string
//   is empty and FALSE otherwise.
Boolean my_string_empty(MY_STRING hMy_string)
{
	String* pMy_string = (String*)hMy_string;

	if (my_string_get_size(pMy_string) == 0)
		return TRUE;

	return FALSE;
}
