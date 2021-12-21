#include "get_next_line.h"
int check_newline(char *buffer)
{
    int i;

    i = 0;
    if(!buffer)
        return (0);
    while(buffer[i])
    {
       if(buffer[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}
char    *get_next_line(int fd)
{
    char    *buffer;
    char    *tmp;
    int i;

    i = 1;
    tmp = malloc(BUFFER_SIZE + 1);
    if(!tmp)
        return (NULL);
    while(i && !check_newline(tmp)) 
    {
        i = read(fd, tmp, BUFFER_SIZE);
        //buffer = ft_strjoin(buffer, tmp);
    }
    return (tmp);
}
int main()
{
    int fd = open("Imoon.txt", O_RDONLY);
    printf("%s\n", get_next_line(fd));
    //printf("%s\n", get_next_line(fd));
    //printf("%s", get_next_line(fd));
    //printf("%s", get_next_line(fd));
    //printf("%s", get_next_line(fd));
    //system("leaks a.out");
}