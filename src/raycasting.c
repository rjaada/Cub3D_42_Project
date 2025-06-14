/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:22 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/14 17:41:11 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_vertical_line(mlx_image_t *img, int x, int start, int end)
{
	int	y;

	y = start;
	while (y < end)
	{
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
			mlx_put_pixel(img, x, y, 0xFF888888);
		y++;
	}
}

static t_ray	init_ray_vars(t_game *game, int ray)
{
	t_ray	vars;

	vars.ray_angle = (game->player.angle - (FOV / 2.0)) + ((double)ray
			/ NUM_RAYS) * FOV;
	vars.ray_cos = cos(vars.ray_angle * M_PI / 180.0);
	vars.ray_sin = sin(vars.ray_angle * M_PI / 180.0);
	vars.x = game->player.x;
	vars.y = game->player.y;
	return (vars);
}

void	raycast_and_render(t_game *game, mlx_image_t *img)
{
	double	distance;
	int		wall_start;
	int		wall_end;
	int		ray;
	t_ray	vars;

	ray = 0;
	while (ray < NUM_RAYS)
	{
		vars = init_ray_vars(game, ray);
		while (1)
		{
			if (vars.x < 0 || vars.x >= strlen(game->map[0]) || vars.y < 0
				|| vars.y >= game->map_height)
				break ;
			if (game->map[(int)vars.y][(int)vars.x] == '1')
				break ;
			vars.x += vars.ray_cos * 0.01;
			vars.y += vars.ray_sin * 0.01;
		}
		distance = sqrt((vars.x - game->player.x) * (vars.x - game->player.x)
				+ (vars.y - game->player.y) * (vars.y - game->player.y));
		distance *= cos(vars.ray_angle * M_PI / 180.0 - game->player.angle
				* M_PI / 180.0);
		wall_start = (img->height / 2) - ((int)(img->height / (distance
						+ 0.0001)) / 2);
		wall_end = wall_start + (int)(img->height / (distance + 0.0001));
		draw_vertical_line(img, ray, wall_start, wall_end);
		ray++;
	}
}

void	clear_image(mlx_image_t *img, int ceiling_color, int floor_color)
{
	uint32_t	color;
	int			y;
	int			x;

	y = 0;
	while (y < (int)img->height)
	{
		if (y < (int)img->height / 2)
			color = ceiling_color;
		else
			color = floor_color;
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
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
