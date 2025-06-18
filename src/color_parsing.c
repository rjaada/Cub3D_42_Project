/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:02:49 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/19 00:58:36 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_floor_color(char *line, t_colors *colors)
{
	int	r;
	int	g;
	int	b;

	parse_rgb_color(line + 2, &r, &g, &b);
	if (!validate_color_range(r, g, b))
		return (0);
	colors->f_r = r;
	colors->f_g = g;
	colors->f_b = b;
	return (1);
}

static int	parse_ceiling_color(char *line, t_colors *colors)
{
	int	r;
	int	g;
	int	b;

	parse_rgb_color(line + 2, &r, &g, &b);
	if (!validate_color_range(r, g, b))
		return (0);
	colors->c_r = r;
	colors->c_g = g;
	colors->c_b = b;
	return (1);
}

static int	parse_colors(char *line, t_colors *colors)
{
	if (line[0] == 'F' && line[1] == ' ')
		return (parse_floor_color(line, colors));
	if (line[0] == 'C' && line[1] == ' ')
		return (parse_ceiling_color(line, colors));
	return (-1);
}

int	parse_texture_line(char *line, t_textures *textures, t_colors *colors,
		t_seen_keys *seen)
{
	int	result;

	if (!is_valid_config_line(line) || !check_duplicate_key(line, seen))
		return (0);
	result = parse_texture_no_so(line, textures);
	if (result != -1)
		return (result);
	result = parse_texture_we_ea(line, textures);
	if (result != -1)
		return (result);
	result = parse_colors(line, colors);
	if (result != -1)
		return (result);
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
