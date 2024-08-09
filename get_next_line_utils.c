/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemkliuiev <artemkliuiev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:19:05 by artemkliuie       #+#    #+#             */
/*   Updated: 2024/08/09 17:17:31 by artemkliuie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *main_str, char *last_str)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!main_str)
	{
		main_str = (char *)malloc(1 * sizeof(char));
		main_str[0] = '\0';
	}
	if (!main_str || !last_str)
		return (NULL);
	i = chrsearch(main_str, '0') + chrsearch(last_str, '0') + 1;
	new_str = malloc(i * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (main_str)
		while (main_str[++i] != '\0')
			new_str[i] = main_str[i];
	while (last_str[j] != '\0')
		new_str[i++] = last_str[j++];
	new_str[i] = '\0';
	free(main_str);
	return (new_str);
}
