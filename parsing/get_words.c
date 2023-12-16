/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:47:45 by dtunderm          #+#    #+#             */
/*   Updated: 2023/12/16 16:48:44 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_result(char *input, int *i, t_env *l_env, t_p_t_p *par)
{
	char	*env_variable;
	char	*before_env;
	char	**result;
	int		start;

	result = ft_calloc(sizeof(char *), 2);
	result[0] = ft_calloc(sizeof(char), 1);
	result[1] = ft_calloc(sizeof(char), 1);
	if ((par->quote_type == '\"' || par->different) && input[*i] == '$')
	{
		before_env = get_env_var_ex(input, *i);
		env_variable = get_env_var(input, i, l_env);
		result[0] = ft_strjoin(result[0], before_env);
		result[1] = ft_strjoin(result[1], env_variable);
		start = *i;
	}
	else
	{
		result[0] = ft_strjoin(result[0], ft_strndup(&input[*i], 1));
		result[1] = ft_strjoin(result[1], ft_strndup(&input[*i], 1));
		(*i)++;
	}
	return (result);
}

void	__initstuff(int *i, int *start, char ***result)
{
	(*i)++;
	*start = *i;
	(*result) = ft_calloc(sizeof(char *), 2);
	(*result)[0] = ft_calloc(sizeof(char), 1);
	(*result)[1] = ft_calloc(sizeof(char), 1);
}

char	**get_quoted_word(char *input, int *i, t_env *l_env, char quote_type)
{
	char	**result;
	char	*env_variable;
	char	*before_env;
	int		start;

	__initstuff(i, &start, &result);
	while (input[*i] && input[*i] != quote_type)
	{
		if (quote_type == '\"' && input[*i] == '$')
		{
			before_env = get_env_var_ex(input, *i);
			env_variable = get_env_var(input, i, l_env);
			result[0] = ft_strjoin(result[0], before_env);
			result[1] = ft_strjoin(result[1], env_variable);
			start = *i;
		}
		else
		{
			result[0] = ft_strjoin(result[0], ft_strndup(&input[*i], 1));
			result[1] = ft_strjoin(result[1], ft_strndup(&input[*i], 1));
			(*i)++;
		}
	}
	return (result);
}

char	*get_word(char *input, int *i)
{
	int		start;
	char	*word;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i])
		&& input[*i] != '\"' && input[*i] != '\'' && input[*i] != '$')
		(*i)++;
	word = ft_strndup(&input[start], *i - start);
	return (word);
}

char	*find_env_var(const char *var_name, t_env *l_env)
{
	size_t	len;
	t_env	*current;

	len = ft_strlen(var_name);
	current = l_env;
	while (current)
		current = current->next;
	while (l_env)
	{
		if (ft_strncmp(l_env->key, var_name, len)
			== 0 && l_env->key[len] == '\0')
			return (l_env->value);
		l_env = l_env->next;
	}
	return (NULL);
}
