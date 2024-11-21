#ifndef CHECKER_H
#define CHECKER_H


/*Macros*/
#define M_PI acos(-1.0)

/*struct*/
typedef struct node
{
	struct node	*next;
	struct node	*parent;
	int			x;
	int			y;
}				t_node;

typedef struct s_player {
	int x;
	int y;
	int radius;
	int turn_dir;
	int walk_dir;
	double rot_angle;
	double move_speed;
	int rot_speed;
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
	void	*s;
	void	*win;
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;



/*libs headers*/
#include <stdio.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../libft/libft.h"

/*Functions prototype*/
int	find_longest_row(char **map, t_gdata *d);
int read_map(int fd, t_gdata *data);
void draw_map(t_gdata *d, t_data *data);
void free_arr(void **arr, int i);
int	cross_win(t_data *d);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void color_square(int x, int y, int color, t_data *d);
int     close_win(int key_press, t_data *d);
void draw_map(t_gdata *d, t_data *data);
int	bfs(int st_x, int st_y, t_gdata *d, t_data *data);
#endif
