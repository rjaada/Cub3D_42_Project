/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:32:59 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/07 16:15:10 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"

void	close_window(void *param)
{
	(void)param; // Suppress unused parameter warning
	exit(0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS) // ESC key - FIXED!
	{
		printf("ESC pressed - Exiting\n");
		exit(0);
	}
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // W - FIXED!
	{
		printf("Move forward - Player at (%.1f, %.1f)\n", game->player.x,
			game->player.y);
		game->player.y -= 0.1; // move up (in 2D for now)
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS) // S - FIXED!
	{
		printf("Move backward - Player at (%.1f, %.1f)\n", game->player.x,
			game->player.y);
		game->player.y += 0.1; // move down
	}
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS) // A - FIXED!
	{
		printf("Move left - Player at (%.1f, %.1f)\n", game->player.x,
			game->player.y);
		game->player.x -= 0.1; // move left
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS) // D - FIXED!
	{
		printf("Move right - Player at (%.1f, %.1f)\n", game->player.x,
			game->player.y);
		game->player.x += 0.1; // move right
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	// Left arrow - FIXED!
	{
		printf("Turn left - Angle: %.1f\n", game->player.angle);
		game->player.angle -= 0.1; // rotate left
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	// Right arrow - FIXED!
	{
		printf("Turn right - Angle: %.1f\n", game->player.angle);
		game->player.angle += 0.1; // rotate right
	}
	// REMOVED return (0) - MLX42 key_hook returns void!
}

void	print_parsed_data(t_game *game)
{
	printf("\n=== STORED DATA VERIFICATION ===\n");
	// Check textures
	printf("North texture: %s\n",
		game->textures.north ? game->textures.north : "NULL");
	printf("South texture: %s\n",
		game->textures.south ? game->textures.south : "NULL");
	printf("West texture: %s\n",
		game->textures.west ? game->textures.west : "NULL");
	printf("East texture: %s\n",
		game->textures.east ? game->textures.east : "NULL");
	// Check colors
	printf("Floor color: RGB(%d, %d, %d)\n", game->colors.floor_r,
		game->colors.floor_g, game->colors.floor_b);
	printf("Ceiling color: RGB(%d, %d, %d)\n", game->colors.ceiling_r,
		game->colors.ceiling_g, game->colors.ceiling_b);
	printf("=== END VERIFICATION ===\n\n");
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!parse_and_validate_cub_file(argv[1], &game))
	{
		cleanup_game(&game);
		return (1);
	}
	print_parsed_data(&game);
	// MLX42 initialization - no separate window creation needed!
	game.mlx = mlx_init(800, 600, "cub3D - Movement Test!", true);
	if (!game.mlx)
	{
		printf("Error: MLX init failed\n");
		return (1);
	}
	// Initialize player position
	game.player.x = 5.0;
	game.player.y = 5.0;
	game.player.angle = 0.0;
	// Set up event handling - MLX42 style!
	mlx_close_hook(game.mlx, close_window, &game); // Window close hook
	mlx_key_hook(game.mlx, key_hook, &game);       // Key hook
	printf("SUCCESS! Use WASD to move, arrows to turn, ESC to quit.\n");
	printf("Starting position: (%.1f, %.1f) angle: %.1f\n", game.player.x,
		game.player.y, game.player.angle);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
