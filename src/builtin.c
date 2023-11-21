/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:42:27 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:42:29 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_command(t_mparse *parse, t_shell *m_shell)
{
	t_mparse	*mparse;

	mparse = parse;
	if ((ft_strcmp(mparse->cmd, "echo") == 0)
		|| (ft_strcmp(mparse->cmd, "ECHO") == 0))
		exec_echo(mparse, m_shell);
	if (ft_strcmp(mparse->cmd, "cd") == 0)
		exec_cd(mparse, m_shell);
	if ((ft_strcmp(mparse->cmd, "pwd") == 0)
		|| (ft_strcmp(mparse->cmd, "PWD") == 0))
		exec_pwd(mparse, m_shell);
	if (ft_strcmp(mparse->cmd, "export") == 0)
		exec_export(mparse, m_shell);
	if (ft_strcmp(mparse->cmd, "unset") == 0)
		exec_unset(mparse, m_shell, 0, 0);
	if (((ft_strcmp(mparse->cmd, "env") == 0)
			|| (ft_strcmp(mparse->cmd, "ENV") == 0)))
		exec_env(m_shell);
}

int	is_builtin(t_mparse *data)
{
	if ((ft_strcmp(data->cmd, "echo") == 0)
		|| (ft_strcmp(data->cmd, "ECHO") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "pwd") == 0)
		|| (ft_strcmp(data->cmd, "PWD") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "env") == 0)
		|| (ft_strcmp(data->cmd, "ENV") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "cd") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "export") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "unset") == 0))
		return (1);
	return (0);
}
