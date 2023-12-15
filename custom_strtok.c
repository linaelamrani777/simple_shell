#include "shell.h"

/**
 * check_match - Checks if a character matches any in a string
 * @c: Character to check
 * @str: String to check
 *
 * Return: 1 If match, 0 If not
 */
unsigned int check_match(char c, const char *str)
{
	unsigned int x;

	for (x = 0; str[x] != '\0'; x++)
	{
		if (c == str[x])
			return (1);
	}
	return (0);
}

/**
 * custom_strtok - Custom strtok
 * @str: String to tokenize_input
 * @delim: Delimiter to tokenize_input against
 *
 * Return: Pointer to the next token or NULL
 */
char *custom_strtok(char *str, const char *delim)
{
	static char *s_token;
	static char *n_token;
	unsigned int x;

	if (str != NULL)
		n_token = str;
	s_token = n_token;
	if (s_token == NULL)
		return (NULL);
	for (x = 0; n_token[x] != '\0'; x++)
	{
		if (check_match(n_token[x], delim) == 0)
			break;
	}
	if (n_token[x] == '\0' || n_token[x] == '#')
	{
		n_token = NULL;
		return (NULL);
	}
	s_token = n_token + x;
	n_token = s_token;
	for (x = 0; n_token[x] != '\0'; x++)
	{
		if (check_match(n_token[x], delim) == 1)
			break;
	}
	if (n_token[x] == '\0')
		n_token = NULL;
	else
	{
		n_token[x] = '\0';
		n_token = n_token + x + 1;
		if (*n_token == '\0')
			n_token = NULL;
	}
	return (s_token);
}
