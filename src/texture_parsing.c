/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:43:55 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/16 01:14:17 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	parse_texture_paths(char *line, t_textures *textures)
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
}

static void	parse_colors(char *line, t_colors *colors)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		printf("Found Floor color: %s\n", line + 2);
		parse_rgb_color(line + 2, &colors->f_r, &colors->f_g, &colors->f_b);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		printf("Found Ceiling color: %s\n", line + 2);
		parse_rgb_color(line + 2, &colors->c_r, &colors->c_g, &colors->c_b);
	}
}

int	parse_texture_line(char *line, t_textures *textures, t_colors *colors)
{
	parse_texture_paths(line, textures);
	parse_colors(line, colors);
	return (1);
}

int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || strcmp(filename + len - 4, ".cub") != 0)
		return (printf("Error\nFile must have .cub extension\n"), 0);
	return (1);
}

void	clear_image(mlx_image_t *img, int ceiling_color, int floor_color)
{
	uint32_t	color;
	int			y;
	int			x;

	y = 0;
	while (y < (int)img->height)
	{
		if (y < (int)img->height / 2)
			color = ceiling_color;
		else
			color = floor_color;
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
