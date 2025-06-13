/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:34 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/13 19:50:36 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void	close_window(void *param)
{
	(void)param;
	exit(0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game || !game->map)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(0);
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_forward_backward(game, 1);
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_forward_backward(game, -1);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left_right(game, -1);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_left_right(game, 1);
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		rotate_player(game, -ROT_SPEED * 180.0 / M_PI);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		rotate_player(game, ROT_SPEED * 180.0 / M_PI);
}

void	print_parsed_data(t_game *game)
{
	printf("\n=== STORED DATA VERIFICATION ===\n");
	printf("North texture: %s\n",
		game->textures.north ? game->textures.north : "NULL");
	printf("South texture: %s\n",
		game->textures.south ? game->textures.south : "NULL");
	printf("West texture: %s\n",
		game->textures.west ? game->textures.west : "NULL");
	printf("East texture: %s\n",
		game->textures.east ? game->textures.east : "NULL");
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
	// Initialize game structure
	memset(&game, 0, sizeof(t_game));
	game.textures.north = NULL;
	game.textures.south = NULL;
	game.textures.west = NULL;
	game.textures.east = NULL;
	if (!parse_and_validate_cub_file(argv[1], &game))
	{
		cleanup_game(&game);
		return (1);
	}
	print_parsed_data(&game);
	// Set map_height for later use
	game.map_height = 0;
	while (game.map && game.map[game.map_height])
		game.map_height++;
	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D - Movement Test!", true);
	if (!game.mlx)
	{
		printf("Error: MLX init failed\n");
		return (1);
	}
	// Initialize image
	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.img)
	{
		printf("Error: Failed to create main image\n");
		mlx_terminate(game.mlx);
		return (1);
	}
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_close_hook(game.mlx, close_window, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	printf("SUCCESS! Use WASD to move, arrows to turn, ESC to quit.\n");
	printf("Starting position: (%.1f, %.1f) angle: %.1f\n", game.player.x,
		game.player.y, game.player.angle);
	mlx_loop_hook(game.mlx, game_loop, &game); // Set the game loop function
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
