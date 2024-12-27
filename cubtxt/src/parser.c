/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:23:40 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/12/25 11:58:45 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
/*
	- CHECK THE BOUNDARIES OF THE MAP
	TODO : flood fill to check if the map is open
	-UPDATE THE STRUCT WITH 2D MAP
*/
//check the edges of the map
int	find_longest_row(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}
int check_boundaries(char **map, size_t map_h)
{
	size_t i;
	size_t j;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(i == 0 || i == map_h - 1)
			{
				if(map[i][j] != '1' && map[i][j] != ' ')
					return(false);
			}
			if(j == 0 || j == ft_strlen(map[i]) - 1)
			{
				if(map[i][j] != '1' && map[i][j] != ' ')
					return(false);
			}
			j++;
		}
		i++;
	}
	return(true);
}
int line_processing(char *str, int *item, int mod)
{
	while (*str)
	{
		if(mod &&( *str != 'N' &&  *str != 'E' &&  *str != 'W' &&  *str != 'S' && *str != '0' && *str != '1' && *str != ' ' && *str != '\n' && *str != 'D'))
			return(false);
		if(item && (*str == 'N' || *str == 'E' ||  *str == 'W' ||  *str == 'S'))
			*item += 1;
		if(ft_strnstr(str, "NO ", 3))
			return(2);
		else if(ft_strnstr(str, "EA ", 3))
			return(3);
		else if(ft_strnstr(str, "WE ", 3))
			return(4);
		else if(ft_strnstr(str, "SO ", 3))
			return(5);
		else if(ft_strnstr(str, "C ", 2))
			return(6);
		else if(ft_strnstr(str, "F ", 2))
			return(7);
		else if(!mod)
			return(false);
		str++;
	}
	return(true);
}
void print_map(char **str)
{
	for(int i =0; str[i]; i++)
	{
		printf("%s\n", str[i]);
	}
}

