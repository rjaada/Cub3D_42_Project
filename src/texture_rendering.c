/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:59:00 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/16 01:09:21 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static mlx_texture_t	*get_wall_texture(t_game *game, int wall_direction)
{
	if (wall_direction == 0)
		return (game->north_texture);
	else if (wall_direction == 1)
		return (game->south_texture);
	else if (wall_direction == 2)
		return (game->east_texture);
	else
		return (game->west_texture);
}

static double	calculate_wall_x(int wall_direction, double wall_hit_x,
		double wall_hit_y)
{
	if (wall_direction == 0 || wall_direction == 1)
		return (wall_hit_x - floor(wall_hit_x));
	else
		return (wall_hit_y - floor(wall_hit_y));
}

static uint32_t	get_texture_pixel(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint32_t	*pixels;

	if (tex_x >= (int)texture->width)
		tex_x = (int)texture->width - 1;
	if (tex_y >= (int)texture->height)
		tex_y = (int)texture->height - 1;
	pixels = (uint32_t *)texture->pixels;
	return (pixels[tex_y * texture->width + tex_x]);
}

static void	draw_texture_pixel(t_draw_params params, t_texture_data *tex, int y)
{
	int			tex_y;
	uint32_t	color;

	if (params.x >= 0 && params.x < (int)params.img->width && y >= 0
		&& y < (int)params.img->height)
	{
		tex_y = ((y - params.start) * (int)tex->texture->height) / (params.end
				- params.start);
		color = get_texture_pixel(tex->texture, tex->tex_x, tex_y);
		mlx_put_pixel(params.img, params.x, y, color);
	}
}

void	draw_vertical_line(t_draw_params params, t_wall_data wall, t_game *game)
{
	t_texture_data	tex;
	int				y;

	tex.texture = get_wall_texture(game, wall.wall_direction);
	tex.wall_x = calculate_wall_x(wall.wall_direction, wall.wall_hit_x,
			wall.wall_hit_y);
	tex.tex_x = (int)(tex.wall_x * tex.texture->width);
	y = params.start;
	while (y < params.end)
	{
		draw_texture_pixel(params, &tex, y);
		y++;
	}
}
