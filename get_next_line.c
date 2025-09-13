/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:42:11 by fconde-p          #+#    #+#             */
/*   Updated: 2025/09/13 20:07:10 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	fill_buffer(int fd, char **buffer)
{
	char	*str_slice;
	int		bytes_read;
	char	*ptr_tmp;

	bytes_read = 0;
	str_slice = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (str_slice == NULL)
		return ;
	while (get_nl_char(*buffer) < 0)
	{
		bytes_read = read(fd, str_slice, BUFFER_SIZE);
		str_slice[bytes_read] = '\0';
		ptr_tmp = ft_strjoin(*buffer, str_slice);
		free(*buffer);
		*buffer = ptr_tmp;
		printf("TESTE01: %s\n", *buffer);

		if (bytes_read <= 0)
			break ;
	}
	// if (bytes_read < BUFFER_SIZE) // Control EOF
	// 	*buffer = ft_strjoin(*buffer, str_slice);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	// char		*line;
	// static char	*remain;

	// fill buffer (deal with reading of file)
	buffer = ft_calloc(1, 1);
	fill_buffer(fd, &buffer);
	printf("TESTE02: %s\n", buffer);
	// fill line (start from remain, then with buffer)
	// check remain (if there is remaining, save here for later)

	return ("TESTE");
}
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char	*str;
	int		i;

	str = NULL;
	if (argc != 2)
		return (0);
	int	fd = open(argv[1], O_RDONLY);
	i = 0;
	// while (i < 6)
	// {
	// 	str = get_next_line(fd);
	// 	printf("%s", str);
	// 	free(str);
	// 	i++;
	// }
	str = get_next_line(fd);
	// printf("%s", str);
	free(str);
	return (0);
}