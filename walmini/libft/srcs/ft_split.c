/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:11:08 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:11:09 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_next_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static int	get_strs(char const *s, char c)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = -1;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i - j != 1)
				count++;
			j = i;
		}
		i++;
	}
	if (i - j != 1)
		count++;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	count = get_strs(s, c);
	res = malloc((count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < ft_strlen((char *)s) && j < count)
	{
		while (!get_next_len(s + i, c))
			i++;
		res[j] = malloc((get_next_len(s + i, c) + 1) * sizeof(char));
		if (!res)
			return (NULL);
		ft_strlcpy(res[j++], s + i, get_next_len(s + i, c) + 1);
		i += get_next_len(s + i, c) + 1;
	}
	res[j] = NULL;
	return (res);
}
