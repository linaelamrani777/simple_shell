#include "shell.h"

/**
 * initialize_environment - Make the shell environment from the environment passed to main
 * @env: Environment passed to main
 *
 * Return: Pointer to the new environment
 */
char **initialize_print_env(char **env)
{
	char **new_envr = NULL;
	size_t x;

	for (x = 0; env[x] != NULL; x++)
		;
	new_envr = malloc(sizeof(char *) * (x + 1));

	if (new_envr == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}

	for (x = 0; env[x] != NULL; x++)
		new_envr[x] = custom_strdup(env[x]);
	new_envr[x] = NULL;

	return (new_envr);
}

/**
 * free_environment - Free the shell's environment
 * @env: Shell's environment
 *
 * Return: void
 */
void free_print_env(char **env)
{
	unsigned int x;

	for (x = 0; env[x] != NULL; x++)
		free(env[x]);

	free(env);
}
