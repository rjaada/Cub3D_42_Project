/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:51 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/14 17:46:27 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Sets up the game structure, initializes MLX and player position
int	init_game(t_game *game)
{
	game->mlx = mlx_init(800, 600, "cub3D - Movement Test!", true);
	if (!game->mlx)
	{
		printf("Error: MLX init failed\n");
		return (0);
	}
	game->img = NULL;
	game->player.x = 5.0;
	game->player.y = 5.0;
	game->player.angle = 0.0;
	return (1);
}

// memory cleanup function
void	cleanup_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->textures.north)
		free(game->textures.north);
	if (game->textures.south)
		free(game->textures.south);
	if (game->textures.west)
		free(game->textures.west);
	if (game->textures.east)
		free(game->textures.east);
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
}
