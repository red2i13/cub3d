/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_err_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:11:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/24 11:38:37 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int destroy_img(void *mlx, t_img_info *img)
{
    mlx_destroy_image(mlx, img->img);
    free(img);
    return (0);
}

void free_weapon_imgs(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < WEAPON_N)
    {
        j = 0;
        while (j < data->all_weapons[i].frame_numb)
        {
            free(data->all_weapons[i].weapon[j]->filename);
            destroy_img(data->mlx, data->all_weapons[i].weapon[j]);
            // printf("destroyed the img named %s\n", data->all_weapons[i].weapon[j]->filename);
            j++;
        }
        free(data->all_weapons[i].weapon);
        i++;
    }
    free(data->all_weapons);
}

void free_weapon_names(t_data *data)
{
    int i;

    i = 0;
    while (i < WEAPON_N)
    {
        free(data->weapon_names[i]);
        i++;
    }
    free(data->weapon_names);
}

int close_win(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    mlx_destroy_window(data->mlx, data->mlx_win);
    destroy_img(data->mlx, data->bullet);
    destroy_img(data->mlx, data->no_bullet);
    destroy_img(data->mlx, data->minimap_img);
    destroy_img(data->mlx, data->frame);
    destroy_img(data->mlx, data->game_frame);
    free_weapon_imgs(data);
    free_weapon_names(data);
    //final
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(1);
}