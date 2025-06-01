/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:32:59 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/01 18:49:51 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_player {
    double x;
    double y;
    double angle;
} t_player;

typedef struct s_game {
    void *mlx;
    void *win;
    t_player player;
} t_game;

int close_window(t_game *game)
{
    (void)game;
    exit(0);
    return (0);
}

int key_hook(int keycode, t_game *game)
{
    printf("Key pressed: %d\n", keycode);

    if (keycode == 65307) // ESC key
        exit(0);
	 else if (keycode == 119)   // W
    {
        printf("Move forward - Player at (%.1f, %.1f)\n", game->player.x, game->player.y);
        game->player.y -= 0.1; // move up (in 2D for now)
    }
    else if (keycode == 115)   // S
    {
        printf("Move backward - Player at (%.1f, %.1f)\n", game->player.x, game->player.y);
        game->player.y += 0.1; // move down
    }
    else if (keycode == 97)    // A
    {
        printf("Move left - Player at (%.1f, %.1f)\n", game->player.x, game->player.y);
        game->player.x -= 0.1; // move left
    }
    else if (keycode == 100)   // D
    {
        printf("Move right - Player at (%.1f, %.1f)\n", game->player.x, game->player.y);
        game->player.x += 0.1; // move right
    }
    else if (keycode == 65361) // Left arrow
    {
        printf("Turn left - Angle: %.1f\n", game->player.angle);
        game->player.angle -= 0.1; // rotate left
    }
    else if (keycode == 65363) // Right arrow
    {
        printf("Turn right - Angle: %.1f\n", game->player.angle);
        game->player.angle += 0.1; // rotate right
    }	
    return (0);
}

int main(void)
{
    t_game game;
    
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        printf("Error: MLX init failed\n");
        return (1);
    }
    
    game.win = mlx_new_window(game.mlx, 800, 600, "cub3D - Mouvment Test!");
    if (!game.win)
    {
        printf("Error: Window creation failed\n");
        return (1);
    }
    
    // Initialize player position
    game.player.x = 5.0;
    game.player.y = 5.0;
    game.player.angle = 0.0;
    
    // Set up event handling
    mlx_hook(game.win, 17, 0, (int(*)())close_window, &game);
    mlx_key_hook(game.win, (int(*)())key_hook, &game);
    
    printf("SUCCESS! Use WASD to move, arrows to turn, ESC to quit.\n");
    printf("Starting position: (%.1f, %.1f) angle: %.1f\n", 
           game.player.x, game.player.y, game.player.angle);
    
    mlx_loop(game.mlx);
    return (0);
}
