#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include <stdint.h>
#define TILE_SIZE 32
#define MAP_OFFSET_X 20
#define MAP_OFFSET_Y 20

void	draw_minimap(t_game *game)
{
    int x, y, i, j;
    uint32_t color;
    int map_width, map_height;

    map_height = 0;
    while (game->map[map_height])
        map_height++;
    map_width = strlen(game->map[0]);

    // Create minimap image only once
    if (!game->img)
    {
        game->img = mlx_new_image(game->mlx,
            map_width * TILE_SIZE + 2 * MAP_OFFSET_X,
            map_height * TILE_SIZE + 2 * MAP_OFFSET_Y);
        mlx_image_to_window(game->mlx, game->img, 0, 0);
    }

    // Clear the image (set all pixels to background color)
    for (uint32_t y_img = 0; y_img < game->img->height / 2; y_img++)
        for (uint32_t x_img = 0; x_img < game->img->width; x_img++)
            mlx_put_pixel(game->img, x_img, y_img, 0xFFFFFFFF); // White background
    
    for (uint32_t y_img = game->img->height / 2; y_img < game->img->height; y_img++)
        for (uint32_t x_img = 0; x_img < game->img->width; x_img++)
            mlx_put_pixel(game->img, x_img, y_img, 0xFF000000); // Black floor

    // Draw map cells (loop over map, not image!)
    for (y = 0; y < map_height; y++)
    {
        for (x = 0; x < map_width; x++)
        {
            if (game->map[y][x] == '1')
                color = 0xFF444444; // Wall
            else
                color = 0xFFCCCCCC; // Floor

            for (i = 0; i < TILE_SIZE; i++)
            {
                for (j = 0; j < TILE_SIZE; j++)
                {
                    int draw_x = MAP_OFFSET_X + x * TILE_SIZE + i;
                    int draw_y = MAP_OFFSET_Y + y * TILE_SIZE + j;
                    if (draw_x >= 0 && draw_x < (int)game->img->width &&
                        draw_y >= 0 && draw_y < (int)game->img->height)
                        mlx_put_pixel(game->img, draw_x, draw_y, color);
                }
            }
        }
    }

    // Draw player as a red square
    int px = MAP_OFFSET_X + (int)(game->player.x * TILE_SIZE) - TILE_SIZE / 4;
    int py = MAP_OFFSET_Y + (int)(game->player.y * TILE_SIZE) - TILE_SIZE / 4;
    for (i = 0; i < TILE_SIZE / 2; i++)
    {
        for (j = 0; j < TILE_SIZE / 2; j++)
        {
            int draw_x = px + i;
            int draw_y = py + j;
            if (draw_x >= 0 && draw_x < (int)game->img->width &&
                draw_y >= 0 && draw_y < (int)game->img->height)
                mlx_put_pixel(game->img, draw_x, draw_y, 0xFFFF0000);
        }
    }
}
