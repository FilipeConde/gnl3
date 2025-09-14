/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:42:11 by fconde-p          #+#    #+#             */
/*   Updated: 2025/09/14 17:07:25 by fconde-p         ###   ########.fr       */
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
		if (bytes_read <= 0)
			break ;
		str_slice[bytes_read] = '\0';
		ptr_tmp = ft_strjoin(*buffer, str_slice);
		free(*buffer);
		*buffer = ptr_tmp;
	}
	if (bytes_read < 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	free(str_slice);
}

char	*set_line(char *remain, char *buffer)
{
	char	*return_ptr;
	char	*tmp;

	return_ptr = NULL;
	tmp = NULL;
	if (!(get_nl_char(remain) < 0))   // if has no '\n' join all
	{
		return_ptr = ft_calloc(get_nl_char(remain) + 2, sizeof(char));
		ft_strlcpy(return_ptr, remain, get_nl_char(remain) + 1);
		return (return_ptr);
	}
	else if (get_nl_char(buffer) >= 0)
		{
			tmp = ft_calloc(get_nl_char(buffer) + 2, sizeof(char));
			ft_strlcpy(tmp, buffer, get_nl_char(buffer) + 2);
			return_ptr = ft_strjoin(remain, tmp);
			free(tmp);
		}
	else if (ft_strlen(buffer))
		return_ptr = ft_strjoin(remain, buffer);
	return (return_ptr);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*remain;

	// fill buffer (deal with reading of file)
	buffer = ft_calloc(1, 1);
	// line = ft_calloc(1, 1);

	// check_remain(*remain);
	if (remain == NULL)
		remain = ft_calloc(1, 1);
		
	if (get_nl_char(remain) < 0)
		fill_buffer(fd, &buffer);
	// join with remain and buffer into line
	line = set_line(remain, buffer);
	free(buffer);
	return (line);
	// return line


	// printf("TESTE02: %s\n", buffer);
	// fill line (start from remain, then with buffer)
	// check remain (if there is remaining, save here for later)
	// check_remain(buffer, &remain, &line);

	return (line);
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
	while (i < 5)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	// str = get_next_line(fd);
	// printf("SAÍDA GERAL GNL =>> %sX", str);
	// free(str);
	return (0);
}