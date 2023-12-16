/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:13 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 14:34:16 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_pathll(char *data, t_node *head)
{
	while (head)
	{
		if (!ft_strcmp(head->data, data) && head->path)
			return (head->path);
		else if (!ft_strcmp(head->data, data))
			return (data);
		head = head->next;
	}
	return (data);
}

void	_void(void)
{
	return ;
}

void	close_fds(int *fds)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
	if (fds[3] != -1)
		close(fds[3]);
	if (fds[4] != -1)
		close(fds[4]);
}

int	is_in(char *cmd, char c)
{
	int	x;

	x = 0;
	while (cmd && cmd[x])
	{
		if (cmd[x] == c)
			return (1);
		x++;
	}
	return (0);
}

void	det_last(t_comparsed *cmds, char ***last_proc)
{
	int	x;

	x = 0;
	while (x < cmds->cmd_count)
	{
		if (cmds->exec_ready[x])
			*last_proc = cmds->exec_ready[x];
		x++;
	}
}
