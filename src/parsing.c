/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:54 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/06 06:16:01 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../libraries/libft/libft.h"
#include "../includes/cub3d.h"

int	parse_texture_line(char *line, t_textures *textures, t_colors *colors)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		printf("Found North texture: %s\n", line + 3);
		textures->north = malloc(ft_strlen(line + 3) + 1);
		strcpy(textures->north, line + 3);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		printf("Found South texture: %s\n", line + 3);
		textures->south = malloc(ft_strlen(line + 3) + 1);
		strcpy(textures->south, line + 3);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		printf("Found West texture: %s\n", line + 3);
		textures->west = malloc(ft_strlen(line + 3) + 1);
		strcpy(textures->west, line + 3);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		printf("Found East texture: %s\n", line + 3);
		textures->east = malloc(ft_strlen(line + 3) + 1);
		strcpy(textures->east, line + 3);
	}
	else if (line[0] == 'F' && line[1] == ' ')
	{
		printf("Found Floor color: %s\n", line + 2);
		parse_rgb_color(line + 2, &colors->floor_r, &colors->floor_g,
			&colors->floor_b);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		printf("Found Ceiling color: %s\n", line + 2);
		parse_rgb_color(line + 2, &colors->ceiling_r, &colors->ceiling_g,
			&colors->ceiling_b);
	}
	return (1);
}

int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	buffer[1000];
	int		bytes_read;
	int		i;
	int		line_start;

	i = 0;
	line_start = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (0);
	}
	bytes_read = read(fd, buffer, 999);
	buffer[bytes_read] = '\0';
	close(fd);
	printf("=== FILE CONTENT ===\n");
	printf("%s", buffer);
	printf("=== END FILE ===\n");
	printf("\n=== PARSING ===\n");
	while (i < bytes_read)
	{
		if (buffer[i] == '\n' || i == bytes_read - 1)
		{
			buffer[i] = '\0'; // end the line
			parse_texture_line(&buffer[line_start], &game->textures,
				&game->colors);
			line_start = i + 1;
		}
		i++;
	}
	return (1);
}
