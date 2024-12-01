#include "../includes/checker.h"

void init_player(t_gdata *data)
{
	data->p->y = data->st_pos[0] * T_SIZE + T_SIZE /2;
	data->p->x = data->st_pos[1] * T_SIZE + T_SIZE /2;
	data->p->move_speed = 3.0;//2 for linux post
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
double norm_angle(double angle)
{
	angle = fmod(angle , (2 * M_PI));
	if(angle < 0)
		angle = angle + (2 * M_PI);
	return(angle);
}
int rad2deg(double angle)
{
	return((angle * 180) / M_PI);
}
void draw_rays(t_data *d)
{
	int col_id;
	t_player *p;
	t_ray rays[NUM_RAYS];

	float s_ang = p->rot_angle - (FOV / 2.0);
	col_id = 0;
	for(int i = 0; i < NUM_RAYS; i++)
	{
		rays[col_id].angle = norm_angle(s_ang);
		//horizontal intersection
		double xstep;
		double ystep;
		// printf("angle in deg %d\n", rad2deg(norm_angle(s_ang)));
		long ix, iy;

		iy = floor(p->y / T_SIZE) * T_SIZE; 
		ix = p->x + (p->y - iy) / tan(rays[col_id].angle);

		ystep = T_SIZE;
		xstep = T_SIZE / tan(rays[col_id].angle);

		//vertical intersection
		long ix, iy;

		ix = (p->x / T_SIZE) * T_SIZE; 
		ix = p->y + (p->x - ix) / tan(rays[col_id].angle);
		printf("ver %f %f\n", ix, iy);
		xstep = T_SIZE;
		ystep = T_SIZE / tan(rays[col_id].angle);
		//
		col_id++;
		break;
	}




	// (void)col_id;
	// p = d->gdata->p;
	// float incre = FOV / (NUM_RAYS - 1);
	// printf("t %f %f\n", incre * NUM_RAYS, FOV);
	// 	//cast each ray
	// 	draw_line(d, s_ang, p->x, p->y);
	// 	s_ang = s_ang + incre;
	
}
void draw_line(t_data *data, double angle, int x, int y)
{
	int dx;
	int dy;
	int x1, y1;
	int sx, sy;
	int p;
	
	dx = (int)(cos(angle) * 30);
	dy = (int)(sin(angle) * 30);
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
			my_mlx_pixel_put(data, x, y, 0xFF00FF);
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
			my_mlx_pixel_put(data, x, y, 0xFF00FF);
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

/*TASK TO DO
-To calculate the horizantal intersection with the grid (delta'y' / 32) *32 
-Begin chatp 4

-BONUS: MAKE A FUNCTION THAT DISPLAY A LINE BASED ON X Y COORDINATES

*/
//protype of the function int (*f)(int keycode, void *param)

int key_press(int keycode, t_player *p)
{
	(void)p;
	// printf("THE BUTTON PRESSED %i\n", keycode);
	if(keycode == 119)
		p->walk_dir = 1;
	if(keycode == 115)
		p->walk_dir = -1;
	if(keycode == 100)
		p->turn_dir = 1;
	if(keycode == 97)
		p->turn_dir = -1;
	// printf("walk dirc %i\n", p->walk_dir);
	return(0);
}

int update(t_data *d)
{
	draw_map(d->gdata, d);
	draw_circle(d,  d->gdata->p->x , d->gdata->p->y, 4);
	//draw_line(d,  d->gdata->p->rot_angle , d->gdata->p->x , d->gdata->p->y);
		// draw_line(d, M_PI /2, d->gdata->p->x , d->gdata->p->y);
		// draw_line(d, 0      , d->gdata->p->x , d->gdata->p->y);
		// draw_line(d, M_PI   , d->gdata->p->x , d->gdata->p->y);

	draw_rays(d);


	//make a function for the movement
	d->gdata->p->rot_angle += d->gdata->p->turn_dir * d->gdata->p->rot_speed;
	int move_step;
	move_step = d->gdata->p->move_speed * d->gdata->p->walk_dir;
	int sx, sy;
	sx = round(move_step * cos(d->gdata->p->rot_angle));
	sy = round(move_step * sin(d->gdata->p->rot_angle));

	d->gdata->p->x += sx *(d->gdata->map[d->gdata->p->y/T_SIZE][(d->gdata->p->x + sx)/T_SIZE ] != '1');
	d->gdata->p->y += sy *(d->gdata->map[(d->gdata->p->y + sy)/T_SIZE ][d->gdata->p->x/T_SIZE] != '1');
	//
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
	d.win = mlx_new_window(d.s,  st.map_x * T_SIZE, st.map_y * T_SIZE, "Cub3d by ysahraou and rbenmakh");
	d.img = mlx_new_image(d.s, st.map_x * T_SIZE, st.map_y * T_SIZE);
	d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel, &d.line_length, &d.endian);
	d.gdata = &st;


	mlx_hook(d.win, 2, 1<<0, key_press, &p);
	mlx_hook(d.win, 3, 1<< 1, key_release, &p);
	mlx_hook(d.win, 17, 1L << 0, cross_win, &d);
	mlx_loop_hook(d.s, update, &d);
	mlx_loop(d.s);
	return(0);
}