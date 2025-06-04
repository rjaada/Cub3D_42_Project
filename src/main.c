/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:32:59 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/04 19:14:15 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../libraries/libft/libft.h"
#include <stdio.h>
#include <stdlib.h> // for exit(), malloc(), free(), ft_atoi()
#include <fcntl.h>  // for open()
#include <unistd.h> // for read(), close()
#include <string.h> // for ft_strlen(), strcpy(), strtok()

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
    mlx_t *mlx;           // Changed to mlx_t* for MLX42
    t_player player;
    t_textures textures;  
    t_colors colors;      
    char **map;           
} t_game;

void close_window(void *param)
{
    (void)param;  // Suppress unused parameter warning
    exit(0);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS) // ESC key - FIXED!
    {
        printf("ESC pressed - Exiting\n");
        exit(0);
    }
    else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)   // W - FIXED!
    {
        printf("Move forward - Player at (%.1f, %.1f)\n", game->player.x, game->player.y);
        game->player.y -= 0.1; // move up (in 2D for now)
    }
    else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)   // S - FIXED!
    {
        printf("Move backward - Player at (%.1f, %.1f)\n", game->player.x, game->player.y);
        game->player.y += 0.1; // move down
    }
    else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)    // A - FIXED!
    {
        printf("Move left - Player at (%.1f, %.1f)\n", game->player.x, game->player.y);
        game->player.x -= 0.1; // move left
    }
    else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)   // D - FIXED!
    {
        printf("Move right - Player at (%.1f, %.1f)\n", game->player.x, game->player.y);
        game->player.x += 0.1; // move right
    }
    else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // Left arrow - FIXED!
    {
        printf("Turn left - Angle: %.1f\n", game->player.angle);
        game->player.angle -= 0.1; // rotate left
    }
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // Right arrow - FIXED!
    {
        printf("Turn right - Angle: %.1f\n", game->player.angle);
        game->player.angle += 0.1; // rotate right
    }
    // REMOVED return (0) - MLX42 key_hook returns void!
}

void parse_rgb_color(char *color_str, int *r, int *g, int *b)
{
    char *token;
    char *str_copy;
    
    // Make a copy since strtok modifies the string
    str_copy = malloc(ft_strlen(color_str) + 1);
    strcpy(str_copy, color_str);
    
    // Parse R value
    token = strtok(str_copy, ",");
    *r = ft_atoi(token);
    
    // Parse G value  
    token = strtok(NULL, ",");
    *g = ft_atoi(token);
    
    // Parse B value
    token = strtok(NULL, ",");
    *b = ft_atoi(token);
    
    free(str_copy);
}

int parse_texture_line(char *line, t_textures *textures, t_colors *colors)
{
    if (line[0] == 'N' && line[1] == 'O')
    {
        printf("Found North texture: %s\n", line + 3);
        textures->north = malloc(ft_strlen(line + 3) + 1);
        strcpy(textures->north, line + 3);
    }
    else if (line[0] == 'S' && line[1] == 'O')
    {
        printf("Found South texture: %s\n", line + 3);
        textures->south = malloc(ft_strlen(line + 3) + 1);
        strcpy(textures->south, line + 3);
    }
    else if (line[0] == 'W' && line[1] == 'E')
    {
        printf("Found West texture: %s\n", line + 3);
        textures->west = malloc(ft_strlen(line + 3) + 1);
        strcpy(textures->west, line + 3);
    }
    else if (line[0] == 'E' && line[1] == 'A')
    {
        printf("Found East texture: %s\n", line + 3);
        textures->east = malloc(ft_strlen(line + 3) + 1);
        strcpy(textures->east, line + 3);
    }
    else if (line[0] == 'F' && line[1] == ' ')
    {
        printf("Found Floor color: %s\n", line + 2);
        parse_rgb_color(line + 2, &colors->floor_r, &colors->floor_g, &colors->floor_b);
    }
    else if (line[0] == 'C' && line[1] == ' ') 
    {
        printf("Found Ceiling color: %s\n", line + 2);
        parse_rgb_color(line + 2, &colors->ceiling_r, &colors->ceiling_g, &colors->ceiling_b);
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

void print_parsed_data(t_game *game)
{
    printf("\n=== STORED DATA VERIFICATION ===\n");
    
    // Check textures
    printf("North texture: %s\n", game->textures.north ? game->textures.north : "NULL");
    printf("South texture: %s\n", game->textures.south ? game->textures.south : "NULL");
    printf("West texture: %s\n", game->textures.west ? game->textures.west : "NULL");
    printf("East texture: %s\n", game->textures.east ? game->textures.east : "NULL");
    
    // Check colors
    printf("Floor color: RGB(%d, %d, %d)\n", 
           game->colors.floor_r, game->colors.floor_g, game->colors.floor_b);
    printf("Ceiling color: RGB(%d, %d, %d)\n", 
           game->colors.ceiling_r, game->colors.ceiling_g, game->colors.ceiling_b);
    
    printf("=== END VERIFICATION ===\n\n");
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
    print_parsed_data(&game);
    
    // MLX42 initialization - no separate window creation needed!
    game.mlx = mlx_init(800, 600, "cub3D - Movement Test!", true);

    if (!game.mlx)
    {
        printf("Error: MLX init failed\n");
        return (1);
    }
    
    // Initialize player position
    game.player.x = 5.0;
    game.player.y = 5.0;
    game.player.angle = 0.0;
    
    // Set up event handling - MLX42 style!
    mlx_close_hook(game.mlx, close_window, &game);  // Window close hook
    mlx_key_hook(game.mlx, key_hook, &game);        // Key hook
    
    printf("SUCCESS! Use WASD to move, arrows to turn, ESC to quit.\n");
    printf("Starting position: (%.1f, %.1f) angle: %.1f\n", 
           game.player.x, game.player.y, game.player.angle);
    
    mlx_loop(game.mlx);
    return (0);
}
