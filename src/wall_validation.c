/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:44:47 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/18 23:13:38 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_max_line_width(t_game *game)
{
	int	max_width;
	int	i;
	int	current_width;

	max_width = 0;
	i = 0;
	while (game->map[i])
	{
		current_width = ft_strlen(game->map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	validate_top_bottom_walls(t_game *game, int map_height, int map_width)
{
	int	start;
	int	end;

	(void)map_width;
	start = find_content_start(game->map[0]);
	end = find_content_end(game->map[0]);
	if (!check_horizontal_wall(game->map[0], start, end, "top"))
		return (0);
	start = find_content_start(game->map[map_height - 1]);
	end = find_content_end(game->map[map_height - 1]);
	if (!check_horizontal_wall(game->map[map_height - 1], start, end, "bottom"))
		return (0);
	return (1);
}

int	validate_left_right_walls(t_game *game, int map_height)
{
	int	row;
	int	start;
	int	end;

	row = 0;
	while (row < map_height)
	{
		if (ft_strlen(game->map[row]) > 0)
		{
			start = find_content_start(game->map[row]);
			end = find_content_end(game->map[row]);
			if (!check_wall_boundary(game->map[row], start, end, row))
				return (0);
		}
		row++;
	}
	return (1);
}
