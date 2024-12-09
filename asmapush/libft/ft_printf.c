/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:27:56 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:27:58 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_ch(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putnum(int n, int *len)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) = (*len) + 11;
		return ;
	}
	if (n < 0)
	{
		ft_ch('-', len);
		ft_putnum(n * -1, len);
	}
	else
	{
		if (n > 9)
			ft_putnum(n / 10, len);
		ft_ch(n % 10 + 48, len);
	}
}

static void	ft_printf_checker(char c, va_list *args, int *len)
{
	if (c == 'd')
		ft_putnum(va_arg(*args, int), len);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		length;

	i = 0;
	length = 0;
	va_start(args, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			ft_printf_checker(string[i], &args, &length);
			i++;
		}
	}
	va_end(args);
	return (length);
}
