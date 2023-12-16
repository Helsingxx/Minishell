/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:20 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 14:28:21 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned long long		a;
	char					*ptr;

	a = 0;
	ptr = alloc_wrap(malloc(count * size));
	if (ptr == 0)
		return (0);
	while (a < count * size)
	{
		ptr[a++] = 0;
	}
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t		a;
	char		*sc;

	a = 0;
	sc = (char *) s;
	while (a < n)
	{
		sc[a] = 0;
		a++;
	}
}

int	det_subshell(t_comparsed *cmds)
{
	int	subshell;

	subshell = 1;
	if (cmds->cmd_count == 1)
		subshell = 0;
	return (subshell);
}

int	set_pipe(int *_pipe, int x, int cmd_count)
{
	if (cmd_count > 1 && x < cmd_count - 1 && pipe(_pipe))
		return (SYSCALLFAIL);
	return (0);
}
