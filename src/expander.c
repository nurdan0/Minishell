/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 16:44:17 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*ft_mini_strdup(const char *str)
{
	char	*s;
	size_t	len;
	int		qulen;
	int		i;

	i = 0;
	qulen = 2 * quate_len(str);
	len = ft_strlen(str);
	s = (char *)malloc(sizeof(char) * (len - qulen + 1));
	if (!s)
		return (NULL);
	return (ft_mini_strdup2(len, s, i, str));
}

void	ft_tilde(char *lex_c, char *env_value, t_list *lex)
{
	int		i;
	int		j;
	char	*key;

	j = 0;
	i = 0;
	key = malloc(sizeof(char) * (ft_strlen(env_value) + 1));
	if (!key)
		return ;
	if (ft_strchr(lex_c, '/'))
	{
		lex_c = ft_strchr(lex_c, '/');
		while (env_value[i])
		{
			key[j] = env_value[i++];
			j++;
		}
		key[j] = '\0';
		ft_tilde_build1(lex, key, lex_c);
	}
	else
		ft_tilde_build2(lex, env_value);
	free(key);
}

int	check_env(t_list *lex, char *lex_c, int i, t_shell *m_shell)
{
	t_env	*y;
	char	*x;
	t_list	*env;

	env = m_shell->env;
	x = ft_strdup((char *)lex->content);
	while (env)
	{
		y = env->content;
		if (lex_c[i] == '~' && ft_strcmp(y->key, "HOME") == 0)
			ft_tilde(lex_c, y->value, lex);
		if (lex_c[i] == '$' && lex_c[i + 1] == '?')
			ft_exit_status(lex_c, lex, m_shell);
		else if (lex_c[i] == '$' && ft_isdigit(lex_c[i + 1]) && lex_c[i + 2])
			get_after_num(lex_c, lex, i + 2);
		else if (lex_c[i] == '$')
			does_dollar_make_sense(lex_c, lex, env, i + 1);
		env = env->next;
	}
	if (!ft_strcmp(x, (char *)lex->content))
		erase_after(lex_c, lex, i + 1);
	free(x);
	return (0);
}

void	get_env_to_lexlist(t_shell *m_shell, int i, char *lex_c, t_list *lex)
{
	lex = m_shell->lex_list->lex;
	while (lex)
	{
		i = 0;
		lex_c = ft_strdup(lex->content);
		while (lex_c[i])
		{
			env_lex_list_(&lex, &lex_c, i, m_shell);
			if (lex_c[i] == '$' && lex_c[0] != '\'')
			{
				check_env(lex, lex_c, i, m_shell);
				if (!ft_strcmp(lex->content, ""))
					break ;
			}
			free(lex_c);
			(lex_c) = ft_strdup((lex)->content);
			i++;
		}
		if (lex->content)
			free(lex->content);
		lex->content = ft_mini_strdup(lex_c);
		free(lex_c);
		(lex) = (lex)->next;
	}
}

void	expander(t_shell *m_shell)
{
	char	*lex_c;
	t_list	*lex;

	lex = NULL;
	lex_c = NULL;
	if (ft_strcmp(m_shell->cmd, ""))
		get_env_to_lexlist(m_shell, 0, lex_c, lex);
}
