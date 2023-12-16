/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:48:06 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 14:57:38 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_childs(t_ex *_, t_comparsed *cmds)
{
	int	captured;
	int	discard;

	discard = 0;
	captured = 0;
	_->pid_wait = waitpid(-1, &cmds->exit_status, 0);
	while (_->pid_wait > 0)
	{
		if (!captured && _->last_proc && _->pid_last == _->pid_wait
			&& WIFEXITED(cmds->exit_status))
			(captured = 1)
				&& (cmds->exit_status = WEXITSTATUS(cmds->exit_status));
		else if (!captured && _->last_proc && _->pid_last == _->pid_wait
			&& WIFSIGNALED(cmds->exit_status))
			(captured = 1)
				&& (cmds->exit_status = 128 + WTERMSIG(cmds->exit_status));
		if (!captured && _->last_proc && _->pid_last == _->pid_wait
			&& cmds->exit_status > 255)
			(captured = 1) && (cmds->exit_status = 255);
		if (!captured)
			_->pid_wait = waitpid(-1, &cmds->exit_status, 0);
		else
			_->pid_wait = waitpid(-1, &discard, 0);
	}
}

int	initialize(t_ex *_, t_comparsed *cmds)
{
	(_->sv_next = -1) && (_->pid_last = -1)
		&& ((_->last_proc = 0) || (_->x = 0));
	(_->_pipe[0] = -1) && (_->_pipe[1] = -1);
	if (set_fds(cmds) == SYSCALLFAIL)
		return (signal(SIGINT, SIG_IGN), restore_fds(0), SYSCALLFAIL);
	cmds->exit_status = exit_status(YIELD);
	signal(SIGINT, SIG_IGN);
	restore_fds(0);
	det_last(cmds, &_->last_proc);
	return (0);
}

int	launch_cmd(t_ex *_, t_comparsed *cmds, t_env **env)
{
	if (is_builtin(cmds->exec_ready[_->x][0]) && !det_subshell(cmds))
	{
		if (overridefds(cmds, _->x, _->_pipe, _->sv_next) == SYSCALLFAIL)
			return (close_fds(cmds->fds[_->x]), close(_->_pipe[0]),
				close(_->_pipe[1]), SYSCALLFAIL);
		call_respective(cmds->exec_ready[_->x], &cmds->exit_status, env);
	}
	else
	{
		if (setup_child(_, cmds, env))
			return (SYSCALLFAIL);
		if (!_->chld_pid)
			child_routines(_, cmds, env);
	}
	return (0);
}

int	_redirs(t_ex *_, t_comparsed *cmds)
{
	if (apply_garbage_redir(cmds->garbage_redirects_arr[_->x])
		== ABORTCURRENTCMD)
	{
		(close(_->_pipe[0]), 1) && (close(_->_pipe[1]), 1) && (_->sv_next = -2);
		return (ABORTCURRENTCMD);
	}
	else if (set_redirects(cmds->real_redirects[_->x],
			cmds->fds[_->x]) == ABORTCURRENTCMD)
	{
		(close(_->_pipe[0]), 1) && (close(_->_pipe[1]), 1) && (_->sv_next = -2);
		return (ABORTCURRENTCMD);
	}
	return (0);
}

int	execute_list(t_comparsed *cmds, t_env **env)
{
	struct s_ex	_;

	if (initialize(&_, cmds))
		return (SYSCALLFAIL);
	while (cmds && _.x < cmds->cmd_count)
	{
		if (_redirs(&_, cmds))
			;
		else if (cmds->exec_ready[_.x] && cmds->exec_ready[_.x][0])
		{
			if (launch_cmd(&_, cmds, env))
				return (SYSCALLFAIL);
			if (_.sv_next != -1)
				close(_.sv_next);
			close(_._pipe[1]);
			_.sv_next = _._pipe[0];
		}
		close_fds(cmds->fds[_.x]);
		restore_fds(0);
		_.x++;
	}
	wait_for_childs(&_, cmds);
	return (0);
}
