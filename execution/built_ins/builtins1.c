/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:42:54 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 20:16:58 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_noargs(t_env **env)
{
	t_env	*restore;

	restore = *env;
	while (*env)
	{
		if ((*env)->only_export && (!(*env)->value || !(*env)->value[0]))
			printf("declare -x %s\n", (*env)->key);
		else
			printf("declare -x %s=\"%s\"\n", (*env)->key, (*env)->value);
		(*env) = (*env)->next;
	}
	(*env) = restore;
}

void	export_mgadra(char **args, t_env **env, int *exit_stat, int x)
{
	int	opti;
	int	c;

	c = 0;
	while (c < x)
	{
		opti = chck_node((*env), args[c]);
		if (opti == 0)
			append_env_node(env, args[c++]);
		else if (opti == 1)
			c++;
		else if (opti == -1)
		{
			*exit_stat = 1;
			printf("Invalid identifier!\n");
			c++;
		}
		else if (opti == 2)
		{
			if (!is_there(*env, args[c]))
				append_env_node(env, args[c]);
			set_exp(*env, args[c++]);
		}
	}
}

int	export(char **args, t_env **env, int *exit_stat)
{
	int	x;

	x = 0;
	*exit_stat = 0;
	while (args && args[x])
		x++;
	if (x == 0)
		export_noargs(env);
	else
		export_mgadra(args, env, exit_stat, x);
	return (0);
}

int	unset(char **args, t_env **env, int *exit_stat)
{
	int		x;
	t_env	*prev;
	t_env	*sv;

	x = 0;
	sv = *env;
	while (args[x])
	{
		prev = 0;
		if (!valid_key(args[x]))
			(*exit_stat = 1) && (printf("Invalid identifier!\n"));
		while (*env && _ft_strcmp((*env)->key, args[x]))
		{
			prev = *env;
			*env = (*env)->next;
		}
		if (!prev && *env)
			sv = (*env)->next;
		else if (prev && *env)
			prev->next = (*env)->next;
		*env = sv;
		x++;
	}
	*exit_stat = 0;
	return (0);
}

void	print_env(char **args, t_env *head, int *exit_stat)
{
	(void) args;
	while (head)
	{
		if (!head->only_export)
		{
			if (head->value)
				printf("%s=%s\n", head->key, head->value);
			else
				printf("%s=\n", head->key);
		}
		head = head->next;
	}
	*exit_stat = 0;
}
