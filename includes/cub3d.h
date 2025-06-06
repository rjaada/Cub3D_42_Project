/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 06:09:40 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/06 06:17:11 by rjaada           ###   ########.fr       */
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
void	close_window(void *param);
void	key_hook(mlx_key_data_t keydata, void *param);
int		parse_texture_line(char *line, t_textures *textures, t_colors *colors);
int		parse_cub_file(char *filename, t_game *game);
void	parse_rgb_color(char *color_str, int *r, int *g, int *b);
void	print_parsed_data(t_game *game);

#endif // CUB3D_H