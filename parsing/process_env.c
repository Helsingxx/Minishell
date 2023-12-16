/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:43:25 by dtunderm          #+#    #+#             */
/*   Updated: 2023/12/16 17:40:07 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_dollar(char *input, int *i, t_env *l_env, t_p_t_p *params)
{
	params->temp = *i;
	params->before_env = get_env_var_ex(input, *i);
	params->data = get_env_var(input, i, l_env);
	params->space_flag = ft_isspace(input[*i]);
	params->type = ARG;
}

char	*get_env_var_ex(char *input, int i)
{
	int		start;
	char	*var_name;
	int		dollar;

	dollar = 0;
	start = i;
	while (input[i] == '$')
	{
		i++;
		dollar++;
	}
	while (input[i] && !ft_isspace(input[i]) && !is_operator(input[i])
		&& input[i] != '\"' && input[i] != '\'' && input[i] != '$')
		i++;
	var_name = ft_strndup(&input[start], i - start);
	return (var_name);
}

char	*get_env_var(char *input, int *i, t_env *l_env)
{
	t_make_env	*_;

	_ = create_m_e();
	(*i)++;
	loop_dollar(input, i, _);
	if (input[*i] == '?')
		get_var_es(input, i, _);
	else
	{
		if (get_var(input, i, _, l_env) == -1)
			return (ft_strndup(&input[_->start - _->dol - 1],
					_->dol + 1));
	}
	if (_->var_value == NULL)
		return (no_var_value(input, _));
	_->result = ft_calloc(sizeof(char),
			ft_strlen(_->var_value) + 1 + ft_strlen(_->delim) + _->dol);
	ft_strcat(_->result,
		ft_strndup(&input[_->start - _->dol], _->dol));
	ft_strcat(_->result, _->var_value);
	ft_strcat(_->result, _->delim);
	_->result = ft_strdup(_->result);
	return (_->result);
}

void	get_var_es(char *input, int *i, t_make_env *_)
{
	(*i)++;
	_->non_delim_index = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i])
		&& input[*i] != '\"' && input[*i] != '\'' && input[*i] != '$')
		(*i)++;
	_->end = *i;
	_->delim = ft_substr(&input[_->non_delim_index],
			0, _->end - _->non_delim_index);
	_->var_value = ft_itoa(exit_status(YIELD));
}

int	get_var(char *input, int *i, t_make_env *_, t_env *l_env)
{
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_' ))
		(*i)++;
	_->non_delim_index = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i])
		&& input[*i] != '\"' && input[*i] != '\'' && input[*i] != '$')
		(*i)++;
	_->end = *i;
	if (_->end == _->start - _->dol)
		return (-1);
	_->delim = ft_substr(&input[_->non_delim_index],
			0, _->end - _->non_delim_index);
	_->var_name = ft_strndup(&input[_->start],
			_->non_delim_index - _->start);
	_->var_value = find_env_var(_->var_name, l_env);
	return (1);
}
