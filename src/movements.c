/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:16:49 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/16 01:58:49 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_walkable(char **map, int x, int y)
{
	return (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W');
}

void	rotate_player(t_game *game, double angle)
{
	game->player.angle += angle;
	if (game->player.angle < 0)
		game->player.angle += 360.0;
	if (game->player.angle >= 360.0)
		game->player.angle -= 360.0;
}

void	move_forward_backward(t_game *game, int dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle * M_PI / 180.0) * MOVE_SPEED
		* dir;
	new_y = game->player.y + sin(game->player.angle * M_PI / 180.0) * MOVE_SPEED
		* dir;
	if (is_walkable(game->map, (int)new_x, (int)game->player.y))
		game->player.x = new_x;
	if (is_walkable(game->map, (int)game->player.x, (int)new_y))
		game->player.y = new_y;
}

void	move_left_right(t_game *game, int dir)
{
	double	perp_angle;
	double	new_x;
	double	new_y;

	perp_angle = game->player.angle + (dir * 90.0);
	new_x = game->player.x + cos(perp_angle * M_PI / 180.0) * MOVE_SPEED;
	new_y = game->player.y + sin(perp_angle * M_PI / 180.0) * MOVE_SPEED;
	if (is_walkable(game->map, (int)new_x, (int)game->player.y))
		game->player.x = new_x;
	if (is_walkable(game->map, (int)game->player.x, (int)new_y))
		game->player.y = new_y;
}

void	handle_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward_backward(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_forward_backward(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left_right(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_left_right(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, -ROT_SPEED * 180.0 / M_PI);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, ROT_SPEED * 180.0 / M_PI);
}
