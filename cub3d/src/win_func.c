#include "../includes/checker.h"


int	cross_win(t_data *d)
{
	mlx_destroy_window(d->s, d->win);
	mlx_destroy_display(d->s);
	free(d->s);
	exit(0);
}
void clear_image(t_data *d)
{
	for(int i = 0; i < W_HEIGHT; i++)
	{
		for(int j = 0; j < W_WIDTH; j++)
		{
			my_mlx_pixel_put(d, j, i, 0x000000);
		}
	}	
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if(x < 0 || y < 0 || x > W_WIDTH || y > W_HEIGHT)
		return;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (dst < data->addr || dst >= data->addr + (data->line_length * 480)) 
		return;
	*(unsigned int*)dst = color;
}
void color_rect(int x, int y, int width, int height, int color, t_data *d)
{
	if(x < 0 || y < 0)
		return;
	// printf("%i %i width %i height %i\n", x, y, width, height);
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			my_mlx_pixel_put(d, x + j, y + i, color);
			// mlx_pixel_put(d->s, d->win, x + j, y + i, color);

		}
	}
}
void color_square(int x, int y, int color, t_data *d)
{
	for(int i = 0; i < T_SIZE * MINIMAP_SCALE_F; i++)
	{
		for(int j = 0; j < T_SIZE * MINIMAP_SCALE_F; j++)
		{
			if(i == 0 || j == 0 || i == T_SIZE * MINIMAP_SCALE_F -1 || j == T_SIZE * MINIMAP_SCALE_F -1)
				my_mlx_pixel_put(d, x * T_SIZE * MINIMAP_SCALE_F + i, y * T_SIZE * MINIMAP_SCALE_F + j, 0x000000);
			else
				my_mlx_pixel_put(d, x * T_SIZE * MINIMAP_SCALE_F + i, y * T_SIZE * MINIMAP_SCALE_F + j, color);
		}
	}
}
int     key_release(int keycode, t_player *p)
{
	(void)p;
	// printf("key released %i\n", keycode);
	if(keycode == 119)
		p->walk_dir = 0;
	if(keycode == 115)
		p->walk_dir = 0;
	if(keycode == 100)
		p->turn_dir = 0;
	if(keycode == 97)
		p->turn_dir = 0;
	// printf("walk dir %i\n", p->walk_dir);
	// printf("turn dir %i\n", p->turn_dir);
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
				color_square(j, i, 0x00F2DDBA, data);
			else if(d->map[i][j] == '0')
				color_square(j, i, 0x00FFFFFF, data);
			else if(d->map[i][j] == '6')
				color_square(j, i, 0x0000FF00, data);
			else if(d->map[i][j] == '5')
				color_square(j, i, 0x000000FF, data);
			else if(d->map[i][j] == 'P')
				color_square(j, i, 0x00FFFFFF, data);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->s, data->win, data->img, 0, 0);

}