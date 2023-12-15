#include "shell.h"

/**
 * print_error_msg - Prints error messages to standard error
 * @vars: Pointer to struct of variables
 * @msg: Message to print
 *
 * Return: void
 */
void print_error_msg(shell_vars_t *vars, char *msg)
{
	char *command_count;

	custom_puts_stderr(vars->initial_args[0]);
	custom_puts_stderr(": ");
	command_count = _uitoa(vars->command_count);
	custom_puts_stderr(command_count);
	free(command_count);
	custom_puts_stderr(": ");
	custom_puts_stderr(vars->command_line[0]);
	if (msg)
	{
		custom_puts_stderr(msg);
	}
	else
		perror("");
}
/**
 * custom_puts_stderr - Prints a string to standard error
 * @str: String to print
 *
 * Return: void
 */
void custom_puts_stderr(char *str)
{
	ssize_t num, len;

	num = custom_strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - Converts an unsigned int to a string
 * @command_count: Unsigned int to convert
 *
 * Return: Pointer to the converted string
 */
char *_uitoa(unsigned int command_count)
{
	char *str_num;
	unsigned int tmp, idigits;

	tmp = command_count;
	for (idigits = 0; tmp != 0; idigits++)
		tmp /= 10;
	str_num = malloc(sizeof(char) * (idigits + 1));
	if (str_num == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	str_num[idigits] = '\0';
	for (--idigits; command_count; --idigits)
	{
		str_num[idigits] = (command_count % 10) + '0';
		command_count /= 10;
	}

	return (str_num);
}
