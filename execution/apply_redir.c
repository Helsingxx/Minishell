/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:45:30 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/16 16:05:03 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_or_not(t_norminettetwo *_, int *fds, char **intheenv)
{
	if (_->type != QUOTE_ARG)
	{
		if (write(fds[1], intheenv[1], ft_strlen(intheenv[1])) == -1)
			return (printf("Error writing to pipe!\n"),
				close(fds[1]), free(_->result), SYSCALLFAIL);
	}
	else
	{
		if (write(fds[1], _->result, ft_strlen(_->result)) == -1)
			return (printf("Error writing to pipe!\n"),
				close(fds[1]), free(_->result), SYSCALLFAIL);
	}
	if (write(fds[1], "\n", 1) == -1)
		return (printf("Error writing to pipe!\n"),
			close(fds[1]), free(_->result), SYSCALLFAIL);
	return (0);
}

int	heredoc_loop(t_norminettetwo *_, int *fds, t_comparsed *cmds)
{
	char	**intheenv;

	while (_ft_strcmp(_->result, _->delimiter))
	{
		intheenv = _get_quoted_word(_->result, &(int){-1},
				cmds->environment);
		if (expand_or_not(_, fds, intheenv))
			return (SYSCALLFAIL);
		free(_->result);
		_->result = readline("> ");
		if (!_->result)
		{
			close(fds[1]);
			return (0);
		}
	}
	return (0);
}

int	heredoc(char *delimiter, int *fds, int type, t_comparsed *cmds)
{
	char			*result;
	t_norminettetwo	_;

	result = 0;
	if (pipe(fds))
		return (SYSCALLFAIL);
	result = readline("> ");
	if (!result)
	{
		close(fds[1]);
		return (0);
	}
	_.delimiter = delimiter;
	_.result = result;
	_.type = type;
	if (heredoc_loop(&_, fds, cmds))
		return (SYSCALLFAIL);
	free(_.result);
	close(fds[1]);
	return (0);
}

int	call_heredocs(t_comparsed *cmds, int **fds)
{
	int	x;
	int	c;

	c = 0;
	x = 0;
	while (x < cmds->cmd_count)
	{
		fds[x] = set_invalid(ft_calloc(sizeof(int), 5));
		if (cmds->real_redirects[x][1]
			&& cmds->heredocs[c] == cmds->real_redirects[x][1])
		{
			if (heredoc(cmds->real_redirects[x][1], &fds[x][1],
				detnxttype(cmds->all_thestuff, x)
				, cmds) == SYSCALLFAIL)
				return (SYSCALLFAIL);
			c++;
		}
		else if (cmds->real_redirects[x][1]
			&& cmds->heredocs[c] != cmds->real_redirects[x][1])
			if (fake_skip(&c, &x, cmds, fds))
				return (SYSCALLFAIL);
		x++;
	}
	return (0);
}

int	set_fds(t_comparsed *cmds)
{
	sigset_t	type;

	sigemptyset(&type);
	cmds->fds = ft_calloc(sizeof(int *), cmds->cmd_count);
	end_command(cmds);
	sigaction(SIGINT,
		&(struct sigaction)
	{.__sigaction_u.__sa_handler = herestop,
		.sa_mask = type, .sa_flags = 0},
		NULL);
	return (call_heredocs(cmds, cmds->fds));
}
