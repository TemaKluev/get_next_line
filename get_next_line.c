/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemkliuiev <artemkliuiev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:19:05 by artemkliuie       #+#    #+#             */
/*   Updated: 2024/08/07 18:23:11 by artemkliuie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = chrsearch(s1, '0') + chrsearch(s2, '0');
	if (!i)
		return (NULL);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int	chrsearch(const char *s, char type)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (type == '0')
		while (s[i])
			i++;
	else if (type == 'n')
		while (s[i] != '\0' && s[i] != '\n')
			i++;
	else if (type == 's')
	{
		while (s[i] != '\0')
		{
			if (s[i] == '\n')
				return (1);
			i++;
		}
		return (0);
	}
	return (i);
}

char	*str_line(char *s1, int i)
{
	int		j;
	int		k;
	char	*s2;

	j = 0;
	k = 0;
	if (i == 1)
		i = (chrsearch(s1, 'n') + 1);
	else if (i == 5)
	{
		i = (chrsearch(s1, '0') - chrsearch(s1, 'n') + 1);
		j = chrsearch(s1, 'n') + 1;
	}
	s2 = malloc(i * sizeof(char));
	if (!s2)
		return (NULL);
	while (k < i)
		s2[k++] = s1[j++];
	s2[k] = '\0';
	return (s2);
}

char	*str_read(int fd, char *leftstr)
{
	int		rd_bytes;
	char	*str;

	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	rd_bytes = 1;
	while (!chrsearch(leftstr, 's') && rd_bytes != 0)
	{
		rd_bytes = read(fd, str, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free (str);
			return (NULL);
		}
		str[rd_bytes] = '\0';
		leftstr = ft_strjoin(leftstr, str);
	}
	free(str);
	return (leftstr);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = str_read(fd, str);
	printf("str = %s\n", str);
	if (!str)
		return (NULL);
	line = str_line(str, 1);
	str = str_line(str, 5);
	return (line);
}

int main(void)
{
	int		text1;
	//int		text2;
	int		i;
	char	*line;

	text1 = open("tests/test.txt", O_RDONLY);
	//text2 = open("tests/test2.txt", O_RDONLY);
	i = 0;
	while (i < 8)
	{
		printf ("run: %d\n", i);
		line = get_next_line(text1);
		printf("main: %s\n\n", line);
		free(line);
		// line = get_next_line(text2);
		// printf("main: %s\n\n", line);
		// free(line);
		i++;
	}
	close(text1);
	//close(text2);
	return(0);
}
