#include "../includes/checker.h"

void init_player(t_gdata *data)
{
	data->p->x = data->st_pos[0];
	data->p->y = data->st_pos[1];
	data->p->move_speed = 3.0;
	data->p->radius = 3;
	data->p->turn_dir = 0; //if turn left -1 right 1
	data->p->walk_dir = 0; // move upword 1 move backward -1
	data->p->rot_speed = 3 * M_PI / 180;
	data->p->rot_angle = M_PI / 2;
}

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
				my_mlx_pixel_put(data, cx + x, cy + y, 0xFF00FF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->s, data->win, data->img, 0, 0);
}
void draw_line(t_data *data, int angle, int x, int y)
{

}
/*TASK TO DO
-MAKE A FUNC THAT UPDATE THE VAR OF THE PLAYER
-MAKE A FUNC THAT DRAW A LINE
-BONUS: MAKE A FUNCTION THAT DISPLAY A LINE BASED ON X Y COORDINATES

*/
//protype of the function int (*f)(int keycode, void *param)

int key_press(int keycode, t_player *p)
{
	(void)p;
	printf("THE BUTTON PRESSED %i\n", keycode);
	if(keycode == 119)
		p->walk_dir = 1;
	if(keycode == 115)
		p->walk_dir = -1;
	if(keycode == 100)
		p->turn_dir = -1;
	if(keycode == 97)
		p->turn_dir = 1;
	// printf("walk dir %i\n", p->walk_dir);
	// printf("turn dir %i\n", p->turn_dir);
	return(0);
}
int movement1(int keycode, void *param)
{
	(void)param;
	printf("THE BUTTON RELEASED %i\n", keycode);
	return(0);
}
int main(int ac, char **av)
{
	t_data d;
	t_gdata st;
	t_player p;

	st.p = &p;
	if(ac < 2)
	{
		printf("Please provide the map to the program\n./map_checker [MAP]\n");
		return(1);
	}
	read_map(open(av[1], 0644), &st);
	init_player(&st);
	d.s = mlx_init();
	d.win = mlx_new_window(d.s,  st.map_x * 32, st.map_y * 32, "Cub3d by ysahraou and rbenmakh");
	d.img = mlx_new_image(d.s, st.map_x * 32, st.map_y * 32);
	d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel, &d.line_length, &d.endian);
	//why sleep fix the display of the window ?????
	//usleep(20000);
	// while(1)
	// {
	// 	draw_circle(&d, 100, 100, 3);
	// 	draw_map(&st, &d);
	// 	usleep(10000);
		
	// }
	/*
		UP : 119
		DOWN : 115
		RIGHT: 100
		LEFT: 97
	*/
	mlx_hook(d.win, 2, 1<<0, key_press, &p);
	mlx_hook(d.win, 3, 1<< 1, key_release, &p);
	mlx_hook(d.win, 17, 1L << 0, cross_win, &d);
	mlx_loop(d.s);
	return(0);
}