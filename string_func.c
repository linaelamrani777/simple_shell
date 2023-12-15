#include "shell.h"

/**
 * custom_puts - Writes a string to standard output.
 * @str: String to write.
 *
 * Return: Number of characters printed or -1 on failure.
 */
ssize_t custom_puts(char *str)
{
	ssize_t num, len;

	num = custom_strlen(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}

/**
 * custom_strdup - Returns a pointer to a new memory allocation space containing a copy.
 * @strtod_up: String to be duplicated.
 *
 * Return: A pointer to the new duplicated string.
 */
char *custom_strdup(char *strtod_up)
{
	char *copy;

	int len, x;

	if (strtod_up == 0)
		return (NULL);

	for (len = 0; strtod_up[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (x = 0; x <= len; x++)
		copy[x] = strtod_up[x];

	return (copy);
}

/**
 * custom_strcmpr - Compares two strings.
 * @strcmp_1: First string, of two, to be compared in length.
 * @strcmp_2: Second string, of two, to be compared.
 *
 * Return: 0 on success, anything else is a failure.
 */
int custom_strcmpr(char *strcmp_1, char *strcmp_2)
{
	int x;

	x = 0;
	while (strcmp_1[x] == strcmp_2[x])
	{
		if (strcmp_1[x] == '\0')
			return (0);
		x++;
	}
	return (strcmp_1[x] - strcmp_2[x]);
}

/**
 * custom_strcat - Concatenates two strings.
 * @strc_1: First string.
 * @strc_2: Second string.
 *
 * Return: Pointer to the resulting string.
 */
char *custom_strcat(char *strc_1, char *strc_2)
{
	char *newstring;
	unsigned int len_1, len_2, new_len, x, y;

	len_1 = 0;
	len_2 = 0;
	if (strc_1 == NULL)
		len_1 = 0;
	else
	{
		for (len_1 = 0; strc_1[len_1]; len_1++)
			;
	}
	if (strc_2 == NULL)
		len_2 = 0;
	else
	{
		for (len_2 = 0; strc_2[len_2]; len_2++)
			;
	}
	new_len = len_1 + len_2 + 2;
	newstring = malloc(new_len * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	for (x = 0; x < len_1; x++)
		newstring[x] = strc_1[x];
	newstring[x] = '/';
	for (y = 0; y < len_2; y++)
		newstring[x + 1 + y] = strc_2[y];
	newstring[len_1 + len_2 + 1] = '\0';
	return (newstring);
}

/**
 * custom_strlen - Returns the length of a string.
 * @str: String to be measured.
 *
 * Return: Length of the string.
 */
unsigned int custom_strlen(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++)
		;
	return (len);
}
