/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:08:03 by dtunderm          #+#    #+#             */
/*   Updated: 2023/12/16 16:19:19 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer(char *input, t_node **head, t_env *l_env)
{
	int	i;

	i = 0;
	*head = NULL;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else
			process_token(input, &i, head, l_env);
	}
}

void	minishell_no_alzheimer(t_node *head, char *data)
{
	while (head->next)
		head = head->next;
	head->exp_nosplit = data;
}

t_make_env	*create_m_e(void)
{
	t_make_env	*m_e;

	m_e = (t_make_env *)ft_calloc(sizeof(t_make_env), 1);
	m_e->dol = 0;
	m_e->start = 0;
	m_e->end = 0;
	m_e->non_delim_index = 0;
	m_e->delim = NULL;
	m_e->var_name = NULL;
	m_e->var_value = NULL;
	m_e->result = NULL;
	return (m_e);
}

void	loop_dollar(char *input, int *i, t_make_env *_)
{
	while (input[*i] == '$')
	{
		(*i)++;
		_->dol++;
	}
	_->start = *i;
}

char	*no_var_value(char *input, t_make_env *_)
{
	if (_->non_delim_index - _->start)
	{
		if (!(_->end - _->non_delim_index))
			return (ft_strndup(&input[_->start - _->dol], _->dol));
		else
			return (ft_strjoin(ft_strndup(&input[_->start - _->dol],
						_->dol), _->delim));
	}
	else
		return (ft_strjoin(ft_strndup(&input[_->start - _->dol - 1],
					_->dol + 1), _->delim));
}
