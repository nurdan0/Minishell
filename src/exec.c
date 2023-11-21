/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:42:27 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 17:12:12 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	run_command(char **env, t_mparse *tmp, int *fd, t_shell *m_shell)
{
	int			control;

	control = is_builtin(tmp);
	if (control)
		execute_builtin_command(tmp, m_shell);
	else
		exec_others(tmp, env, fd, m_shell);
	free_(m_shell);
	free_loop(1, m_shell);
	free(m_shell->lex_list);
	free(m_shell);
	exit(0);
}

void	run_single_command(char **env, t_mparse *parse, t_shell *m_shell)
{
	int	control;

	control = 0;
	if (parse->type != HEREDOC)
		control = is_builtin(parse);
	if (control)
		execute_builtin_command(m_shell->mparse, m_shell);
	else
		exec_others(m_shell->mparse, env, NULL, m_shell);
}

void	multi_command_(t_mparse *mparse, char **env, t_shell *m_shell, int *fd)
{
	t_mparse	*nparse;
	int			x;

	x = 0;
	while (mparse)
	{
		if (mparse->next)
			pipe(fd);
		nparse = _next_command(&mparse);
		mparse->pid = fork();
		if (mparse->pid == 0)
		{
			create_dup_one(mparse, fd);
			run_command(env, mparse, fd, m_shell);
		}
		if (nparse)
			create_dup_two(nparse, fd);
		mparse = nparse;
	}
}

void	multi_command(char **env, int x, t_mparse *parse, t_shell *m_shell)
{
	int			*fd;
	t_mparse	*mparse;

	(void)x;
	mparse = parse;
	m_shell->mparse->std_in = dup(0);
	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return ;
	multi_command_(mparse, env, m_shell, fd);
	dup2(m_shell->mparse->std_in, 0);
	clear_pipe(fd);
	wait_all(m_shell);
}

void	exec(char **env, t_shell *m_shell)
{
	int			x;

	if (g_does_have_heredoc != 0)
		loop_heredoc(m_shell);
	if (!ft_strcmp(m_shell->cmd, ""))
		return ;
	if (m_shell->mparse->cmd)
	{
		if (ft_strcmp(m_shell->mparse->cmd, "exit") == 0
			&& g_does_have_heredoc != -10)
		{
			free_(m_shell);
			free_loop(1, m_shell);
			free(m_shell->lex_list);
			free(m_shell);
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
	}
	x = single_or_multi_command(m_shell);
	if (!x && g_does_have_heredoc != -10)
		run_single_command(env, m_shell->mparse, m_shell);
	else if (g_does_have_heredoc != -10)
		multi_command(env, 0, m_shell->mparse, m_shell);
	g_does_have_heredoc = 0;
}
