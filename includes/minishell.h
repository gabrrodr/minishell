/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:09:20 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/24 16:19:21 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libs/libft/libft.h"
#include <stdbool.h>


typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

//Lexer//

t_lexer	*ft_lexernew(char *str, t_tokens tokenType);
void	ft_lexeradd_back(t_lexer **lst, t_lexer *node);



#endif