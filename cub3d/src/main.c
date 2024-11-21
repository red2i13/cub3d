#include "../includes/checker.h"

int main(int ac, char **av)
{
	t_data d;
	t_gdata st;

	if(ac < 2)
	{
		printf("Please provide the map to the program\n./map_checker [MAP]\n");
		return(1);
	}
	read_map(open(av[1], 0644), &st);
	d.s = mlx_init();
	d.win = mlx_new_window(d.s,  st.map_x * 32, st.map_y * 32, "Cub3d by ysahraou and rbenmakh");
	d.img = mlx_new_image(d.s, st.map_x * 32, st.map_y * 32);
	d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel, &d.line_length, &d.endian);
	//why sleep fix the display of the window ?????
	usleep(20000);
	draw_map(&st, &d);
	mlx_hook(d.win, 17, 1L << 0, cross_win, &d);
	mlx_hook(d.win, 3, 1L << 1, close_win, &d);
	mlx_loop(d.s);
	return(0);
}