/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:24:42 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/25 16:06:41 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void create_frame(t_data *data, int fx, int fy)
{
    fx = data->player.x - FRAME_WIDTH / 2;
    fy = data->player.y - FRAME_HEIGHT / 2;
    
    if (fx < 0)
        fx = 0;
    else if (fx > data->minimap_img->img_width)
        fx = data->minimap_img->img_width - FRAME_WIDTH;
    if (fy < 0)
        fy = 0;
    else if (fy > data->minimap_img->img_height)
        fy = data->minimap_img->img_height - FRAME_HEIGHT;
    copy_img(data->minimap_img, data->frame, fx, fy, FRAME_HEIGHT, FRAME_WIDTH);
    rect(data->frame, 0, 0, FRAME_WIDTH, 10, LBAR9O9I);
    rect(data->frame, 0, 0, 10, FRAME_WIDTH, LBAR9O9I);
    rect(data->frame, 0, FRAME_HEIGHT - 10, FRAME_WIDTH, 10, LBAR9O9I);
    rect(data->frame, FRAME_WIDTH - 10, 0, 10, FRAME_HEIGHT, LBAR9O9I);
    // printf("frame width = %i\n", FRAME_WIDTH);
    // printf("frame height = %i\n", FRAME_HEIGHT);
    copy_img(data->frame, data->game_frame, 0, 0, FRAME_HEIGHT, FRAME_WIDTH);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
}

int get_player_y(char **map)
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
                return i;
            j++;
        }
        i++;
    }
    return 1;
}

int get_player_angle(char **map)
{
    int i;
    int j;
    
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'W')
                return W;
            else if (map[i][j] == 'N')
                return N;
            else if (map[i][j] == 'E')
                return E;
            else if (map[i][j] == 'S')
                return S;
            j++;
        }
        i++;
    }
    return 0;
}

void p_setup(t_player *p, char **map)
{
    p->radius = RADIUS;
    p->turnDirection = 0;
    p->walkDirection = 0;
    p->rotationAngle = get_player_angle(map);
    p->moveSpeed = MOVE_SPEED;
    p->rotationSpeed = ROTATION_SPEED + 5.5;
    p->x = (get_player_x(map) * TILE_SIZE) + TILE_SIZE / 2;
    p->y = (get_player_y(map) * TILE_SIZE) + TILE_SIZE / 2;
    p->is_move_side = 0;
}

void draw_line_y(double x, double y, double x1, double y1, t_img_info *img, int color)
{
    double dx;
    double dy;
    double xinc;
    double yinc;
    double steps;
    int i = 0;

    dx = x1 - x;
    dy = y1 - y;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else 
        steps = fabs(dy);
    xinc = dx / steps;
    yinc = dy / steps;
    while (i <= steps)
    {
        ft_put_pixel(img, x, y, color);
        x += xinc;
        y += yinc;
        i++;
    }
}