/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:42:27 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/18 10:45:54 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	env_get(char **env, t_shell **shell)
{
	t_env	*a;
	char	**str;

	free((*shell)->env);
	(*shell)->env = NULL;
	while (*env)
	{
		a = malloc(sizeof(t_env));
		if (!a)
			return ;
		str = ft_split(*env, '=');
		if (!str)
			return ;
		a->key = ft_strdup(str[0]);
		a->value = ft_strdup(str[1]);
		ft_lstadd_back(&(*shell)->env, ft_lstnew(a));
		free_str(str);
		env++;
	}
}
