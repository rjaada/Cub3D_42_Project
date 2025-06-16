/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 02:20:48 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/16 02:21:10 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanup_texture_paths(t_game *game)
{
	if (game->textures.north)
		free(game->textures.north);
	if (game->textures.south)
		free(game->textures.south);
	if (game->textures.west)
		free(game->textures.west);
	if (game->textures.east)
		free(game->textures.east);
}

void	cleanup_mlx_textures(t_game *game)
{
	if (game->north_texture)
		mlx_delete_texture(game->north_texture);
	if (game->south_texture)
		mlx_delete_texture(game->south_texture);
	if (game->east_texture)
		mlx_delete_texture(game->east_texture);
	if (game->west_texture)
		mlx_delete_texture(game->west_texture);
}

void	cleanup_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

void	cleanup_game(t_game *game)
{
	cleanup_texture_paths(game);
	cleanup_mlx_textures(game);
	cleanup_map(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
