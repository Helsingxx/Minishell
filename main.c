/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:02:14 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/16 18:46:33 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*duplicate_env(t_env *env)
{
	t_env	*res;
	t_env	*head;

	res = 0;
	if (env)
		res = malloc(sizeof(t_env));
	head = res;
	while (env)
	{
		res->key = m_ft_strdup(env->key);
		res->value = m_ft_strdup(env->value);
		res->only_export = env->only_export;
		env = env->next;
		if (env)
		{
			res->next = malloc(sizeof(t_env));
			res = res->next;
		}
		else
			res->next = 0;
	}
	return (head);
}

void	alloc_wrap_env(t_env *env)
{
	while (env)
	{
		alloc_wrap(env);
		alloc_wrap(env->key);
		alloc_wrap(env->value);
		env = env->next;
	}
}

void	start_cmd(t_node *head, t_env **l_env, char **envp)
{
	t_comparsed	*parsed;

	parsed = parsed_single_cmd(head, count_cmd(head), exit_status(YIELD), envp);
	resolve_path(head, *l_env);
	parsed->environment = *l_env;
	if (execute_list(parsed, l_env) == SYSCALLFAIL)
		parsed->exit_status = 1;
	exit_status(parsed->exit_status);
	restore_fds(0);
}

void	main_loop(t_node *head, char **envp)
{
	char			*input;
	static t_env	*l_env;

	l_env = envp_to_linked_list(envp);
	while (1)
	{
		if (sig_init())
			continue ;
		input = readline("minishell$: ");
		signal(SIGINT, SIG_IGN);
		if (!input)
			fail_exit();
		alloc_wrap(input);
		if (input && ft_strlen(input) && (add_history(input), 1)
			&& checker_quotes(input))
		{
			lexer(input, &head, l_env);
			set_redirect_in_nodes(head);
			if (!error_all_check(head))
				start_cmd(head, &l_env, envp);
			l_env = duplicate_env(l_env);
			fail(0, 0);
			alloc_wrap_env(l_env);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		x;
	char	*key;
	char	*value;

	(void)argc;
	(void)argv;
	x = 0;
	while (envp && envp[x])
	{
		split_env_var(envp[x], &key, &value);
		if (!_ft_strcmp(key, "SHLVL"))
			envp[x] = ft_strjoin(ft_strjoin(key, "="),
					ft_itoa(ft_atoi(value) + 1));
		x++;
	}
	rl_catch_signals = 0;
	restore_fds(0);
	return (main_loop(0, envp), 0);
}
