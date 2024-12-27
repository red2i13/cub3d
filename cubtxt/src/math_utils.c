/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:23:22 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/12/25 09:38:11 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void draw_circle(t_data *data, double cx, double cy, float radius)
{
	int x, y;
	x= -radius;
	y = -radius;
	while(y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if((x * x) +( y * y) <= (radius * radius))
				ft_put_pixel(data->minimap_img, cx + x, cy + y, 0xFF00FF);
			x++;
		}
		y++;
	}
	// mlx_put_image_to_window(data->s, data->win, data->img, 0, 0);
}
double norm_angle(double angle)
{
	angle = fmod(angle , (2 * M_PI));
	if(angle < 0)
		angle = angle + (2 * M_PI);
	return(angle);
}
double rad2deg(double angle)
{
	return((angle * 180) / M_PI);
}
double calc_dist(long x, long x1, long y , long y1)
{
	long dx, dy;

	dx = x1 - x;
	dy = y1 - y;
	return(sqrt(dx * dx + dy * dy));
}


void draw_line(t_data *data, int x, int y, int x1, int y1)
{
	int dx;
	int dy;
	int sx, sy;
	int p;
	
	dx = x1 - x;
	dy = y1 - y;

	sx = (dx >= 0) * 1 +  (dx < 0) * -1;
	sy = (dy >= 0) * 1 +  (dy < 0) * -1;
	dx = abs(dx); 
	dy = abs(dy);
    if(dx > dy)
	{
		p = 2 * dy - dx;
		while (x != x1 )
		{
			ft_put_pixel(data->minimap_img, x, y, 0x00FF00FF);
			x+=sx;
			if(p >= 0)
				{
				y+=sy;
				p-=2*dx;
			}
			p=p+2*dy;
		}
	}
	else 
	{
		p = 2 * dx - dy; 
		while (y != y1) 
		{ 
			ft_put_pixel(data->minimap_img, x, y, 0x00FF00FF);
			y += sy;
			if (p >= 0)
			{
				x += sx;
				p -= 2 * dy;
			}
				p += 2 * dx; 
		}
	}
}

void draw_line_angle(t_data *data, double angle, int x, int y)
{
	int dx;
	int dy;
	int x1, y1;
	int sx, sy;
	int p;
	
	dx = (int)(cos(angle) * 12);
	dy = (int)(sin(angle) * 12);
	x1 = x + dx;
	y1 = y + dy;
	sx = (dx >= 0) * 1 +  (dx < 0) * -1;
	sy = (dy >= 0) * 1 +  (dy < 0) * -1;
	dx = abs(dx); 
	dy = abs(dy);
    if(dx > dy)
	{
		p = 2 * dy - dx;
		while (x != x1 )
		{
			ft_put_pixel(data->minimap_img, x, y, 0xFF00FF);
			x+=sx;
			if(p >= 0)
				{
				y+=sy;
				p-=2*dx;
			}
			p=p+2*dy;
		}
	}
	else 
	{
		p = 2 * dx - dy; 
		while (y != y1) 
		{ 
			ft_put_pixel(data->minimap_img, x, y, 0xFF00FF);
			y += sy;
			if (p >= 0)
			{
				x += sx;
				p -= 2 * dy;
			}
				p += 2 * dx; 
		}
	}
}