/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:26:10 by ciusca            #+#    #+#             */
/*   Updated: 2024/03/18 16:04:28 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_all(char *buffer, char *file)
{
	free(buffer);
	free(file);
	file = NULL;
	return (NULL);
}

char	*trim_first_line(char *str)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == '\n')
		i++;
	len = ft_strlen(str);
	len -= i;
	temp = str;
	str = ft_substr(temp, i, len + 1);
	free(temp);
	return (str);
}

char	*get_curr_line(const char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == '\n')
		i++;
	dup = ft_calloc(i + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (str && str[i] != 0 && str[i] != '\n')
	{
		dup[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		dup[i] = '\n';
		dup[i + 1] = 0;
	}
	else
		dup[i] = 0;
	return (dup);
}

char	*find_line(char *file, int fd)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	if (!file)
		file = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!file)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!(ft_strchr(buffer, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_all(buffer, file));
		buffer[bytes_read] = 0;
		temp = file;
		file = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	file = find_line(file, fd);
	if (!file)
		return (NULL);
	line = get_curr_line(file);
	file = trim_first_line(file);
	if (!*line)
	{
		if (file != NULL)
			free(file);
		file = NULL;
		free(line);
		return (NULL);
	}
	if (!file)
		free(line);
	return (line);
}
#include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*next_line;
	int		count;

	count = 0;
	fd = open("example1.txt", O_CREAT);
	next_line = get_next_line(fd);
	count++;
	printf("[%d]:%s\n", count, next_line);
	free(next_line);
	next_line = get_next_line(fd);
	printf("[2]:%s\n", next_line);
	free(next_line);
	close(fd);
	return (0);
}
