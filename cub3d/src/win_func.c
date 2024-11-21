#include "../includes/checker.h"


int	cross_win(t_data *d)
{
	mlx_destroy_window(d->s, d->win);
	mlx_destroy_display(d->s);
	free(d->s);
	exit(0);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void color_square(int x, int y, int color, t_data *d)
{
	for(int i = 0; i < 32; i++)
	{
		for(int j = 0; j < 32; j++)
		{
			if(i == 0 || j == 0 || i == 32 -1 || j == 32 -1)
				my_mlx_pixel_put(d, x * 32 + i, y * 32 + j, 0x000000);
			else
				my_mlx_pixel_put(d, x * 32 + i, y * 32 + j, color);
		}
	}
}
int     close_win(int key_press, t_data *d)
{
        if (key_press == 65307)
        {
                cross_win(d);
        }
        return (EXIT_SUCCESS);
}
void draw_map(t_gdata *d, t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(d->map[i])
	{
		j = 0;
		while(d->map[i][j])
		{
			if(d->map[i][j] == '1')
				color_square(j, i, 0x00FF0000, data);
			else if(d->map[i][j] == '0')
				color_square(j, i, 0x00FFFFFF, data);
			else if(d->map[i][j] == '6')
				color_square(j, i, 0x0000FF00, data);
			else if(d->map[i][j] == '5')
				color_square(j, i, 0x000000FF, data);
			else if(d->map[i][j] == 'P')
				color_square(j, i, 0x00FF00FF, data);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->s, data->win, data->img, 0, 0);

}