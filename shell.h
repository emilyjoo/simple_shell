#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global env */
extern char **environ;
/* Global program */
char *name;
/* Global counter */
int hist;

/**
 * struct list_s - Struct type defining a linked list.
 * @dir: Directory path.
 * @next: Pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - Struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: Pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s -Struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next:Pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void *re_alloc(void *ptr, unsigned int past_size, unsigned int current_size);
char **str_tok(char *line, char *delim);
char *get_path(char *command);
list_t *_dirpath(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);

void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* Error Handling */
int costum_error(char **args, int err);
char *env_error(char **args);
char *alias_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);
char *error_126(char **args);
char *error_127(char **args);

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

int (*get_builtin(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int env_cmd(char **args, char **front);
int setenv_cmd(char **args, char **front);
int unsetenv_cmd(char **args, char **front);
int cd_cmd(char **args, char **front);
int alias_cmd(char **args, char **front);
int shell_help(char **args, char **front);
char **copy_env(void);
void _freeenv(void);
char **get_env(const char *var);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_commands(char *file_path, int *exe_ret);

#endif
