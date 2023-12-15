#include "shell.h"


/**
 * tokenize_input - Tokenizes an input_buffer with a delimiter.
 * @input_buffer: Input buffer to tokenize.
 * @delimiter: Delimiter to tokenize along.
 *
 * Return: Pointer to an array of pointers to the tokenns.
 */
char **tokenize_input(char *input_buffer, char *delimiter)
{
	char **tokenns = NULL;
	size_t i = 0, mcommand_count = 10;

	if (input_buffer == NULL)
		return (NULL);
	tokenns = malloc(sizeof(char *) * mcommand_count);
	if (tokenns == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((tokenns[i] = custom_strtok(input_buffer, delimiter)) != NULL)
	{
		i++;
		if (i == mcommand_count)
		{
			tokenns = custom_realloc(tokenns, &mcommand_count);
			if (tokenns == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		input_buffer = NULL;
	}
	return (tokenns);
}
