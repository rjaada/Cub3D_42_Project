/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:29:23 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/17 12:29:34 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_byte;

	read_byte = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(line), line = NULL, NULL);
	buffer[0] = '\0';
	while (!ft_strchr_gnl(line, '\n') && read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == 0)
			break ;
		if (read_byte > 0)
		{
			buffer[read_byte] = '\0';
			line = ft_strjoin_gnl(line, buffer);
		}
	}
	free(buffer);
	buffer = NULL;
	if (read_byte == -1)
		return (free(line), line = NULL, NULL);
	return (line);
}

char	*ft_get_new_line(char *str)
{
	char	*new_line;
	char	*ptr;
	int		len;

	ptr = ft_strchr_gnl(str, '\n');
	len = ptr - str + 1;
	new_line = ft_substr_gnl(str, 0, len);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*ft_get_rest_line(char *str)
{
	char	*rest_line;
	char	*ptr;
	int		len;

	ptr = ft_strchr_gnl(str, '\n');
	if (!ptr)
	{
		rest_line = NULL;
		return (free(str), str = NULL, NULL);
	}
	len = ptr - str + 1;
	if (!str[len])
		return (free(str), str = NULL, NULL);
	rest_line = ft_substr_gnl(str, len, ft_strlen(str) - len);
	free(str);
	str = NULL;
	if (!rest_line)
		return (NULL);
	return (rest_line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0)
		return (NULL);
	rest = ft_get_line(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_get_new_line(rest);
	if (!line)
		return (free(rest), rest = NULL, NULL);
	rest = ft_get_rest_line(rest);
	return (line);
}

char	**array_map(int fd)
{
	char	**map;
	int		i;
	char	*line;

	i = 0;
	map = (char **)malloc(1000 * sizeof(char *));
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i] = (char *)malloc(1000 * sizeof(char));
		if (!map[i])
		{
			while (i >= 0)
				free(map[i--]);
			return (free(map), NULL);
		}
		ft_strlcpy_gnl(map[i], line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	return (map);
}
/*
#include <stdio.h>

int	main(void)
{
	int	file;

	int i=0;
	file = open("mapa/test.ber", O_RDONLY);
	if (file < 0)
	{
		perror("Error opening file");
		return (1);
	}
	char **map=array_map(file);
	while(map[i])
	{
		printf("%s\n",map[i]);
		free(map[i]);
		i++;
	}
	free(map);
	close(file);
	return (0);
}
*/
/*
#include <stdio.h>

int	main(void)
{

	int file = open("../maps_valid/ok.ber", O_RDONLY);
	if (file < 0)
	{
		perror("Error opening file");
		return (1);
	}
	char *line;
	while ((line = get_next_line(file)) != NULL)
	{


		printf("%s%ld\n", line,ft_strlen(line));
		free(line);
	}
	close(file);
	return (0);
}*/