/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:02:58 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:04:59 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strdup(char	*remainder)
{
	int		i;
	char	*buff;

	if (!remainder)
		return (NULL);
	i = 0;
	buff = (char *)malloc(sizeof(char) * (gnl_strlen(remainder) + 1));
	if (!buff)
		return (NULL);
	while (remainder[i])
	{
		buff[i] = remainder[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

char	*gnl_strchr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *old, char *new)
{
	int		i;
	char	*updated;

	updated = (char *)malloc(sizeof(char) * (gnl_strlen(old) + \
	gnl_strlen(new) + 1));
	if (!updated)
		return (NULL);
	i = 0;
	if (old)
	{
		while (*old)
			updated[i++] = *old++;
	}
	while (*new)
		updated[i++] = *new++;
	updated[i] = '\0';
	return (updated);
}
