/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:25:44 by iel-moha          #+#    #+#             */
/*   Updated: 2021/12/15 18:23:43 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

short check_newline(char *buffer)
{
    short i;
    
    i = 0;
    while(buffer[i])
    {
       if(buffer[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
    if(!s1)
    {
        s1 = malloc(1);
        *s1 = '\0';
    }
	new = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		new[i] = (char)s1[i];
		i++;
	}
	j = 0;
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		new[i] = (char)s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
    free(s1);
	return (new);
}

char    *get_next_line(int fd)
{
    char    *line;
    static char *buffer;
    int i;

    buffer = (char *)malloc(BUFFER_SIZE + 1);
    if(!buffer)
        return (NULL);
    line = malloc(1);
    while(i && !check_newline(line))
    {
        i = read(fd, buffer, BUFFER_SIZE);
        if (i == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[i] = '\0';
        line = ft_strjoin(line, buffer);
    }
    free(buffer);
    return (line);
}
int main()
{
    int fd;

    char *s;
    fd = open("t.txt", O_RDONLY);
    s = get_next_line(fd);
    printf("%s", s);
    printf("%s", get_next_line(fd));
    //system("leaks a.out");
}