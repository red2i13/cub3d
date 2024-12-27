/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/27 23:24:16 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void init_bullet(t_data *data)
{
    data->bullet = malloc(sizeof(t_img_info));
    data->no_bullet = malloc(sizeof(t_img_info));
    data->no_bullet->img_width = 64;
    data->no_bullet->img_height = 64;
    data->bullet->img_width = 64;
    data->bullet->img_height = 64;
    data->bullet->img = mlx_xpm_file_to_image(data->mlx, "./textures/bullet/bullet.xpm", &data->bullet->img_width, &data->bullet->img_height);
    data->no_bullet->img = mlx_xpm_file_to_image(data->mlx, "./textures/bullet/no_bullet.xpm", &data->no_bullet->img_width, &data->no_bullet->img_height);
    data->bullet->addr = mlx_get_data_addr(data->bullet->img, &data->bullet->bits_per_pixel, &data->bullet->line_length, &data->bullet->endian);
    data->no_bullet->addr = mlx_get_data_addr(data->no_bullet->img, &data->no_bullet->bits_per_pixel, &data->no_bullet->line_length, &data->no_bullet->endian);
}

int main(int argc, char **argv)
{
    t_data data;
    
    if (argc != 2)
        return printf("Error There is no map\n");
    else
        printf("map name : %s\n", argv[1]);
    if(!setup(argc, argv, &data))
    {
        printf("false map\n");
        return(1);
    }
    intialize_data(&data, data.map, 0, 0);
    init_weapon_names(&data);
    init_weapons(&data);
    p_setup(&data.player, data.map);
    init_bullet(&data);
    //debug
    data.iii = malloc(sizeof(t_img_info));
    data.iii->img_width = 64;
    data.iii->img_height = 64;
    data.iii->img = NULL;
    data.iii->img = mlx_xpm_file_to_image(data.mlx, "./wall_txtures/Door1.xpm", &data.iii->img_width, &data.iii->img_height);
    if (data.iii->img == NULL)
    {
        printf("Error loading image\n");
        return (1);
    }
    data.iii->addr = mlx_get_data_addr(data.iii->img, &data.iii->bits_per_pixel, &data.iii->line_length, &data.iii->endian);
    mlx_hook(data.mlx_win, ON_DESTROY, 0, close_win, &data);
    mlx_hook(data.mlx_win, ON_KEYDOWN, 1L << 0, key_p, &data);
    mlx_hook(data.mlx_win, ON_KEYUP, 1L << 1, key_r, &data);
    mlx_hook(data.mlx_win, ON_MOUSEDOWN, 1L << 2, mouse_down, &data);
    mlx_hook(data.mlx_win, ON_MOUSEMOVE, 1L << 6, mouse_hook, &data);
    mlx_loop_hook(data.mlx, update, &data);
    mlx_loop(data.mlx);
    return (0);
}
