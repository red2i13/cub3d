#ifndef CUB3D_H
#define CUB3D_H


/*Structs*/
typedef struct node
{
	struct node	*next;
	struct node	*parent;
	int			x;
	int			y;
}				t_node;

typedef struct s_gdata
{
	char **map;
	int c[3];
	int f[3];
	char *texures[4];
	int res_x;
	int res_y;
	int map_x;
	int map_y;
}				t_gdata;
/*Headers*/
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"

/*Enums*/
enum IDENTIFIERS
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
};

#endif