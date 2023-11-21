/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:42:27 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:42:44 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	other_out_filesme(t_mparse *mparse)
{
	char		str[256];
	char		*pwd;
	char		*pwd1;
	t_mparse	*nparse;

	getcwd(str, 256);
	nparse = mparse->next;
	pwd = ft_strjoin(str, "/");
	pwd1 = ft_strjoin(pwd, nparse->text[0]);
	open(pwd1, O_CREAT | O_RDWR, 0777);
	free(pwd1);
	pwd1 = ft_strjoin(pwd, nparse->next->text[0]);
	if (nparse->type == 4)
		mparse->fd = open(pwd1, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (mparse->type == 3)
		mparse->fd = open(pwd1, O_CREAT | O_RDWR | O_TRUNC, 0777);
	mparse->outfile = mparse->fd;
	if (pwd)
		free(pwd);
	if (pwd1)
		free(pwd1);
}

void	other_text_create_me(t_mparse *m_parse)
{
	t_mparse	*n_parse;
	int			i;
	int			j;

	n_parse = m_parse->next;
	i = 0;
	while (m_parse->text[i])
		i++;
	while (n_parse->next && n_parse->type != 2)
	{
		j = 1;
		while (n_parse->text[j])
		{
			m_parse->text[i] = ft_strdup(n_parse->text[j]);
			i++;
			j++;
		}
		n_parse = n_parse->next;
	}
	m_parse->text[i] = NULL;
	other_out_filesme(m_parse);
}

char	*ft_strjoin2(char *s1, const char *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (str);
}

void	create_out_files_me(t_mparse *m_parse, t_mparse *prev_parse)
{
	char		str[256];
	char		*pwd;
	t_mparse	*m_next;

	getcwd(str, 256);
	m_next = m_parse->next;
	if (m_next->type == 3 || m_next->type == 4)
		return (other_text_create_me(m_parse));
	pwd = ft_strjoin(str, "/");
	pwd = ft_strjoin2(pwd, m_next->text[0]);
	if (m_parse->type == 4)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (m_parse->type == 3)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (m_parse->cmd)
		m_parse->outfile = m_next->fd;
	else if (prev_parse->cmd)
		prev_parse->outfile = m_next->fd;
	if (pwd)
		free(pwd);
}

int	create_files_m(t_shell *m_shell)
{
	t_mparse	*parse;
	int			i;

	i = 1;
	parse = m_shell->mparse;
	while (parse)
	{
		if (parse->type == 3 || parse->type == 4)
			create_out_files_me(parse, m_shell->mparse);
		else if (parse->type == 5)
			i = create_in_files_me(parse);
		parse = parse->next;
	}
	return (i);
}
