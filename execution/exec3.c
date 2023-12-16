/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:15 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 14:34:19 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_errfds(t_comparsed *cmds, int x)
{
	if (cmds->fds[x][3] == -1 && cmds->real_redirects[x][2])
		close(STDOUT_FILENO);
	if (cmds->fds[x][4] == -1 && cmds->real_redirects[x][3])
		close(STDOUT_FILENO);
	if (cmds->fds[x][0] == -1 && cmds->real_redirects[x][0])
		close(STDIN_FILENO);
}

int	override_stdout(t_comparsed *cmds, int x, int *_pipe)
{
	if (cmds->fds[x][3] != -1)
	{
		if (dup2(cmds->fds[x][3], STDOUT_FILENO) == -1)
			return (SYSCALLFAIL);
	}
	else if (cmds->fds[x][4] != -1)
	{
		if (dup2(cmds->fds[x][4], STDOUT_FILENO) == -1)
			return (SYSCALLFAIL);
	}
	else if (x < cmds->cmd_count - 1)
	{
		if (dup2(_pipe[1], STDOUT_FILENO) == -1)
			return (close(_pipe[0]), SYSCALLFAIL);
		close(_pipe[0]);
	}
	return (0);
}

int	override_stdin(t_comparsed *cmds, int x, int *_pipe, int sv_next)
{
	if (cmds->fds[x][0] != -1)
	{
		if (dup2(cmds->fds[x][0], STDIN_FILENO) == -1)
			return (SYSCALLFAIL);
	}
	else if (cmds->fds[x][1] != -1)
	{
		if (dup2(cmds->fds[x][1], STDIN_FILENO) == -1)
			return (SYSCALLFAIL);
	}
	else if (x > 0)
	{
		if (sv_next == -2)
			close(STDIN_FILENO);
		else
		{
			if (dup2(sv_next, STDIN_FILENO) == -1)
				return (close(_pipe[0]), SYSCALLFAIL);
			close(_pipe[0]);
		}
	}
	return (0);
}

int	overridefds(t_comparsed *cmds, int x, int *_pipe, int sv_next)
{
	int	flag;

	flag = 0;
	if (override_stdout(cmds, x, _pipe))
		return (SYSCALLFAIL);
	if (override_stdin(cmds, x, _pipe, sv_next))
		return (SYSCALLFAIL);
	clean_errfds(cmds, x);
	return (0);
}

void	restore_fds(int isclose)
{
	static int	fd0;
	static int	fd1;
	static int	set;

	if (isclose)
	{
		close(fd0);
		close(fd1);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		return ;
	}
	if (!set)
	{
		fd0 = dup(STDIN_FILENO);
		fd1 = dup(STDOUT_FILENO);
		set = 1;
	}
	else
	{
		dup2(fd0, STDIN_FILENO);
		dup2(fd1, STDOUT_FILENO);
	}
}
