/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:46:17 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/17 00:04:26 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_redir_args(t_node **linked_list)
{
	(*linked_list) = (*linked_list)->next;
	skip_expand_split(linked_list);
	while ((*linked_list) && (*linked_list)->next
		&& !(*linked_list)->space_after
		&& !((*linked_list)->next->type == STDIN_RD
			|| (*linked_list)->next->type == STDOUT_RD
			|| (*linked_list)->next->type == HERDOC
			|| (*linked_list)->next->type == APPEND
			|| (*linked_list)->next->type == OPERATOR))
	{
		(*linked_list) = (*linked_list)->next;
		skip_expand_split(linked_list);
	}
}

char	*_join(char *acc, char *a)
{
	int		x;
	int		c;
	char	*res;

	x = 0;
	res = ft_calloc(sizeof(char), _ft_strlen(acc) + _ft_strlen(a) + 1);
	while (acc && acc[x])
	{
		res[x] = acc[x];
		x++;
	}
	c = 0;
	while (a && a[c])
	{
		res[x] = a[c];
		x++;
		c++;
	}
	res[x] = 0;
	return (res);
}

char	**append(char **exec_ready, char *data)
{
	int		x;
	int		c;
	char	**newexecready;

	x = 0;
	while (exec_ready && exec_ready[x])
		x++;
	newexecready = ft_calloc(sizeof(char *), x + 1 + 1);
	c = 0;
	while (c < x)
	{
		newexecready[c] = exec_ready[c];
		c++;
	}
	newexecready[c] = data;
	return (newexecready);
}

void	get_joined_single_exec_arg(t_node **linked_list, char ***single_execrdy)
{
	char	*acc;

	acc = 0;
	while ((*linked_list) && (*linked_list)->data
		&& !(*linked_list)->data[0] && (*linked_list)->type == ARG)
		(*linked_list) = (*linked_list)->next;
	if (*linked_list && ((*linked_list)->type == ARG
			|| (*linked_list)->type == 2 || (*linked_list)->type == CMD))
		acc = _join(acc, (*linked_list)->data);
	while ((*linked_list) && ((*linked_list)->type == QUOTE_ARG
			|| (*linked_list)->type == ARG
			|| (*linked_list)->type == CMD)
		&& (*linked_list)->next && ((*linked_list)->next->type == QUOTE_ARG
			|| (*linked_list)->next->type == ARG
			|| (*linked_list)->next->type == CMD)
		&& !(*linked_list)->space_after)
	{
		acc = _join(acc, (*linked_list)->next->data);
		(*linked_list) = (*linked_list)->next;
	}
	*single_execrdy = append(*single_execrdy, acc);
}

char	**get_exec_rdy(t_node **linked_list)
{
	char	**single_execrdy;
	char	*acc;

	acc = 0;
	single_execrdy = 0;
	while ((*linked_list) && (*linked_list)->type != OPERATOR)
	{
		if ((*linked_list) && ((*linked_list)->type == STDIN_RD
				|| (*linked_list)->type == STDOUT_RD
				|| (*linked_list)->type == HERDOC
				|| (*linked_list)->type == APPEND))
			skip_redir_args(linked_list);
		else if ((*linked_list))
			get_joined_single_exec_arg(linked_list, &single_execrdy);
		if ((*linked_list))
			(*linked_list) = (*linked_list)->next;
	}
	if ((*linked_list))
		(*linked_list) = (*linked_list)->next;
	return (single_execrdy);
}
