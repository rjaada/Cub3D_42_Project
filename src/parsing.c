/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:49:54 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/13 20:31:25 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_texture_line(char *line, t_textures *textures, t_colors *colors)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		printf("Found North texture: %s\n", line + 3);
		textures->north = malloc(ft_strlen(line + 3) + 1);
		strcpy(textures->north, line + 3);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		printf("Found South texture: %s\n", line + 3);
		textures->south = malloc(ft_strlen(line + 3) + 1);
		strcpy(textures->south, line + 3);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		printf("Found West texture: %s\n", line + 3);
		textures->west = malloc(ft_strlen(line + 3) + 1);
		strcpy(textures->west, line + 3);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		printf("Found East texture: %s\n", line + 3);
		textures->east = malloc(ft_strlen(line + 3) + 1);
		strcpy(textures->east, line + 3);
	}
	else if (line[0] == 'F' && line[1] == ' ')
	{
		printf("Found Floor color: %s\n", line + 2);
		parse_rgb_color(line + 2, &colors->floor_r, &colors->floor_g,
			&colors->floor_b);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		printf("Found Ceiling color: %s\n", line + 2);
		parse_rgb_color(line + 2, &colors->ceiling_r, &colors->ceiling_g,
			&colors->ceiling_b);
	}
	return (1);
}

// map parsing function - reads the 1s and 0s from .cub file
// this goes after we parse all textures and colors
// stores everything in game->map as 2D array

