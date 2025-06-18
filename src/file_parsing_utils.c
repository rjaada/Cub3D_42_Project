/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:30:28 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/18 23:54:30 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_texture_or_color_line(char c, char c2)
{
	return ((c == 'N' && c2 == 'O') || (c == 'S' && c2 == 'O') || (c == 'W'
			&& c2 == 'E') || (c == 'E' && c2 == 'A') || (c == 'F' && c2 == ' ')
		|| (c == 'C' && c2 == ' '));
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_chars;

	i = 0;
	has_map_chars = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			has_map_chars = 1;
		}
		else if (line[i] != ' ' && line[i] != '\t')
		{
			return (0);
		}
		i++;
	}
	return (has_map_chars && i > 0);
}

void	init_seen_keys(t_seen_keys *seen)
{
	seen->has_north = 0;
	seen->has_south = 0;
	seen->has_west = 0;
	seen->has_east = 0;
	seen->has_floor = 0;
	seen->has_ceiling = 0;
}

int	handle_texture_line(char *line, t_game *game, t_seen_keys *seen)
{
	if (!parse_texture_line(line, &game->textures, &game->colors, seen))
		exit(1);
	return (1);
}
