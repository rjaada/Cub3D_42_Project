/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 06:09:40 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/07 16:13:35 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libraries/libft/libft.h"
# include <fcntl.h> // for open()
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

typedef struct s_colors
{
	int floor_r, floor_g, floor_b;
	int ceiling_r, ceiling_g, ceiling_b;
}				t_colors;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
}				t_player;

typedef struct s_game
{
	mlx_t *mlx; // Changed to mlx_t* for MLX42
	t_player	player;
	t_textures	textures;
	t_colors	colors;
	char		**map;
}				t_game;

// Function prototypes
void			close_window(void *param);
void			key_hook(mlx_key_data_t keydata, void *param);
int				parse_texture_line(char *line, t_textures *textures,
					t_colors *colors);
int				parse_cub_file(char *filename, t_game *game);
void			parse_rgb_color(char *color_str, int *r, int *g, int *b);
void			print_parsed_data(t_game *game);
int				count_map_lines(char *buffer, int start_pos, int total_size);
char			*copy_map_line(char *buffer, int start, int end);
int				parse_map_section(char *buffer, int map_start, int total_size,
					t_game *game);
int				find_player_position(t_game *game);
int				validate_map_walls(t_game *game);
int				check_file_extension(char *filename);
int				parse_and_validate_cub_file(char *filename, t_game *game);
void			cleanup_game(t_game *game);

#endif // CUB3D_H