/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemkliuiev <artemkliuiev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:19:05 by artemkliuie       #+#    #+#             */
/*   Updated: 2024/08/09 17:31:39 by artemkliuie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_get_line(char *main_str)
{
	int		i;
	char	*line;

	i = 0;
	if (!main_str[i])
		return (NULL);
	while (main_str[i] && main_str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (main_str[i] && main_str[i] != '\n')
	{
		line[i] = main_str[i];
		i++;
	}
	if (main_str[i] == '\n')
	{
		line[i] = main_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*new_main_str(char *main_str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (main_str[i] && main_str[i] != '\n')
		i++;
	if (!main_str[i])
	{
		free(main_str);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (chrsearch(main_str, '0') - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (main_str[i])
		new_str[j++] = main_str[i++];
	new_str[j] = '\0';
	free(main_str);
	return (new_str);
}

char	*str_read(int fd, char *main_str)
{
	int		rd_bytes;
	char	*new_str;

	new_str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	rd_bytes = 1;
	while (!chrsearch(main_str, 's') && rd_bytes != 0)
	{
		rd_bytes = read(fd, new_str, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free (new_str);
			return (NULL);
		}
		new_str[rd_bytes] = '\0';
		main_str = ft_strjoin(main_str, new_str);
	}
	free(new_str);
	return (main_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*main_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	main_str = str_read(fd, main_str);
	if (!main_str)
		return (NULL);
	line = ft_get_line(main_str);
	main_str = new_main_str(main_str);
	return (line);
}

// int main(void)
// {
// 	int		text1;
// 	//int		text2;
// 	int		i;
// 	char	*line;

// 	text1 = open("tests/read_error.txt", O_RDONLY);
// 	//text2 = open("tests/test2.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 8)
// 	{
// 		printf ("run: %d\n", i);
// 		line = get_next_line(text1);
// 		printf("main: %s\n\n", line);
// 		free(line);
// 		// line = get_next_line(text2);
// 		// printf("main: %s\n\n", line);
// 		// free(line);
// 		i++;
// 	}
// 	close(text1);
// 	//close(text2);
// 	return(0);
// }

// char	*str_line(char *s1, int s)
// {
// 	int		j;
// 	int		k;
// 	int		i;
// 	char	*s2;

// 	j = 0;
// 	k = 0;
// 	if (!s1[j])
// 		return (NULL);
// 	if (s == 1)
// 		i = (chrsearch(s1, 'n') + 1);
// 	else if (s == 5)
// 	{
// 		i = (chrsearch(s1, '0') - chrsearch(s1, 'n') + 1);
// 		j = chrsearch(s1, 'n') + 1;
// 	}
// 	s2 = malloc(i * sizeof(char));
// 	if (!s2)
// 		return (NULL);
// 	while (k < i)
// 		s2[k++] = s1[j++];
// 	s2[k] = '\0';
// 	if (s == 5)
// 		free(s1);
// 	return (s2);
// }
