/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:51 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/19 00:59:05 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	load_textures(t_game *game)
{
	game->north_texture = mlx_load_png(game->textures.north);
	game->south_texture = mlx_load_png(game->textures.south);
	game->east_texture = mlx_load_png(game->textures.east);
	game->west_texture = mlx_load_png(game->textures.west);
	if (!game->north_texture || !game->south_texture || !game->east_texture
		|| !game->west_texture)
	{
		printf("Error: Failed to load textures\n");
		return (0);
	}
	return (1);
}
