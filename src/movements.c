/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:16:49 by cschnath          #+#    #+#             */
/*   Updated: 2025/06/19 13:43:33 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	can_move_to(char ***map, double x, double y)
{
	double	tight_radius;

	tight_radius = COLLISION_RADIUS * 0.6;
	if (!is_walkable(map, x, y))
		return (0);
	if (!is_walkable(map, x - tight_radius, y))
		return (0);
	if (!is_walkable(map, x + tight_radius, y))
		return (0);
	if (!is_walkable(map, x, y - tight_radius))
		return (0);
	if (!is_walkable(map, x, y + tight_radius))
		return (0);
	return (1);
}

void	rotate_player(t_game *game, double angle)
{
	game->player.angle += angle;
	while (game->player.angle < 0)
		game->player.angle += 360.0;
	while (game->player.angle >= 360.0)
		game->player.angle -= 360.0;
}

void	move_forward_backward(t_game *game, int dir)
{
	double	angle_rad;
	double	new_x;
	double	new_y;

	angle_rad = game->player.angle * M_PI / 180.0;
	new_x = game->player.x + cos(angle_rad) * MOVE_SPEED * dir;
	new_y = game->player.y + sin(angle_rad) * MOVE_SPEED * dir;
	if (can_move_to(&game->map, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
		return ;
	}
	if (can_move_to(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move_to(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_left_right(t_game *game, int dir)
{
	double	perp_angle_rad;
	double	new_x;
	double	new_y;

	perp_angle_rad = (game->player.angle + (dir * 90.0)) * M_PI / 180.0;
	new_x = game->player.x + cos(perp_angle_rad) * MOVE_SPEED;
	new_y = game->player.y + sin(perp_angle_rad) * MOVE_SPEED;
	if (can_move_to(&game->map, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
		return ;
	}
	if (can_move_to(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move_to(&game->map, game->player.x, new_y))
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
		game->mouse_locked = !game->mouse_locked;
	if (mlx_is_key_down(game->mlx, MLX_KEY_N))
		game->mouse_locked = 0;
}
