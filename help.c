/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:17:51 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/16 16:17:54 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	int		a;
	char	*str;

	a = 0;
	str = ft_calloc (ft_strlen(s1) + 1, 1);
	if (str == 0)
		return (0);
	while (a < ft_strlen(s1))
	{
		str[a] = s1[a];
		a++;
	}
	str[a] = 0;
	return (str);
}

int	exit_status(int value)
{
	static int	status;

	if (value > 255)
		return (status);
	else
		status = value;
	return (1);
}

int	count_cmd(t_node *head)
{
	int	count;

	count = 1;
	while (head)
	{
		if (head->type == OPERATOR)
			count++;
		head = head->next;
	}
	return (count);
}
