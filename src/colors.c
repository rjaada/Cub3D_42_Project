/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:49 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/13 20:13:52 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"

void	parse_rgb_color(char *color_str, int *r, int *g, int *b)
{
	char	*token;
	char	*str_copy;

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

// Getter for floor color
uint32_t	get_floor_color(t_colors *colors)
{
	return ((colors->floor_r << 24) | (colors->floor_g << 16) | (colors->floor_b << 8) | 0xFF);
}

// Getter for ceiling color
uint32_t	get_ceiling_color(t_colors *colors)
{
	return ((colors->ceiling_r << 24) | (colors->ceiling_g << 16) | (colors->ceiling_b << 8) | 0xFF);
}
