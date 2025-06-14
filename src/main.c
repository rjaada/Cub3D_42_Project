/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:34 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/14 18:03:23 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	close_window(void *param)
{
	(void)param;
	exit(0);
}

// MAKE A HOOKS FILE WITH ALL THE HOOKS AND FUNCTIONS FOR MOVEMENT, ETC.
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

// LESS LINES; USE ft_memset and make an init function
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	memset(&game, 0, sizeof(t_game)); // I feel like we're doing this twice
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
	game.map_height = 0;
	while (game.map && game.map[game.map_height])
		game.map_height++;
	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D - Movement Test!", true);
	if (!game.mlx)
	{
		printf("Error: MLX init failed\n");
		return (1);
	}
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
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
