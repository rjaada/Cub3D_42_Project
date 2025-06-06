/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:49 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/06 06:16:12 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../libraries/libft/libft.h"
#include "../includes/cub3d.h"

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
