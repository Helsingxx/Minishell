/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:43:41 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 17:43:42 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_key(char *key)
{
	int	x;

	x = 0;
	if (key[0] >= '0' && key[0] <= '9')
		return (0);
	while (key[x] && ((key[x] >= 'a' && key[x] <= 'z')
			|| (key[x] >= 'A' && key[x] <= 'Z')
			|| (key[x] >= '0' && key[x] <= '9') || key[x] == '_'))
		x++;
	if (x == ft_strlen(key) && x != 0)
		return (1);
	return (0);
}

int	chck_node(t_env *env, char *arg)
{
	char	*key;
	char	*value;

	split_env_var(arg, &key, &value);
	if (!valid_key(key))
		return (-1);
	if (!value)
		return (2);
	while (env && _ft_strcmp(env->key, key))
		env = env->next;
	if (env)
	{
		env->value = value;
		env->only_export = 0;
	}
	else
		return (0);
	return (1);
}

int	is_there(t_env *env, char *key)
{
	while (env && _ft_strcmp(env->key, key))
		env = env->next;
	if (env)
		return (1);
	return (0);
}

void	set_exp(t_env *env, char *key)
{
	while (env && _ft_strcmp(env->key, key))
		env = env->next;
	if (env)
		env->only_export = 1;
}

void	unset_exp(t_env *env, char *key)
{
	while (env && _ft_strcmp(env->key, key))
		env = env->next;
	if (env)
		env->only_export = 0;
}
