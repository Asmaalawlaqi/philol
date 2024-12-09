/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:21:29 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:21:31 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_conversions(va_list ar, char ch)
{
	int	len;

	len = 0;
	if (ch == 'c')
		len += ft_putchar(va_arg(ar, int));
	else if (ch == 's')
		len += ft_putstr(va_arg(ar, char *));
	else if (ch == 'd' || ch == 'i')
		len += ft_putnbr(va_arg(ar, int));
	else if (ch == 'u')
		len += ft_putuint(va_arg(ar, unsigned int));
	else if (ch == 'x' || ch == 'X')
		len += ft_puthex(va_arg(ar, unsigned int), ch);
	else if (ch == 'p')
		len += ft_putpointer(va_arg(ar, unsigned long));
	else
		len += ft_putchar(ch);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	ar;

	len = 0;
	va_start(ar, str);
	while (*str)
	{
		if (*str == '%')
			len += ft_conversions(ar, *++str);
		else
			len += ft_putchar(*str);
		if (*str)
			str++;
	}
	va_end(ar);
	return (len);
}
