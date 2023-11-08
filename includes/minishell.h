/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:04:22 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/08 14:35:08 by mcarneir         ###   ########.fr       */
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

typedef enum s_tokens
{
	IDENTIFIER,
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}				t_tokens;

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
	char			**env;
	int				flag;
	bool			reset;
}				t_prompt;

//init
t_prompt	*init_prompt(char **argv, char **env);
t_simple_cmds	*init_simple_cmds(void);

void	exit_env(t_prompt *prompt);
void	dupe_arr(t_prompt *prompt, char **arr);

//frees
void	free_array(char **arr);
void	free_data(t_prompt *prompt);
void	free_lexer(t_lexer *lst);
t_prompt	*reset_prompt(t_prompt *prompt, char **argv, char **env);


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
int	is_redirection(t_tokens tokenType);
int		is_builtin(char *str);
int	nbr_nodes(t_lexer *lexer);
void	alloc_double_array(int size, t_simple_cmds *cmds);

//builtins

void	ms_pwd(void);
void	ms_echo(char **args);
//int	ms_cd(char **args);

#endif
