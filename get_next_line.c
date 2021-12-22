/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:25:44 by iel-moha          #+#    #+#             */
/*   Updated: 2021/12/22 13:09:59 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*saved;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	saved = get_line(fd, saved);
	if (!saved)
		return (NULL);
	line = one_line(saved);
	saved = before_line(saved);
	return (line);
}
/*int main()
{
    int fd = open("Imoon.txt", O_RDONLY);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));

    //printf("%s", b);

     //printf("%s", get_next_line(fd));
     //printf("%s", get_next_line(fd));
     //printf("%s", get_next_line(fd));
     close(fd);
     //system("leaks a.out");
}*/
