/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:08:35 by ciusca            #+#    #+#             */
/*   Updated: 2023/12/04 17:19:22 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while ((unsigned char)*s != (unsigned char)c && *s)
		s++;
	if (*s == '\0' && (unsigned char)c != '\0')
		return (NULL);
	return ((char *)s);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	int		i;
	int		n;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = -1;
	newstr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (newstr == NULL)
		return (NULL);
	if (!s1 || !s2)
		return (0);
	while (s1[++i] != '\0')
		newstr[i] = s1[i];
	n = i;
	i = -1;
	while (s2[++i] != '\0')
		newstr[n + i] = s2[i];
	newstr[n + i] = '\0';
	return (newstr);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = -1;
	if ((int)start > ft_strlen(s))
	{
		substr = malloc(sizeof(char) * 1);
		if (substr == NULL)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	s += start;
	if (ft_strlen(s) <= (int)len)
		substr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (s[++i] != '\0' && i < len)
		substr[i] = s[i];
	substr[i] = '\0';
	return (substr);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*arr;
	int		i;

	i = -1;
	if (nitems != 0 && size > ULONG_MAX / nitems)
		return (NULL);
	arr = (void *)malloc(size * nitems);
	if (arr == NULL)
		return (NULL);
	while ((size_t)++i < nitems * size)
		arr[i] = 0;
	return (arr);
}
