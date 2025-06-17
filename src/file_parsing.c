/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:20:17 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/17 23:11:16 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_texture_or_color_line(char c, char c2)
{
	return ((c == 'N' && c2 == 'O') || (c == 'S' && c2 == 'O') || (c == 'W'
			&& c2 == 'E') || (c == 'E' && c2 == 'A') || (c == 'F' && c2 == ' ')
		|| (c == 'C' && c2 == ' '));
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	process_line(char *buffer, int line_start, int i, t_game *game)
{
	char	temp;

	temp = buffer[i];
	buffer[i] = '\0';
	if (line_start >= i || buffer[line_start] == '\0')
	{
		buffer[i] = temp;
		return ;
	}
	if (game->map_start == -1)
	{
		if (is_texture_or_color_line(buffer[line_start], buffer[line_start
					+ 1]))
		{
			if (!parse_texture_line(&buffer[line_start], &game->textures,
					&game->colors))
				exit(1);
		}
		else if (is_map_line(&buffer[line_start]))
			game->map_start = line_start;
		else if (buffer[line_start] != ' ')
			exit(error_invalid_line(&buffer[line_start]));
	}
	buffer[i] = temp;
}

static int	process_file_content(char *buffer, int bytes_read, t_game *game)
{
	int	i;
	int	line_start;

	i = 0;
	line_start = 0;
	game->map_start = -1;
	printf("\n=== PARSING TEXTURES & COLORS ===\n");
	while (i < bytes_read)
	{
		if (buffer[i] == '\n' || i == bytes_read - 1)
		{
			process_line(buffer, line_start, i, game);
			line_start = i + 1;
		}
		i++;
	}
	if (!validate_all_required_elements())
		return (0);
	if (game->map_start == -1)
		return (printf("Error\nNo map found in file\n"), 0);
	return (parse_map_section(buffer, game->map_start, bytes_read, game));
}

int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	buffer[1000];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCannot open file %s\n", filename), 0);
	bytes_read = read(fd, buffer, 999);
	buffer[bytes_read] = '\0';
	close(fd);
	printf("=== FILE CONTENT ===\n%s=== END FILE ===\n", buffer);
	return (process_file_content(buffer, bytes_read, game));
}
