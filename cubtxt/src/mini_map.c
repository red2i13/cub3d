/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:10:37 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/25 10:25:48 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void ft_put_pixel(t_img_info *img, int x, int y, int color)
{
    char *pxl;

    if (x >= 0 && x < img->img_width && y >= 0 && y < img->img_height)
    {
        pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
        *(unsigned int *)pxl = color;
    }
}

int get_player_x(char **map)
{
    int i;
    int j;
    
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' ||map[i][j] == 'W' || map[i][j] == 'E')
                return j;
            j++;
        }
        i++;
    }
    return 1;
}

double deg2rad(double x)
{
	return (x * (M_PI / 180.0));
}

void render_p(t_img_info *img, t_player *p)
{
    int d;
    double x1;
    double y1;

    d = p->radius*2;
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            if (pow(j - p->radius, 2) + pow(i - p->radius,2) <= pow(p->radius,2))
                ft_put_pixel(img, (j+p->x-p->radius)  , (i+p->y-p->radius), 0x00FF0000);
    x1 = p->x + cos(deg2rad(p->rotationAngle)) * LINE_LENGTH;
    y1 = p->y + sin(deg2rad(p->rotationAngle)) * LINE_LENGTH;
    draw_line_y(p->x, p->y, x1 , y1, img, 0x00FF0000);
}


void render_minimap(t_data *data)
{
    render_wall(data->map, data->minimap_img);      
    render_floor(data->map, data->minimap_img);
    render_p(data->minimap_img, &data->player);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap_img->img, 0 , 0);
}