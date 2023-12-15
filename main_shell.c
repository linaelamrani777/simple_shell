#include "shell.h"

/* Global variable for handling Ctrl+C (^C) */
unsigned int cntr_c;

/**
 * shortcut_sig - Handles the Ctrl+C (^C) signal interrupt.
 * @uv: Unused variable (required for the signal function prototype).
 *
 * Return: void.
 */
static void shortcut_sig(int uv)
{
	(void) uv;
	if (cntr_c == 0)
		custom_puts("\n$ ");
	else
		custom_puts("\n");
}

/**
 * main - Main function for the shell.
 * @argc: Number of arguments passed to main.
 * @initial_args: Array of arguments passed to main.
 * @environment: Array of environment variables.
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **initial_args, char **environment)
{
	size_t len_input_buffer = 0;
	unsigned int is_pip = 0, x;
	shell_vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.initial_args = initial_args;
	vars.env = initialize_print_env(environment);
	signal(SIGINT, shortcut_sig);
	if (!isatty(STDIN_FILENO))
		is_pip = 1;
	if (is_pip == 0)
		custom_puts("$ ");
	cntr_c = 0;
	while (getline(&(vars.input_buffer), &len_input_buffer, stdin) != -1)
	{
		cntr_c = 1;
		vars.command_count++;
		vars.commands = tokenize_input(vars.input_buffer, ";");
		for (x = 0; vars.commands && vars.commands[x] != NULL; x++)
		{
			vars.command_line = tokenize_input(vars.commands[x], "\n \t\r");
			if (vars.command_line && vars.command_line[0])
				if (check_for_shell_builtins(&vars) == NULL)
					check_for_path(&vars);
			free(vars.command_line);
		}
		free(vars.input_buffer);
		free(vars.commands);
		cntr_c = 0;
		if (is_pip == 0)
			custom_puts("$ ");
		vars.input_buffer = NULL;
	}
	if (is_pip == 0)
		custom_puts("\n");
	free_print_env(vars.env);
	free(vars.input_buffer);
	exit(vars.exit_status);
}
