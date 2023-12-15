#include "shell.h"

/**
 * add_key_value - Create a new environment variable
 * @vars: Pointer to struct of variables
 *
 * Return: void
 */
void add_key_value(shell_vars_t *vars)
{
	unsigned int y;
	char **new_envr;

	for (y = 0; vars->env[y] != NULL; y++)
		;
	new_envr = malloc(sizeof(char *) * (y + 2));
	if (new_envr == NULL)
	{
		print_error_msg(vars, NULL);
		vars->exit_status = 127;
		exit_shell(vars);
	}
	for (y = 0; vars->env[y] != NULL; y++)
		new_envr[y] = vars->env[y];
	new_envr[y] = add_value_2_key(vars->command_line[1], vars->command_line[2]);
	if (new_envr[y] == NULL)
	{
		print_error_msg(vars, NULL);
		free(vars->input_buffer);
		free(vars->commands);
		free(vars->command_line);
		free_print_env(vars->env);
		free(new_envr);
		exit(127);
	}
	new_envr[y + 1] = NULL;
	free(vars->env);
	vars->env = new_envr;
}

/**
 * find_env_var - Finds an environment variable
 * @env: Array of environment variables
 * @key: Environment variable to find
 *
 * Return: Pointer to address of the environment variable
 */
char **find_env_var(char **env, char *key)
{
	unsigned int y, x, len;

	len = custom_strlen(key);
	for (y = 0; env[y] != NULL; y++)
	{
		for (x = 0; x < len; x++)
			if (key[x] != env[y][x])
				break;
		if (x == len && env[y][x] == '=')
			return (&env[y]);
	}
	return (NULL);
}

/**
 * add_value_2_key - Create a new environment variable string
 * @key: Variable name
 * @value: Variable value
 *
 * Return: Pointer to the new string
 */
char *add_value_2_key(char *key, char *value)
{
	unsigned int len_1, len_2, y, x;
	char *new;

	len_1 = custom_strlen(key);
	len_2 = custom_strlen(value);
	new = malloc(sizeof(char) * (len_1 + len_2 + 2));

	if (new == NULL)
		return (NULL);
	for (y = 0; key[y] != '\0'; y++)
		new[y] = key[y];
	new[y] = '=';
	for (x = 0; value[x] != '\0'; x++)
		new[y + 1 + x] = value[x];
	new[y + 1 + x] = '\0';
	return (new);
}

/**
 * custom_atoi - Converts a string into an integer
 * @str: String to convert
 *
 * Return: The integer value, or -1 if an error occurs
 */
int custom_atoi(char *str)
{
	unsigned int y, idigits;
	int num = 0, test_num;

	test_num = INT_MAX;
	for (idigits = 0; test_num != 0; idigits++)
		test_num /= 10;

	for (y = 0; str[y] != '\0' && y < idigits; y++)
	{
		num *= 10;
		if (str[y] < '0' || str[y] > '9')
			return (-1);

		if ((y == idigits - 1) && (str[y] - '0' > INT_MAX % 10))
			return (-1);

		num += str[y] - '0';
		if ((y == idigits - 2) && (str[y + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (y > idigits)
		return (-1);
	return (num);
}
