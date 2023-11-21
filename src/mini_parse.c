/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:45:03 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_mparse	*mparse_init(size_t len)
{
	t_mparse	*mparse;

	mparse = malloc(sizeof(t_mparse));
	if (!mparse)
		return (NULL);
	(mparse)->next = NULL;
	(mparse)->cmd = NULL;
	(mparse)->text = ft_calloc(sizeof(char *), len + 1);
	if (!(mparse)->text)
		return (NULL);
	(mparse)->type = 0;
	(mparse)->infile = STDINN;
	(mparse)->outfile = STDOUT;
	(mparse)->fd = 1;
	(mparse)->pid = 0;
	(mparse)->control = 0;
	return (mparse);
}

void	tokenize_type_m(t_mparse **parse, const char *str)
{
	if (str[0] == '|')
		(*parse)->type = PIPE;
	else if (str[0] == '>' && str[1] == '>')
		(*parse)->type = GREATER;
	else if (str[0] == '<' && str[1] == '<')
	{
		(*parse)->type = HEREDOC;
		g_does_have_heredoc = 1;
	}
	else if (str[0] == '>')
		(*parse)->type = GREAT;
	else if (str[0] == '<')
		(*parse)->type = LESS;
}

void	parse_text_m(t_mparse *parse, char *str, int *j, int *flag)
{
	parse->text[*j] = ft_strdup(str);
	*j += 1;
	parse->text[*j] = NULL;
	*flag = 1;
}

void	flag_(t_mparse *parse)
{
	free_text(parse->text);
	parse->text = NULL;
}

void	mini_parse(t_list *lex, t_shell *m_shell, int a[3])
{
	char		*str;
	t_mparse	*parse;

	parse = mparse_init((size_t)ft_lstsize(lex));
	m_shell->mparse = parse;
	while (lex)
	{
		str = lex->content;
		if (a[0]++ == 0 && ft_strcmp(str, "<<"))
			parse->cmd = ft_strdup(str);
		else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		{
			if (tokenize_type_m(&parse, str), str[0] == '|')
				a[0] = 0;
			parse->next = mparse_init((size_t)ft_lstsize(lex));
			a[1] = 0;
			parse = parse->next;
		}
		else if (ft_strcmp(str, ""))
			parse_text_m(parse, str, &a[1], &a[2]);
		lex = lex->next;
	}
	if (a[2] == 0)
		flag_(parse);
}
