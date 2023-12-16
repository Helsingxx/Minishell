/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:39:26 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/16 20:58:41 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_expand_split(t_node **linked_list)
{
	char	*exp_nosplit;

	exp_nosplit = 0;
	if ((*linked_list)->space_after >= 2)
		exp_nosplit = (*linked_list)->exp_nosplit;
	while ((*linked_list)->next && (*linked_list)->next->space_after >= 2)
		(*linked_list) = (*linked_list)->next;
	if ((*linked_list)->next && (*linked_list)->space_after >= 2)
		(*linked_list) = (*linked_list)->next;
	return (exp_nosplit);
}

char	**alloc_heredocs(t_node *linked_list)
{
	int		sz;
	char	**result;
	t_node	*sv;

	sv = linked_list;
	sz = 0;
	while (linked_list)
	{
		if (linked_list->type == HERDOC && linked_list->next)
			sz++;
		linked_list = linked_list->next;
	}
	result = ft_calloc(sizeof(char *), sz + 1);
	return (result);
}

t_comparsed	*init_parsed(t_node *linked_list, int cmd_count,
			int exit_stat, char **envp)
{
	t_comparsed	*parsed;

	parsed = ft_calloc(sizeof(t_comparsed), 1);
	parsed->exit_status = exit_stat;
	parsed->uptodate_env = envp;
	parsed->all_thestuff = linked_list;
	parsed->cmd_count = cmd_count;
	parsed->exec_ready = ft_calloc (sizeof(char **), cmd_count + 1);
	parsed->real_redirects = ft_calloc (sizeof(char **), cmd_count + 1);
	parsed->garbage_redirects_arr = ft_calloc (sizeof(char **), cmd_count + 1);
	parsed->heredocs = alloc_heredocs(linked_list);
	return (parsed);
}

t_comparsed	*parsed_single_cmd(t_node *linked_list, int cmd_count,
								int exit_stat, char **envp)
{
	int			x;
	t_node		*rn_linked_list;
	t_node		*sv;
	t_comparsed	*parsed;

	sv = linked_list;
	x = 0;
	parsed = init_parsed(linked_list, cmd_count, exit_stat, envp);
	while (x < cmd_count && linked_list)
	{
		rn_linked_list = linked_list;
		parsed->exec_ready[x] = get_exec_rdy(&linked_list);
		parsed->real_redirects[x] = get_real_redirs(rn_linked_list,
				parsed->heredocs, sv);
		parsed->garbage_redirects_arr[x] = get_garbage_redirs(rn_linked_list,
				parsed->real_redirects[x]);
		x++;
	}
	return (parsed);
}
