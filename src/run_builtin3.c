/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 17:00:01 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	edit_env_(t_list *node, char *key, char *value, t_shell *m_shell)
{
	t_env	*new_env;

	if (node == NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return ;
		new_env->key = key;
		new_env->value = value;
		ft_lstadd_back(&(m_shell->env), ft_lstnew(new_env));
	}
}

void	exec_pwd(t_mparse *data, t_shell *m_shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(data->outfile, &cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		m_shell->exec_status = 0;
	}
	else
	{
		perror("getcwd");
		m_shell->exec_status = 1;
	}
}

char	*get_home(t_shell *m_shell)
{
	t_list	*tmp;
	t_env	*env;

	tmp = m_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "HOME"))
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}
