#include "../includes/cub3d.h"
#include <math.h>

#define FOV 60.0
#define NUM_RAYS WIN_WIDTH

void	draw_vertical_line(mlx_image_t *img, int x, int start, int end, uint32_t color)
{
    for (int y = start; y < end; y++)
    {
        if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
            mlx_put_pixel(img, x, y, color);
    }
}

void	raycast_and_render(t_game *game, mlx_image_t *img)
{
    double	ray_angle;
    double	ray_x, ray_y;
    double	distance;
    int		wall_height;
    int		screen_height = img->height;

    for (int ray = 0; ray < NUM_RAYS; ray++)
    {
        ray_angle = (game->player.angle - (FOV / 2.0)) + ((double)ray / NUM_RAYS) * FOV;
        double ray_rad = ray_angle * M_PI / 180.0;
        double ray_dir_x = cos(ray_rad);
        double ray_dir_y = sin(ray_rad);
        ray_x = game->player.x;
        ray_y = game->player.y;
        while (1)
        {
            int test_x = (int)ray_x;
            int test_y = (int)ray_y;
            if (test_x < 0 || test_x >= (int)strlen(game->map[0]) ||
                test_y < 0 || test_y >= (int)game->map_height)
                break;
            if (game->map[test_y][test_x] == '1')
                break;
            ray_x += ray_dir_x * 0.01;
            ray_y += ray_dir_y * 0.01;
        }
        distance = sqrt((ray_x - game->player.x) * (ray_x - game->player.x) +
                        (ray_y - game->player.y) * (ray_y - game->player.y));
        wall_height = (int)(screen_height / (distance + 0.0001));
        int wall_start = (screen_height / 2) - (wall_height / 2);
        int wall_end = wall_start + wall_height;
        draw_vertical_line(img, ray, wall_start, wall_end, 0xFF888888); // Gray wall
    }
}

void	clear_image(mlx_image_t *img, int ceiling_color, int floor_color)
{
    for (int y = 0; y < (int)img->height; y++)
    {
        uint32_t color = (y < (int)img->height / 2) ? ceiling_color : floor_color;
        for (int x = 0; x < (int)img->width; x++)
            mlx_put_pixel(img, x, y, color);
    }
}

void	game_loop(void *param)
{
    t_game *game = (t_game *)param;
    clear_image(game->img,
        0x00000000, // ceiling color (light gray)
        0xFFFFFFFF  // floor color (dark gray)
    );
    draw_minimap(game);
    raycast_and_render(game, game->img);
}
