#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

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

/* Read/write buffer sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining types */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Convert number options */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Use system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".my_shell_history"
#define HIST_MAX 4096

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

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 */
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

    char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

/* Function prototypes */

/* toem_shloop.c */
int my_shell(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loop_shell(char **);

/* toem_errors.c */
void error_puts(char *);
int error_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* toem_string.c */
int str_length(char *);
int str_compare(char *, char *);
char *starts_with(const char *, const char *);
char *str_concat(char *, char *);

/* toem_string1.c */
char *str_copy(char *, char *);
char *str_duplicate(const char *);
void string_puts(char *);
int string_putchar(char);

/* toem_exits.c */
char *str_n_copy(char *, char *, int);
char *str_n_concat(char *, char *, int);
char *str_character(char *, char);

/* toem_tokenizer.c */
char **string_to_words(char *, char *);
char **string_to_words2(char *, char);

/* toem_realloc.c */
char *mem_set(char *, char, unsigned int);
void free_ptr_array(char **);
void *my_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int buffer_free(void **);

/* toem_atoi.c */
int interactive_mode(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_integer(char *);

/* toem_errors1.c */
int error_string_to_integer(char *);
void print_shell_error(info_t *, char *);
int print_decimal(int, int);
char *convert_to_string(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int exit_shell(info_t *);
int change_directory(info_t *);
int help_shell(info_t *);

/* toem_builtin1.c */
int history_shell(info_t *);
int alias_shell(info_t *);

/* toem_getline.c */
ssize_t get_shell_input(info_t *);
int get_line(info_t *, char **, size_t *);
void signal_interrupt_handler(int);

/* toem_getinfo.c */
void clear_shell_info(info_t *);
void set_shell_info(info_t *, char **);
void free_shell_info(info_t *, int);

/* toem_environ.c */
char *get_environment_variable(info_t *, const char *);
int shell_environment(info_t *);
int set_shell_environment(info_t *);
int unset_shell_environment(info_t *);
int populate_environment_list(info_t *);

/* toem_getenv.c */
char **get_shell_environment(info_t *);
int unset_environment_variable(info_t *, char *);
int set_environment_variable(info_t *, char *, char *);

/* toem_history.c */
char *get_shell_history_file(info_t *info);
int write_shell_history(info_t *info);
int read_shell_history(info_t *info);
int build_shell_history_list(info_t *info, char *buffer, int linecount);
int renumber_shell_history(info_t *info);

/* toem_lists.c */
list_t *add_node_to_list(list_t **, const char *, int);
list_t *add_node_to_list_end(list_t **, const char *, int);
size_t print_list_of_strings(const list_t *);
int delete_node_at_list_index(list_t **, unsigned int);
void free_list_of_strings(list_t **);

/* toem_lists1.c */
size_t list_length(const list_t *);
char **list_to_string_array(list_t *);
size_t print_list_of_integers(const list_t *);
list_t *node_starts_with_string(list_t *, char *, char);
ssize_t get_node_index_in_list(list_t *, list_t *);

/* toem_vars.c */
int is_command_chain(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_shell_alias(info_t *);
int replace_shell_variables(info_t *);
int replace_string(char **, char *);

/* Function Declarations */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

#endif /* _MY_SHELL_H_ */

