/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/21 13:43:27 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	g_does_have_heredoc;

void	shell_init(t_shell **m_shell)
{
	*m_shell = malloc(sizeof(t_shell));
	if (!(*m_shell))
		return ;
	(*m_shell)->env = malloc(sizeof(t_env));
	if (!(*m_shell)->env)
		return ;
	(*m_shell)->lex_list = malloc(sizeof(t_lexer));
	if (!(*m_shell)->lex_list)
		return ;
	(*m_shell)->mparse = NULL;
	(*m_shell)->lex_list->lex = NULL;
	(*m_shell)->exec_status = 0;
	(*m_shell)->heredoc = NULL;
	(*m_shell)->cmd = NULL;
	g_does_have_heredoc = 0;
}

void	get_readline(t_shell *m_shell)
{
	ft_putstr_fd(PURPLE, 1);
	m_shell->cmd = readline(" ♠️ ♣️ ♥️ ♦️ ⇾ ");
	if (m_shell->cmd && !is_space(m_shell->cmd))
	{
		free(m_shell->cmd);
		get_readline(m_shell);
	}
	if (!m_shell->cmd)
	{
		free_loop(0, m_shell);
		free_(m_shell);
		free(m_shell->lex_list);
		free(m_shell);
		exit(1);
	}
	add_history(m_shell->cmd);
}

void	go_parser(char **env, t_shell *m_shell)
{
	if (ft_strcmp(m_shell->cmd, ""))
	{
		if (ft_parser(m_shell))
		{
			exec(env, m_shell);
		}
	}
}

void	error_free(t_list **node)
{
	if (!*node)
		return ;
	if ((*node)->next != NULL)
		free_node((*node)->next);
	if ((*node)->content)
		(*node)->content = (free((*node)->content), NULL);
	if ((*node))
		(*node) = (free(*node), NULL);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*m_shell;
	int		control;

	(void)av;
	control = 0;
	if (ac != 1)
		exit(printf("This program cannot accept any arguments\n"));
	shell_init(&m_shell);
	env_get(env, &m_shell);
	signals_control();
	while (1)
	{
		get_readline(m_shell);
		if (quote_check(m_shell->cmd))
		{
			lexer(m_shell);
			expander(m_shell);
			control = check(m_shell);
			if (control)
				go_parser(env, m_shell);
			else
				error_free(&(m_shell->lex_list)->lex);
		}
		else
			control = 0;
		free_loop(control, m_shell);
	}
}
