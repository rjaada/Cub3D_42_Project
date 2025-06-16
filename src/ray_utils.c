/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:00:12 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/16 01:14:45 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_ray	init_ray_vars(t_game *game, int ray)
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

static int	determine_wall_direction(double vars_x, double vars_y,
		double prev_x, double prev_y)
{
	if ((int)vars_y != (int)prev_y)
	{
		if (vars_y > prev_y)
			return (0);
		else
			return (1);
	}
	else
	{
		if (vars_x > prev_x)
			return (2);
		else
			return (3);
	}
}

static int	is_wall_hit(t_game *game, double x, double y)
{
	if (x < 0 || x >= strlen(game->map[0]) || y < 0 || y >= game->map_height)
		return (1);
	return (game->map[(int)y][(int)x] == '1');
}

static void	step_ray(t_ray *vars, double *prev_x, double *prev_y)
{
	*prev_x = vars->x;
	*prev_y = vars->y;
	vars->x += vars->ray_cos * 0.01;
	vars->y += vars->ray_sin * 0.01;
}

t_ray_result	cast_single_ray(t_game *game, t_ray vars)
{
	t_ray_result	result;
	double			prev_x;
	double			prev_y;

	prev_x = vars.x;
	prev_y = vars.y;
	while (!is_wall_hit(game, vars.x, vars.y))
		step_ray(&vars, &prev_x, &prev_y);
	if (vars.x >= 0 && vars.x < strlen(game->map[0]) && vars.y >= 0
		&& vars.y < game->map_height
		&& game->map[(int)vars.y][(int)vars.x] == '1')
	{
		result.wall_hit_x = vars.x;
		result.wall_hit_y = vars.y;
		result.wall_direction = determine_wall_direction(vars.x, vars.y, prev_x,
				prev_y);
	}
	result.final_x = vars.x;
	result.final_y = vars.y;
	return (result);
}
