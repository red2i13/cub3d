/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:25:31 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/27 23:44:05 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

unsigned int darken_color(unsigned int color, double factor) 
{
    if (factor < 0.0) 
        factor = 0.0;
    if (factor > 1.0)
        return color;
    unsigned char r = (color >> 16) & 0xFF; // Extract red
    unsigned char g = (color >> 8) & 0xFF;  // Extract green
    unsigned char b = color & 0xFF;         // Extract blue

    // Apply factor and clamp to [0, 255]
    r = (unsigned char)(r * (1.0 - factor));
    g = (unsigned char)(g * (1.0 - factor));
    b = (unsigned char)(b * (1.0 - factor));

    // Combine back into ARGB format (assuming alpha remains the same)
    return (color & 0xFF000000) | (r << 16) | (g << 8) | b;
}
int get_texture_color(double x, double y, void *texture)
{
    int color;
    char *dst;

    dst = texture + ((int)y * 64 + (int)x) * 4;
    color = *(unsigned int*)dst;
    return (color);
}
void render_3d_walls(t_data *data)
{
    double distanceProjPlane;
    double wallStripHeight;
    double correctDistance;
    int shade_color;
    int color;
    double alpha;

    int i;

    i = 0;
    correctDistance = 0;
    
    while (i < NUM_RAYS)
    {
        color = RED;
        distanceProjPlane = ((double)WINDOW_WIDTH / 2.0) / tan(deg2rad(FOV / 2));
        correctDistance = data->rays[i].distance * cos(deg2rad(data->rays[i].angle) - deg2rad(data->player.rotationAngle));

        alpha = 1.0 - (90.0 / correctDistance);
        // if (data->rays[i].wasHitVertical != 1)
        //     color = RED;
        // else 
        //     color = B_RED;
        if (data->map[(int)data->rays[i].hit_y / TILE_SIZE][(int)data->rays[i].hit_x / TILE_SIZE] == 'D')
            color = GREEN;
        shade_color = darken_color(color, alpha);
        (void)shade_color;
        wallStripHeight = ((double)TILE_SIZE / correctDistance) * distanceProjPlane;
        //todo : make a loop to map the each wall strip to the texture mapping
        //add vars wall_height_top and wall_height_bottom
        double wall_height_top = (WINDOW_HEIGHT / 2) - ((int)wallStripHeight / 2);
        wall_height_top = wall_height_top < 0 ? 0 : wall_height_top;
        double wall_height_bottom = (WINDOW_HEIGHT / 2) + ((int)wallStripHeight / 2);
        wall_height_bottom = wall_height_bottom > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_height_bottom;
       //calculate the offset to acess to the texture buffer
       //create two variable texture_offset_x and  texture_offset_y  
       double texture_offset_x = 0;
       double texture_offset_y = 0;
       if(data->rays[i].Was_hit_vertical)
       {
           texture_offset_x = (int)data->rays[i].hit_y % TILE_SIZE;
       }
       else
       {
           texture_offset_x = (int)data->rays[i].hit_x % TILE_SIZE;
       }
       (void)texture_offset_x;
       (void)texture_offset_y;
    //    printf("texture_offset_x = %f\n", texture_offset_x);
        //color the wall from wall height top to wall height bottom
       for(int j = wall_height_top; j < wall_height_bottom;j++)
       {
            // printf("j = %d\n", j);
            // printf("wall_height_top = %f wall_height_bottom = %f\n", wall_height_top, wall_height_bottom);
           //calculate the texture offset y
           int dst_from_top = j + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
           texture_offset_y = dst_from_top * ((double)TILE_SIZE / (double)wallStripHeight);
        //    printf("texture_offset_y = %f\n", texture_offset_y);
           //get the color from the texture buffer
           //printf("address = %p\n", iiimg.img); 
           //printf("address = %p\n", iiimg.img); 
           //printf("color = %d\n", color);
           color = get_px_color(data->iii,texture_offset_x, texture_offset_y);
           //printf("color = %d\n", color);
           //shade_color = darken_color(color, alpha);
           (void)shade_color;
        //    printf("x %i y %i\n", i, j);
           ft_put_pixel(data->game_frame, i * WALL_STRIP_WIDTH, j, color);             
        }
        // printf("*****************************************\n");

    // rect(data->game_frame, i * WALL_STRIP_WIDTH, (WINDOW_HEIGHT / 2) - ((int)wallStripHeight / 2), WALL_STRIP_WIDTH, (int)wallStripHeight, shade_color);
        i++;
    }
}