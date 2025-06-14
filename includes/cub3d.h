/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 06:09:40 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/14 17:42:52 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define TILE_SIZE 32
# define MAP_OFFSET_X 20
# define MAP_OFFSET_Y 20
# define FOV 60.0
# define NUM_RAYS WIN_WIDTH

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h> // for open()
# include <math.h>  // for M_PI, cos(), sin(), sqrt()
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h> // for exit(), malloc(), free(), ft_atoi()
# include <string.h> // for ft_strlen(), strcpy(), strtok()
# include <unistd.h> // for read(), close()

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_textures;

// Floor and ceiling colors
typedef struct s_colors
{
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
}				t_colors;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
}				t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			map_height;
	t_player	player;
	t_textures	textures;
	t_colors	colors;
	char		**map;
}				t_game;

typedef struct s_ray
{
	double	ray_angle;
	double	ray_cos;
	double	ray_sin;
	double	x;
	double	y;
}	t_ray;

// main.c
void			close_window(void *param);
void			key_hook(mlx_key_data_t keydata, void *param);
void			print_parsed_data(t_game *game);

// parsing.c
int				parse_texture_line(char *line, t_textures *textures,
					t_colors *colors);
int				count_map_lines(char *buffer, int start_pos, int total_size);
char			*copy_map_line(char *buffer, int start, int end);
int				parse_map_section(char *buffer, int map_start, int total_size,
					t_game *game);
int				parse_cub_file(char *filename, t_game *game);
int				find_player_position(t_game *game);
int				validate_top_bottom_walls(t_game *game, int map_height,
					int map_width);
int				validate_left_right_walls(t_game *game, int map_height);
int				validate_map_characters(t_game *game, int map_height);
int				validate_map_walls(t_game *game);
int				check_file_extension(char *filename);
int				parse_and_validate_cub_file(char *filename, t_game *game);

// colors.c
void			parse_rgb_color(char *color_str, int *r, int *g, int *b);
uint32_t		get_floor_color(t_colors *colors);
uint32_t		get_ceiling_color(t_colors *colors);

// 2Dmap.c
void			draw_minimap(t_game *game);

// movements.c
void			rotate_player(t_game *game, double angle);
void			move_forward_backward(t_game *game, int dir);
void			move_left_right(t_game *game, int dir);

// raycasting.c
void			raycast_and_render(t_game *game, mlx_image_t *img);
void			draw_vertical_line(mlx_image_t *img, int x, int start, int end);
void			game_loop(void *param);

// init.c
int				init_game(t_game *game);
void			cleanup_game(t_game *game);

#endif // CUB3D_H