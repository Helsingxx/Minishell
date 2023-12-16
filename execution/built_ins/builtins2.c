/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:44:24 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 17:44:28 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char **args, t_env *env, int *exit_stat)
{
	char	*old;

	old = getcwd(NULL, 0);
	if (old)
		alloc_wrap(old);
	if (!args[0])
		return (cd_home(env, exit_stat, old));
	if (chdir(args[0]) == -1)
	{
		if (args[0][0])
			*exit_stat = 1;
		return (printf("Failure to change directory!\n"), 1);
	}
	update_wd(getcwd(NULL, 0), env);
	update_oldwd(old, env);
	*exit_stat = 0;
	return (0);
}

int	det_nnl(char ***args, int *exit_stat)
{
	int	x;
	int	nnl;

	x = 0;
	nnl = 0;
	if (!(*args)[0])
		return (*exit_stat = 0, printf("\n"), 2);
	if ((*args)[0][x++] == '-')
	{
		while ((*args)[0][x])
		{
			if ((*args)[0][x] != 'n')
			{
				nnl = 0;
				break ;
			}
			if ((*args)[0][x] == 'n')
				nnl = 1;
			x++;
		}
	}
	if (nnl)
		(*args) = &((*args)[1]);
	return (nnl);
}

int	echooo(char **args, int *exit_stat)
{
	int	x;

	x = 0;
	while (args[x])
	{
		if (x > 0)
		{
			if (printf(" ") < 0)
			{
				*exit_stat = 1;
				return (1);
			}
		}
		if (printf("%s", args[x++]) < 0)
		{
			*exit_stat = 1;
			return (1);
		}
	}
	return (0);
}

int	echo(char **args, t_env *env, int *exit_stat)
{
	char	**sv;
	int		nnl;

	(void)(env);
	sv = args;
	nnl = det_nnl(&args, exit_stat);
	if (nnl == 2)
		return (1);
	if (echooo(args, exit_stat))
		return (1);
	if (!nnl)
	{
		if (printf("\n") < 0)
		{
			*exit_stat = 1;
			return (1);
		}
	}
	*exit_stat = 0;
	return (0);
}

int	print_wd(char **args, t_env *env, int *exit_stat)
{
	char	*wd;

	(void)(args);
	(void)(env);
	wd = getcwd(NULL, 0);
	if (!wd)
	{
		*exit_stat = 0;
		return (printf(".\n"), 0);
	}
	if (printf("%s\n", wd) < 0)
	{
		*exit_stat = 1;
		return (free(wd), 1);
	}
	free(wd);
	*exit_stat = 0;
	return (0);
}
