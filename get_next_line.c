/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:25:44 by iel-moha          #+#    #+#             */
/*   Updated: 2021/12/15 13:06:02 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int check_newline(char *buffer)
{
    int i;
    
    i = 0;
    while(buffer[i])
    {
       if(buffer[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}
/*char    *get_new_line(int fd)
{
    char    *buffer;

    buffer = (char *)malloc(BUFFER_SIZE);
    if(!buffer)
        return (NULL);
    read(fd, buffer, BUFFER_SIZE);
    if(check_newline(buffer) == 1)
        printf("This is a line");
    else
        printf("This is not a line");
    return (buffer);    
}*/
char    *get_next_line(int fd)
{
    static char *str;
    char    *line;
    char    *buffer;
    int i;

    buffer = (char *)malloc(BUFFER_SIZE);
    if(!buffer)
        return (NULL);
    read(fd, buffer, BUFFER_SIZE);
    while(!check_newline(buffer))
    {
        read(fd, buffer, BUFFER_SIZE);
        i++;
    }
    line = (char * )malloc((i*BUFFER_SIZE) + 1);
    return (buffer);
}
int main()
{
    int fd;

    char *s;
    fd = open("Imoon.txt", O_RDONLY);
    s = get_next_line(fd);
    printf("%s", s);
    //system("leaks a.out");
}