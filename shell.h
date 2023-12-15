#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>


/**
 * struct shell_variables - Shell variables
 * @command_line: Command line arguments
 * @input_buffer: Input buffer of the command
 * @environment: Environment variables
 * @command_count: Counts of commands entered
 * @initial_args: Arguments at the opening of the shell
 * @exit_status: Exit status
 * @commands: Array of commands
 */
typedef struct shell_variables
{
	char **command_line;
	char *input_buffer;
	char **env;
	size_t command_count;
	char **initial_args;
	int exit_status;
	char **commands;
} shell_vars_t;

/**
 * struct shell_shell_builtins - Struct for the builtin functions
 * @name: Name of builtin command
 * @function: Function for corresponding builtin
 */
typedef struct shell_builtins
{
	char *name;
	void (*function)(shell_vars_t *);
} shell_builtins_t;

char **initialize_print_env(char **env);
void free_print_env(char **env);

ssize_t custom_puts(char *str);
char *custom_strdup(char *strtod_up);
int custom_strcmpr(char *strcmp_1, char *strcmp_2);
char *custom_strcat(char *strc_1, char *strc_2);
unsigned int custom_strlen(char *str);

char **tokenize_input(char *input_buffer, char *delimiter);
char **custom_realloc(char **ptr, size_t *size);
char *custom_strtok(char *str, const char *delim);

void (*check_for_shell_builtins(shell_vars_t *vars))(shell_vars_t *vars);
void exit_shell(shell_vars_t *vars);
void print_environment(shell_vars_t *vars);
void set_env_var(shell_vars_t *vars);
void unset_env_var(shell_vars_t *vars);

void add_key_value(shell_vars_t *vars);
char **find_env_var(char **env, char *key);
char *add_value_2_key(char *key, char *value);
int custom_atoi(char *str);

void check_for_path(shell_vars_t *vars);
int execute_path(char *command, shell_vars_t *vars);
char *find_path_in_env(char **env);
int execute_in_current_dir(shell_vars_t *vars);
int check_dir_exists(char *str);

void print_error_msg(shell_vars_t *vars, char *msg);
void custom_puts_stderr(char *str);
char *_uitoa(unsigned int command_count);

#endif /* _SHELL_H_ */
