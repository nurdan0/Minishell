/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:44:13 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	ft_ultimatestrcmp(char *key, char *tmp, int i)
{
	int	j;

	j = 0;
	if (tmp[i] != key[0])
		return (0);
	while (tmp[i] == key[j])
	{
		i++;
		j++;
		if (!key[j])
		{
			if (!ft_isalnum(tmp[i]))
				return (1);
			return (0);
		}
	}
	return (0);
}

void	_ft_exit_status(t_list *data, char *str1)
{
	data->content = str1;
}

void	free_tmps(char *str, char *str2, char *str_tmp)
{
	if (str)
		free(str);
	if (str_tmp)
		free(str_tmp);
	if (str2)
		free(str2);
}

void	free_str1(char *str1, int flag)
{
	if (flag == 0 && str1)
		free(str1);
}

void	env_lex_list_(t_list **lex, char **lex_c, int i, t_shell *m_shell)
{
	if (((*lex_c)[i] == '~') && ((*lex_c)[0] != '\''
	|| (*lex_c)[0] != '\"') && ((*lex_c)[i + 1] == '/'
		|| !(*lex_c)[i + 1]))
		if (!(i >= 1))
			check_env(*lex, *lex_c, i, m_shell);
}
