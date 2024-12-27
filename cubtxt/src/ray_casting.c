/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:27:19 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/12/25 17:01:36 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2)
                + pow(y2 - y1, 2) * 1.0);
}

int	is_wall(float x, float y, char **map, t_data *data, int mod)
{
	if(x < 0 || y < 0 || (int)y >= data->minimap_img->img_height  || (int)x >= data->minimap_img->img_width)
		return(1);
	int map_grid_x;
	int map_grid_y;
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	if(ft_strlen(map[map_grid_y]) < (size_t)map_grid_x)
		return(1);
    if (map[map_grid_y][map_grid_x] == 'D' && distance(data->player.x, data->player.y, x, y) <= TILE_SIZE * 2 && mod == 1)
    {
        // printf("You Win\n");
        if (map_grid_x == data->player.x / TILE_SIZE || map_grid_y == data->player.y / TILE_SIZE)
        {
            if (map_grid_x + 1 == data->player.x / TILE_SIZE)
                return(0);
            if (map_grid_x - 1 == data->player.x / TILE_SIZE)
                return(0);
            if (map_grid_y + 1 == data->player.y / TILE_SIZE)
                return(0);
            if (map_grid_y - 1 == data->player.y / TILE_SIZE)
                return(0);
        }
        else 
            return(1);
    }
    return(map[map_grid_y][map_grid_x] == '1' || map[map_grid_y][map_grid_x] == 'D');
}



void castAllrays(t_data *param)
{
    int i;
    double xintercept;
    double yintercept;
    double xstep;
    double ystep;
    int Hhitx = 0;
    int Hhity = 0;
    int Vhitx = 0;
    int Vhity = 0;
    int foundHwallhit;
    int foundVwallhit;
    double Hdistance = 0;
    double Vdistance = 0;
    int px;
    int py;
    double rayAngle;

    rayAngle = param->player.rotationAngle - (FOV / 2);
    i = 0;
    // int count = 0;
    while (i < NUM_RAYS)
    {
        foundHwallhit = 0;
        foundVwallhit = 0;
        Hdistance = 0;
        Hdistance = 0;
        px = 0;
        py = 0;
        rayAngle = normalizeAngle(rayAngle);
        param->rays[i].angle = rayAngle;
        param->rays[i].is_down = rayAngle > 0 && rayAngle < 180;
        param->rays[i].is_up = (rayAngle > 180 && rayAngle < 360);
        param->rays[i].is_right = rayAngle < 90 || rayAngle > 270;
        param->rays[i].is_left = (rayAngle > 90 && rayAngle < 270);
        param->rays[i].column_id = i;


        //horizontal interception
        yintercept = floor(param->player.y / TILE_SIZE) * TILE_SIZE;
        if (param->rays[i].is_down)
            yintercept += TILE_SIZE;
        xintercept = param->player.x + ((yintercept - param->player.y) / tan(deg2rad(rayAngle)));

        //xstep and ystep
        ystep = (double)TILE_SIZE;
        if (param->rays[i].is_up)
            ystep *= -1;
        xstep = (double)TILE_SIZE / tan(deg2rad(rayAngle));
        if (param->rays[i].is_left && xstep > 0)
            xstep *= -1;
        if (param->rays[i].is_right && xstep < 0)
            xstep *= -1;
        if (param->rays[i].is_up)
            py = 1;
        while (xintercept >= 0 && xintercept < param->minimap_img->img_width \
                && yintercept >= 0 && yintercept < param->minimap_img->img_height)
        {
            if(is_wall(xintercept, yintercept - py, param->map, param, 1))
			{
                foundHwallhit = 1;
                Hhitx = xintercept;
                Hhity = yintercept - py;
                break;
            }
            yintercept += ystep;
            xintercept += xstep;
        }

        // vertical interception
        xintercept = floor(param->player.x / TILE_SIZE) * TILE_SIZE;
        if (param->rays[i].is_right)
            xintercept += TILE_SIZE;
        yintercept = param->player.y + (xintercept - param->player.x) * tan(deg2rad(rayAngle));
        // xstep and ystep
        xstep = (double)TILE_SIZE;
        if (param->rays[i].is_left)
            xstep *= -1;
        ystep = (double)TILE_SIZE * tan(deg2rad(rayAngle));
        if (param->rays[i].is_up && ystep > 0)
            ystep *= -1;
        if (param->rays[i].is_down && ystep < 0)
            ystep *= -1;
        if (param->rays[i].is_left)
            px = 1;
        while (xintercept >= 0 && xintercept < param->minimap_img->img_width \
                && yintercept >= 0 && yintercept < param->minimap_img->img_height)
        {
			if(is_wall(xintercept - px, yintercept , param->map, param, 1))
            {
                foundVwallhit = 1;
                Vhitx = xintercept - px;
                Vhity = yintercept;
                break;
            }
            yintercept += ystep;
            xintercept += xstep;
        }
        if (foundHwallhit)
            Hdistance = distance(param->player.x, param->player.y, Hhitx, Hhity);
        else 
            Hdistance = INT_MAX;
        if (foundVwallhit)
            Vdistance = distance(param->player.x, param->player.y, Vhitx, Vhity);
        else 
            Vdistance = INT_MAX;
		Hdistance += Hdistance == 0;
		Vdistance += Vdistance == 0;
        
        if (Hdistance < Vdistance)
        {
            param->rays[i].distance = Hdistance;
            param->rays[i].hit_x = Hhitx;
            param->rays[i].hit_y = Hhity;
            param->rays[i].Was_hit_vertical = 0;
        }
        else
        {
            param->rays[i].distance = Vdistance;
            param->rays[i].hit_x = Vhitx;
            param->rays[i].hit_y = Vhity;
            param->rays[i].Was_hit_vertical = 1;
        }
        draw_line_y(param->player.x , param->player.y ,  param->rays[i].hit_x ,  param->rays[i].hit_y , param->minimap_img, PINK);
        rayAngle += (double)(FOV) / (double)(NUM_RAYS);
        i++;
    }
}