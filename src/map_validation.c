/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:22:57 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/19 00:59:48 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_map_characters(t_game *game, int map_height)
{
	int	row;

	row = 0;
	while (row < map_height)
	{
		if (!game->map[row])
		{
			row++;
			continue ;
		}
		if (!validate_row_characters(game->map[row], row))
			return (0);
		row++;
	}
	return (1);
}

static int	perform_validation_checks(t_game *game, int map_height,
		int map_width)
{
	if (!validate_top_bottom_walls(game, map_height, map_width))
		return (0);
	if (!validate_left_right_walls(game, map_height))
		return (0);
	if (!validate_map_characters(game, map_height))
		return (0);
	return (1);
}

int	validate_map_walls(t_game *game)
{
	int	map_height;
	int	map_width;

	map_height = 0;
	map_width = 0;
	while (game->map[map_height])
		map_height++;
	if (map_height > 0)
		map_width = get_max_line_width(game);
	if (!perform_validation_checks(game, map_height, map_width))
		return (0);
	return (1);
}

int	parse_and_validate_cub_file(char *filename, t_game *game)
{
	if (!check_file_extension(filename))
		return (0);
	if (!parse_cub_file(filename, game))
		return (0);
	if (!find_player_position(game))
		return (0);
	if (!validate_map_walls(game))
		return (0);
	return (1);
}
