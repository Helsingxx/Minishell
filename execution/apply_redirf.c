/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:14:52 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 20:25:38 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fake_heredoc_loop(t_norminettetwo *_, int *fds)
{
	while (_ft_strcmp(_->result, _->delimiter))
	{
		if (write(fds[1], _->result, ft_strlen(_->result)) == -1)
			return (printf("Error writing to pipe!\n"), close(fds[0]),
				close(fds[1]), free(_->result), WHOCARES);
		if (write(fds[1], "\n", 1) == -1)
			return (printf("Error writing to pipe!\n"), close(fds[0]),
				close(fds[1]), free(_->result), WHOCARES);
		free(_->result);
		_->result = readline("> ");
		if (!_->result)
		{
			close(fds[0]);
			close(fds[1]);
			return (0);
		}
	}
	return (0);
}

int	fake_heredoc(char *delimiter)
{
	char			*result;
	t_norminettetwo	_;
	int				fds[2];

	result = 0;
	if (pipe(fds))
		return (WHOCARES);
	result = readline("> ");
	if (!result)
	{
		close(fds[0]);
		close(fds[1]);
		return (0);
	}
	_.result = result;
	_.delimiter = delimiter;
	fake_heredoc_loop(&_, fds);
	free(_.result);
	close(fds[0]);
	close(fds[1]);
	return (0);
}

int	fake_skip(int *c, int *x, t_comparsed *cmds, int **fds)
{
	while (cmds->heredocs[*c]
		&& cmds->heredocs[*c] != cmds->real_redirects[*x][1] && cmds->cmd_count)
	{
		fake_heredoc(cmds->heredocs[*c]);
		(*c)++;
	}
	if (cmds->heredocs[*c] && cmds->cmd_count)
		if (heredoc(cmds->real_redirects[*x][1], &fds[*x][1],
			detnxttype(cmds->all_thestuff, *x)
			, cmds) == SYSCALLFAIL)
			return (SYSCALLFAIL);
	if (cmds->heredocs[*c])
		(*c)++;
	return (0);
}
