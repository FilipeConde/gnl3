/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:42:11 by fconde-p          #+#    #+#             */
/*   Updated: 2025/09/17 19:45:52 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*tmp;
	size_t	i;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	if (nmemb > (size_t)(-1) / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	tmp = (char *)ptr;
	while (i < nmemb * size)
	{
		tmp[i] = '\0';
		i++;
	}
	return (ptr);
}

int	fill_buffer(int fd, char **buffer)
{
	char	*str_slice;
	int		bytes_read;
	char	*ptr_tmp;

	bytes_read = 0;
	str_slice = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (str_slice == NULL)
		return (1);
	while (get_nl_char(*buffer) < 0)
	{
		bytes_read = read(fd, str_slice, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		str_slice[bytes_read] = '\0';
		ptr_tmp = ft_strjoin(*buffer, str_slice);
		free(*buffer);
		*buffer = ptr_tmp;
	}
	free(str_slice);
	// if (bytes_read < BUFFER_SIZE)
	// 	return (1);
	// return (0);
	return (bytes_read);
}

char	*set_remain(char *buffer)
{
	char	*tmp;
	size_t	nl_index;
	size_t	b_size;

	if (!buffer)
		return (NULL);
	if (ft_strlen(buffer) == 0)
		return (buffer);
	nl_index = 0;
	b_size = (size_t)ft_strlen(buffer);
	nl_index = get_nl_char(buffer);
	tmp = NULL;
	tmp = ft_calloc(b_size - nl_index, sizeof(char));
	ft_strlcpy(tmp, (buffer + (int)nl_index) + 1, b_size - nl_index);
	free(buffer);
	buffer = tmp;
	return (buffer);
}

char	*set_line(char **buffer)
{
	char	*return_ptr;

	return_ptr = NULL;
	if ((get_nl_char(*buffer) >= 0))
	{
		return_ptr = ft_calloc(get_nl_char(*buffer) + 2, sizeof(char));
		ft_strlcpy(return_ptr, *buffer, get_nl_char(*buffer) + 2);
		*buffer = set_remain(*buffer);
	}
	else if (get_nl_char(*buffer) < 0)
	{
		return_ptr = ft_calloc(ft_strlen(*buffer) + 1, sizeof(char));
		ft_strlcpy(return_ptr, *buffer, ft_strlen(*buffer) + 1);
		free(*buffer);
		*buffer = NULL;
	}
	return (return_ptr);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			eof;

	eof = 1;
	if (buffer == NULL)
		buffer = ft_calloc(1, 1);
	if (get_nl_char(buffer) < 0)
		eof = fill_buffer(fd, &buffer);
	if ((eof == 0 && ft_strlen(buffer) == 0) || eof < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = set_line(&buffer);
	return (line);
}
// #include <fcntl.h>
// #include <stdio.h>

// int main(int argc, char *argv[])
// {
// 	char	*str;
// 	int		i;

// 	str = NULL;
// 	if (argc != 2)
// 		return (0);
// 	int	fd = open(argv[1], O_RDONLY);
// 	i = 0;
// 	while (i < 5)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
// 		free(str);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }

// int main(void)
// {
// 	char	*str;

// 	str = NULL;
// 	while ((str = get_next_line(0)) != NULL)
// 	{
// 		printf("Teste: %s", str);
// 		free(str);
// 	}
// 	return (0);
// }