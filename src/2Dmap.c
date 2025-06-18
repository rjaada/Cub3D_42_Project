/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:42 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/18 23:37:39 by rjaada           ###   ########.fr       */
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
			if (draw_x >= 0 && draw_x < (int)game->minimap->width && draw_y >= 0
				&& draw_y < (int)game->minimap->height)
				mlx_put_pixel(game->minimap, draw_x, draw_y, color);
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
				color = 0xFF4444FF;
			else
				color = 0xFFCCCCFF;
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
			if (px + i >= 0 && px + i < (int)game->minimap->width && py + j >= 0
				&& py + j < (int)game->minimap->height)
				mlx_put_pixel(game->minimap, px + i, py + j, 0xFFFF00FF);
			j++;
		}
		i++;
	}
}

//clear_minimap_bg(game); i move it above for norminette
void	draw_minimap(t_game *game)
{
	game->map_width = strlen(game->map[0]);
	if (!game->minimap)
	{
		game->minimap = mlx_new_image(game->mlx, game->map_width * TILE_SIZE + 2
				* MAP_OFFSET_X / 2, game->map_height * TILE_SIZE + 2
				* MAP_OFFSET_Y / 2);
		mlx_image_to_window(game->mlx, game->minimap, 0, 0);
	}
	draw_minimap_map(game, game->map_width, game->map_height);
	draw_minimap_player(game);
}
