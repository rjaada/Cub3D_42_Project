/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:51 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/13 18:48:26 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Initialize everything here

#include "../includes/cub3d.h"

int	init_game(t_game *game)
{
    game->mlx = mlx_init(800, 600, "cub3D - Movement Test!", true);
    if (!game->mlx)
    {
        printf("Error: MLX init failed\n");
        return (0);
    }
    game->img = NULL; // Initialize minimap image to NULL
    game->player.x = 5.0; // Set initial player position
    game->player.y = 5.0;
    game->player.angle = 0.0; // Initial angle
    return (1);
}
