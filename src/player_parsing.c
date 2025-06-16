/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:44:23 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/16 00:44:30 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_player_angle(t_game *game, char direction)
{
	if (direction == 'N')
		game->player.angle = 270.0;
	else if (direction == 'S')
		game->player.angle = 90.0;
	else if (direction == 'E')
		game->player.angle = 0.0;
	else if (direction == 'W')
		game->player.angle = 180.0;
}

static int	process_player_cell(t_game *game, int row, int col)
{
	char	direction;

	direction = game->map[row][col];
	game->player.x = col + 0.5;
	game->player.y = row + 0.5;
	set_player_angle(game, direction);
	printf("Player found at map[%d][%d] = '%c'\n", row, col, direction);
	printf("Player coordinates: (%.1f, %.1f) angle: %.1f\n", game->player.x,
		game->player.y, game->player.angle);
	game->map[row][col] = '0';
	return (1);
}

int	find_player_position(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	printf("\n=== FINDING PLAYER POSITION ===\n");
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'N' || game->map[row][col] == 'S'
				|| game->map[row][col] == 'E' || game->map[row][col] == 'W')
			{
				process_player_cell(game, row, col);
				printf("=== PLAYER POSITION SET ===\n");
				return (1);
			}
			col++;
		}
		row++;
	}
	printf("Error\nNo player position found in map\n");
	return (0);
}
