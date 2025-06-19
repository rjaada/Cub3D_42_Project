/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:42 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/19 14:12:21 by cschnath         ###   ########.fr       */
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
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE / 2)
	{
		j = 0;
		while (j < TILE_SIZE / 2)
		{
			draw_x = local_x * TILE_SIZE / 2 + i;
			draw_y = local_y * TILE_SIZE / 2 + j;
			if (draw_x >= 0 && draw_x < MINIMAP_WIDTH && draw_y >= 0
				&& draw_y < MINIMAP_HEIGHT)
				mlx_put_pixel(game->minimap, draw_x, draw_y, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_map(t_game *game, int y)
{
	int			i;
	int			j;
	uint32_t	color;
	int			x;

	while (y < (MINIMAP_HEIGHT / (TILE_SIZE / 2)))
	{
		x = 0;
		while (x < (MINIMAP_WIDTH / (TILE_SIZE / 2)))
		{
			i = ((int)game->player.x) - MINIMAP_WIDTH / (TILE_SIZE / 2) / 2 + x;
			j = ((int)game->player.y) - MINIMAP_HEIGHT / (TILE_SIZE / 2) / 2
				+ y;
			if (j >= 0 && j < game->map_height && i >= 0 && i < game->map_width)
			{
				if (game->map[j][i] == '1')
					color = 0xFF4444FF;
				else
					color = 0xFFCCCCFF;
				draw_minimap_cell(game, x, y, color);
			}
			x++;
		}
		y++;
	}
}

static void	draw_minimap_player(t_game *game)
{
	int	px;
	int	py;
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE / 3)
	{
		j = 0;
		while (j < TILE_SIZE / 3)
		{
			px = (MINIMAP_WIDTH / 2 - TILE_SIZE / 6) + i;
			py = (MINIMAP_HEIGHT / 2 - TILE_SIZE / 6) + j;
			if (px >= 0 && px < MINIMAP_WIDTH && py >= 0 && py < MINIMAP_HEIGHT)
				mlx_put_pixel(game->minimap, px, py, 0xFFFF00FF);
			j++;
		}
		i++;
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
	draw_minimap_map(game, 0);
	draw_minimap_player(game);
}
