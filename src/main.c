/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:32:59 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/01 20:35:10 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  // for open()
#include <unistd.h> // for read(), close()

typedef struct s_textures {
    char *north;
    char *south;
    char *west;
    char *east;
} t_textures;

typedef struct s_colors {
    int floor_r, floor_g, floor_b;
    int ceiling_r, ceiling_g, ceiling_b;
} t_colors;

typedef struct s_player {
    double x;
    double y;
    double angle;
} t_player;

typedef struct s_game {
    void *mlx;
    void *win;
    t_player player;
    t_textures textures;  
    t_colors colors;      
    char **map;           
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

int parse_texture_line(char *line, t_textures *textures, t_colors *colors)
{
	(void)textures; // We will use this later to store texture paths
	(void)colors;   // We will use this later to store color values
	if (line[0] == 'N' && line[1] == 'O')
	{
		printf("Found North texture: %s\n", line + 3);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		printf("Found South texture: %s\n", line + 3);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		printf("Found West texture: %s\n", line + 3);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		printf("Found East texture: %s\n", line + 3);
	}
	else if (line[0] == 'F' && line[1] == ' ')
    {
        printf("Found Floor color: %s\n", line + 2);
    }
    else if (line[0] == 'C' && line[1] == ' ') 
    {
        printf("Found Ceiling color: %s\n", line + 2);
    }
	return (1);
}

int parse_cub_file(char *filename, t_game *game)
{
    int fd;
    char buffer[1000];
    int bytes_read;
	int i = 0;
	int line_start = 0;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file %s\n", filename);
        return (0);
    }
    
    bytes_read = read(fd, buffer, 999);
    buffer[bytes_read] = '\0';
    close(fd);
    
    printf("=== FILE CONTENT ===\n");
    printf("%s", buffer);
    printf("=== END FILE ===\n");
	printf("\n=== PARSING ===\n");
    while (i < bytes_read)
    {
        if (buffer[i] == '\n' || i == bytes_read - 1)
        {
            buffer[i] = '\0';  // end the line
            parse_texture_line(&buffer[line_start], &game->textures, &game->colors);
            line_start = i + 1;
        }
        i++;
    }
    
    return (1);
}


int main(int argc, char **argv)
{
    t_game game;
    
	if (argc != 2)
    {
        printf("Usage: %s <map.cub>\n", argv[0]);
        return (1);
    }

	if (!parse_cub_file(argv[1], &game))
        return (1);
	
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
