/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:45:03 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 20:11:40 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	jma3_kolchi_init(t_node **linked_list, char **fill, int type_from)
{
	if (type_from == HERDOC && (*linked_list)->before_env)
	{
		fill[0] = _join(fill[0], (*linked_list)->before_env);
		skip_expand_split(linked_list);
	}
	else
	{
		if (type_from != HERDOC && (*linked_list)->exp_nosplit)
		{
			fill[0] = _join(fill[0], (*linked_list)->exp_nosplit);
			skip_expand_split(linked_list);
		}
		else
			fill[0] = _join(fill[0], (*linked_list)->data);
	}
}

void	jma3_next_nospace(t_node **linked_list, int type_from,
						char **fill, int *skipped)
{
	if (type_from == HERDOC && (*linked_list)->next->before_env)
	{
		fill[0] = _join(fill[0], (*linked_list)->next->before_env);
		if ((*linked_list)->next->exp_nosplit)
		{
			(*linked_list) = (*linked_list)->next;
			*skipped = 1;
			skip_expand_split(linked_list);
		}
	}
	else
	{
		if (type_from != HERDOC && (*linked_list)->next->exp_nosplit)
		{
			fill[0] = _join(fill[0], (*linked_list)->next->exp_nosplit);
			(*linked_list) = (*linked_list)->next;
			*skipped = 1;
			skip_expand_split(linked_list);
		}
		else
			fill[0] = _join(fill[0], (*linked_list)->next->data);
	}
}

void	jma3_kolchi(t_node **linked_list, char **fill,
					char **empty, int type_from)
{
	int	skipped;

	skipped = 0;
	fill[0] = 0;
	jma3_kolchi_init(linked_list, fill, type_from);
	while ((*linked_list) && ((*linked_list)->type == QUOTE_ARG
			|| (*linked_list)->type == ARG
			|| (*linked_list)->type == CMD)
		&& (*linked_list)->next && ((*linked_list)->next->type == QUOTE_ARG
			|| (*linked_list)->next->type == ARG
			|| (*linked_list)->next->type == CMD)
		&& (!(*linked_list)->space_after))
	{
		jma3_next_nospace(linked_list, type_from, fill, &skipped);
		if (skipped)
			skipped = 0;
		else
			(*linked_list) = (*linked_list)->next;
	}
	empty[0] = 0;
}

void	assemble_garbage_init(t_node **linked_list, int type_from, char **fill)
{
	*fill = 0;
	if (type_from == HERDOC && (*linked_list)->before_env)
	{
		*fill = _join(*fill, (*linked_list)->before_env);
		skip_expand_split(linked_list);
	}
	else
	{
		if (type_from != HERDOC && (*linked_list)->exp_nosplit)
		{
			*fill = _join(*fill, (*linked_list)->exp_nosplit);
			skip_expand_split(linked_list);
		}
		else
			*fill = _join(*fill, (*linked_list)->data);
	}
}

void	assemble_garbage_next_nospace(t_node **linked_list,
					int type_from, char **fill, int *skipped)
{
	if (type_from == HERDOC && (*linked_list)->next->before_env)
	{
		*fill = _join(*fill, (*linked_list)->next->before_env);
		if ((*linked_list)->next->exp_nosplit)
		{
			(*linked_list) = (*linked_list)->next;
			*skipped = 1;
			skip_expand_split(linked_list);
		}
	}
	else
	{
		if (type_from != HERDOC && (*linked_list)->next->exp_nosplit)
		{
			*fill = _join(*fill, (*linked_list)->next->exp_nosplit);
			(*linked_list) = (*linked_list)->next;
			*skipped = 1;
			skip_expand_split(linked_list);
		}
		else
			*fill = _join(*fill, (*linked_list)->next->data);
	}
}
