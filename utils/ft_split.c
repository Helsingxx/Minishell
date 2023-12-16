/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:37:27 by eamrati           #+#    #+#             */
/*   Updated: 2023/12/16 15:37:38 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	spliit(char const *s, char **list, int listindex)
{
	int	a;
	int	save;

	a = 0;
	while (a < ft_strlen(s))
	{
		if (!ft_isspace(s[a]))
		{
			save = a;
			while (!ft_isspace(s[a]) && s[a] != '\x00')
				a++;
			list[listindex] = ft_calloc(a - save + 1, 1);
			ft_strlcpy(list[listindex], &s[save], a - save + 1);
			listindex++;
		}
		a++;
	}
	list[listindex] = 0;
	return (1);
}

char	**ft_split(char const *s) // isspace, char * in tokenizer!
{
	char	**list;
	int		listindex;

	listindex = 0;
	if (s == 0)
		return (0);
	list = ft_calloc (ft_strlen(s) + 1, sizeof(char *));
	if (list == 0)
		return (0);
	spliit(s, list, listindex);
	return (list);
}
