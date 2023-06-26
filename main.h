#ifndef MAIN_H
#define MAIN_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define BUFFER_READ 1024
#define BUFFER_WRITE 1024
#define BUF_FLUSH -1

#define GETLINE 0
#define STRTOK 0

#define HISTORY_FILE	".history_file"
#define HISTORY_MAX	4096

#define LOWERCASE	1
#define UNSIGNED	2

#define NORMAL	0
#define OR		1
#define AND		2
#define CHAIN	3


/**
 * struct llstr - singly linked list
 * @number: the number field
 * @str: a string
 * @nextnode: points to the next node
 */
typedef struct llstr
{
	int number;
	char *str;
	struct llstr *nextnode;
} list_t;

/**
 *struct command_info - information related to command execution
 *@arg: arguments
 *@argv: array of strings
 *@path: string path for the current command
 *@argc: argument count
 *@error_count: error count
 *@error_code: error code for exit
 *@linecount: on count
 *@filename: program filename
 *@enviro: ll local copy of environ
 *@environ: copy of environ from LL enviro
 *@history: history
 *@alias: alias
 *@environ_changed: on if environ changed
 *@status: return status of the last executed command
 *@cmd_buffer: buffer commande
 *@cmd_buffer_type: command Type ||, &&, ;
 *@read_fd: file decriptor from which to read line input
 *@historycount: history line number count
 */
typedef struct command_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int error_count;
	int error_code;
	int linecount;
	char *filename;
	list_t *enviro;
	list_t *history;
	list_t *alias;
	char **environ;
	int environ_changed;
	int status;
	char **cmd_buffer;
	int cmd_buffer_type;
	int read_fd;
	int historycount;
} cmdinfo_t;

/**
 * struct builtin_command - a built-in command
 * @command: string.
 * @function: Pointer to the function
 */
typedef struct builtin_command
{
	char *command;
	int (*function)(cmdinfo_t *);
} builtin_command_t;

/* functions */

void _puts(char *);
int _putchar(char);

int _strlen(char *);
int _strcmp(char *, char *);
char *start_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strncpy(char *, char *, int);
char *_strcpy(char *, char *);
char *_strduplicate(const char *);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **_split_str(char *, char *);
char **_split_str2(char *, char);
void free_str(char **);
int myshell(cmdinfo_t *, char **);
int get_built_in(cmdinfo_t *);
void get_command(cmdinfo_t *);
void fork_command(cmdinfo_t *);
int is_command(cmdinfo_t *, char *);
char *duplicate_chars(char *, int, int);
char *get_path(cmdinfo_t *, char *, char *);
void print_input_string(char *);
int write_char(char);
int write_to_fd(char c, int fd);
int print_to_fd(char *str, int fd);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
int free_ptr(void **);
int is_interactive(cmdinfo_t *);
int is_delimeter(char, char *);
int _isalpha(int);
int _atoi(char *);
int parse_integer(char *);
void print_error(cmdinfo_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _shellexit(cmdinfo_t *);
int _cd(cmdinfo_t *);
int _printHelpMessage(cmdinfo_t *);
int _historylist(cmdinfo_t *);
int unset_alias(cmdinfo_t *, char *);
int set_alias(cmdinfo_t *, char *);
int print_alias(list_t *);
int _alias(cmdinfo_t *);
ssize_t input_buf(cmdinfo_t *, char **, size_t *);
ssize_t get_input(cmdinfo_t *);
ssize_t read_buf(cmdinfo_t *, char *, size_t *);
int _getline(cmdinfo_t *, char **, size_t *);
void handleSIGINT(int);
void initialize_info(cmdinfo_t *);
void set_info(cmdinfo_t *, char **);
void free_info(cmdinfo_t *, int);
int _currentenv(cmdinfo_t *);
char *_getenvvalue(cmdinfo_t *, const char *);
int _ssetenv(cmdinfo_t *);
int _uunsetenv(cmdinfo_t *);
int populate_envlist(cmdinfo_t *);
char **get_environ(cmdinfo_t *);
int _unsetenv(cmdinfo_t *, char *);
int _setenv(cmdinfo_t *, char *, char *);
char *get_hist_file(cmdinfo_t *info);
int create_history(cmdinfo_t *info);
int read_historyfile(cmdinfo_t *info);
int addto_history_list(cmdinfo_t *info, char *buf, int linecount);
int reindex_history(cmdinfo_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_toend(list_t **, const char *, int);
size_t print_str_list(const list_t *);
int delete_node_at(list_t **, unsigned int);
void free_list(list_t **);
size_t list_length(const list_t *);
char **list_to_string(list_t *);
size_t print_list(const list_t *);
list_t *node_start_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain_delimeter(cmdinfo_t *, char *, size_t *);
void chain_check(cmdinfo_t *, char *, size_t *, size_t, size_t);
int replace_alias(cmdinfo_t *);
int replace_vars(cmdinfo_t *);
int replace_string(char **, char *);

#endif
