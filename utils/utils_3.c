/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:41:26 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/16 17:46:35 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	det_incomplete(char *line, int *i, int *complete)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (!line[*i])
			*complete = 0;
	}
	else if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		if (!line[*i])
			*complete = 0;
	}
}

int	checker_quotes(char *line)
{
	int	i;
	int	complete;

	i = 0;
	complete = 1;
	while (line[i])
	{
		det_incomplete(line, &i, &complete);
		if (line[i])
			i++;
	}
	if (!complete)
		return (printf("Quoting error!\n"), 0);
	return (1);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*res;
	int		i;

	i = 0;
	if (start < 0)
		start = 0;
	if (len < 0)
		len = 0;
	if (start > ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	res = (char *)ft_calloc(sizeof(char), len + 1);
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	ft_isalnum(char c)
{
	return (('0' <= c && c <= '9') || ('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z'));
}
