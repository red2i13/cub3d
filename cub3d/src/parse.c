#include "../includes/checker.h"


int read_map(int fd, t_gdata *data)
{
	char *full;
    char *read;
	char *tmp;
	int j;

    j = 0;
    read = get_next_line(fd);
	full = ft_strdup("\n");
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
	data->map_x = find_longest_row(data->map, data);
	printf("st_pos: %d %d\n", data->st_pos[0], data->st_pos[1]);

	free(full);
	close(fd);
	return(0);
}