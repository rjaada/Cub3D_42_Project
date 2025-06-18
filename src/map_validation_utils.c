/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:21:01 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/19 00:21:13 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_map_character(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == '\t' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	validate_character_at_position(char c, int row, int col)
{
	if (!is_valid_map_character(c))
	{
		printf("Error\nInvalid character (ASCII %d) at [%d][%d]\n", (int)c, row,
			col);
		return (0);
	}
	return (1);
}

int	validate_row_characters(char *row_data, int row_index)
{
	int		col;
	char	c;

	col = 0;
	while (row_data[col])
	{
		c = row_data[col];
		if (!validate_character_at_position(c, row_index, col))
			return (0);
		col++;
	}
	return (1);
}
