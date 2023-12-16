/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:49:38 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 16:50:21 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

unsigned char	_ft_strcmp(char *str1, char *str2)
{
	int				x;
	unsigned char	*str1u;
	unsigned char	*str2u;

	x = 0;
	str1u = (unsigned char *) str1;
	str2u = (unsigned char *) str2;
	while (str1u[x] && str2u[x] && str1u[x] == str2u[x])
		x++;
	return (str1u[x] - str2u[x]);
}

int	node_count(t_env *env)
{
	int	x;

	x = 0;
	while (env)
	{
		env = env->next;
		x++;
	}
	return (x);
}

char	**env_toarray(t_env *env)
{
	char	**envp;
	int		x;
	char	*tmp;

	x = 0;
	envp = ft_calloc(sizeof(char *), node_count(env) + 1);
	while (env)
	{
		if (!env->only_export)
		{
			tmp = ft_strjoin(env->key, "=");
			envp[x] = ft_strjoin(tmp, env->value);
			x++;
		}
		env = env->next;
	}
	return (envp);
}
