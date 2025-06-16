/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:49 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/15 23:33:46 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Remove strtok
void	parse_rgb_color(char *color_str, int *r, int *g, int *b)
{
	char	*token;
	char	*str_copy;

	str_copy = malloc(ft_strlen(color_str) + 1);
	strcpy(str_copy, color_str);
	token = strtok(str_copy, ",");
	*r = ft_atoi(token);
	token = strtok(NULL, ",");
	*g = ft_atoi(token);
	token = strtok(NULL, ",");
	*b = ft_atoi(token);
	free(str_copy);
}

// Getter for floor color
// // The alpha value is set to 0xFF for full opacity
uint32_t	get_floor_color(t_colors *colors)
{
	int	a;

	a = 0xFF;
	return ((colors->f_r << 24) | (colors->f_g << 16) | (colors->f_b << 8) | a);
}

// Getter for ceiling color
uint32_t	get_ceiling_color(t_colors *colors)
{
	int	a;

	a = 0xFF;
	return ((colors->c_r << 24) | (colors->c_g << 16) | (colors->c_b << 8) | a);
}
