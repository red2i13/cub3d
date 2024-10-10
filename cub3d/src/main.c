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
	if
}