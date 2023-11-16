/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:37 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/16 13:50:54 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_word(char *str)
{
   char   *val;
   int       i;
   int       j;
   int       start;

   i = 0;
   while (str[i] && str[i] != '$')
      i++;
   i++;
   start = i;
   while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
      i++;
   val = ft_calloc(i - start + 1, sizeof(char));
   j = 0;
   while (start < i)
      val[j++] = str[start++];
   return (val);
}

static void cat_str(char **str, char *result, size_t total_length)
{
   while (*str != NULL)
   {
      ft_strlcat(result, *str, total_length + 1);
      if (*(str + 1) != NULL)
         ft_strlcat(result, " ", total_length + 1);
      str++;
   }
}

char *array_to_str(char **arr) 
{
	char *result;
	size_t total_length;
    char **str;

	total_length = 0;
    str = arr;
    if (arr == NULL || arr[0] == NULL)
        return NULL;
    while (*str != NULL)
	{
        total_length += strlen(*str);
        str++;
    }
    total_length += (size_t)(str - arr - 1);
    result = malloc(total_length + 1);
    if (result == NULL)
        return NULL;
    result[0] = '\0';
    str = arr;
    cat_str(str, result, total_length);
	free_array(arr);
    return (result);
}
