/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:59:24 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	_change_pwd(t_env **env)
{
	char	cwd[1024];

	if (!ft_strcmp((*env)->key, "PWD"))
	{
		if ((*env)->value)
			free((*env)->value);
		(*env)->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	}
}

void	oldpwd_(char *oldpwd, t_shell *m_shell)
{
	printf("%s\n", oldpwd);
	chdir(oldpwd);
	m_shell->exec_status = 0;
	free(oldpwd);
}

void	exec_cd1(char *str, t_mparse *data, t_shell *m_shell)
{
	change_old(str, m_shell);
	chdir(get_home(m_shell));
	change_pwd(data, m_shell);
	m_shell->exec_status = 0;
}

void	ft_change(t_mparse *data, t_shell *m_shell, char *str)
{
	if (!ft_strcmp(data->text[0], "-"))
		dont_change_oldpwd(str, m_shell);
	change_old(str, m_shell);
	change_pwd(data, m_shell);
	m_shell->exec_status = 0;
}

void	exec_cd(t_mparse *data, t_shell *m_shell)
{
	char	cwd[1024];
	char	*str;

	str = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (data->text && data->text[0])
	{
		if (chdir(data->text[0]) == 0)
			ft_change(data, m_shell, str);
		else if (!ft_strcmp(data->text[0], "-"))
			ft_change(data, m_shell, str);
		else
		{
			if (str)
				free(str);
			m_shell->exec_status = 1;
			perror("cd");
		}
	}
	else
		exec_cd1(str, data, m_shell);
}
