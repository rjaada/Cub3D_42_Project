/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:44:47 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/16 00:44:55 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_top_wall(t_game *game, int map_width)
{
	int	col;

	col = 0;
	while (col < map_width)
	{
		if (game->map[0][col] != '1')
		{
			printf("Error\nMap not closed - top wall missing at position %d\n",
				col);
			return (0);
		}
		col++;
	}
	return (1);
}

static int	check_bottom_wall(t_game *game, int map_height, int map_width)
{
	int	col;

	col = 0;
	while (col < map_width)
	{
		if (game->map[map_height - 1][col] != '1')
		{
			printf("Error\nMap not closed - bottom wall missing at pos %d\n",
				col);
			return (0);
		}
		col++;
	}
	return (1);
}

int	validate_top_bottom_walls(t_game *game, int map_height, int map_width)
{
	if (!check_top_wall(game, map_width))
		return (0);
	if (!check_bottom_wall(game, map_height, map_width))
		return (0);
	return (1);
}

int	validate_left_right_walls(t_game *game, int map_height)
{
	int	row;
	int	line_len;

	row = 0;
	while (row < map_height)
	{
		if (game->map[row][0] != '1')
		{
			printf("Error\nMap not closed - left wall missing at row %d\n",
				row);
			return (0);
		}
		line_len = ft_strlen(game->map[row]);
		if (line_len > 0 && game->map[row][line_len - 1] != '1')
		{
			printf("Error\nMap not closed - right wall missing at row %d\n",
				row);
			return (0);
		}
		row++;
	}
	return (1);
}
