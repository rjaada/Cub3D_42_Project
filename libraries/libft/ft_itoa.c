/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:20:04 by kmoundir          #+#    #+#             */
/*   Updated: 2024/10/04 23:09:16 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_int(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	str_implement(char *nbr, long n, int len, int is_negative)
{
	nbr[len] = '\0';
	len--;
	while (len >= is_negative)
	{
		nbr[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	if (is_negative)
		nbr[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*nbr;
	long	long_n;
	int		len;
	int		is_negative;

	long_n = (long)n;
	is_negative = (long_n < 0);
	if (is_negative)
		long_n *= -1;
	len = len_int(long_n) + is_negative;
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	str_implement(nbr, long_n, len, is_negative);
	return (nbr);
}
