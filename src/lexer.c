/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:44:50 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	ignore_quote(char const *cmd, int i)
{
	if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"')
			i++;
	}
	else if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'')
			i++;
	}
	return (i);
}

static int	ft_count_words(char const *cmd)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ' && cmd[i])
			i++;
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i = ignore_quote(cmd, i) + 1;
		if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
		{
			if ((cmd[i] == '<' && cmd[i + 1] == '<')
				|| (cmd[i] == '>' && cmd[i + 1] == '>'))
				i++;
			i++;
		}
		else
			ft_count_words_(cmd, &i);
		count++;
		while (cmd[i] == ' ' && cmd[i])
			i++;
	}
	return (count);
}

static char	**ft_mini_split_words(char **res, char const *s, int word_ct)
{
	int	i;
	int	j;
	int	word_ln;

	i = 0;
	j = 0 ;
	word_ln = 0;
	while (s[j] && i < word_ct)
	{
		while (s[j] && s[j] == ' ')
			j++;
		if (s[j] && s[j] != ' ')
		{
			word_ln = check_what_is(s, j);
			j += word_ln;
		}
		res[i] = (char *)malloc(sizeof(char) * (word_ln + 1));
		if (!res[i])
			return (NULL);
		ft_make_words (res[i], s, j, word_ln);
		word_ln = 0;
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_mini_split(char const *s)
{
	int		word_ct;
	char	**res;

	if (s == 0)
		return (0);
	word_ct = ft_count_words(s);
	res = (char **)malloc(sizeof(char *) * (word_ct + 1));
	if (!res)
		return (NULL);
	ft_mini_split_words (res, s, word_ct);
	return (res);
}

void	lexer(t_shell *m_shell)
{
	char	**str;
	int		i;
	t_list	*new_node;

	i = 0;
	str = ft_mini_split(m_shell->cmd);
	if (!str)
		return ;
	m_shell->lex_list->lex = NULL;
	while (str[i])
	{
		new_node = ft_lstnew(str[i]);
		ft_lstadd_back(&m_shell->lex_list->lex, new_node);
		i++;
	}
	free(str);
}
