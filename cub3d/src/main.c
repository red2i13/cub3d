#include "../includes/cub3d.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
int check_file_name(char *str)
{
	char *tmp;

	if(!str || str[0] == '.')
		return(1);
	tmp = ft_strchr(str, '.');
	if(!tmp)
		return(1);
	if(ft_strncmp(tmp , ".cub", ft_strlen(str)))
		return(1);
	return(0);
}
int check_type(char **arr, t_gdata *data)
{
	if(!arr)
		return(1);
	if(arr[1] && arr[2] != NULL)
		return(0);
	if(!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
		return(data->texures[0] = ft_strdup(arr[1]), 1);
	else if(!ft_strncmp(arr[0], "SO", ft_strlen(arr[0])))
		return(data->texures[1] = ft_strdup(arr[1]), 1);
	else if(!ft_strncmp(arr[0], "WE", ft_strlen(arr[0])))
		return(data->texures[2] = ft_strdup(arr[1]), 1);
	else if(!ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
		return(data->texures[3] = ft_strdup(arr[1]) ,1);
	else if(!ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
	{
		char **arr2;

		arr2 = ft_split(arr[1], ',');
		if(!arr2)
			return(0);
		data->f[0] = ft_atoi(arr2[0]);
		data->f[1] = ft_atoi(arr2[1]);
		data->f[2] = ft_atoi(arr2[2]);
		free_arr(arr2);
		return (1);
	}
	else if(!ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		char **arr3;

		arr3 = ft_split(arr[1], ',');
		if(!arr3)
			return(0);
		data->c[0] = ft_atoi(arr3[0]);
		data->c[1] = ft_atoi(arr3[1]);
		data->c[2] = ft_atoi(arr3[2]);
		free_arr(arr3);
		return (1);
	}
	return(0);
}

int prs_file(char *path, t_gdata *data)
{
	int fd;
	char *read;
	char **arr;
	int i;

	i = 0;
	arr = NULL;
	fd = open(path, 0644);
	if(fd < 0)
		return(1);
	read = get_next_line(fd);
	while (read)
	{
		arr = ft_split(read, ' ');
		if(!arr || (arr && arr[0] && arr[0][0] == '\n'))
		{
			free(read);
			read = get_next_line(fd);
			continue;
		}
		else if(!check_type(arr, data))
		{
			free_arr(arr);
			break;
		}
		i++;
		free(read);
		free_arr(arr);
		read = get_next_line(fd);
	}
	if(i < 6)
		return(1);
	char *full;
	char *tmp;
	full = ft_strdup("\n");
	int j = 0;
	while (read)
	{
		//parse each line of the map if it contains only 1, 0, N, S, E, W
		//if not return 1
		tmp = full;
		full = ft_strjoin(full, read);
		free(read);
		free(tmp);
		read = get_next_line(fd);
		j++;
	}
	data->map = ft_split(full, '\n');
	data->map_y = j;
	data->map_x = find_longest_row(data->map);
	free(full);
	close(fd);
	return(0);
}
int main(int ac, char **av)
{
	t_gdata data;

	if(ac != 2)
	{
		write(2, "Error\nInvalid number of arguments\n", 35);
		return(1);
	}
	if(check_file_name(av[1]) || prs_file(av[1], &data))
	{
		write(2, "Error\nDescription file is invalid\n", 34);
		return(1);
	}
	
	return (0);
}