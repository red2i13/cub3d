#ifndef CHECKER_H
#define CHECKER_H

// Basic Colors
#define BLACK       0x000000
#define WHITE       0xFFFFFF
#define RED         0xFF0000
#define GREEN       0x00FF00
#define BLUE        0x0000FF

// Shades of Red
#define DARK_RED    0x8B0000
#define LIGHT_RED   0xFF6347

// Shades of Green
#define DARK_GREEN  0x006400
#define LIME_GREEN  0x32CD32

// Shades of Blue
#define DARK_BLUE   0x00008B
#define NAVY        0x000080
#define SKY_BLUE    0x87CEEB

// Yellows and Oranges
#define YELLOW      0xFFFF00
#define GOLD        0xFFD700
#define ORANGE      0xFFA500

// Purples and Magentas
#define PURPLE      0x800080
#define MAGENTA     0xFF00FF
#define VIOLET      0x9400D3

// Cyan and Teals
#define CYAN        0x00FFFF
#define TEAL        0x008080

// Browns
#define BROWN       0xA52A2A
#define CHOCOLATE   0xD2691E

// Grays
#define GRAY        0x808080
#define LIGHT_GRAY  0xD3D3D3
#define DARK_GRAY   0x404040
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
#define T_SIZE 64
#define FOV 60 * (M_PI / 180)
#define WALL_STRIP_WIDTH 8
#define NUM_RAYS W_WIDTH/WALL_STRIP_WIDTH
#define MINIMAP_SCALE_F 0.2
// #define MINIMAP_SCALE_F 1.8

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
	double rot_speed;
	t_ray *r;

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
int		bfs(int st_x, int st_y, t_gdata *d, t_data *data);
int		cross_win(t_data *d);
int     key_release(int keycode, t_player *p);
int 	darken_color(int original_color, float darkness_factor);
int 	create_trgb(int t, int r, int g, int b);
void 	clear_image(t_data *d);
void	draw_map(t_gdata *d, t_data *data);
void	free_arr(void **arr, int i);
void	draw_line(t_data *data, int x, int y, int x1, int y1);
void	draw_test(t_data *data, double angle, int x, int y);
void	draw_circle(t_data *data, double cx, double cy, float radius);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void 	color_square(int x, int y, int color, t_data *d);
void 	color_rect(int x, int y, int width, int height, int color, t_data *d);
void 	draw_map(t_gdata *d, t_data *data);
#endif
