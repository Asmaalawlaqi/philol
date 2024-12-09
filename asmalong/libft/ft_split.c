/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:20:42 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/29 10:42:17 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_pull_the_word(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	ft_counting_words(const char *s, char c)
{
	int	num;

	num = 0;
	while (*s)
	{
		if (*s && *s == c)
			s++;
		else
		{
			num++;
			while (*s && *s != c)
				s++;
		}
	}
	return (num);
}

char	**ft_split(const char *s, char c)
{
	int		number_of_words;
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	number_of_words = ft_counting_words(s, c);
	result = (char **)malloc(sizeof(char *) * (number_of_words + 1));
	if (!result)
		return (NULL);
	while (number_of_words--)
	{
		while (*s && *s == c)
			s++;
		result[i] = ft_pull_the_word(s, c);
		while (*s && *s != c)
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}
