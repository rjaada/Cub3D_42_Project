/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:51 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/16 02:21:21 by rjaada           ###   ########.fr       */
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
	printf("✅ All textures loaded successfully!\n");
	return (1);
}

void	print_parsed_data(t_game *game)
{
	printf("\n=== STORED DATA VERIFICATION ===\n");
	if (game->textures.north)
		printf("North texture: %s\n", game->textures.north);
	else
		printf("North texture: NULL\n");
	if (game->textures.south)
		printf("South texture: %s\n", game->textures.south);
	else
		printf("South texture: NULL\n");
	if (game->textures.west)
		printf("West texture: %s\n", game->textures.west);
	else
		printf("West texture: NULL\n");
	if (game->textures.east)
		printf("East texture: %s\n", game->textures.east);
	else
		printf("East texture: NULL\n");
	printf("Floor color: RGB(%d, %d, %d)\n", game->colors.f_r, game->colors.f_g,
		game->colors.f_b);
	printf("Ceiling color: RGB(%d, %d, %d)\n", game->colors.c_r,
		game->colors.c_g, game->colors.c_b);
	printf("=== END VERIFICATION ===\n\n");
}
