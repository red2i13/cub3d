/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:08:50 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/24 10:21:12 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int render_bullets(t_data *data)
{
    if (data->all_weapons[data->weapon_numb].ammo_numb == 0)
        copy_img_sprite(data->no_bullet, data->game_frame, 0, 0, data->no_bullet->img_height, data->no_bullet->img_width);
    else
        copy_img_sprite(data->bullet, data->game_frame, 0, 0, data->bullet->img_height, data->bullet->img_width);
    return 0;
}

unsigned int get_px_color(t_img_info *img, int x, int y)
{
    char *pxl;

    pxl = 0;
    if (x >= 0 && x < img->img_width && y >= 0 && y < img->img_height)
    {
        pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    }
    if (pxl == 0)
        return 6;
    return *(unsigned int *)pxl;
}


void copy_img(t_img_info *src, t_img_info *dest, int x, int y, int height, int width)
{
    int i;
    int j;
    int xc;

    i = 0;
    while (i < height)
    {
        j = 0;
        xc = x;
        while (j < width)
        {
            ft_put_pixel(dest, j, i, get_px_color(src, xc, y));
            xc++;
            j++;
        }
        y++;
        i++;
    }
}

void copy_img_sprite(t_img_info *src, t_img_info *dest, int x, int y, int height, int width)
{
    int i;
    int j;
    int xc;
    int color;

    i = 0;
    while (i < height)
    {
        j = 0;
        xc = x;
        while (j < width)
        {
            color = get_px_color(src, xc, y);
            if (color != 65535 && color != 592187 && color != -16777216)
                ft_put_pixel(dest, j, i, color);
            xc++;
            j++;
        }
        y++;
        i++;
    }
}
