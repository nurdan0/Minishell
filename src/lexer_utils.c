/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:56:54 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_words_(char const *cmd, int *i)
{
	while (cmd[*i] != '<' && cmd[*i] != '>'
		&& cmd[*i] != '|' && cmd[*i] && cmd[*i] != ' ')
	{
		if (cmd[*i] == '\"' || cmd[*i] == '\'')
			*i = ignore_quote(cmd, *i) + 1;
		else
			*i += 1;
	}
}

char	*ft_make_words(char *word, char const *s, int j, int word_ln)
{
	int	i;

	i = 0;
	while (word_ln > 0)
		word[i++] = s[j - word_ln--];
	word[i] = 0;
	return (word);
}

void	check_what_is_(const char *cmd, int *i)
{
	while (cmd[*i] != '<' && cmd[*i] != '>'
		&& cmd[*i] != '|' && cmd[*i] && cmd[*i] != ' ')
	{
		if (cmd[*i] == '\"' || cmd[*i] == '\'')
			*i = ignore_quote(cmd, *i) + 1;
		else
			*i += 1;
	}
}

int	check_what_is(const char *cmd, int i)
{
	int	a;

	a = i;
	if (cmd[i] == '\"' || cmd[i] == '\'')
	{
		i = ignore_quote(cmd, i);
		i++;
	}
	if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
	{
		if ((cmd[i] == '<' && cmd[i + 1] == '<')
			|| (cmd[i] == '>' && cmd[i + 1] == '>'))
			i += 2;
		else
			i++;
	}
	else
		check_what_is_(cmd, &i);
	return (i - a);
}
