#include "shell.h"

/**
 * _free - Used to free a pointer
 * @ptr: Address of the pointer to be freed
 *
 * Return: 1 if freed, else 0.
 */
int _free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);	 
		*ptr = NULL; 
		return 1;	 
	}
	return 0; 
}
