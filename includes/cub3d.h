/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 06:09:40 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/19 14:12:00 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1800
# define WIN_HEIGHT 1350
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.02
# define TILE_SIZE 32
# define MAP_OFFSET_X 20
# define MAP_OFFSET_Y 20
# define FOV 60.0
# define NUM_RAYS WIN_WIDTH
# define M_PI 3.14159265358979323846
# define COLLISION_RADIUS 0.5
# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_seen_keys
{
	int				has_north;
	int				has_south;
	int				has_west;
	int				has_east;
	int				has_floor;
	int				has_ceiling;
}					t_seen_keys;

typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
}					t_textures;

typedef struct s_colors
{
	int				f_r;
	int				f_g;
	int				f_b;
	int				c_r;
	int				c_g;
	int				c_b;
}					t_colors;

typedef struct s_player
{
	double			x;
	double			y;
	double			angle;
}					t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	int				map_height;
	int				map_width;
	int				map_start;
	int				total_size;
	int				line_count;
	int				current_line;
	t_seen_keys		*seen;
	t_player		player;
	t_textures		textures;
	t_colors		colors;
	char			**map;
	int				mouse_locked;
}					t_game;

typedef struct s_ray
{
	double			ray_angle;
	double			ray_cos;
	double			ray_sin;
	double			x;
	double			y;
}					t_ray;

typedef struct s_ray_result
{
	double			wall_hit_x;
	double			wall_hit_y;
	double			final_x;
	double			final_y;
	int				wall_direction;
}					t_ray_result;

typedef struct s_draw_params
{
	mlx_image_t		*img;
	int				x;
	int				start;
	int				end;
}					t_draw_params;

typedef struct s_wall_data
{
	int				wall_direction;
	double			wall_hit_x;
	double			wall_hit_y;
}					t_wall_data;

typedef struct s_render_data
{
	t_game			*game;
	mlx_image_t		*img;
	int				ray;
	t_ray_result	result;
	double			distance;
}					t_render_data;

typedef struct s_texture_data
{
	mlx_texture_t	*texture;
	double			wall_x;
	int				tex_x;
}					t_texture_data;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

// 2Dmap.c
void				clear_minimap_bg(t_game *game);
void				draw_minimap(t_game *game);

// cleanup.c
void				cleanup_texture_paths(t_game *game);
void				cleanup_mlx_textures(t_game *game);
void				cleanup_map(t_game *game);
void				cleanup_game(t_game *game);

// color_parsing.c
int					parse_texture_line(char *line, t_textures *textures,
						t_colors *colors, t_seen_keys *seen);
int					check_file_extension(char *filename);

// colors.c
void				parse_rgb_color(char *color_str, int *r, int *g, int *b);
uint32_t			get_floor_color(t_colors *colors);
uint32_t			get_ceiling_color(t_colors *colors);
void				clear_image(mlx_image_t *img, int ceiling_color,
						int floor_color);

// config_validation.c
int					validate_color_range(int r, int g, int b);
int					is_valid_config_line(char *line);
int					check_duplicate_key(char *line, t_seen_keys *seen);
int					validate_all_required_elements(t_seen_keys *seen);

// error_handler.c
int					error_duplicate_key(char *key);
int					error_missing_element(char *element);
int					error_color_range(void);
int					error_unknown_identifier(char *line);
int					error_invalid_line(char *line);

// file_parsing_utils.c
int					is_texture_or_color_line(char c, char c2);
int					is_map_line(char *line);
void				init_seen_keys(t_seen_keys *seen);
int					handle_texture_line(char *line, t_game *game,
						t_seen_keys *seen);

// file_parsing.c
int					parse_cub_file(char *filename, t_game *game);

// init.c
int					init_game(t_game *game);
int					load_textures(t_game *game);

// main.c
void				close_window(void *param);
void				key_hook(mlx_key_data_t keydata, void *param);
int					init_mlx_and_start(t_game *game);
void				cursor_hook(double xpos, double ypos, void *param);

// map_parsing.c

int					count_map_lines(char *buffer, int start_pos,
						int total_size);
char				*copy_map_line(char *buffer, int start, int end);
int					parse_map_section(char *buffer, int map_start,
						int total_size, t_game *game);

// map_validation_utils.c
int					is_valid_map_character(char c);
int					validate_character_at_position(char c, int row, int col);
int					validate_row_characters(char *row_data, int row_index);

// map_validation.c
int					validate_map_characters(t_game *game, int map_height);
int					validate_map_walls(t_game *game);
int					parse_and_validate_cub_file(char *filename, t_game *game);
int					is_walkable(char ***map, double x, double y);

// movements.c
void				rotate_player(t_game *game, double angle);
void				move_forward_backward(t_game *game, int dir);
void				move_left_right(t_game *game, int dir);
void				handle_movement(t_game *game);

// player_parsing.c
int					find_player_position(t_game *game);

// ray_utils.c
t_ray				init_ray_vars(t_game *game, int ray);
t_ray_result		cast_single_ray(t_game *game, t_ray vars);

// raycasting.c
void				raycast_and_render(t_game *game, mlx_image_t *img);
void				game_loop(void *param);

// texture_parsing.c
int					parse_texture_no_so(char *line, t_textures *textures);
int					parse_texture_we_ea(char *line, t_textures *textures);

// texture_rendering.c
void				draw_vertical_line(t_draw_params params, t_wall_data wall,
						t_game *game);

// wall_validation_utils.c
int					find_content_start(char *line);
int					find_content_end(char *line);
int					check_wall_boundary(char *line, int start, int end,
						int row);
int					check_horizontal_wall(char *line, int start, int end,
						char *wall_type);

// wall_validation.c
int					get_max_line_width(t_game *game);
int					validate_top_bottom_walls(t_game *game, int map_height,
						int map_width);
int					validate_left_right_walls(t_game *game, int map_height);

#endif