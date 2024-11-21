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

/* PSUEDO CODE FOR DRAWING THE CIRCLE
function drawDisc(centerX, centerY, radius):
    for y from -radius to radius:
        for x from -radius to radius:
            // Calculate distance from center
            distance = sqrt(x^2 + y^2)
            
            // If point is inside or on the circle's radius
            if distance <= radius:
                drawPixel(centerX + x, centerY + y)
SECOND METHOD
function drawDisc(centerX, centerY, radius):
    for angle = 0 to 360 degrees:
        // Convert polar coordinates to Cartesian
        x = centerX + radius * cos(angle)
        y = centerY + radius * sin(angle)
        
        // Draw line from center to edge of disc along this radius
        drawLine(centerX, centerY, x, y)
*/
void draw_circle(t_data *data, double cx, double cy, int radius)
{

	double x, y;
	int angle;
	angle =0;
	sleep(1);
	while(angle < 360)
	{
		x = cx + radius * cos(angle * M_PI / 180);
		y = cy + radius * sin(angle * M_PI / 180);
		printf("%f %f\n", x, y);
		// while (x > cx && y > cy)
		// {
		// 	my_mlx_pixel_put(data, cx + (int)x  , cy + (int)y  , 0xFF00FF);
		// 	x--;
		// 	y--;
		// }
		angle++;
	}
	mlx_put_image_to_window(data->s, data->win, data->img, 0, 0);

}
/*TASK TO DO
-MAKE MACROS OF KEYS
-MAKE A FUNC THAT UPDATE THE VAR OF THE PLAYER
-BONUS: MAKE A FUNCTION THAT DISPLAY A LINE BASED ON X Y COORDINATES

*/
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
	//init_player(&st);
	d.s = mlx_init();
	d.win = mlx_new_window(d.s,  st.map_x * 32, st.map_y * 32, "Cub3d by ysahraou and rbenmakh");
	d.img = mlx_new_image(d.s, st.map_x * 32, st.map_y * 32);
	d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel, &d.line_length, &d.endian);
	//why sleep fix the display of the window ?????
	//usleep(20000);
	draw_circle(&d, 100, 100, 105);
	// while(1)
	// {
	// 	draw_map(&st, &d);
	// }
	mlx_hook(d.win, 17, 1L << 0, cross_win, &d);
	mlx_hook(d.win, 3, 1L << 1, close_win, &d);
	mlx_loop(d.s);
	return(0);
}