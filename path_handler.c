#include "shell.h"

/**
 * execute_path - Executes a command given its full path.
 * @command: Full path to the command.
 * @vars: Pointer to the struct of variables.
 *
 * Return: 0 on success, 1 on failure.
 */
int execute_path(char *command, shell_vars_t *vars)
{
	pid_t child_pd;
	if (access(command, X_OK) == 0)
	{
		child_pd = fork();
		if (child_pd == -1)
			print_error_msg(vars, NULL);
		if (child_pd == 0)
		{
			if (execve(command, vars->command_line, vars->env) == -1)
				print_error_msg(vars, NULL);
		}
		else
		{
			wait(&vars->exit_status);
			if (WIFEXITED(vars->exit_status))
				vars->exit_status = WEXITSTATUS(vars->exit_status);
	
			else if (WIFSIGNALED(vars->exit_status) && WTERMSIG(vars->exit_status) == SIGINT)
				vars->exit_status = 130;
			return (0);
		}
		vars->exit_status = 127;
		return (1);
	}
	else
	{
		print_error_msg(vars, ": Permission denied\n");
		vars->exit_status = 126;
	}
	return (0);
}

/**
 * find_path_in_env - Finds the PATH variable in the array of environment variables.
 * @env: Array of environment variables.
 *
 * Return: Pointer to the node that contains the PATH, or NULL on failure.
 */
char *find_path_in_env(char **env)
{
	char *path = "PATH=";
	unsigned int x, y;
	for (x = 0; env[x] != NULL; x++)
	{
		for (y = 0; y < 5; y++)
			if (path[y] != env[x][y])
				break;
		if (y == 5)
			break;
	}
	return (env[x]);
}

/**
 * check_for_path - Checks if the command is in the PATH.
 * @vars: Variables.
 *
 * Return: void.
 */
void check_for_path(shell_vars_t *vars)
{
	char *path, *dup_path = NULL, *check = NULL;
	unsigned int x = 0, t = 0;
	char **path_tokens;
	struct stat buff;

	if (check_dir_exists(vars->command_line[0]))
		t = execute_in_current_dir(vars);
	else
	{
		path = find_path_in_env(vars->env);
		if (path != NULL)
		{
			dup_path = custom_strdup(path + 5);
			path_tokens = tokenize_input(dup_path, ":");
			for (x = 0; path_tokens && path_tokens[x]; x++, free(check))
			{
				check = custom_strcat(path_tokens[x], vars->command_line[0]);
				if (stat(check, &buff) == 0)
				{
					t = execute_path(check, vars);
					free(check);
					break;
				}
			}
			free(dup_path);
			if (path_tokens == NULL)
			{
				vars->exit_status = 127;
				exit_shell(vars);
			}
		}
		if (path == NULL || path_tokens[x] == NULL)
		{
			print_error_msg(vars, ": not found\n");
			vars->exit_status = 127;
		}
		free(path_tokens);
	}
	if (t == 1)
		exit_shell(vars);
}

/**
 * execute_in_current_dir - Executes the command in the current working directory.
 * @vars: Pointer to struct of variables.
 *
 * Return: 0 on success, 1 on failure.
 */
int execute_in_current_dir(shell_vars_t *vars)
{
	pid_t child_pd;
	struct stat buff;

	if (stat(vars->command_line[0], &buff) == 0)
	{
		if (access(vars->command_line[0], X_OK) == 0)
		{
			child_pd = fork();
			if (child_pd == -1)
				print_error_msg(vars, NULL);
			if (child_pd == 0)
			{
				if (execve(vars->command_line[0], vars->command_line, vars->env) == -1)
					print_error_msg(vars, NULL);
			}
			else
			{
				wait(&vars->exit_status);
				if (WIFEXITED(vars->exit_status))
					vars->exit_status = WEXITSTATUS(vars->exit_status);
				else if (WIFSIGNALED(vars->exit_status) && WTERMSIG(vars->exit_status) == SIGINT)
					vars->exit_status = 130;
				return (0);
			}
			vars->exit_status = 127;
			return (1);
		}
		else
		{
			print_error_msg(vars, ": Permission denied\n");
			vars->exit_status = 126;
		}
		return (0);
	}
	print_error_msg(vars, ": Not found\n");
	vars->exit_status = 127;
	return (0);
}

/**
 * check_dir_exists - Checks if the command is a part of a path.
 * @str: Command.
 *
 * Return: 1 on success, 0 on failure.
 */
int check_dir_exists(char *str)
{
	unsigned int x;
	for (x = 0; str[x]; x++)
	{
		if (str[x] == '/')
			return (1);
	}
	return (0);
}
