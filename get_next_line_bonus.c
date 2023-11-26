/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:41:51 by sel-jadi          #+#    #+#             */
/*   Updated: 2023/11/26 19:26:06 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	if (!str || !str[0])
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(1 + i);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_move_start(char	*str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	i += (str[i] == '\n');
	new_str = (char *)malloc(1 + ft_strlen(str) - i);
	if (!new_str)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		new_str[j] = str[i + j];
		j++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*ft_store(int fd, char *start_str)
{
	int			fd_read;
	char		*tmp;

	tmp = (char *)malloc(1 + BUFFER_SIZE);
	if (!tmp)
		return (NULL);
	fd_read = 1;
	while ((ft_strchr(start_str, '\n')) == 0 && fd_read != 0)
	{
		fd_read = read(fd, tmp, BUFFER_SIZE);
		if (fd_read == -1)
		{
			free(tmp);
			free(start_str);
			return (NULL);
		}
		tmp[fd_read] = '\0';
		start_str = ft_strjoin(start_str, tmp);
	}
	free(tmp);
	return (start_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*start_str[10240];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (NULL);
	start_str[fd] = ft_store(fd, start_str[fd]);
	if (!start_str[fd])
	{
		free(start_str[fd]);
		return (NULL);
	}
	line = ft_line(start_str[fd]);
	start_str[fd] = ft_move_start(start_str[fd]);
	return (line); 
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	char *line;
// 	int fd;
// 	fd = open("test2.txt", O_RDWR | O_CREAT | O_APPEND );
// 	write(fd,"hello\n",6);
// 	close(fd);
// 	fd = open("test2.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s",line);	
// }
// int main()
// {
//     int fd = open("test.txt",O_RDONLY);
//     int l = 0;
//     char *s;
//     while ((s = get_next_line(fd)))
//     {
//         printf("%d ---> %s",l,s);
//         l++;
//     }
// 	// s = get_next_line(fd);
//     // printf(" ---> %s",s);
// 	// s = get_next_line(fd);
//     // printf(" ---> %s",s);
// }
