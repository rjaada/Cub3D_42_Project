/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:43:55 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/19 01:00:16 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_texture_no_so(char *line, t_textures *textures)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		textures->north = malloc(ft_strlen(line + 3) + 1);
		if (!textures->north)
			return (0);
		strcpy(textures->north, line + 3);
		return (1);
	}
	if (line[0] == 'S' && line[1] == 'O')
	{
		textures->south = malloc(ft_strlen(line + 3) + 1);
		if (!textures->south)
			return (0);
		strcpy(textures->south, line + 3);
		return (1);
	}
	return (-1);
}

int	parse_texture_we_ea(char *line, t_textures *textures)
{
	if (line[0] == 'W' && line[1] == 'E')
	{
		textures->west = malloc(ft_strlen(line + 3) + 1);
		if (!textures->west)
			return (0);
		strcpy(textures->west, line + 3);
		return (1);
	}
	if (line[0] == 'E' && line[1] == 'A')
	{
		textures->east = malloc(ft_strlen(line + 3) + 1);
		if (!textures->east)
			return (0);
		strcpy(textures->east, line + 3);
		return (1);
	}
	return (-1);
}
