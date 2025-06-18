/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:59:06 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/18 23:20:06 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_color_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (error_color_range());
	return (1);
}

int	is_valid_config_line(char *line)
{
	if ((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E') || (line[0] == 'E'
			&& line[1] == 'A') || (line[0] == 'F' && line[1] == ' ')
		|| (line[0] == 'C' && line[1] == ' '))
		return (1);
	if (line[0] == '\0' || line[0] == ' ')
		return (1);
	return (error_unknown_identifier(line));
}

int	check_duplicate_key(char *line, t_seen_keys *seen)
{
	if (line[0] == 'N' && line[1] == 'O' && seen->has_north++)
		return (error_duplicate_key("NO"));
	if (line[0] == 'S' && line[1] == 'O' && seen->has_south++)
		return (error_duplicate_key("SO"));
	if (line[0] == 'W' && line[1] == 'E' && seen->has_west++)
		return (error_duplicate_key("WE"));
	if (line[0] == 'E' && line[1] == 'A' && seen->has_east++)
		return (error_duplicate_key("EA"));
	if (line[0] == 'F' && line[1] == ' ' && seen->has_floor++)
		return (error_duplicate_key("F"));
	if (line[0] == 'C' && line[1] == ' ' && seen->has_ceiling++)
		return (error_duplicate_key("C"));
	return (1);
}

int	validate_all_required_elements(t_seen_keys *seen)
{
	if (!seen->has_north)
		return (error_missing_element("NO"));
	if (!seen->has_south)
		return (error_missing_element("SO"));
	if (!seen->has_west)
		return (error_missing_element("WE"));
	if (!seen->has_east)
		return (error_missing_element("EA"));
	if (!seen->has_floor)
		return (error_missing_element("F"));
	if (!seen->has_ceiling)
		return (error_missing_element("C"));
	return (1);
}
