/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:04:22 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/24 17:19:12 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>

typedef enum	s_tokens
{
	PIPE,
	GREAT,
	DOUBLE_GREAT,
	LESS,
	DOUBLE_LESS,
}				t_tokens;

typedef struct s_lexer
{
	char    		*str;
	t_tokens		token;
	int				i;
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
}				t_prompt;

//command_table??


#endif