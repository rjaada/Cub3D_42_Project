/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:42 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/15 23:49:04 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	clear_minimap_bg(t_game *game)
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

static void	draw_minimap_cell(t_game *game, int map_x, int map_y,
		uint32_t color)
{
	int	i;
	int	j;
	int	draw_x;
	int	draw_y;

	i = 0;
	while (i < TILE_SIZE / 2)
	{
		j = 0;
		while (j < TILE_SIZE / 2)
		{
			draw_x = MAP_OFFSET_X + map_x * TILE_SIZE / 2 + i;
			draw_y = MAP_OFFSET_Y + map_y * TILE_SIZE / 2 + j;
			if (draw_x >= 0 && draw_x < (int)game->img->width && draw_y >= 0
				&& draw_y < (int)game->img->height)
				mlx_put_pixel(game->img, draw_x, draw_y, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_map(t_game *game, int map_width, int map_height)
{
	uint32_t	color;
	int			x;
	int			y;

	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			if (game->map[y][x] == '1')
				color = 0xFF444444;
			else
				color = 0xFFCCCCCC;
			draw_minimap_cell(game, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_player(t_game *game)
{
	int	i;
	int	j;
	int	px;
	int	py;

	px = MAP_OFFSET_X + (int)(game->player.x * TILE_SIZE / 2) - TILE_SIZE / 4;
	py = MAP_OFFSET_Y + (int)(game->player.y * TILE_SIZE / 2) - TILE_SIZE / 4;
	i = 0;
	while (i < TILE_SIZE / 3)
	{
		j = 0;
		while (j < TILE_SIZE / 3)
		{
			if (px + i >= 0 && px + i < (int)game->img->width && py + j >= 0
				&& py + j < (int)game->img->height)
				mlx_put_pixel(game->img, px + i, py + j, 0xFFFF0000);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	map_width;
	int	map_height;

	map_height = 0;
	while (game->map[map_height])
		map_height++;
	map_width = strlen(game->map[0]);
	if (!game->img)
	{
		game->img = mlx_new_image(game->mlx, map_width * TILE_SIZE + 2
				* MAP_OFFSET_X / 2, map_height * TILE_SIZE + 2 * MAP_OFFSET_Y
				/ 2);
		mlx_image_to_window(game->mlx, game->img, 0, 0);
	}
	clear_minimap_bg(game);
	draw_minimap_map(game, map_width, map_height);
	draw_minimap_player(game);
}
