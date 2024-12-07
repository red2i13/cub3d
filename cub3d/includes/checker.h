#ifndef CHECKER_H
#define CHECKER_H


/*libs headers*/
# include <stdio.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"

/*Macros*/
#define W_WIDTH 640
#define W_HEIGHT 480
//#define M_PI acos(-1.0)
#define T_SIZE 120
#define FOV 60 * (M_PI / 180)
#define WALL_STRIP_WIDTH 20
#define NUM_RAYS W_WIDTH/WALL_STRIP_WIDTH
#define MINIMAP_SCALE_F 0.2
/*struct*/
typedef struct node
{
	struct node	*next;
	struct node	*parent;
	int			x;
	int			y;
}				t_node;
typedef struct s_ray
{
	double	angle;
	int		column_id;
	int		hit_x;
	int		hit_y;
	double	distance;
	bool	is_down;
	bool	is_up;
	bool	is_right;
	bool	is_left;
}				t_ray;

typedef struct s_player {
	int x;
	int y;
	int radius;
	int turn_dir;
	int walk_dir;
	double rot_angle;
	double move_speed;
	float rot_speed;
	t_ray *rays;

}				t_player;

typedef struct s_gdata
{
	t_player *p;
	char **map;
	int st_pos[2];
	int c[3];
	int f[3];
	char *texures[4];
	int res_x;
	int res_y;
	int map_x;
	int map_y;
}				t_gdata;

typedef struct s_data {
	t_gdata *gdata;
	void	*s;
	void	*win;
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;




/*Functions prototype*/
int		find_longest_row(char **map, t_gdata *d);
int		read_map(int fd, t_gdata *data);
void	draw_map(t_gdata *d, t_data *data);
void	free_arr(void **arr, int i);
int		cross_win(t_data *d);
void	draw_line(t_data *data, int x, int y, int x1, int y1);
void	draw_test(t_data *data, double angle, int x, int y);
void	draw_circle(t_data *data, double cx, double cy, float radius);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void 	color_square(int x, int y, int color, t_data *d);
int     key_release(int keycode, t_player *p);
void color_rect(int x, int y, int width, int height, int color, t_data *d);
void draw_map(t_gdata *d, t_data *data);
int	bfs(int st_x, int st_y, t_gdata *d, t_data *data);
#endif
