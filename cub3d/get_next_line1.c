#include "get_next_line1.h"
#include<fcntl.h>

char *fill_line_buffer(int fd, char *leftovers, char *buffer, int *flag)
{
	ssize_t nbyte;
	char *tmp;

	nbyte = 1;
	*flag = 0;
	buffer[BUFFER_SIZE] = '\0';
	if(!leftovers)
		leftovers = ft_realloc("", NULL);
	while (nbyte > 0)
	{
		nbyte = read(fd, buffer ,BUFFER_SIZE);
		buffer[nbyte] = '\0';
		tmp = ft_realloc(leftovers, buffer);
		free(leftovers);
		leftovers = ft_realloc(tmp, NULL);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	if (nbyte == 0)
		*flag += 1;
	return (leftovers);
}
char *_set_line(char *line_buffer, ssize_t *index, int *flag)
{
	char *line;
	size_t i;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	*index = i;

	(void)*index;
	(void)flag;
	line = ft_substr(line_buffer, 0, i);
	return(line);
}
char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	char *tmp;
	static char *left;
	static ssize_t i;
	static int flag;

	i = 0;
	if (flag)
	{
		free(left);
		left = NULL;
	}
	printf("get_next_line line content (%p)\n", left);
	if (fd < 0 || BUFFER_SIZE == 0 || flag)
		return(NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!buffer)
		return(NULL);
	left = fill_line_buffer(fd, left, buffer, &flag);
	line = _set_line(left, &i, &flag);
	tmp = ft_substr(left, i + 1, ft_strlen(left));
	free(left);
	left = tmp;
	tmp = NULL;
	free(buffer);
	return (line);
}
int main()
{
	int fd = open("file.txt", O_RDONLY, 0644);
	char *line;
	line = get_next_line(fd);
	printf("result %s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("result %s\n", line);
	line = get_next_line(fd);
	printf("result %s\n", line);
	line = get_next_line(fd);
	printf("result %s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("result %s\n", line);
	line = get_next_line(fd);
	printf("result %s\n", line);
	free(line);
	close(fd);
}