int	count_map_lines(char *buffer, int start_pos, int total_size)
{
	int	lines;
	int	i;

	lines = 0;
	i = start_pos;
	// count how many map lines we have
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
	// allocate memory for this map line
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	// copy the line (including spaces - they're valid!)
	while (i < len)
	{
		line[i] = buffer[start + i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	parse_map_section(char *buffer, int map_start, int total_size, t_game *game)
{
	int	line_count;
	int	i;
	int	line_start;
	int	current_line;

	i = map_start;
	line_start = map_start;
	current_line = 0;
	printf("\n=== MAP PARSING ===\n");
	// first count how many lines we need
	line_count = count_map_lines(buffer, map_start, total_size);
	printf("Found %d map lines\n", line_count);
	// allocate array for map lines
	game->map = malloc(sizeof(char *) * (line_count + 1));
	if (!game->map)
		return (0);
	// parse each map line
	while (i <= total_size && current_line < line_count)
	{
		if (buffer[i] == '\n' || i == total_size)
		{
			// copy this line to our map array
			game->map[current_line] = copy_map_line(buffer, line_start, i);
			if (!game->map[current_line])
				return (0);
			printf("Map line %d: '%s'\n", current_line,
				game->map[current_line]);
			current_line++;
			line_start = i + 1;
		}
		i++;
	}
	// null terminate the array
	game->map[current_line] = NULL;
	printf("=== MAP PARSING COMPLETE ===\n");
	return (1);
}

// updated main parsing function - now handles map too
int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	buffer[1000];
	int		bytes_read;
	int		i;
	int		line_start;
	int		map_start;
	char	temp;

	i = 0;
	line_start = 0;
	map_start = -1;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (0);
	}
	bytes_read = read(fd, buffer, 999);
	buffer[bytes_read] = '\0';
	close(fd);
	printf("=== FILE CONTENT ===\n");
	printf("%s", buffer);
	printf("=== END FILE ===\n");
	printf("\n=== PARSING TEXTURES & COLORS ===\n");
	// first pass - parse textures and colors
	while (i < bytes_read)
	{
		if (buffer[i] == '\n' || i == bytes_read - 1)
		{
			temp = buffer[i];
			buffer[i] = '\0'; // end the line temporarily
			// check if this line has texture/color info
			if (line_start < i && (buffer[line_start] == 'N'
					|| buffer[line_start] == 'S' || buffer[line_start] == 'W'
					|| buffer[line_start] == 'E' || buffer[line_start] == 'F'
					|| buffer[line_start] == 'C'))
			{
				parse_texture_line(&buffer[line_start], &game->textures,
					&game->colors);
			}
			else if (line_start < i && buffer[line_start] != '\0'
				&& buffer[line_start] != ' ')
			{
				// this might be start of map section
				if (map_start == -1)
				{
					map_start = line_start;
					printf("Map section starts at position %d\n", map_start);
				}
			}
			buffer[i] = temp; // restore the character
			line_start = i + 1;
		}
		i++;
	}
	// now parse the map if we found it
	if (map_start != -1)
	{
		if (!parse_map_section(buffer, map_start, bytes_read, game))
		{
			printf("Error: Failed to parse map section\n");
			return (0);
		}
	}
	else
	{
		printf("Error: No map found in file\n");
		return (0);
	}
	return (1);
}

// find player in map and set real coordinates
int	find_player_position(t_game *game)
{
	int	row;
	int	col;
	int	player_found;

	row = 0;
	col = 0;
	player_found = 0;
	printf("\n=== FINDING PLAYER POSITION ===\n");
	// search through entire map for N/S/E/W
	while (game->map[row] && !player_found)
	{
		col = 0;
		while (game->map[row][col] && !player_found)
		{
			if (game->map[row][col] == 'N' || game->map[row][col] == 'S'
				|| game->map[row][col] == 'E' || game->map[row][col] == 'W')
			{
				// found player! set coordinates
				game->player.x = col + 0.5; // center of grid cell
				game->player.y = row + 0.5; // center of grid cell
				// set angle based on direction
				if (game->map[row][col] == 'N')
					game->player.angle = 270.0; // facing north
				else if (game->map[row][col] == 'S')
					game->player.angle = 90.0; // facing south
				else if (game->map[row][col] == 'E')
					game->player.angle = 0.0; // facing east
				else if (game->map[row][col] == 'W')
					game->player.angle = 180.0; // facing west
				printf("Player found at map[%d][%d] = '%c'\n", row, col,
					game->map[row][col]);
				printf("Player coordinates: (%.1f, %.1f) angle: %.1f\n",
					game->player.x, game->player.y, game->player.angle);
				// replace player char with empty space
				game->map[row][col] = '0';
				player_found = 1;
			}
			col++;
		}
		row++;
	}
	if (!player_found)
	{
		printf("Error\nNo player position found in map\n");
		return (0);
	}
	printf("=== PLAYER POSITION SET ===\n");
	return (1);
}

// I DON'T THINK WE'RE EVER USING THIS ANYWHERE ?
// validate map walls - top and bottom rows
int	validate_top_bottom_walls(t_game *game, int map_height, int map_width)
{
	int	col;

	col = 0;
	// check top row
	while (col < map_width)
	{
		if (game->map[0][col] != '1')
		{
			printf("Error\nMap not closed - top wall missing at position %d\n",
				col);
			return (0);
		}
		col++;
	}
	// check bottom row
	col = 0;
	while (col < map_width)
	{
		if (game->map[map_height - 1][col] != '1')
		{
			printf("Error\nMap not closed - bottom wall missing at position %d\n", col);
			return (0);
		}
		col++;
	}
	return (1);
}

// validate map walls - left and right columns
int	validate_left_right_walls(t_game *game, int map_height)
{
	int	row;
	int	line_len;

	row = 0;
	while (row < map_height)
	{
		if (game->map[row][0] != '1')
		{
			printf("Error\nMap not closed - left wall missing at row %d\n",
				row);
			return (0);
		}
		line_len = ft_strlen(game->map[row]);
		if (line_len > 0 && game->map[row][line_len - 1] != '1')
		{
			printf("Error\nMap not closed - right wall missing at row %d\n",
				row);
			return (0);
		}
		row++;
	}
	return (1);
}

// check for invalid characters in map
int	validate_map_characters(t_game *game, int map_height)
{
	int		row;
	int		col;
	char	c;

	row = 0;
	col = 0;
	while (row < map_height)
	{
		col = 0;
		while (game->map[row][col])
		{
			c = game->map[row][col];
			if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
			{
				printf("Error\nInvalid character '%c' in map at [%d][%d]\n", c,
					row, col);
				return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

// validate map - check if surrounded by walls
int	validate_map_walls(t_game *game)
{
	int	map_height;
	int	map_width;

	map_height = 0;
	map_width = 0;
	printf("\n=== VALIDATING MAP ===\n");
	// count map dimensions
	while (game->map[map_height])
		map_height++;
	if (map_height > 0)
		map_width = ft_strlen(game->map[0]);
	printf("Map size: %d x %d\n", map_width, map_height);
	// validate all walls and characters
	if (!validate_top_bottom_walls(game, map_height, map_width))
		return (0);
	if (!validate_left_right_walls(game, map_height))
		return (0);
	if (!validate_map_characters(game, map_height))
		return (0);
	printf("Map validation: PASSED ✅\n");
	printf("=== MAP VALIDATION COMPLETE ===\n");
	return (1);
}

// check file extension
int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	// file must end with .cub
	if (len < 4 || strcmp(filename + len - 4, ".cub") != 0)
	{
		printf("Error\nFile must have .cub extension\n");
		return (0);
	}
	return (1);
}

// updated main parsing function with validation
int	parse_and_validate_cub_file(char *filename, t_game *game)
{
	// check file extension first
	if (!check_file_extension(filename))
		return (0);
	// parse the file (your existing function)
	if (!parse_cub_file(filename, game))
		return (0);
	// find and set player position
	if (!find_player_position(game))
		return (0);
	// validate map structure
	if (!validate_map_walls(game))
		return (0);
	printf("\n🔥 CUB3D PARSING COMPLETE - ALL CHECKS PASSED! 🔥\n");
	return (1);
}
