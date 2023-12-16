/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:10:44 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 15:24:15 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*alloc_wrapper(void *allocation, int mode)
{
	static t_alloc	*nodes;
	t_alloc			*tmp;

	if (mode)
	{
		while (nodes)
		{
			free(nodes->allocation);
			tmp = nodes;
			nodes = nodes->next;
			free(tmp);
		}
		nodes = 0;
		return (0);
	}
	if (!allocation)
		exit(exit_status(YIELD));
	if (!nodes)
		nodes = ft_lstnew(allocation);
	else
		ft_lstadd_back(&nodes, ft_lstnew(allocation));
	return (allocation);
}

void	*alloc_wrap(void *arg)
{
	return (alloc_wrapper(arg, 0));
}

void	*fail(void *ret, int smth)
{
	(void) smth;
	if (!ret)
		alloc_wrapper(0, 1);
	return (ret);
}

void	*wrap_wrap(void *allocation)
{
	if (!allocation)
		alloc_wrap(0);
	return (allocation);
}

void	fail_exit(void)
{
	alloc_wrap(0);
}
