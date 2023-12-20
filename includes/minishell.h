/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:04:22 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/12/07 18:26:39 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>

typedef enum s_tokens
{
	IDENTIFIER,
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}				t_tokens;

typedef struct s_heredoc
{
	bool	status;
	int		err_num;
}			t_heredoc;

typedef struct s_lexer
{
	char    		*str;
	t_tokens		token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_simple_cmds
{
	char                    **str;
	char                    *builtin;
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirect;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_prompt
{
	t_simple_cmds	*simple_cmds;
	t_lexer			*lexer;
	t_heredoc		*heredoc;
	char			**env;
	//char			*input;
	int				flg[4];
	int				*pid;
	char			*pwd;
	char			*oldpwd;
	bool			reset;
	int				*exit_codes;
	bool			interact;
}				t_prompt;

//init
t_prompt		*init_prompt(char **argv, char **env);
t_simple_cmds	*init_simple_cmds(void);
int				init_pid(t_prompt *prompt);

void	exit_env(t_prompt *prompt);
char	**dupe_arr(char **arr);

//frees
void	free_array(char **arr);
void	free_data(t_prompt *prompt);
void	free_parser(t_simple_cmds *simple_cmds);

//lexer
t_lexer	*ft_lexernew(char *str, t_tokens tokenType);
void	ft_lexeradd_back(t_lexer **lst, t_lexer *node);
void	ft_clear_lexer(t_lexer **lexer);
void	ft_skip_spaces(char **line);
int		ft_is_quote(char c);
int		ft_is_separator(char *c);
bool	ft_skip_quotes(char *line, size_t *i);
void	ft_print_q_err(char	c);
int		ft_append_separator(t_tokens token, char **line, t_lexer **lexer_tok);
int		ft_append_identifier(char **str, t_lexer **lexer_tok, size_t i);
t_lexer	*lexer(char *input);
t_lexer	*ms_lstlast(t_lexer *lst);

//parser
void	parser(t_prompt *prompt);
int		is_redirection(t_tokens tokenType);
int		is_builtin(char *str);
int		nbr_nodes(t_lexer *lexer);
void	alloc_double_array(int size, t_simple_cmds *cmds);

//utils
char	*array_to_str(char **arr);
char    *get_env(t_prompt *prompt, char *val);
char    *get_word(char *str);
void	print_args(t_prompt *prompt, char **args, int i);
void	print_new_directory(t_prompt *tools);
char	*find_path_ret(char *str, t_prompt *tools);
void	init_exit_codes(t_prompt *prompt, char *input);
int		if_question_mark(void);


//void	replace_variables(t_prompt *prompt);
char		*expand_input(t_prompt *prompt, char *input);
t_prompt	*reset_prompt(t_prompt *prompt, char **argv, char **env);

//builtins
void	ms_echo(char **args, t_prompt *prompt);
int		ms_unset(t_prompt *prompt, t_simple_cmds *cmds);
void	ms_env(t_prompt *prompt);
int		ms_export(t_prompt *prompt, t_simple_cmds *cmds);
int		builtin(t_prompt *prompt, t_simple_cmds *process);
int		ms_cd(t_prompt *tools, t_simple_cmds *simple_cmd);
int		ms_exit(t_prompt *prompt, t_simple_cmds *cmds);

//env
char	**ms_setenv(char *variable, char *value, char **env);
char	*ms_getenv(char **env, char *var);

//export
int		check_equal(t_prompt *prompt, t_simple_cmds *cmds, int i);
void	sub_value(t_prompt *prompt, t_simple_cmds *cmds, int i);
int		check_variable(t_prompt *prompt, char *new);
int		check_key(t_prompt *prompt, t_simple_cmds *cmds, int i);
char	**sort_export(t_prompt *prompt);
int		is_identifier(char c);

//signals
void	set_sign(void);
void	execute_signal(int sig, void *prompt);

//expander
char	*delquotes(char *str, char c);
int		if_digit(char *str, int i);
char	*char_to_str(char c);
int		equal_sign(char *str);
int		dol_sign(char *str);
char	*str_expander(t_prompt *prompt, char *str);
char 	**single_cmd_expander(t_prompt *prompt, char **str);

//error
int ms_error(int error);
int	check_redirections(t_prompt *prompt);


//execute
int	execute(t_prompt *prompt);

//redirects
int	setup_redirect(t_simple_cmds *cmd);

//cmds
//int	cmds(t_prompt *prompt);
int	handle_error_cmd(t_simple_cmds *cmds);
int	handle_cmd(t_prompt *prompt, t_simple_cmds *cmds);
int	single_cmd(t_prompt *prompt, t_simple_cmds *cmds);

//exit codes
bool is_exit_status(char *str);
int	current_exit_status(t_prompt *prompt);

//heredocs
int				send_heredoc(t_prompt *prompt, t_simple_cmds *cmds);
t_simple_cmds	*single_cmd_heredoc(t_prompt *prompt, t_simple_cmds *cmds);

#endif
