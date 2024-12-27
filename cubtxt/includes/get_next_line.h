#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include<unistd.h>
#include<stdlib.h>
#include<stddef.h>
#include<stdio.h>

#define BUFFER_SIZE 5
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char *ft_realloc(char *str, char *buffer);

#endif