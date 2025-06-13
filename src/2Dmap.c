/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:42 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/13 20:30:33 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_minimap(t_game *game)
{
	uint32_t	color;
	int			draw_x;
	int			draw_y;
	int			px;
	int			py;
	uint32_t	y_img;
	uint32_t	x_img;

	int x, y, i, j;
	int map_width, map_height;
	map_height = 0;
	while (game->map[map_height])
		map_height++;
	map_width = strlen(game->map[0]);
	// Create minimap image only once
	if (!game->img)
	{
		game->img = mlx_new_image(game->mlx, map_width * TILE_SIZE + 2
				* MAP_OFFSET_X, map_height * TILE_SIZE + 2 * MAP_OFFSET_Y);
		mlx_image_to_window(game->mlx, game->img, 0, 0);
	}
	// Clear the image (set all pixels to background color)
	y_img = 0;
	while (y_img < game->img->height / 2)
	{
		x_img = 0;
		while (x_img < game->img->width)
		{
			mlx_put_pixel(game->img, x_img, y_img,
				get_ceiling_color(&game->colors)); // Ceiling color
			x_img++;
		}
		y_img++;
	}
	y_img = game->img->height / 2;
	while (y_img < game->img->height)
	{
		x_img = 0;
		while (x_img < game->img->width)
		{
			mlx_put_pixel(game->img, x_img, y_img,
				get_floor_color(&game->colors)); // Black floor
			x_img++;
		}
		y_img++;
	}
	// Draw map cells (loop over map, not image!)
	for (y = 0; y < map_height; y++)
	{
		for (x = 0; x < map_width; x++)
		{
			if (game->map[y][x] == '1')
				color = 0xFF444444; // Wall
			else
				color = 0xFFCCCCCC; // Floor
			for (i = 0; i < TILE_SIZE; i++)
			{
				for (j = 0; j < TILE_SIZE; j++)
				{
					draw_x = MAP_OFFSET_X + x * TILE_SIZE + i;
					draw_y = MAP_OFFSET_Y + y * TILE_SIZE + j;
					if (draw_x >= 0 && draw_x < (int)game->img->width
						&& draw_y >= 0 && draw_y < (int)game->img->height)
						mlx_put_pixel(game->img, draw_x, draw_y, color);
				}
			}
		}
	}
	// Draw player as a red square
	px = MAP_OFFSET_X + (int)(game->player.x * TILE_SIZE) - TILE_SIZE / 4;
	py = MAP_OFFSET_Y + (int)(game->player.y * TILE_SIZE) - TILE_SIZE / 4;
	for (i = 0; i < TILE_SIZE / 2; i++)
	{
		for (j = 0; j < TILE_SIZE / 2; j++)
		{
			draw_x = px + i;
			draw_y = py + j;
			if (draw_x >= 0 && draw_x < (int)game->img->width && draw_y >= 0
				&& draw_y < (int)game->img->height)
				mlx_put_pixel(game->img, draw_x, draw_y, 0xFFFF0000);
		}
	}
}
