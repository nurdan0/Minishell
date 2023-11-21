/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:42:27 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:43:18 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	ft_tilde_build1(t_list *lex, char *key, char *lex_c)
{
	if (lex->content)
		free(lex->content);
	lex->content = ft_strjoin(key, lex_c);
}

void	ft_tilde_build2(t_list *lex, char *str)
{
	if (lex->content)
		free(lex->content);
	lex->content = ft_strdup(str);
}

char	*before_dollar(char *lex_c)
{
	char	*str;
	int		i;

	i = 0;
	while (lex_c[i])
	{
		if (lex_c[i] == '$')
		{
			str = ft_substr(lex_c, 0, i);
			if (i != 0)
				return (str);
			else
			{
				free(str);
				break ;
			}
		}
		i++;
	}
	return (NULL);
}

void	get_after_num(char *lex_c, t_list *lex, int i)
{
	char	*before;
	char	*str;

	str = NULL;
	before = before_dollar(lex_c);
	if (before)
	{
		if (lex->content)
			free(lex->content);
		str = ft_substr(lex_c, i, ft_strlen(lex_c) - i);
		lex->content = ft_strjoin(before, str);
	}
	else
	{
		if (lex->content)
			free(lex->content);
		lex->content = ft_substr(lex_c, i, ft_strlen(lex_c) - i);
	}
	if (before)
		free(before);
	if (str)
		free(str);
}
