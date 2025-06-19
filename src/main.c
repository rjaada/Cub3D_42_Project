/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:34 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/19 11:34:35 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	close_window(void *param)
{
	(void)param;
	exit(0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(0);
	(void)param;
}

int	init_mlx_and_start(t_game *game)
{
	game->map_height = 0;
	while (game->map && game->map[game->map_height])
		game->map_height++;
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D!", true);
	if (!game->mlx)
		return (printf("Error: MLX init failed\n"), 0);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		return (printf("Error: Failed to create main image\n"),
			mlx_terminate(game->mlx), 0);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_close_hook(game->mlx, close_window, game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_cursor_hook(game->mlx, cursor_hook, game);
	printf("SUCCESS! Use WASD to move, arrows to turn, ESC to quit.\n");
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (1);
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_game	*data;

	(void)ypos;
	data = (t_game *)param;
	mlx_set_mouse_pos(data->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	if (xpos > WIN_WIDTH / 2)
		data->player.angle += 1;
	else if (xpos < WIN_WIDTH / 2)
		data->player.angle -= 1;
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_seen_keys	seen;

	if (argc != 2)
		return (printf("Usage: %s <map.cub>\n", argv[0]), 1);
	memset(&game, 0, sizeof(t_game));
	game.seen = &seen;
	game.textures.north = NULL;
	game.textures.south = NULL;
	game.textures.west = NULL;
	game.textures.east = NULL;
	if (!parse_and_validate_cub_file(argv[1], &game))
		return (cleanup_game(&game), 1);
	if (!load_textures(&game))
		return (cleanup_game(&game), 1);
	if (!init_mlx_and_start(&game))
		return (cleanup_game(&game), 1);
	return (cleanup_game(&game), 0);
}
