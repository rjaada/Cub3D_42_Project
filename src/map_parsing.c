/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:24:12 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/19 00:59:32 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_map_lines(char *buffer, int start_pos, int total_size)
{
	int	lines;
	int	i;

	lines = 0;
	i = start_pos;
	while (i < total_size)
	{
		if (buffer[i] == '\n' || i == total_size - 1)
			lines++;
		i++;
	}
	return (lines);
}

char	*copy_map_line(char *buffer, int start, int end)
{
	char	*line;
	int		len;
	int		i;

	len = end - start;
	i = 0;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = buffer[start + i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	process_map_line(char *buffer, int line_start, int i, t_game *game)
{
	game->map[game->current_line] = copy_map_line(buffer, line_start, i);
	if (!game->map[game->current_line])
		return (0);
	game->current_line++;
	return (1);
}

static int	parse_map_lines(char *buffer, int map_start, t_game *game)
{
	int	i;
	int	line_start;

	i = map_start;
	line_start = map_start;
	game->current_line = 0;
	while (i <= game->total_size && game->current_line < game->line_count)
	{
		if (buffer[i] == '\n' || i == game->total_size)
		{
			if (!process_map_line(buffer, line_start, i, game))
				return (0);
			line_start = i + 1;
		}
		i++;
	}
	game->map[game->current_line] = NULL;
	return (1);
}

int	parse_map_section(char *buffer, int map_start, int total_size, t_game *game)
{
	game->total_size = total_size;
	game->line_count = count_map_lines(buffer, map_start, total_size);
	game->map = malloc(sizeof(char *) * (game->line_count + 1));
	if (!game->map)
		return (0);
	if (!parse_map_lines(buffer, map_start, game))
		return (0);
	return (1);
}
