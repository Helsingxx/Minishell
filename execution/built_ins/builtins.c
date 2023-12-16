/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:54:31 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/15 17:44:31 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_wd(char *wd, t_env *env)
{
	char	*sv;

	if (!wd)
		return ;
	alloc_wrap(wd);
	sv = ft_strjoin("PWD=", wd);
	while (env && _ft_strcmp(env->key, "PWD"))
		env = env->next;
	if (!env)
		append_env_node(&env, sv);
	else
		env->value = wd;
}

void	update_oldwd(char *old, t_env *env)
{
	char	*sv;

	if (!old)
		return ;
	sv = ft_strjoin("OLDPWD=", old);
	while (env && _ft_strcmp(env->key, "OLDPWD"))
		env = env->next;
	if (!env)
		append_env_node(&env, sv);
	else
		env->value = old;
}

int	cd_home(t_env *env, int *exit_stat, char *old)
{
	while (env && _ft_strcmp(env->key, "HOME"))
		env = env->next;
	if (!env || !env->value)
		return (printf("Failure to change directory!\n"), 1);
	else if (chdir(env->value) == -1)
	{
		*exit_stat = 1;
		return (printf("Failure to change directory!\n"), 1);
	}
	update_wd(getcwd(NULL, 0), env);
	update_oldwd(old, env);
	return (0);
}
