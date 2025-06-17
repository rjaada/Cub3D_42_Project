/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:58:42 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/17 22:58:46 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	error_duplicate_key(char *key)
{
	printf("Error\nDuplicate key '%s'\n", key);
	return (0);
}

int	error_missing_element(char *element)
{
	printf("Error\nMissing required element '%s'\n", element);
	return (0);
}

int	error_color_range(void)
{
	printf("Error\nColor values must be in range [0-255]\n");
	return (0);
}

int	error_unknown_identifier(char *line)
{
	printf("Error\nUnknown identifier '%.2s'\n", line);
	return (0);
}

int	error_invalid_line(char *line)
{
	printf("Error\nInvalid line: '%.10s'\n", line);
	return (0);
}
