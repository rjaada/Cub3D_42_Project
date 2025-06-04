/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:59:43 by kmoundir          #+#    #+#             */
/*   Updated: 2024/10/04 23:21:41 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start = (char *) s1;
	end = (char *)s1 + (ft_strlen(s1) - 1);
	while (*start && ft_check_set(*start, set))
		start ++;
	while (end > start && ft_check_set(*end, set))
		end --;
	len = end - start + 1;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, start, len);
	result[len] = '\0';
	return (result);
}
