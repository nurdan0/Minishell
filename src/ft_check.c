/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:44:27 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	is_valid_other(char *a, char *b)
{
	if ((a[0] == '<' && !a[1]) && !b)
		return (0);
	else if ((a[0] == '>' && !a[1]) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && !a[1])) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && a[1] == '<')) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '>' && a[1] == '>')) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && a[1] != '<'))
		&& (b[0] == '<' || b[0] == '>' || b[0] == '|'))
		return (0);
	else if ((a[0] == '>' && a[1] != '>')
		&& (b[0] == '<' || b[0] == '>' || b[0] == '|'))
		return (0);
	else if (((a[0] == '<' && a[1] == '<'))
		&& (b[0] == '>' || b[0] == '|'))
		return (0);
	else if ((a[0] == '>' && a[1] == '>')
		&& (b[0] == '<' || b[0] == '>' || b[0] == '|'))
		return (0);
	else if ((a[0] == '|' && !a[1] && b[0] == '|' && !b[1]))
		return (0);
	return (1);
}

int	cmd_is_valid(t_lexer *lex_list, char *a, char *b)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lex_list->lex;
	while (tmp)
	{
		a = tmp->content;
		if (tmp->next)
			b = tmp->next->content;
		if (i == 0 && !b && ((a[0] == '<') || (a[0] == '>')))
			return (print_error());
		if ((a[0] == '|' && !a[1]) && i == 0)
			return (print_error());
		else if ((a[0] == '>' && !a[1]) && !b)
			return (print_error());
		else
			if (!is_valid_other(a, b))
				return (print_error());
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	quote_len1(char *data)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '\"' || data[i] == '\'')
			j++;
		i++;
	}
	return (j);
}

int	quote_check(char *data)
{
	int		i;
	int		flag;
	char	c;

	flag = 1;
	i = 0;
	while (data[i])
	{
		if (data[i] == '\"' || data[i] == '\'')
		{
			c = data[i];
			i++;
			while (data[i] != c && data[i])
				i++;
			if (data[i] == c)
				flag = 1;
			else
				return (flag = 0, printf("minishell: quote error\n"), 0);
		}
		i++;
	}
	return (flag);
}

int	check(t_shell *m_shell)
{
	return (cmd_is_valid(m_shell->lex_list, NULL, NULL));
}
