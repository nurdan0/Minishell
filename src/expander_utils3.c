/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:43:56 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	quote_build(char **tmp, char **data, int *i, int *j)
{
	char	a;
	int		x;
	int		y;

	x = *i;
	y = *j;
	a = (*tmp)[x++];
	*i += 1;
	while ((*tmp)[x] && (*tmp)[x] != a)
	{
		(*data)[y] = (*tmp)[x++];
		*i += 1;
		*j += 1;
		y++;
	}
}

char	*ft_before_dollar_control(char *tmp)
{
	int		i;
	char	*data;

	i = 0;
	while (tmp[i] && tmp[i] != '$')
		i++;
	if (i > 0)
	{
		data = ft_substr(tmp, 0, i);
		return (data);
	}
	return (NULL);
}

char	*ft_after_dark(char *str)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	if (str[0] == '$' && str[1] == '?')
		flag = 1;
	while ((str[i] != '$' && str[i + 1] != '?') && str[i] && flag == 0)
		i++;
	if (str[i] && (str[i] == '$' && str[i + 1] == '?') && str[i + 2])
	{
		i += 2;
		tmp = ft_substr(str, i, ft_strlen(str));
		return (tmp);
	}
	return (NULL);
}

void	ft_exit_status(char *lex_c, t_list *lex, t_shell *m_shell)
{
	char	*str;
	char	*str1;
	char	*str2;
	char	*str_tmp;
	int		flag;

	flag = 0;
	str_tmp = NULL;
	str = ft_before_dollar_control(lex_c);
	str1 = ft_itoa(m_shell->exec_status);
	str2 = ft_after_dark(lex_c);
	free(lex->content);
	if (str && str2)
	{
		str_tmp = ft_strjoin(str, str1);
		lex->content = ft_strjoin(str_tmp, str2);
	}
	else if (str2)
		lex->content = ft_strjoin(str1, str2);
	else if (str)
		lex->content = ft_strjoin(str, str1);
	else
		flag = (_ft_exit_status(lex, str1), 1);
	free_tmps(str, str2, str_tmp);
	free_str1(str1, flag);
}
