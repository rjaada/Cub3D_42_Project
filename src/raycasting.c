/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:22 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/16 01:08:23 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	calculate_distance(t_game *game, t_ray_result result,
		double ray_angle)
{
	double	distance;

	distance = sqrt((result.final_x - game->player.x) * (result.final_x
				- game->player.x) + (result.final_y - game->player.y)
			* (result.final_y - game->player.y));
	distance *= cos(ray_angle * M_PI / 180.0 - game->player.angle * M_PI
			/ 180.0);
	return (distance);
}

static void	render_wall_column(t_render_data *data)
{
	t_draw_params	params;
	t_wall_data		wall;

	params.img = data->img;
	params.x = data->ray;
	params.start = (data->img->height / 2) - ((int)(data->img->height
				/ (data->distance + 0.0001)) / 2);
	params.end = params.start + (int)(data->img->height / (data->distance
				+ 0.0001));
	wall.wall_direction = data->result.wall_direction;
	wall.wall_hit_x = data->result.wall_hit_x;
	wall.wall_hit_y = data->result.wall_hit_y;
	draw_vertical_line(params, wall, data->game);
}

void	raycast_and_render(t_game *game, mlx_image_t *img)
{
	int				ray;
	t_ray			vars;
	t_render_data	data;

	ray = 0;
	data.game = game;
	data.img = img;
	while (ray < NUM_RAYS)
	{
		vars = init_ray_vars(game, ray);
		data.result = cast_single_ray(game, vars);
		data.distance = calculate_distance(game, data.result, vars.ray_angle);
		data.ray = ray;
		render_wall_column(&data);
		ray++;
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_movement(game);
	clear_image(game->img, get_ceiling_color(&game->colors),
		get_floor_color(&game->colors));
	draw_minimap(game);
	raycast_and_render(game, game->img);
}
