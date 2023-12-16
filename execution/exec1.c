/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:10 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 14:34:14 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_r1(t_ex *_, t_comparsed *cmds, t_env **env)
{
	inc_val(*env, "SHLVL=whocares");
	if (overridefds(cmds, _->x, _->_pipe, _->sv_next) == SYSCALLFAIL)
	{
		exit_status(SYSCALLFAIL);
		fail_exit();
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	print_err(int perm)
{
	if (perm)
		write(2, "Permission issue.\n", ft_strlen("Permission issue.\n"));
	else
		write(2, "Command not found.\n", ft_strlen("Command not found.\n"));
	return (1);
}

void	child_r2(t_ex *_, t_comparsed *cmds, t_env **env)
{
	if (is_builtin(cmds->exec_ready[_->x][0]))
		(call_respective(cmds->exec_ready[_->x], &cmds->exit_status, env), 1)
		&& exit_status(cmds->exit_status);
	else if (find_executable(cmds->exec_ready[_->x][0], *env))
	{
		if (execve(find_executable(cmds->exec_ready[_->x][0], *env),
			cmds->exec_ready[_->x], cmds->uptodate_env) == -1)
			(exit_status(ACCESS_DENIED)) && (print_err(1));
	}
	else if (is_in(cmds->exec_ready[_->x][0], '/')
		&& execve(cmds->exec_ready[_->x][0],
		cmds->exec_ready[_->x], cmds->uptodate_env) == -1)
	{
		if (!access(cmds->exec_ready[_->x][0], F_OK)
			&& access(cmds->exec_ready[_->x][0], X_OK))
			(exit_status(ACCESS_DENIED), 1) && print_err(1);
		else
			(exit_status(127), 1) && print_err(0);
	}
	else
		(exit_status(127), 1) && print_err(0);
	fail_exit();
}

void	child_routines(t_ex *_, t_comparsed *cmds, t_env **env)
{
	child_r1(_, cmds, env);
	child_r2(_, cmds, env);
}

int	setup_child(t_ex *_, t_comparsed *cmds, t_env **env)
{
	if (set_pipe(_->_pipe, _->x, cmds->cmd_count) == SYSCALLFAIL)
		return (close_fds(cmds->fds[_->x]),
			close(_->_pipe[0]), close(_->_pipe[1]), SYSCALLFAIL);
	cmds->uptodate_env = env_toarray(*env);
	_->chld_pid = fork();
	if (_->chld_pid == -1)
		return (SYSCALLFAIL);
	if (cmds->exec_ready[_->x] == _->last_proc)
		_->pid_last = _->chld_pid;
	return (0);
}
