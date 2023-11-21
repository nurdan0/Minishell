/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:45:23 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	run_echo(t_mparse *data, int *i)
{
	int	x;
	int	j;

	x = *i;
	while (data->text[x])
	{
		j = 0;
		while (data->text[x][j])
			write(data->outfile, &data->text[x][j++], 1);
		if (data->text[x][j] == '\0' && data->text[x + 1] != NULL)
			write(data->outfile, " ", 1);
		x++;
		*i += 1;
	}
}

void	exec_echo(t_mparse *data, t_shell *m_shell)
{
	int	i;

	i = 0;
	if (!data->text)
		write(data->outfile, "\n", 1);
	else
	{
		if (ft_strcmp(data->text[0], "-n") == 0)
		{
			i = 1;
			if (data->text[1])
				run_echo(data, &i);
		}
		else
		{
			run_echo(data, &i);
			if (!data->text[i])
				write(data->outfile, "\n", 1);
		}
	}
	m_shell->exec_status = 0;
}

void	print_list(void *data, t_shell *m_shell)
{
	t_mparse	*str;
	t_env		*new;
	int			i;

	i = 0;
	str = m_shell->mparse;
	new = (t_env *)data;
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	write(str->outfile, "=", 1);
	i = 0;
	while (new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

void	exec_env(t_shell *m_shell)
{
	ft_newlstiter(m_shell->env, print_list, m_shell);
	m_shell->exec_status = 0;
}
