/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:43:34 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 20:09:36 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*assemble_garbage(t_node **linked_list, int type_from)
{
	char	*fill;
	int		skipped;

	skipped = 0;
	fill = 0;
	assemble_garbage_init(linked_list, type_from, &fill);
	while ((*linked_list) && ((*linked_list)->type == QUOTE_ARG
			|| (*linked_list)->type == ARG
			|| (*linked_list)->type == CMD)
		&& (*linked_list)->next && ((*linked_list)->next->type == QUOTE_ARG
			|| (*linked_list)->next->type == ARG
			|| (*linked_list)->next->type == CMD)
		&& (!(*linked_list)->space_after))
	{
		assemble_garbage_next_nospace(linked_list, type_from, &fill, &skipped);
		if (skipped)
			skipped = 0;
		else
			(*linked_list) = (*linked_list)->next;
	}
	return (fill);
}

void	get_garbage_by_type(t_node *rn_linked_list,
		char **dont_be_this, char ***g_redirs, t_norminette *_)
{
	char	*sv;

	sv = 0;
	if (rn_linked_list && rn_linked_list->type == STDOUT_RD)
	{
		rn_linked_list = rn_linked_list->next;
		sv = assemble_garbage(&rn_linked_list, STDOUT_RD);
		if (!dont_be_this[2] || _ft_strcmp(sv, dont_be_this[2]))
			g_redirs[0][_->x++] = sv;
	}
	if (rn_linked_list && rn_linked_list->type == APPEND)
	{
		rn_linked_list = rn_linked_list->next;
		sv = assemble_garbage(&rn_linked_list, APPEND);
		if (!dont_be_this[3] || _ft_strcmp(sv, dont_be_this[3]))
			g_redirs[1][_->app++] = sv;
	}
	if (rn_linked_list && rn_linked_list->type == STDIN_RD)
	{
		rn_linked_list = rn_linked_list->next;
		sv = assemble_garbage(&rn_linked_list, STDIN_RD);
		if (!dont_be_this[0] || _ft_strcmp(sv, dont_be_this[0]))
			g_redirs[2][_->in++] = sv;
	}
}

void	get_them_forreal(t_node *rn_linked_list,
			char **dont_be_this, char ***g_redirs)
{
	t_norminette	_;

	_.app = 0;
	_.x = 0;
	_.in = 0;
	while (rn_linked_list && rn_linked_list->type != OPERATOR)
	{
		get_garbage_by_type(rn_linked_list, dont_be_this, g_redirs, &_);
		if (rn_linked_list && (rn_linked_list->type == ARG
				|| rn_linked_list->type == QUOTE_ARG
				|| rn_linked_list->type == CMD
				|| rn_linked_list->type == HERDOC))
			rn_linked_list = rn_linked_list->next;
	}
}

void	count_garbage(t_node *rn_linked_list,
				char **dont_be_this, t_norminette *_)
{
	if (rn_linked_list && rn_linked_list->type == STDOUT_RD)
	{
		rn_linked_list = rn_linked_list->next;
		if ((!dont_be_this[2] && assemble_garbage(&rn_linked_list, STDOUT_RD))
			|| _ft_strcmp(assemble_garbage(&rn_linked_list, STDOUT_RD),
				dont_be_this[2]))
			_->x++;
	}
	if (rn_linked_list && rn_linked_list->type == APPEND)
	{
		rn_linked_list = rn_linked_list->next;
		if ((!dont_be_this[3] && assemble_garbage(&rn_linked_list, APPEND))
			|| _ft_strcmp(assemble_garbage(&rn_linked_list, APPEND),
				dont_be_this[3]))
			_->app++;
	}
	if (rn_linked_list && rn_linked_list->type == STDIN_RD)
	{
		rn_linked_list = rn_linked_list->next;
		if ((!dont_be_this[0] && assemble_garbage(&rn_linked_list, STDIN_RD))
			|| _ft_strcmp(assemble_garbage(&rn_linked_list, STDIN_RD),
				dont_be_this[0]))
			_->in++;
	}
}

char	***get_garbage_redirs(t_node *rn_linked_list, char **dont_be_this)
{
	t_node			*sv;
	char			***g_redirs;
	t_norminette	_;

	sv = rn_linked_list;
	_.x = 0;
	_.app = 0;
	_.in = 0;
	while (rn_linked_list && rn_linked_list->type != OPERATOR)
	{
		count_garbage(rn_linked_list, dont_be_this, &_);
		if (rn_linked_list && (rn_linked_list->type == ARG
				|| rn_linked_list->type == QUOTE_ARG
				|| rn_linked_list->type == CMD
				|| rn_linked_list->type == HERDOC))
			rn_linked_list = rn_linked_list->next;
	}
	g_redirs = ft_calloc(sizeof (char **), 3);
	g_redirs[0] = ft_calloc(sizeof (char *), _.x + 1);
	g_redirs[1] = ft_calloc(sizeof (char *), _.app + 1);
	g_redirs[2] = ft_calloc(sizeof (char *), _.in + 1);
	get_them_forreal(sv, dont_be_this, g_redirs);
	return (g_redirs);
}
