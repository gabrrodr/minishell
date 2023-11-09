/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:58:13 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/08 14:38:36 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool    is_expandable(char *str)
{
   bool   in_double_quotes;
   bool   in_single_quotes;
   int       i;

   in_double_quotes = false;
   in_single_quotes = false;
   i = 0;
   while (str[i])
   {
      if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')
         && !in_double_quotes)
         in_single_quotes = !in_single_quotes;
      else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')
         && !in_single_quotes)
         in_double_quotes = !in_double_quotes;
      else if (str[i] == '$' && in_single_quotes)
         return (false);
      i++;
   }
   return (true);
}

static char    *create_str(t_prompt *prompt, char *str, char *var, char *word)
{
   size_t final_length;
   char   *final_str;

   final_length = (ft_strlen(str) - ft_strlen(word)) + ft_strlen(var);
   final_str = ft_calloc(final_length + 1, sizeof(char));
   if (!final_str)
      return (NULL);
   prompt->flg[0] = 0;
   prompt->flg[1] = 0;
   while (str[prompt->flg[0]] != '$')
      final_str[prompt->flg[1]++] = str[prompt->flg[0]++];
   ft_strlcat(final_str, var, final_length + 1);
   prompt->flg[0] += ft_strlen(word) + 1;
   while (final_str[prompt->flg[1]])
      prompt->flg[1]++;
   while (str[prompt->flg[0]])
      final_str[prompt->flg[1]++] = str[prompt->flg[0]++];
   return (final_str);
}

static char    *replace(t_prompt *prompt, char *str)
{
	char   *final_str;
	char   *var;
	char   *word;

	word = get_word(str);
	var = get_env(prompt, get_word(str));
	if (!var)
	{
		free(word);
		return (NULL);
	}
	final_str = create_str(prompt, str, var, word);
	free(word);
	free(var);
	return (final_str);
}

static void    expand_word(t_prompt *prompt, char **word)
{
   char   *tmp;
   int       j;

   j = -1;
   while ((*word)[++j])
   {
      if ((*word)[j] == '$' && is_expandable(*word))
      {
         tmp = replace(prompt, *word);
         if (tmp)
         {
            free(*word);
            *word = ft_strdup(tmp);
            free(tmp);
         }
      }
   }
}

char   *expand_input(t_prompt *prompt, char *input)
{
	char   **arr;
	int       i;
	
	arr = ft_split(input, ' ');
	if (!arr)
	  return (NULL);
	i = 0;
	while (arr[i])
	{
		expand_word(prompt, &arr[i]);
		i++;
	}
	return (array_to_str(arr));
}
