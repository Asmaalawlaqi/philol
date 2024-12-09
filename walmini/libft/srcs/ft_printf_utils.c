/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:10:50 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:10:51 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_chars(char c, int rep)
{
	int	len;

	len = 0;
	while (rep > 0)
	{
		ft_putchar_fd(c, 1);
		len++;
		rep--;
	}
	return (len);
}
