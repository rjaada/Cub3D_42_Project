/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:10:21 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/19 00:18:56 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	find_content_start(char *line)
{
	int	start;
	int	len;

	if (!line)
		return (-1);
	len = ft_strlen(line);
	start = 0;
	while (start < len)
	{
		if (line[start] != ' ' && line[start] != '\t')
			return (start);
		start++;
	}
	return (-1);
}

int	find_content_end(char *line)
{
	int	end;

	if (!line)
		return (-1);
	end = ft_strlen(line) - 1;
	while (end >= 0)
	{
		if (line[end] != ' ' && line[end] != '\t' && line[end] != '\0')
			return (end);
		end--;
	}
	return (-1);
}

int	check_wall_boundary(char *line, int start, int end, int row)
{
	if (start == -1 || end == -1 || start > end)
		return (1);
	if (line[start] != '1')
	{
		printf("Error\nMap not closed - left wall missing at row %d\n", row);
		return (0);
	}
	if (line[end] != '1')
	{
		printf("Error\nMap not closed - right wall missing at row %d\n", row);
		return (0);
	}
	return (1);
}

int	check_horizontal_wall(char *line, int start, int end, char *wall_type)
{
	if (start == -1 || end == -1 || start > end)
		return (1);
	if (line[start] != '1')
	{
		printf("Error\nMap not closed - %s start not walled\n", wall_type);
		return (0);
	}
	if (line[end] != '1')
	{
		printf("Error\nMap not closed - %s end not walled\n", wall_type);
		return (0);
	}
	return (1);
}
