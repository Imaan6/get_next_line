/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:25:44 by iel-moha          #+#    #+#             */
/*   Updated: 2021/12/21 12:06:50 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (!s)
		return (NULL);
	/*if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));*/
	sub_s = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_s[i] = (char)s[start];
		i++;
		start++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}

int    ft_strlen(char *s)
{
    int    i;

    i = 0;
    if(!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

int check_newline(char *buffer)
{
    int i;

    i = 0;
    if(!buffer)
        return (-1);
    while(buffer[i])
    {
       if(buffer[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char    *ft_strjoin(char *s1, char *s2)
{
    char    *new;
    int i;
    int j;

    // if (!s1 && !s2)
    //     return (NULL);
    if(!s1)
    {
        s1 = malloc(1);
        s1[0] = 0;
    }
    new = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[j])
        new[i++] = s1[j++];
    j = 0;
    while (s2[j])
        new[i++] = s2[j++];
    new[i] = '\0';
    free(s1);
    return (new);
}
char	*ft_strdup(char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	dup = malloc((i + 1) * sizeof (char));
	if (dup == 0)
		return (0);
	dup[i] = '\0';
	while (i >= 0)
	{
		dup[i] = s1[i];
		i--;
	}
	return (dup);
}
char    *get_line(int fd, char *buffer)
{
    char    *tmp;
    
    int i;

    i = 1;
    tmp = malloc(BUFFER_SIZE + 1);
    if(!tmp)
        return (NULL);
    //line = malloc(1);
    while(i && check_newline(buffer) == -1) 
    {
        i = read(fd, tmp, BUFFER_SIZE);
        if (i == -1)
        {
            free(tmp);
            return (NULL);
        }
        tmp[i] = '\0';
        buffer = ft_strjoin(buffer, tmp);
    }  
    free(tmp);
    return (buffer);
}
char    *before_line(char *s)
{
    int i;
    char *p;

    i = 0;
    if (!s[i])
    {
        free(s);
        return (NULL);
    }
    while(s[i] && s[i] != '\n')
        i++;
    if (s[i])
        i++;    
    p = ft_substr(s, i, (ft_strlen(s) - i));
    free(s);
    //printf("%s", p);
    return (p);
}
char    *one_line(char *s)
{
    char    *p;
    int i;
    int j;
    
    i = 0;
    j = 0;
    if (!s[i])
        return (NULL);
    while(s && s[i] && s[i] != '\n')
        i++;
    if (s[i])
        i++;
    p = malloc(i + 1);
    while(s[j] && s[j] != '\n')
    {
        p[j] = s[j];
        j++;
    }
    if(s[j] == '\n')
        p[j++] = '\n';
    p[j] = '\0';
    //p = ft_strjoin(s, p);
    return (p);    
}
char    *get_next_line(int fd)
{
    static char *saved;
    char    *line;

    if (BUFFER_SIZE <= 0 || fd < 0)
        return (NULL);
    saved = get_line(fd, saved);
    //printf("[%s]", s);
    if(!saved)
       return (NULL);
    line = one_line(saved);
    saved = before_line(saved);
    return(line);
}
// int main()
// {
//     int fd = open("Imoon.txt", O_RDONLY);
//     char *a = get_next_line(fd);
//     char *b = get_next_line(fd);
//     printf("%s", a);
//     printf("%s", b);

//     //printf("%s", get_next_line(fd));
//     //printf("%s", get_next_line(fd));
//     //printf("%s", get_next_line(fd));
//     close(fd);
//     system("leaks a.out");
// }