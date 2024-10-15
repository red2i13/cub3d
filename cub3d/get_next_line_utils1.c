#include"get_next_line1.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)s + len);
	return (NULL);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0 || dstsize < i)
		return (dstsize + ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

char *ft_realloc(char *str, char *buffer)
{
	char *tmp;
	int tot;
	int i = 0;
	int j = 0;

	tot = ft_strlen(str);
	if (buffer)
		tot += ft_strlen(buffer);
	tmp = malloc(sizeof(char) * (tot + 1));	
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	while (buffer && buffer[j])
	{
		tmp[i++] = buffer[j++];
	}
	tmp[i] = '\0';
	return (tmp);
}

// char	*ft_strdup(const char *s)
// {
// 	size_t	len;
// 	char	*ptr;
// 	size_t	i;

// 	len = 0;
// 	i = 0;
// 	while (s[len])
// 		len++;
// 	ptr = malloc((len + 1) * sizeof(char));
// 	if (ptr == NULL)
// 		return (0);
// 	while (i < len)
// 	{
// 		ptr[i] = s[i];
// 		i++;
// 	}
// 	return (ptr);
// }