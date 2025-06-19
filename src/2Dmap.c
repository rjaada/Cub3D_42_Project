/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:42 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/19 12:35:09 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clear_minimap_bg(t_game *game)
{
	uint32_t	y_img;
	uint32_t	x_img;

	y_img = 0;
	while (y_img < game->img->height / 2)
	{
		x_img = 0;
		while (x_img < game->img->width)
			mlx_put_pixel(game->img, x_img++, y_img,
				get_ceiling_color(&game->colors));
		y_img++;
	}
	y_img = game->img->height / 2;
	while (y_img < game->img->height)
	{
		x_img = 0;
		while (x_img < game->img->width)
			mlx_put_pixel(game->img, x_img++, y_img,
				get_floor_color(&game->colors));
		y_img++;
	}
}

static void	draw_minimap_cell(t_game *game, int local_x, int local_y,
		uint32_t color)
{
	int	draw_x;
	int	draw_y;

	for (int i = 0; i < TILE_SIZE / 2; i++)
	{
		for (int j = 0; j < TILE_SIZE / 2; j++)
		{
			draw_x = local_x * TILE_SIZE / 2 + i;
			draw_y = local_y * TILE_SIZE / 2 + j;
			if (draw_x >= 0 && draw_x < MINIMAP_WIDTH && draw_y >= 0
				&& draw_y < MINIMAP_HEIGHT)
				mlx_put_pixel(game->minimap, draw_x, draw_y, color);
		}
	}
}

static void	draw_minimap_map(t_game *game)
{
	int			view_tiles_x;
	int			view_tiles_y;
	int			player_tile_x;
	int			player_tile_y;
	int			start_x;
	int			start_y;
	int			map_x;
	int			map_y;
	uint32_t	color;

	view_tiles_x = MINIMAP_WIDTH / (TILE_SIZE / 2);
	view_tiles_y = MINIMAP_HEIGHT / (TILE_SIZE / 2);
	player_tile_x = (int)game->player.x;
	player_tile_y = (int)game->player.y;
	start_x = player_tile_x - view_tiles_x / 2;
	start_y = player_tile_y - view_tiles_y / 2;
	for (int y = 0; y < view_tiles_y; y++)
	{
		for (int x = 0; x < view_tiles_x; x++)
		{
			map_x = start_x + x;
			map_y = start_y + y;
			if (map_y >= 0 && map_y < game->map_height && map_x >= 0
				&& map_x < game->map_width)
			{
				color = (game->map[map_y][map_x] == '1') ? 0xFF4444FF : 0xFFCCCCFF;
				draw_minimap_cell(game, x, y, color);
			}
		}
	}
}

static void	draw_minimap_player(t_game *game)
{
	int	center_x;
	int	center_y;
	int	px;
	int	py;

	center_x = MINIMAP_WIDTH / 2 - TILE_SIZE / 6;
	center_y = MINIMAP_HEIGHT / 2 - TILE_SIZE / 6;
	for (int i = 0; i < TILE_SIZE / 3; i++)
	{
		for (int j = 0; j < TILE_SIZE / 3; j++)
		{
			px = center_x + i;
			py = center_y + j;
			if (px >= 0 && px < MINIMAP_WIDTH && py >= 0 && py < MINIMAP_HEIGHT)
				mlx_put_pixel(game->minimap, px, py, 0xFFFF00FF);
		}
	}
}

void	draw_minimap(t_game *game)
{
	game->map_width = strlen(game->map[0]);
	if (!game->minimap)
	{
		game->minimap = mlx_new_image(game->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
		mlx_image_to_window(game->mlx, game->minimap, MAP_OFFSET_X,
			MAP_OFFSET_Y);
	}
	draw_minimap_map(game);
	draw_minimap_player(game);
}
