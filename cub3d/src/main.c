#include "../includes/checker.h"

void init_player(t_data *data)
{
	data->player.y = data->gdata->st_pos[0] * T_SIZE + T_SIZE /2;
	data->player.x = data->gdata->st_pos[1] * T_SIZE + T_SIZE /2;
	data->player.move_speed = MOVE_SPEED;
	data->player.radius = 3;
	data->player.turn_dir = 0; //if turn left -1 right 1
	data->player.walk_dir = 0; // move upword 1 move backward -1
	data->player.rot_speed = ROT_SPEED;
	data->player.rot_angle = M_PI / 2;
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
#include <float.h>
#define TRUE 1
#define FALSE 0
#define PI 3.14159265358979323846
#define TWO_PI 6.28318530718
float normalizeAngle(float angle) {
    angle = remainder(angle, TWO_PI);
    if (angle < 0) {
        angle = TWO_PI + angle;
    }
    return angle;
}
float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int mapHasWallAt(float x, float y, char **map) {
    if (x < 0 || x > W_WIDTH || y < 0 || y > W_HEIGHT) {
        return TRUE;
    }
    int mapGridIndexX = floor(x / T_SIZE);
    int mapGridIndexY = floor(y / T_SIZE);
    return (map[mapGridIndexY][mapGridIndexX] != '0');
}
void castRay(float rayAngle, int stripId, t_data *data) {
    rayAngle = normalizeAngle(rayAngle);

    int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    int isRayFacingUp = !isRayFacingDown;

    int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = FALSE;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    // Find the y-coordinate of the closest horizontal grid intersection

    yintercept = floor(data->player.y / T_SIZE) * T_SIZE;
    yintercept += isRayFacingDown ? T_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);
	// printf("player x %d player y %d\n", data->player.x, data->player.y);
	// printf("xintercept %f yintercept %f\n", xintercept, yintercept);
    // Calculate the increment xstep and ystep
    ystep = T_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = T_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= W_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= W_HEIGHT) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

        if (mapHasWallAt(xToCheck, yToCheck, data->gdata->map)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            foundHorzWallHit = TRUE;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = FALSE;
    float vertWallHitX = 0;
    float vertWallHitY = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(data->player.x / T_SIZE) * T_SIZE;
    xintercept += isRayFacingRight ? T_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    yintercept = data->player.y + (xintercept - data->player.x) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    xstep = T_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = T_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= W_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= W_HEIGHT) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;

        if (mapHasWallAt(xToCheck, yToCheck, data->gdata->map)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            foundVertWallHit = TRUE;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    float horzHitDistance = foundHorzWallHit
        ? distanceBetweenPoints(data->player.x, data->player.y, horzWallHitX, horzWallHitY)
        : FLT_MAX;
    float vertHitDistance = foundVertWallHit
        ? distanceBetweenPoints(data->player.x, data->player.y, vertWallHitX, vertWallHitY)
        : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        data->rays[stripId].distance = vertHitDistance;
        data->rays[stripId].wallHitX = vertWallHitX;
        data->rays[stripId].wallHitY = vertWallHitY;
		draw_line(data, data->player.x * MINIMAP_SCALE_F,\
			data->player.y * MINIMAP_SCALE_F,\
			  data->rays[stripId].wallHitX * MINIMAP_SCALE_F,\
			 data->rays[stripId].wallHitY * MINIMAP_SCALE_F);
    } else {
        data->rays[stripId].distance = horzHitDistance;
        data->rays[stripId].wallHitX = horzWallHitX;
        data->rays[stripId].wallHitY = horzWallHitY;
		draw_line(data, data->player.x * MINIMAP_SCALE_F,\
			data->player.y * MINIMAP_SCALE_F,\
			  data->rays[stripId].wallHitX* MINIMAP_SCALE_F,\
			 data->rays[stripId].wallHitY * MINIMAP_SCALE_F) 	;
    }
	// printf("ray %d ray dist %f\n", stripId, data->rays[stripId].distance);
    data->rays[stripId].angle = rayAngle;
    data->rays[stripId].isRayFacingDown = isRayFacingDown;
    data->rays[stripId].isRayFacingUp = isRayFacingUp;
    data->rays[stripId].isRayFacingLeft = isRayFacingLeft;
    data->rays[stripId].isRayFacingRight = isRayFacingRight;
}
void castAllrays(t_data *data)
{
    float rayAngle = data->player.rot_angle - (FOV / 2);

    for (int stripId = 0; stripId < NUM_RAYS; stripId++) {
        castRay(rayAngle, stripId, data);
		// break;
        rayAngle += (double)FOV / (double)(NUM_RAYS -1);
    }
}
//to add 			draw_line(d, p->x * MINIMAP_SCALE_F,
			// p->y * MINIMAP_SCALE_F,
			 //horz_wall_x * MINIMAP_SCALE_F,
			 //horz_wall_y * MINIMAP_SCALE_F)
void render3dprojectd_walls(t_data *d)
{
	double ray_dist;
	double dist_projection_plane;
	double wall_stripe_height;


	for(int i = 0; i < NUM_RAYS; i++)
	{
		ray_dist = d->rays[i].distance;
		// change the ray distance to the corrected one to avoid the fish bowl effetct
		// corrected_dst = ray_dist * cos(ray.angle - p->angle)
		if(ray_dist == 0 || ray_dist < 0)
			continue;
		// dist to the projection plane
		double correctd_dst = ray_dist *  cos(d->rays[i].angle - d->player.rot_angle);
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

	//update_frame_time();
	clear_image(d);
	draw_map(d->gdata, d);
	render3dprojectd_walls(d);
	draw_circle(d,  d->player.x * MINIMAP_SCALE_F , d->player.y * MINIMAP_SCALE_F, 4);
	castAllrays(d);
	mlx_put_image_to_window(d->s, d->win, d->img, 0, 0);

	//make a function for the movement
	d->player.rot_angle += d->player.turn_dir * d->player.rot_speed;
	int move_step;
	move_step = d->player.move_speed * d->player.walk_dir;
	int sx, sy;
	sx = round(move_step * cos(d->player.rot_angle));
	sy = round(move_step * sin(d->player.rot_angle));

	
	d->player.x += sx *(d->gdata->map[d->player.y/T_SIZE][(d->player.x + sx)/T_SIZE ] != '1');
	d->player.y += sy *(d->gdata->map[(d->player.y + sy)/T_SIZE ][d->player.x/T_SIZE] != '1');
	// printf("x %i y %i rot %f\n", d->player.x, d->player.y, d->player.rot_angle);
	return(0);
}
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
	d.gdata = &st;
	init_player(&d);
	d.s = mlx_init();
	d.win = mlx_new_window(d.s,  W_WIDTH, W_HEIGHT, "Cub3d by ysahraou and rbenmakh");
	d.img = mlx_new_image(d.s, W_WIDTH, W_HEIGHT);
	d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel, &d.line_length, &d.endian);

	mlx_hook(d.win, 2, 1<<0, key_press, &d.player);
	mlx_hook(d.win, 3, 1<< 1, key_release, &d.player);
	mlx_hook(d.win, 17, 1L << 0, cross_win, &d);
	mlx_loop_hook(d.s, update, &d);
	mlx_loop(d.s);
	return(0);
}