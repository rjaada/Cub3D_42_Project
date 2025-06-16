/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:20:17 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/16 00:53:29 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_texture_or_color_line(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F'
		|| c == 'C');
}

static void	process_line(char *buffer, int line_start, int i, t_game *game)
{
	char	temp;

	temp = buffer[i];
	buffer[i] = '\0';
	if (line_start < i && is_texture_or_color_line(buffer[line_start]))
		parse_texture_line(&buffer[line_start], &game->textures, &game->colors);
	else if (line_start < i && buffer[line_start] != '\0'
		&& buffer[line_start] != ' ' && game->map_start == -1)
		game->map_start = line_start;
	buffer[i] = temp;
}

static int	process_file_content(char *buffer, int bytes_read, t_game *game)
{
	int	i;
	int	line_start;

	i = 0;
	line_start = 0;
	game->map_start = -1;
	while (i < bytes_read)
	{
		if (buffer[i] == '\n' || i == bytes_read - 1)
		{
			process_line(buffer, line_start, i, game);
			line_start = i + 1;
		}
		i++;
	}
	if (game->map_start == -1)
		return (printf("Error: No map found in file\n"), 0);
	return (parse_map_section(buffer, game->map_start, bytes_read, game));
}

int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	buffer[1000];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("Error: Cannot open file %s\n", filename), 0);
	bytes_read = read(fd, buffer, 999);
	buffer[bytes_read] = '\0';
	close(fd);
	printf("=== FILE CONTENT ===\n%s=== END FILE ===\n", buffer);
	printf("\n=== PARSING TEXTURES & COLORS ===\n");
	return (process_file_content(buffer, bytes_read, game));
}

int	parse_and_validate_cub_file(char *filename, t_game *game)
{
	if (!check_file_extension(filename))
		return (0);
	if (!parse_cub_file(filename, game))
		return (0);
	if (!find_player_position(game))
		return (0);
	if (!validate_map_walls(game))
		return (0);
	printf("\n🔥 CUB3D PARSING COMPLETE - ALL CHECKS PASSED! 🔥\n");
	return (1);
}
