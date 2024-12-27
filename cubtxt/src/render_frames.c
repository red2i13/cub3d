/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:54 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/27 23:25:40 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void floor_ceiling(t_img_info *img, int color1, int color2)
{
    int i;
    int j;
    double alpha;
    double beta;
    int shade_color;

    i = 0;
    alpha = 1;
    beta = 0.000005;
    while (i < img->img_height / 2)
    {
        j = 0;
        alpha += beta;
        shade_color = darken_color(color1, alpha);
        while (j < img->img_width)
        {
            ft_put_pixel(img, j, i, shade_color);
            j++;
        }
        i++;
    }
    alpha = 0.05;
    while (i < img->img_height)
    {
        j = 0;
        alpha += beta;
        while (j < img->img_width)
        {
            shade_color = darken_color(color2, alpha);
            ft_put_pixel(img, j, i, shade_color);
            j++;
        }
        i++;
    }
}

void movement_update(t_data *data)
{
    int check_x;
    int check_y;
    double moveStep;

    
    moveStep = data->player.walkDirection * data->player.moveSpeed;
    check_x = data->player.x + round(cos(deg2rad(data->player.rotationAngle + (90 * data->player.is_move_side))) * moveStep);
    check_y = data->player.y + round(sin(deg2rad(data->player.rotationAngle + (90 * data->player.is_move_side))) * moveStep);
    // printf("walkDirection: %f\n", data->player.walkDirection);
    // printf("rotationAngle: %f\n", data->player.rotationAngle);
    if (data->map[data->player.y / TILE_SIZE][check_x / TILE_SIZE] != '1')
        data->player.x = check_x;
    if (data->map[check_y / TILE_SIZE][data->player.x / TILE_SIZE] != '1')
        data->player.y = check_y;
}

int update(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    movement_update(data);
    printf("data animate weapon = %i\n", data->animate_weapon);
    if (data->animate_weapon)
        animate_weapon_shoting(data, data->all_weapons[data->weapon_numb].shoting_end);
    else if (data->weapon_reload)
        animate_weapon_reload(data, data->all_weapons[data->weapon_numb].shoting_end);
    else
    {
        //render_minimap(data);
        castAllrays(data);
        floor_ceiling(data->game_frame, BLUE, WHITE);
        render_3d_walls(data);
        create_frame(data, 0, 0);
        take_weapon(data);
    }
    // printf("player x: %i\nplayer y: %i\n", data->player.x, data->player.y);
    render_bullets(data);
    //TODO=rays calculation

    //put the image to the window
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    
    return 0;
}