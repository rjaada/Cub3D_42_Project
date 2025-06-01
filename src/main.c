/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:32:59 by rjaada            #+#    #+#             */
/*   Updated: 2025/06/01 16:48:22 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

int key_hook(int keycode, void *param)
{
    (void)param;
    if (keycode == 65307) // ESC key
        exit(0);
    return (0);
}

int main(void)
{
    void *mlx;
    void *win;
    
    mlx = mlx_init();
    if (!mlx)
    {
        printf("Error: MLX init failed\n");
        return (1);
    }
    
    win = mlx_new_window(mlx, 800, 600, "cub3D - First Window!");
    if (!win)
    {
        printf("Error: Window creation failed\n");
        return (1);
    }
    
    // Add hooks to handle window closing
    mlx_hook(win, 17, 0, close_window, NULL); // X button
    mlx_key_hook(win, key_hook, NULL);        // ESC key
    
    printf("SUCCESS! Window created. Press ESC to close.\n");
    mlx_loop(mlx);
    return (0);
}
