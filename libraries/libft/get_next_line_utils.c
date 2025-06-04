/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:04:47 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/17 12:29:41 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*join_s1_s2;
	size_t	lens1;
	size_t	lens2;

	if (!s1)
	{
		s1 = malloc(sizeof(char) + 1);
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	join_s1_s2 = (char *)malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!join_s1_s2)
		return (free(s1), s1 = NULL, NULL);
	ft_strlcpy(join_s1_s2, s1, lens1 + 1);
	ft_strlcat(join_s1_s2, s2, lens1 + lens2 + 1);
	free(s1);
	return (join_s1_s2);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	if (c >= 256)
		c = c % 256;
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	str_len;

	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start + len > str_len)
		len = str_len - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

size_t	ft_strlcat_gnl(char *dst, char *src, size_t size)
{
	size_t	len;
	size_t	len_src;
	size_t	len_dest;
	size_t	i;

	len_src = ft_strlen(src);
	len_dest = ft_strlen(dst);
	len = len_src + len_dest;
	if (size == 0)
		return (len_src);
	if (size <= len_dest)
		return (size + len_src);
	i = -1;
	while (src[++i] && (len_dest + i) < size - 1)
	{
		dst[len_dest + i] = src[i];
	}
	dst[len_dest + i] = '\0';
	return (len);
}

size_t	ft_strlcpy_gnl(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = -1;
	if (!size)
		return (len);
	while (src[++i] && src[i] != '\n' && i < size && src[i] != '\0')
		dst[i] = src[i];
	dst[i] = '\0';
	return (len);
}
