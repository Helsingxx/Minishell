/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:14:45 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 15:15:00 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detnxttype(t_node *ll, int x)
{
	t_node	*prev;
	int		c;

	c = 0;
	prev = ll;
	while (ll && (c != x || ll->type != HERDOC))
	{
		if (ll->type == HERDOC)
			c++;
		ll = ll->next;
	}
	if (ll)
		ll = ll->next;
	while (ll && ll->type != HERDOC
		&& (skip_expand_split(&ll) || 1) && ll->space_after == 0)
	{
		if (ll->type == QUOTE_ARG)
			return (QUOTE_ARG);
		ll = ll->next;
	}
	return (ARG);
}

int	set_redirects(char **redirects, int *fds)
{
	if (in_redir(redirects, fds))
		return (ABORTCURRENTCMD);
	if (out_redir(redirects, fds))
		return (ABORTCURRENTCMD);
	if (apnd_redir(redirects, fds))
		return (ABORTCURRENTCMD);
	return (0);
}

int	*set_invalid(int *fds)
{
	int	x;

	x = 0;
	while (x < 5)
	{
		fds[x] = -1;
		x++;
	}
	return (fds);
}

void	end_command(t_comparsed *cmds)
{
	static t_comparsed	*save;
	int					x;

	if (cmds)
		save = cmds;
	if (!cmds)
		close(STDIN_FILENO);
	if (!cmds && save)
	{
		x = 0;
		while (x < save->cmd_count && save->fds[x])
		{
			if (save->fds[x][1] != -1)
			{
				close(save->fds[x][1]);
				save->fds[x][1] = -1;
			}
			x++;
		}
		save->cmd_count = 0;
	}
}

void	herestop(int x)
{
	(void) x;
	end_command(0);
	exit_status(130);
}
