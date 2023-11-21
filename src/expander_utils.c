/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:42:27 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:43:15 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	erase_after(char *lex_c, t_list *lex, int i)
{
	char	*before;
	char	*str;

	str = NULL;
	before = before_dollar(lex_c);
	while (1)
	{
		if (!ft_isalnum(lex_c[i]) || !lex_c[i])
		{
			if (lex->content)
				free(lex->content);
			str = ft_substr(lex_c, i, (ft_strlen(lex_c) - i));
			if (before)
			{
				lex->content = ft_strjoin(before, str);
				free(before);
			}
			else
				lex->content = ft_strdup(str);
			if (str)
				free(str);
			return ;
		}
		i++;
	}
}

void	_does_dollar_make_sense(t_env *y, char *before,
	char *after, t_list *data)
{
	char	*str;
	char	*new_content;

	new_content = NULL;
	str = NULL;
	if (after && before)
	{
		str = ft_strjoin(before, y->value);
		new_content = ft_strjoin(str, after);
		free(str);
	}
	else if (after)
		new_content = ft_strjoin(y->value, after);
	else if (before)
		new_content = ft_strjoin(before, y->value);
	else
		new_content = ft_strdup(y->value);
	if (data->content)
		free(data->content);
	data->content = new_content;
}

char	*after_dark2(char *key, char *tmp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (tmp[i] != key[j])
		i++;
	while (tmp[i] && tmp[i] == key[j])
	{
		i++;
		j++;
		if (!key[j] && (tmp[i] > 0))
		{
			if (tmp[i] == 0)
				return (NULL);
			str = ft_substr(tmp, i, ft_strlen(tmp));
			return (str);
		}
	}
	return (NULL);
}

void	does_dollar_make_sense(char *lex_c, t_list *data,
	t_list *shell_data, int i)
{
	t_env	*y;
	char	*after;
	char	*before;

	y = shell_data->content;
	if (ft_ultimatestrcmp(y->key, lex_c, i))
	{
		before = before_dollar(lex_c);
		after = after_dark2(y->key, lex_c);
		_does_dollar_make_sense(y, before, after, data);
		if (before)
			free(before);
		if (after)
			free(after);
	}
}

int	quate_len(const char *str)
{
	int	i;
	int	number_quate;

	i = 0;
	number_quate = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			i = ignore_quote(str, i);
			number_quate++;
		}
		i++;
	}
	return (number_quate);
}
