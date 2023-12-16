/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:14:50 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/16 16:49:19 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_redir(char **redirects, int *fds)
{
	if (redirects[0])
	{
		fds[0] = open(redirects[0], O_RDONLY, NULL);
		if (fds[0] == -1)
		{
			printf("Error opening file %s\n", redirects[0]);
			return (ABORTCURRENTCMD);
		}
	}
	return (0);
}

int	out_redir(char **redirects, int *fds)
{
	if (redirects[2])
	{
		fds[3] = open(redirects[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (fds[3] == -1)
		{
			printf("Error opening file %s\n", redirects[2]);
			return (ABORTCURRENTCMD);
		}
	}
	return (0);
}

int	apnd_redir(char **redirects, int *fds)
{
	if (redirects[3])
	{
		fds[4] = open(redirects[3], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		if (fds[4] == -1)
		{
			printf("Error opening file %s\n", redirects[3]);
			return (ABORTCURRENTCMD);
		}
	}
	return (0);
}

char	**_get_quoted_word(char *input, int *i, t_env *l_env)
{
	char	**result;
	char	*env_variable;
	char	*before_env;
	int		start;

	__initstuff(i, &start, &result);
	while (input[*i])
	{
		if (input[*i] == '$')
		{
			before_env = get_env_var_ex(input, *i);
			env_variable = get_env_var(input, i, l_env);
			result[0] = ft_strjoin(result[0], before_env);
			result[1] = ft_strjoin(result[1], env_variable);
			start = *i;
		}
		else
		{
			result[0] = ft_strjoin(result[0], ft_strndup(&input[*i], 1));
			result[1] = ft_strjoin(result[1], ft_strndup(&input[*i], 1));
			(*i)++;
		}
	}
	return (result);
}
