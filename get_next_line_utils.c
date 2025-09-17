/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:41:59 by fconde-p          #+#    #+#             */
/*   Updated: 2025/09/17 18:21:03 by fconde-p         ###   ########.fr       */
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

int	get_nl_char(char *str)
{
	int	nl_index;

	if (str == NULL)
		return (-1);
	nl_index = 0;
	while (str[nl_index] != '\0' && str[nl_index] != '\n')
	{
		nl_index++;
	}
	if (str[nl_index] == '\0')
		nl_index = -1;
	else if (str[nl_index] == '\n')
		return (nl_index);
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_size;
	size_t	s2_size;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if ((s1_size == 0 && s2_size == 0))
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	ptr = ft_calloc((s1_size + s2_size + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, s1_size + 1);
	ft_strlcat(ptr, s2, s1_size + s2_size + 1);
	return (ptr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	expected_len;

	i = 0;
	j = 0;
	expected_len = ft_strlen(dst) + ft_strlen(src);
	if (size == 0)
		return (ft_strlen(src));
	if (ft_strlen(dst) >= size)
		return (ft_strlen(src) + size);
	while (dst[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i++] = src[j++];
	}
	dst[i++] = '\0';
	return (expected_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;

	src_size = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_size);
	while (i < (size - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_size);
}
