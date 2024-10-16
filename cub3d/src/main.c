#include "../includes/cub3d.h"

int check_file_name(char *str)
{
	char *tmp;

	if(!str || str[0] == '.')
		return(1);
	tmp = ft_strchr(str, '.');
	if(!tmp)
		return(1);
	if(ft_strncmp(tmp , ".ber", ft_strlen(str)))
		return(1);
	return(0);
}
int main()
{
	//char str[99];
	// while(1)
	// {
		// str[0] = 'f';
		// scanf("%[^\n]%*c", str);
		// if(!str[0])
		// 	break;
		// printf("func %i\n",check_file_name(str));
	// }
	//int fd = open("Makefile", 0644);
	while (1)
	{
		char *str = get_next_line(0);
		printf("(%s)\n", str);
		if(!str)
			break;
		free(str);
	}
	return (0);
}