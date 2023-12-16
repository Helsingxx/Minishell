/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:58:02 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/16 15:58:14 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*m_ft_strdup(const char *s1)
{
	int		a;
	char	*str;

	a = 0;
	str = malloc (ft_strlen(s1) + 1 + 1);
	if (str == 0)
		return (0);
	ft_bzero(str, ft_strlen(s1) + 1 + 1);
	while (a < ft_strlen(s1))
	{
		str[a] = s1[a];
		a++;
	}
	str[a] = 0;
	return (str);
}

char	*ft_strtok_c(char *str, char delim)
{
	static char	*last;
	static char	*last_character;

	last_character = last;
	if (str)
	{
		last = str;
		last_character = str;
	}
	if (last == NULL)
		return (NULL);
	last = ft_strchr(last, delim);
	if (last == NULL)
		return (last_character);
	else
	{
		*last = '\0';
		last++;
	}
	return (last_character);
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
