/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation_v2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:15:41 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/26 09:26:31 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"  

void take_weapon(t_data *data)
{
//     int w_numb;

//     w_numb = data->weapon_numb;
    if (data->all_weapons[data->weapon_numb].ammo_numb == 0 && data->weapon_numb == 2)
        copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[7], data->game_frame, 0, 0, data->all_weapons[data->weapon_numb].weapon[7]->img_height, data->all_weapons[data->weapon_numb].weapon[7]->img_width);
    else
        copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[0], data->game_frame, 0, 0, data->all_weapons[data->weapon_numb].weapon[0]->img_height, data->all_weapons[data->weapon_numb].weapon[0]->img_width);
}


int set_up_animation_delay(int n_frame)
{
    if (n_frame >= 38)
        return (30000);
    else if (n_frame <= 25)
        return (60000);
    return (40000);
}

void animate_weapon_shoting(t_data *data, int end)
{
    int animation_delay;

    if (data->all_weapons[data->weapon_numb].ammo_numb == 0)
    {
        data->animate_weapon = false;
        return;
    }
    animation_delay = set_up_animation_delay(end);
    render_minimap(data);
    castAllrays(data);
    floor_ceiling(data->game_frame, BLUE, WHITE);
    render_3d_walls(data);
    create_frame(data, 0, 0);
    copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[data->frame_index], data->game_frame, 0, 0, data->all_weapons[data->weapon_numb].weapon[data->frame_index]->img_height, data->all_weapons[data->weapon_numb].weapon[data->frame_index]->img_width);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    usleep(animation_delay);
    data->frame_index++;
    if (data->frame_index == end)
    {
        data->animate_weapon = false;
        if (data->all_weapons[data->weapon_numb].ammo_numb != -1)
            data->all_weapons[data->weapon_numb].ammo_numb--;
    }
    data->frame_index = data->frame_index % end;
}


void animate_weapon_reload(t_data *data, int last_end)
{
     int animation_delay;
     int end;
    // printf("ammo_numb = %i\n", data->all_weapons[data->weapon_numb].ammo_numb);
    end = data->all_weapons[data->weapon_numb].frame_numb;
    if (data->all_weapons[data->weapon_numb].ammo_numb == data->all_weapons[data->weapon_numb].default_ammo || data->all_weapons[data->weapon_numb].ammo_numb == -1)
    {
        data->weapon_reload = false;
        return;
    }
    animation_delay = set_up_animation_delay(end - last_end);
    render_minimap(data);
    castAllrays(data);
    floor_ceiling(data->game_frame, BLUE, WHITE);
    render_3d_walls(data);
    create_frame(data, 0, 0);
    copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[data->frame_index + last_end], data->game_frame, 0, 0,\
                     data->all_weapons[data->weapon_numb].weapon[data->frame_index + last_end]->img_height, \
                    data->all_weapons[data->weapon_numb].weapon[data->frame_index + last_end]->img_width);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    usleep(animation_delay);
    data->frame_index++;
    if (data->frame_index + last_end == end)
    {
        data->weapon_reload = false;
        // printf("ammo_numb = %i\n", data->all_weapons[data->weapon_numb].ammo_numb);
        data->all_weapons[data->weapon_numb].ammo_numb = data->all_weapons[data->weapon_numb].default_ammo;
        // printf("ammo_numb = %i\n", data->all_weapons[data->weapon_numb].ammo_numb);
        // printf("default_ammo = %i\n", data->all_weapons[data->weapon_numb].default_ammo);
        data->frame_index = 0;
    }
}