//make function that gets the player position
void get_player(char **map, int *x, int *y)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
			{
				*x = i;
				*y = j;
				return;
			}
			j++;
		}
		i++;
	}
	return;
}
//free the int array
void free_arr(void **arr, int i)
{
	if(!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
//function that check each cell of the map and look in all directions if it is open
int check_map(char **map)
{
	size_t i;
	size_t j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(map[i][j] == '0')
			{
				if(j == 0 ||(j > 0 && map[i][j - 1] == ' ') || (j > 0 && map[i][j + 1] == ' ') \
				|| (j > 0 && map[i][j + 1] == '\0')|| i == 0 || (i > 0 && map[i - 1][j] == ' ' )\
				|| (i > 0 && map[i+1] && j<= ft_strlen(map[i+1]) && map[i + 1][j] == ' ') \
				|| (i > 0 && map[i+1] && j <= ft_strlen(map[i+1]) && map[i + 1][j] == '\0')\
				|| (i > 0 && j > ft_strlen(map[i - 1])) || (i > 0 && map[i+1] && j > ft_strlen(map[i + 1])))
					return(false);
			}
			j++;
		}
		i++;
	}
	return(true);
}
int read_map(int fd, t_data *data)
{
	char *full;
    char *read;
	char *tmp;
	int item;
	int j;

    j = 0;
	item = 0;
    read = get_next_line(fd);
	full = ft_strdup("\n");
	while (read)
	{
		if(read[0] == '\n')
		{
			free(read);
			read = get_next_line(fd);
			continue;
		}
		//parse each line of the map if it contains only 1, 0, N, S, E, W
		if(!line_processing(read, &item, 1))
		{
			free(read);
			free(full);
			close(fd);
			return(false);
		}
		//if not return 1
		tmp = full;
		full = ft_strjoin(full, read);
		free(read);
		free(tmp);
		read = get_next_line(fd);
		j++;
	}
	if(!item || item > 1)
	{
		free(full);
		close(fd);
		return(false);
	}

	data->map = ft_split(full, '\n');
	//printf map with number of columns
	// for (int i = 0; data->map[i]; i++)
	// {
	// 	printf("map[%d] = %s\n", i, data->map[i]);
	// }
	// exit(1);
	free(full);
	int start_x;
	int start_y;

	start_x =0;
	start_y = 0;
	data->map_y = j;
	data->map_x = find_longest_row(data->map);
	get_player(data->map, &start_y, &start_x);
	// printf("start_x = %d start_y = %d\n", start_x, start_y);
	//change bfs to function that check each cell and look in all directions if it is open
	if(!check_map(data->map))
	{
		printf("check map is false\n");
		free_arr((void **)data->map, j);
		return(false);
	}
	close(fd);
	print_map(data->map);
	return(true);
}
void print_char_arr(char **arr)
{
	for(int i = 0; arr[i]; i++)
	{
		printf("%d %s\n", i,arr[i]);
	}
}
//memset the array of textures with 0
void init_textures(char **arr)
{
	for(int i = 0; i < 7; i++)
	{
		arr[i] = 0;
	}
}
int create_trgb(int t, int r, int g, int b) 
{
    return (t << 24 | r << 16 | g << 8 | b);
}
int check_color(int mod, char *col, t_data *data)
{
	char **tmp;
	int check;
	int i;
	int c[3];

	i = 0;
	tmp =ft_split(col, ',');
	while (i < 3)
	{
		check = ft_atoi(tmp[i]);
		if(!(check >= 0  && check < 255))
		{
			//free the array
			printf("i am here %i\n", check);
			return(false);
		}
		c[i] = check;
		i++;
	}
	free_arr((void *)tmp, 0);
	if(tmp[i])
		return(false);
	data->color[mod] = create_trgb(0, c[0], c[1], c[2]);
	return(true);
}
int provide_config(t_data *data, char **arr)
{
	char **tmp;
	char *t;
	int i ;
	int j ;
	int op;

	i = 0;
	while (i < 6)
	{
		tmp = ft_split(arr[i], ' ');
		if(!tmp || !tmp[1] || (tmp[1] && tmp[2]))
		{
			//free the array
			return(false);
		}
		t = tmp[1];
		tmp[1] = ft_strtrim(tmp[1], "\n");
		free(t);
		op = open(tmp[1], 0644);
		if(op < 0 && i < 4)
		{
			//free the array
			return(false);
		}
		j = line_processing(arr[i], NULL, 0);
		if(j < 6)
			data->txt[j - 2] = ft_strdup(tmp[1]);
		else
		{
			if(!check_color(i - 4, tmp[1], data))
			{
				//free the array
				return(false);
			}
		}
		i++;
	}
	return(true);
}
int read_textures_colors(t_data *data, int fd)
{
    char *read;
	char *arr[7];
	int ret;
	int tot;


	tot = 0;
    read = get_next_line(fd);
	init_textures(arr);
	while (read)
	{
		if(read[0] == '\n')
		{
			free(read);
			read = get_next_line(fd);
			continue;
		}
		ret = line_processing(read, NULL, 0);
		if(!ret)
		{
			free(read);
			close(fd);
			return(false);
		}
		tot += ret;
		arr[ret-2] = ft_strdup(read);
		free(read);
		if(arr[0] && arr[1] && arr[2] && arr[3] && arr[4] && arr[5])
			break;
		read = get_next_line(fd);
	}
	if(tot > 27)
	{
		//free the arr
		printf("false config\n");
		return(false);
	}
	print_char_arr(arr);
	if(provide_config(data, arr))
	{
		//free the array
		return(false);
	}
	return(true);
}
//print the config
void print_config(t_data *data)
{
	for(int i = 0; i < 4; i++)
	{
		printf("%s\n", data->txt[i]);
	}
	printf("%d\n", data->color[0]);
	printf("%d\n", data->color[1]);
}
int setup(int argc, char **argv, t_data *d)
{
	(void)argc;
	int fd = open(argv[1], 0644);
	if(fd < 0)
		return(false);
	//TODO check file name extension in the config file
	//todo check if there is a gap in the map
	// if(read_textures_colors(d, fd))
	// {
	// 	close(fd);
	// 	printf("false textures\n");
	// 	return(false);
	// }
	// print_config(d);
	if(!read_map(fd, d))
		return(false); 
	return(true);
}