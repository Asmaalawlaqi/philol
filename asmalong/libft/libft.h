/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:19:13 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/22 10:19:15 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <ctype.h>

char	*ft_strrchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *str, char c);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);

#endif
