/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:22 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/13 20:12:09 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

#define FOV 60.0
#define NUM_RAYS WIN_WIDTH

void	draw_vertical_line(mlx_image_t *img, int x, int start, int end,
		uint32_t color)
{
	int	y;

	y = start;
	while (y < end)
	{
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
			mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void	raycast_and_render(t_game *game, mlx_image_t *img)
{
	double	ray_angle;
	double	distance;
	int		wall_height;
	int		screen_height;
	double	ray_rad;
	double	ray_dir_x;
	double	ray_dir_y;
	int		test_x;
	int		test_y;
	int		wall_start;
	int		wall_end;

	double ray_x, ray_y;
	screen_height = img->height;
	for (int ray = 0; ray < NUM_RAYS; ray++)
	{
		ray_angle = (game->player.angle - (FOV / 2.0)) + ((double)ray
				/ NUM_RAYS) * FOV;
		ray_rad = ray_angle * M_PI / 180.0;
		ray_dir_x = cos(ray_rad);
		ray_dir_y = sin(ray_rad);
		ray_x = game->player.x;
		ray_y = game->player.y;
		while (1)
		{
			test_x = (int)ray_x;
			test_y = (int)ray_y;
			if (test_x < 0 || test_x >= (int)strlen(game->map[0]) || test_y < 0
				|| test_y >= (int)game->map_height)
				break ;
			if (game->map[test_y][test_x] == '1')
				break ;
			ray_x += ray_dir_x * 0.01;
			ray_y += ray_dir_y * 0.01;
		}
		distance = sqrt((ray_x - game->player.x) * (ray_x - game->player.x)
				+ (ray_y - game->player.y) * (ray_y - game->player.y));
		wall_height = (int)(screen_height / (distance + 0.0001));
		wall_start = (screen_height / 2) - (wall_height / 2);
		wall_end = wall_start + wall_height;
		draw_vertical_line(img, ray, wall_start, wall_end, 0xFF888888);
		// Gray wall
	}
}

void	clear_image(mlx_image_t *img, int ceiling_color, int floor_color)
{
	uint32_t	color;

	for (int y = 0; y < (int)img->height; y++)
	{
		color = (y < (int)img->height / 2) ? ceiling_color : floor_color;
		for (int x = 0; x < (int)img->width; x++)
			mlx_put_pixel(img, x, y, color);
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clear_image(game->img, get_ceiling_color(&game->colors),
		get_floor_color(&game->colors));
	draw_minimap(game);
	raycast_and_render(game, game->img);
}
