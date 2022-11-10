/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserafim <rserafim@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:09:26 by eschmid           #+#    #+#             */
/*   Updated: 2022/11/07 18:24:47 by rserafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//caler autre fonction ici!
void	ft_free(char *str)
{
	int	i;

	i = 0;
	while (str[i++] != '\0')
		free(&str[i]);
}

char	**maplloc(const char *arg, int y_size)//allouer avec malloc la map et je la met dans un tableau
{
	int			fd;
	char		**tab;
	char	*line;
	int i;

	i = 0;
	tab = malloc (sizeof(char *) * y_size);
	fd = open(arg, O_RDONLY);
	line = get_next_line(fd);
	while (i < y_size)
	{
		tab[i] = ft_strdup(line);
		free (line);
		line = get_next_line(fd);
		i++;
	}
	close (fd);
	free (line);
	//system("leaks so_long");
	//free(save);
	//system("leaks so_long");
	//tab = ft_split(save, 'S');
	//free (save);
	return (tab);
}
