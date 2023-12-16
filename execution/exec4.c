/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:18 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 14:34:39 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inc_val(t_env *env, char *arg)
{
	char	*key;
	char	*value;

	split_env_var(arg, &key, &value);
	while (env && _ft_strcmp(env->key, key))
		env = env->next;
	if (env)
		env->value = env->value + 1;
	else
		return (0);
	return (1);
}

int	apply_gout(char ***garbage_redirects_arr)
{
	int	x;
	int	fd;

	x = 0;
	while (garbage_redirects_arr[0][x])
	{
		fd = open(garbage_redirects_arr[0][x],
				O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd == -1)
		{
			printf("Error opening file %s\n", garbage_redirects_arr[0][x]);
			return (ABORTCURRENTCMD);
		}
		else
			close(fd);
		x++;
	}
	return (0);
}

int	apply_gapp(char ***garbage_redirects_arr)
{
	int	x;
	int	fd;

	x = 0;
	while (garbage_redirects_arr[1][x])
	{
		fd = open(garbage_redirects_arr[1][x],
				O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		if (fd == -1)
		{
			printf("Error opening file %s\n", garbage_redirects_arr[1][x]);
			return (ABORTCURRENTCMD);
		}
		else
			close(fd);
		x++;
	}
	return (0);
}

int	apply_gin(char ***garbage_redirects_arr)
{
	int	x;
	int	fd;

	x = 0;
	while (garbage_redirects_arr[2][x])
	{
		fd = open(garbage_redirects_arr[2][x], O_RDONLY, S_IRWXU);
		if (fd == -1)
		{
			printf("Error opening file %s\n", garbage_redirects_arr[2][x]);
			return (ABORTCURRENTCMD);
		}
		else
			close(fd);
		x++;
	}
	return (0);
}

int	apply_garbage_redir(char ***garbage_redirects_arr)
{
	if (apply_gout(garbage_redirects_arr))
		return (ABORTCURRENTCMD);
	if (apply_gapp(garbage_redirects_arr))
		return (ABORTCURRENTCMD);
	if (apply_gin(garbage_redirects_arr))
		return (ABORTCURRENTCMD);
	return (0);
}
