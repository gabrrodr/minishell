/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:09:02 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/18 14:04:29 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (env[i][j] != '=' && env[i][j])
		{
			ft_putchar_fd(env[i][j], STDOUT_FILENO);
			j++;
			if (env[i][j] == '=')
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				j++;
				while (env[i][j])
					ft_putchar_fd(env[i][j++], STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
			}
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

int	export_errors(char *str)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	check_params(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || ft_isdigit(str[0]) || str[0] == '=')
	{
		export_errors(str);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (is_identifier(str[i]))
		{
			export_errors(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~' || c == '=' || c == '-' || c == '?' || c == '&'
		|| c == '*');
}
