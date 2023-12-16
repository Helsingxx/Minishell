/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:48:29 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 20:14:14 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_by_type(t_node **rn_linked_list, char **redirs,
					char **heredocs, int *x)
{
	if ((*rn_linked_list) && (*rn_linked_list)->type == STDIN_RD)
	{
		(*rn_linked_list) = (*rn_linked_list)->next;
		jma3_kolchi(rn_linked_list, &redirs[0], &redirs[1], STDIN_RD);
	}
	else if ((*rn_linked_list) && (*rn_linked_list)->type == HERDOC)
	{
		(*rn_linked_list) = (*rn_linked_list)->next;
		jma3_kolchi(rn_linked_list, &redirs[1], &redirs[0], HERDOC);
		heredocs[*x] = redirs[1];
		(*x)++;
	}
	else if ((*rn_linked_list) && (*rn_linked_list)->type == STDOUT_RD)
	{
		(*rn_linked_list) = (*rn_linked_list)->next;
		jma3_kolchi(rn_linked_list, &redirs[2], &redirs[3], STDOUT_RD);
	}
	else if ((*rn_linked_list) && (*rn_linked_list)->type == APPEND)
	{
		(*rn_linked_list) = (*rn_linked_list)->next;
		jma3_kolchi(rn_linked_list, &redirs[3], &redirs[2], APPEND);
	}
}

char	**get_real_redirs(t_node *rn_linked_list,
						char **heredocs, t_node *origin)
{
	char			**redirs;
	static int		x;
	static t_node	*sv;

	if (sv != origin)
	{
		sv = origin;
		x = 0;
	}
	redirs = ft_calloc(sizeof(char *), 4);
	while (rn_linked_list && rn_linked_list->type != OPERATOR)
	{
		get_by_type(&rn_linked_list, redirs, heredocs, &x);
		if (rn_linked_list && (rn_linked_list->type == ARG
				|| rn_linked_list->type == QUOTE_ARG
				|| rn_linked_list->type == CMD))
			rn_linked_list = rn_linked_list->next;
	}
	return (redirs);
}
