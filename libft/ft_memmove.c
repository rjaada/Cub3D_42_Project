/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:17:50 by kmoundir          #+#    #+#             */
/*   Updated: 2024/10/04 23:03:27 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_s;
	unsigned const char	*src_s;

	dest_s = (unsigned char *)dest;
	src_s = (unsigned char *)src;
	if (dest == src || n == 0)
		return (dest);
	if (dest_s < src_s)
		while (n --)
			(*dest_s ++) = (*src_s ++);
	else
	{
		dest_s += n - 1;
		src_s += n - 1;
		while (n --)
			(*dest_s --) = (*src_s --);
	}
	return (dest);
}
