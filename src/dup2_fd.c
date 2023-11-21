/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:42:27 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:42:47 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	_create_dup(t_shell *m_shell)
{
	int		new_fd[2];

	pipe(new_fd);
	write(new_fd[1], m_shell->heredoc,
		ft_strlen(m_shell->heredoc));
	dup2(new_fd[0], 0);
	close (new_fd[1]);
	close(new_fd[0]);
}

void	create_dup(t_shell *m_shell, t_mparse *parse)
{
	if (parse->type == HEREDOC)
		_create_dup(m_shell);
	if (parse->infile > STDERR)
		dup2(parse->infile, 0);
	if (parse->outfile > STDERR)
		dup2(parse->outfile, 1);
}

void	create_dup_one(t_mparse *parse, int *fd)
{
	t_mparse	*nparse;

	nparse = parse->next;
	close(fd[0]);
	if (parse->next && fd && nparse->cmd)
		dup2(fd[1], 1);
	else if (parse->type == HEREDOC && parse->next->next)
		dup2(fd[1], 1);
	close(fd[1]);
}

void	create_dup_two(t_mparse *parse, int *fd)
{
	close(fd[1]);
	if (fd && parse->control != 1)
		dup2(fd[0], 0);
	close(fd[0]);
}
