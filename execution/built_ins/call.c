/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:51:17 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 17:01:00 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_exit(char **args, int *exit_stat)
{
	if (args[0] == NULL)
		exit_status(0);
	else if (is_int0(args[0]) && !args[1])
	{
		if (ft_atoi(args[0]) < 0)
			exit_status(256 - ((-ft_atoi(args[0])) % 256));
		else if (ft_atoi(args[0]) > 255)
			exit_status(ft_atoi(args[0]) % 256);
		else
			exit_status(ft_atoi(args[0]));
	}
	else if (is_int0(args[0]) && args[1])
	{
		printf("minishell: exit: too many arguments\n");
		*exit_stat = 1;
		return ;
	}
	else
		exit_status(255);
	fail_exit();
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	call_respective(char **cmd, int *exit_stat, t_env **env)
{
	if (!_ft_strcmp(cmd[0], "echo"))
		echo(&cmd[1], *env, exit_stat);
	if (!_ft_strcmp(cmd[0], "cd"))
		change_dir(&cmd[1], *env, exit_stat);
	if (!_ft_strcmp(cmd[0], "pwd"))
		print_wd(&cmd[1], *env, exit_stat);
	if (!_ft_strcmp(cmd[0], "export"))
		export(&cmd[1], env, exit_stat);
	if (!_ft_strcmp(cmd[0], "unset"))
		unset(&cmd[1], env, exit_stat);
	if (!_ft_strcmp(cmd[0], "env"))
		print_env(&cmd[1], *env, exit_stat);
	if (!_ft_strcmp(cmd[0], "exit"))
		c_exit(&cmd[1], exit_stat);
}
