/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:45:37 by kmoundir          #+#    #+#             */
/*   Updated: 2024/10/04 23:05:18 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurence;	

	if (c >= 256)
		c = c % 256;
	last_occurence = NULL;
	while (*s)
	{
		if (*s == c)
			last_occurence = (char *) s;
		s ++;
	}
	if (c == 0)
		return ((char *)s);
	return (last_occurence);
}
