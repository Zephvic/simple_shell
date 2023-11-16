#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;
/* for interactive.c */
int is_interactive(info_t *info)
int is_delimeter(char c, char *delimeter)
int _isalphabate(int c)
int _teger(char *s)

/* for construction.c */
int _customexit(info_t *info)
int _my_dir(info_t *info)
int _myhelper(info_t *info)

/* for constructin1.c */
int _myhis(info_t *info)
int set_alias(info_t *info, char *str)
int reset_alias(info_t *info, char *str)
int printalias(list_t *node)
int _mybuiltin(info_t *info)

/* for envi.c*/
int _myenvi(info_t *info)
char *_getenviron(info_t *info, const char *name)
int _mynewenv(info_t *info)
int _remove_env(info_t *info)
int populate_env_list(info_t *info)

/* for error0.c */
void _inputs(char *str)
int _eputchar(char c)
int _inputfd(char c, int fd)
int _putsfd(char *str, int fd)

/* for error1.c */
int _stringint(char *s)
void _errormsg(info_t *info, char *estr)
int print_deci(int input, int fd)
char *convert_number(long int num, int base, int flags)
void rm_comments(char *buf)

/* for close.c */
char *_strngcpy(char *dest, char *src, int n)
char *_strnconcate(char *dest, char *src, int n)
char *_chrlocat(char *s, char c)

/* for getlines.c  */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
ssize_t get_input(info_t *info)
ssize_t reads_buf(info_t *info, char *buf, size_t *i)
int _getline(info_t *info, char **ptr, size_t *length)
void sigint_Handler(__attribute__((unused))int sig_num)

/* for getenviron.c */
char **get_environment(info_t *info)
int _unsetenv(info_t *info, char *var)
int _setenviron(info_t *info, char *var, char *value)

/* for getinformation.c */
void clear_info(info_t *info)
void _info(info_t *info, char **av)
void free_info(info_t *info, int all)

/* for gethis.c */
char *history_file(info_t *info)
int create_history(info_t *info)
int study_history(info_t *info)
int build_history_list(info_t *info, char *buf, int linecount)
int renumber_history(info_t *info)

/* for add node list */
list_t *addnode(list_t **head, const char *str, int num)
list_t *node_end(list_t **head, const char *str, int num)
size_t list_str(const list_t *h)
int delete_node(list_t **head, unsigned int index)
void free_list(list_t **head_ptr)

/* for listlen.c */
ssize_t node_index(list_t *head, list_t *node)
list_t *node_starts(list_t *node, char *prefix, char c)
size_t print_list(const list_t *h)
char **list_strings(list_t *head)
size_t list_len(const list_t *h)

#endif
