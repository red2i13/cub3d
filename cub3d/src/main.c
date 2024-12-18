#include "../includes/checker.h"

void init_player(t_gdata *data)
{
	data->p->y = data->st_pos[0] * T_SIZE + T_SIZE /2;
	data->p->x = data->st_pos[1] * T_SIZE + T_SIZE /2;
	data->p->move_speed = MOVE_SPEED;
	data->p->radius = 3;
	data->p->turn_dir = 0; //if turn left -1 right 1
	data->p->walk_dir = 0; // move upword 1 move backward -1
	data->p->rot_speed = ROT_SPEED;
	data->p->rot_angle = M_PI / 2;
	data->p->r = NULL;
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
// void cast_ray(t_data *d, int col_id, float ray_angle)
// {
// 	t_ray *rays;

// 	rays = d->gdata->p->r;

	
// }
void calc_rays(t_data *d)
{
	int col_id;
	t_player *p;
	t_ray *rays;

	rays = NULL;
	rays = malloc(sizeof(t_ray) * NUM_RAYS);
	d->gdata->p->r = rays;
	bool found_vert_hit = false;
	bool found_horz_hit = false;
	p = d->gdata->p;
	double ray_angle = p->rot_angle - (FOV / 2.0);
	col_id = 0;
	for(; col_id < NUM_RAYS; col_id++)
	{
		rays[col_id].column_id = col_id;
		found_horz_hit = false;
		found_vert_hit = false;
		rays[col_id].angle = norm_angle(ray_angle);
		rays[col_id].is_down = (rays[col_id].angle > 0) && (rays[col_id].angle < M_PI);
		rays[col_id].is_up = !rays[col_id].is_down;
		if((rays[col_id].angle > M_PI / 2) && (rays[col_id].angle < M_PI * 3/2))
			rays[col_id].is_right = 0;
		else
			rays[col_id].is_right = 1;
		// rays[col_id].is_right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
		rays[col_id].is_left = !rays[col_id].is_right;
		////////////////////////////////////////////////////////////////
		/////////////////horizontal intersection////////////////////////
		////////////////////////////////////////////////////////////////
		float xstep;
		float ystep;
		float x_intercept, y_intercept;

		y_intercept = floor(p->y / T_SIZE)* T_SIZE;
		y_intercept += rays[col_id].is_down  * T_SIZE;
		x_intercept = p->x + (y_intercept - p->y) / tan(rays[col_id].angle);

		ystep = T_SIZE;
		if(rays[col_id].is_up)
			ystep *= -1 ;
		xstep = T_SIZE / tan(rays[col_id].angle);
		if((rays[col_id].is_left && xstep > 0) || (rays[col_id].is_right && xstep < 0))
			xstep *= -1;
		//variable for checking if the intercption point is the wall or not and 
		//adding the case if the ray is facing upword add 1 pixel to be able to check it evenly
		float horz_wall_x, horz_wall_y;
		float check_x, check_y;

		// check_x = x_intercept;
		// check_y = y_intercept;
		float nexthorztouchx = x_intercept;
		float nexthorztouchy = y_intercept;
		
		while (nexthorztouchx <= W_WIDTH && nexthorztouchx >= 0 && nexthorztouchy >= 0)
		{
			// printf("%f %f\n", nexthorztouchx, nexthorztouchy);
			// if(nexthorztouchy > W_HEIGHT)
			// 	printf("Error\n");
			check_x = nexthorztouchx;
			check_y = nexthorztouchy + (rays[col_id].is_up ? -1 : 0);
			if(!mapis_wall(check_x, check_y, d->gdata->map))
			{
				horz_wall_x = nexthorztouchx;
				horz_wall_y = nexthorztouchy;
				found_horz_hit = true;
				break;
			}
			nexthorztouchx += xstep;
			nexthorztouchy += ystep;
		}
		// exit(5);
		////////////////////////////////////////////////////////////////
		/////////////////vertical intersection////////////////////////
		////////////////////////////////////////////////////////////////
		x_intercept =  floor(p->x / T_SIZE) * T_SIZE;
		x_intercept += rays[col_id].is_right * T_SIZE;
		y_intercept = p->y + (x_intercept - p->x) * tan(rays[col_id].angle);

		xstep = T_SIZE;
		if(rays[col_id].is_left)
			xstep *= -1;
		ystep = T_SIZE * tan(rays[col_id].angle);
		if((rays[col_id].is_up && ystep > 0) || (rays[col_id].is_down && ystep < 0))
			ystep *= -1;
		long vert_wall_x, vert_wall_y;
		//long check_x, check_y;

		float nextverttouchx = x_intercept;
		float nextverttouchy = y_intercept;
		while (nextverttouchx <= W_WIDTH && nextverttouchx >= 0 && nextverttouchy >= 0)
		// while ((nextverttouchx >= 0) && (nextverttouchy >= 0))
		{
			check_x = nextverttouchx;
			check_y = nextverttouchy + (rays[col_id].is_left ? -3 : 0);
			// printf("debug %d\n",mapis_wall(check_x, check_y, d->gdata->map));
			// printf("%f %f\n", nextverttouchx, nextverttouchy);
			if(!mapis_wall(check_x, check_y, d->gdata->map))
			{
				vert_wall_x = check_x;
				vert_wall_y = check_y;
				found_vert_hit = true;
				break;
			}
			nextverttouchx += xstep;
			nextverttouchy += ystep;
		}
		//todo make two var if the hit bool is true set the distancd accordernly if not its 0 then check if the distance is greaster than 0 then redner the line
		long dst_vert;
		long dst_horz;

		dst_horz = 0;
		dst_vert = 0;
		if(found_vert_hit) 
		{
			dst_vert = calc_dist(p->x, vert_wall_x, p->y, vert_wall_y);
			dst_horz = __INT_MAX__;
		}	
		if(found_horz_hit){
			dst_horz = calc_dist(p->x, horz_wall_x, p->y, horz_wall_y);
			if(!dst_vert)
				dst_vert = __INT_MAX__;
		}
	
		//todo romove the rendering and render in the while loop
		// printf("deg %f col %i h:%i v:%i d_vert %f d_hor %f\n", rad2deg(rays[col_id].angle), col_id, found_horz_hit, found_vert_hit, dst_vert, dst_horz);
		if((dst_vert < dst_horz) && found_vert_hit)
		{
			draw_line(d, p->x * MINIMAP_SCALE_F,
			p->y * MINIMAP_SCALE_F,
			vert_wall_x * MINIMAP_SCALE_F,
			vert_wall_y * MINIMAP_SCALE_F);
			
			rays[col_id].hit_y = vert_wall_y;
			rays[col_id].hit_x = vert_wall_x;
			rays[col_id].distance = dst_vert;
			rays[col_id].dir_hit = 1;
		
		}
		else if(dst_horz <= dst_vert && found_horz_hit)
		{
			draw_line(d, p->x * MINIMAP_SCALE_F,
			 p->y * MINIMAP_SCALE_F,
			 horz_wall_x * MINIMAP_SCALE_F,
			 horz_wall_y * MINIMAP_SCALE_F)
			;
			rays[col_id].hit_y = horz_wall_y;
			rays[col_id].hit_x = horz_wall_x;
			rays[col_id].distance = dst_horz;
			rays[col_id].dir_hit = 0;
		}
		ray_angle += FOV / (NUM_RAYS - 1);
		// break;
	}
}
void render3dprojectd_walls(t_data *d)
{
	t_ray ray;
	double ray_dist;
	double dist_projection_plane;
	double wall_stripe_height;

	if(!d->gdata->p->r)
		return;
	for(int i = 0; i < NUM_RAYS; i++)
	{
		ray = d->gdata->p->r[i];
		ray_dist = ray.distance;

		// change the ray distance to the corrected one to avoid the fish bowl effetct
		// corrected_dst = ray_dist * cos(ray.angle - p->angle)
		if(ray_dist == 0 || ray_dist < 0)
			continue;
		// dist to the projection plane
		double correctd_dst = ray_dist *  cos(d->gdata->p->r[i].angle - d->gdata->p->rot_angle);
		dist_projection_plane = (W_WIDTH / 2) / tan(FOV / 2);
		//wall heigth of every stripe
		wall_stripe_height = ((double)T_SIZE / (double)correctd_dst) * dist_projection_plane;
		if(wall_stripe_height > W_HEIGHT)
			wall_stripe_height = W_HEIGHT;
		int color = darken_color(VIOLET, 1 - 120/correctd_dst);
		//color = wall_shade_color(ray.dir_hit, VIOLET);
		color_rect(i * WALL_STRIP_WIDTH,
					(W_HEIGHT / 2) - (wall_stripe_height / 2),
					WALL_STRIP_WIDTH,wall_stripe_height, color, d);
	}
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

void draw_test(t_data *data, double angle, int x, int y)
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
void update_frame_time()
{
	size_t st_time = get_current_time();
	while(get_current_time() - st_time < FRAME_TIME_LENGTH);
	//instead of update the var of movement and rotation aribtary make this function return a delta time that will improve the moves
	//last time is st_time
}
int	mapis_wall(float x, float y, char **map)
{
	if(x < 0 || y < 0 || x > W_WIDTH || y > W_HEIGHT)
		return(1);
	int map_grid_x;
	int map_grid_y;

	map_grid_x = floor(x / T_SIZE);
	map_grid_y = floor(y / T_SIZE);
	if(map_grid_y > 10||!map[map_grid_y] )
		return(false);
	// printf("debug %d %d\n", map_grid_x, map_grid_y);
	return(map[map_grid_y][map_grid_x] != '1');
}
int update(t_data *d)
{
	//function that update the frame

	update_frame_time();
	clear_image(d);
	// draw_test(d,  d->gdata->p->rot_angle , d->gdata->p->x * MINIMAP_SCALE_F , d->gdata->p->y * MINIMAP_SCALE_F);
	render3dprojectd_walls(d);
	draw_map(d->gdata, d);
	draw_circle(d,  d->gdata->p->x * MINIMAP_SCALE_F , d->gdata->p->y * MINIMAP_SCALE_F, 4);
	calc_rays(d);
	mlx_put_image_to_window(d->s, d->win, d->img, 0, 0);

	//make a function for the movement
	d->gdata->p->rot_angle += d->gdata->p->turn_dir * d->gdata->p->rot_speed;
	int move_step;
	move_step = d->gdata->p->move_speed * d->gdata->p->walk_dir;
	int sx, sy;
	sx = round(move_step * cos(d->gdata->p->rot_angle));
	sy = round(move_step * sin(d->gdata->p->rot_angle));

	// if(mapis_wall(d->gdata->p->x + sx, d->gdata->p->y + sy, d->gdata->map))
	// {
	// 	d->gdata->p->x += sx;
	// 	d->gdata->p->y += sy;
	// }	
	d->gdata->p->x += sx *(d->gdata->map[d->gdata->p->y/T_SIZE][(d->gdata->p->x + sx)/T_SIZE ] != '1');
	d->gdata->p->y += sy *(d->gdata->map[(d->gdata->p->y + sy)/T_SIZE ][d->gdata->p->x/T_SIZE] != '1');
	
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
	d.win = mlx_new_window(d.s,  W_WIDTH, W_HEIGHT, "Cub3d by ysahraou and rbenmakh");
	d.img = mlx_new_image(d.s, W_WIDTH, W_HEIGHT);
	d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel, &d.line_length, &d.endian);
	d.gdata = &st;

	mlx_hook(d.win, 2, 1<<0, key_press, &p);
	mlx_hook(d.win, 3, 1<< 1, key_release, &p);
	mlx_hook(d.win, 17, 1L << 0, cross_win, &d);
	mlx_loop_hook(d.s, update, &d);
	mlx_loop(d.s);
	return(0);
}