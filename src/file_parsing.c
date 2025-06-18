/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:20:17 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/18 23:59:33 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			handle_texture_line(&buffer[line_start], game, game->seen);
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

	init_seen_keys(game->seen);
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
	if (!validate_all_required_elements(game->seen))
		return (0);
	if (game->map_start == -1)
		return (printf("Error\nNo map found in file\n"), 0);
	return (parse_map_section(buffer, game->map_start, bytes_read, game));
}

int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	buffer[4096];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCannot open file %s\n", filename), 0);
	bytes_read = read(fd, buffer, 4095);
	buffer[bytes_read] = '\0';
	close(fd);
	printf("=== FILE CONTENT ===\n%s=== END FILE ===\n", buffer);
	return (process_file_content(buffer, bytes_read, game));
}
