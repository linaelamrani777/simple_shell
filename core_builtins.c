#include "shell.h"

/**
 * check_for_shell_builtins - Checks if the command is a shell builtin
 * @shell_vars: Shell variables
 * Return: Pointer to the function or NULL
 */
void (*check_for_shell_builtins(shell_vars_t *vars))(shell_vars_t *vars)
{
	unsigned int y;
	shell_builtins_t check[] = {
		{"exit", exit_shell},
		{"env", print_environment},
		{"setenv", set_env_var},
		{"unsetenv", unset_env_var},
		{NULL, NULL}
	};

	for (y = 0; check[y].function != NULL; y++)
	{
		if (custom_strcmpr(vars->command_line[0], check[y].name) == 0)
			break;
	}
	if (check[y].function != NULL)
		check[y].function(vars);
	return (check[y].function);
}

/**
 * exit_shell - Exit the shell program
 * @vars: Shell variables
 * Return: void
 */
void exit_shell(shell_vars_t *vars)
{
	int exit_status;

	if (custom_strcmpr(vars->command_line[0], "exit") == 0 && vars->command_line[1] != NULL)
	{
		exit_status = custom_atoi(vars->command_line[1]);
		if (exit_status == -1)
		{
			vars->exit_status = 2;
			print_error_msg(vars, ": Illegal number: ");
			custom_puts_stderr(vars->command_line[1]);
			custom_puts_stderr("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->exit_status = exit_status;
	}
	free(vars->input_buffer);
	free(vars->command_line);
	free(vars->commands);
	free_print_env(vars->env);
	exit(vars->exit_status);
}

/**
 * print_environment - Prints the current environment
 * @vars: Struct of variables
 * Return: void
 */
void print_environment(shell_vars_t *vars)
{
	unsigned int y;

	for (y = 0; vars->env[y]; y++)
	{
		custom_puts(vars->env[y]);
		custom_puts("\n");
	}
	vars->exit_status = 0;
}

/**
 * set_env_var - Create a new environment variable, or edit an existing variable
 * @vars: Pointer to struct of variables
 *
 * Return: void
 */
void set_env_var(shell_vars_t *vars)
{
	char **key;
	char *var;

	if (vars->command_line[1] == NULL || vars->command_line[2] == NULL)
	{
		print_error_msg(vars, ": Incorrect number of arguments\n");
		vars->exit_status = 2;
		return;
	}
	key = find_env_var(vars->env, vars->command_line[1]);
	if (key == NULL)
		add_key_value(vars);
	else
	{
		var = add_value_2_key(vars->command_line[1], vars->command_line[2]);
		if (var == NULL)
		{
			print_error_msg(vars, NULL);
			free(vars->input_buffer);
			free(vars->commands);
			free(vars->command_line);
			free_print_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->exit_status = 0;
}

/**
 * unset_env_var - Remove an environment variable
 * @vars: Pointer to a struct of variables
 *
 * Return: void
 */
void unset_env_var(shell_vars_t *vars)
{
	char **key, **newenv;

	unsigned int y, x;

	if (vars->command_line[1] == NULL)
	{
		print_error_msg(vars, ": Incorrect number Of arguments\n");
		vars->exit_status = 2;
		return;
	}
	key = find_env_var(vars->env, vars->command_line[1]);
	if (key == NULL)
	{
		print_error_msg(vars, ": No variable to unset");
		return;
	}
	for (y = 0; vars->env[y] != NULL; y++)
		;
	newenv = malloc(sizeof(char *) * y);
	if (newenv == NULL)
	{
		print_error_msg(vars, NULL);
		vars->exit_status = 127;
		exit_shell(vars);
	}
	for (y = 0; vars->env[y] != *key; y++)
		newenv[y] = vars->env[y];
	for (x = y + 1; vars->env[x] != NULL; x++, y++)
		newenv[y] = vars->env[x];
	newenv[y] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->exit_status = 0;
}
