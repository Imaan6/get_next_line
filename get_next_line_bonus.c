/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:46:50 by iel-moha          #+#    #+#             */
/*   Updated: 2021/12/22 17:08:48 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(int fd, char *saved)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (i && check_newline(saved) == 0)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[i] = '\0';
		saved = ft_strjoin(saved, tmp);
	}
	free (tmp);
	return (saved);
}

char	*before_line(char *s)
{
	int		i;
	char	*p;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free (s);
		return (NULL);
	}
	i++;
	p = ft_substr(s, i, (ft_strlen(s) - i));
	free (s);
	return (p);
}

char	*one_line(char *s)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s[i])
		return (NULL);
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s[i])
		i++;
	p = malloc(i + 1);
	while (s[j] && s[j] != '\n')
	{
		p[j] = s[j];
		j++;
	}
	if (s[j] == '\n')
		p[j++] = '\n';
	p[j] = '\0';
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*saved[10240];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	saved[fd] = get_line(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = one_line(saved[fd]);
	saved[fd] = before_line(saved[fd]);
	return (line);
}
/*int main()
{
    int fd1 = open("Imoon.txt", O_RDONLY);
	int fd2 = open("kinder.txt", O_RDONLY);
	int fd3 = open("Moon.txt", O_RDONLY);
	printf("%s", get_next_line(fd1));
    printf("%s", get_next_line(fd2));
    printf("%s", get_next_line(fd3));
    //printf("%s", get_next_line(fd1));
    //printf("%s", get_next_line(fd2));

    //printf("%s", b);

     //printf("%s", get_next_line(fd));
     //printf("%s", get_next_line(fd));
     //printf("%s", get_next_line(fd));
     //close(fd);
     //system("leaks a.out");
}*/