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


/*Headers*/
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"


#endif