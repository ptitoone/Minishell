#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR_ARG	"doesn't accept arguments"
# define ERR_MEM	"no memory found"
# define ERR_IDENT	"': not a valid identifier"
# define ERR_PIPE	"syntax error near unexpected token `|'"
# define PROMPT		"minishell-4.2$ "

# include <curses.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include "./libft.h"

typedef struct s_token		t_token;
struct s_token
{
	char		*cmd;
	char		**args;
	char		*cmd_path;
	char		*infile;
	int			infd;
	char		*outfile;
	int			outfd;
	t_ribool	append;
	t_ribool	hd;
	t_token		*next;
};

typedef struct s_var_env	t_var_env;
struct				s_var_env
{
	char		*env;
	char		*key;
	char		*value;
	t_var_env	*prev;
	t_var_env	*next;
	t_var_env	*left;
	t_var_env	*right;
};

typedef struct s_cmd_kv		t_cmd_kv;
typedef struct s_ms_vars	t_ms_vars;

typedef int					(*t_fctn)(t_ms_vars *, char **);
struct s_cmd_kv
{
	char	*cmd;
	t_fctn	fctn;
};

struct s_ms_vars
{
	t_var_env	*head;
	char		**envp;
	char		**paths;
	char		**split;
	char		*prompt;
	t_cmd_kv	builtin[8];
	t_token		*token;
	int			dup_stdin;
	t_ribool	in_heredoc;
	t_ribool	in_fork;
};

///////|	HERE_DOC	|///////
t_ribool	ms_write_here_doc(t_token *token, char *del, t_ms_vars *ms_vars);

///////|	TOOLS		|///////
t_ribool	prep_cmd(char **cmd);
char		*ms_find_bin(char *cmd, char **paths);
char		*ms_find_cmd(char *cmd, char **paths);
t_ribool	ms_prompt(char **prompt);
void		ms_free_tokens(t_token *tokens);

///////|	PARSING		|///////
t_ribool	is_builtin(char *cmd);
t_ribool	is_redir(char c);
t_ribool	is_not_in_cdir(char *path);

///////|	EXEC_CMD	|///////
t_ribool	ms_check_valid_token_param(t_token	*browse, int *pfd, int *ret);
void		ms_exec_cmd(t_ms_vars *ms_vars);
int			ms_exec_pipe(t_ms_vars *ms_vars);
t_ribool	ms_exec_open_files(t_token *token);
int			exec_builtin(t_ms_vars *ms_vars, t_token *token);
void		check_cmd(t_ms_vars *ms_vars, int ret);

///////|	expanD		|///////
void		ms_expend_copy_single_quote(char **enter, char **expanded);
void		ms_expend_mllc_single_quote(char **enter, int *len);
t_ribool	ms_expand_mllc(char *enter, char **expanded,
				t_var_env *env, t_ribool here_doc);
void		ms_expand_copy(char *enter, char *expanded,
				t_var_env *env, t_ribool here_doc);
void		ms_expand(t_ms_vars *ms_vars, t_var_env *env);

///////|	LEXER		|///////
void		ms_lexer(t_ms_vars *ms_vars);
t_ribool	ms_parse_io_file(t_token *browse, int id, t_ms_vars *ms_vars);
t_ribool	ms_subtract_quote_split(char **split);
t_ribool	ms_subtract_quote_cmd(char **cmd);
t_ribool	ms_token_format(t_ms_vars *ms_vars);

///////|	ENV MANIP	|///////
void		ms_init(char **envp, t_ms_vars *ms_vars);
void		ms_init_cmd_kv(t_ms_vars *ms_vars);
t_token		*ms_token_init(t_token **new_token);
void		ms_env_elem_delet(t_ms_vars *ms_vars, char *delet);
void		ms_env_elem_create(char *key, char *value, t_ms_vars *ms_vars);
void		ms_env_parse(char *varp, t_ms_vars *ms_vars, int *src_varp);
t_var_env	*ms_env_elem_finder(t_var_env *root, char *search,
				t_var_env **elem);
void		ms_envp_btree(t_var_env *head);

///////|	ECHO		|///////
int			ms_echo(t_ms_vars *ms_vars, char **args);

///////|	CD			|///////
int			ms_cd(t_ms_vars *ms_vars, char **args);

///////|	PWD			|///////
int			ms_pwd_print(t_ms_vars *ms_vars, char **args);

///////|	EXPORT		|///////
int			ms_export(t_ms_vars *ms_vars, char **args);
void		ms_export_infix(t_var_env *root);
void		ms_export_print(t_var_env *root);
void		ms_export_envp_table(t_ms_vars *ms_vars);
void		ms_export_envp_var(t_var_env *new_elem);

///////|	USET		|///////
int			ms_unset(t_ms_vars *ms_vars, char **delet);

///////|	ENV			|///////
int			ms_env_print(t_ms_vars *ms_vars, char **args);
void		ms_paths_init(t_ms_vars *ms_vars);

///////|	EXIT		|///////
int			ms_exit(t_ms_vars *vars, char **args);
t_ribool	ms_error(char *error1, char *error2, char *error3, t_ribool exit);

///////|	SIGNALS		|///////
void		echo_control_seq(int c);
void		ms_signal(int sig);
void		ms_ctrl_c_interupt(void *init);

#endif
