/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserafim <rserafim@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:46:02 by rserafim          #+#    #+#             */
/*   Updated: 2022/11/07 17:38:59 by rserafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//!!!!!!!!Mettre un fichier ailleurs car + que 5 fonctions!!!!!!!
int	check_need(char c, char *need)
{
	int	y;

	y = 0;
	if (c == 'P' && need[1] == '7')
		return (1);
	if (c == 'E' && need[2] == '7')
		return (1);
	while (need[y] != '\0')
	{
		if (need[y] == c)
			need[y] = '7';
		y++;
	}
	return (0);
}
int	errors_map(int x, int y, const char *need)
{
	if (x == 0 || y == 0)
		return (0);
	if (x == y)
		return (0);
	if (ft_strncmp(need, "777", 3) != 0)
		return (0);
	return (1);
}
int	map_size_error(const char *map_name, t_coord *p)
{
	int			fd;
	char		*line;
	static char	*need;

	fd = (open(map_name, O_RDONLY)); //ouvrir le fichier
	if (fd == -1 || fd == 0)
		return (0);
	line = get_next_line(fd);	//prendre la premiere ligne de notre map
	need = ft_strdup("CPE"); //pour etre sur quil y ait une sortie, une piece et un perso
	if (ft_char_find(line, '0'))//regarder si il trouve le caractere demander dans la string(pas possinle du 0)
	{
		free (need);
		free (line);
		return (0);
	}
	(*p).x = ft_strlen(line); //longeur ligne horizontale (dimension de la ligne)
	(*p).y = check_mid_map (line, need, fd); //controle tout juska la derniere ligne + me donner la hauteur de map
	if (errors_map((*p).x, (*p).y, need) == 0)
	{
		close (fd);
		free (need);
		return (0);
	}
	close (fd);
	free (need);
	return (1);
}

int	ft_char_find(const char *str, int to_find)//trouver le 0 si yen a 1 il menvoie oui sinon 0
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_find)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_line(const char *line, char *need)//verifie si il y a le c,p,e dans notre map
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if ((line[i + 1] == '\0' && line[i] != '1') || line[0] != '1')
			return (1);
		if (line[i] == 'P' || line[i] == 'C' || line[i] == 'E')
			if (check_need(line[i], need))
				return (1);
		if (line[i] != '0' && line[i] != '1' && line[i] != 'C')
			if (line[i] != 'E' && line[i] != 'M' && line[i] != 'P')
				return (1);
	}
	return (0);
}

int	check_mid_map(char *line, char *need, int fd)//regarder le reste de map sauf premiere ligne
{
	int		i;
	char	*last_line;
	size_t	comp;

	i = 0;
	comp = ft_strlen(line);
	last_line = NULL;
	while (line != NULL || line != (void *)0)
	{
		i++;
		if (last_line) //si last_line existe, et si elle est pas a 0 faut free
			free(last_line);
		if (comp != ft_strlen(line))//verif si les prochaines lignes sont toujours a la meme longueur
			return (0);
		if (ft_check_line(line, need) == 1)//verif si il y a le c,p,e
			return (0);
		last_line = ft_strdup(line);//allouer une chaine de caractere
		free (line);
		line = get_next_line(fd);//je donne la valeur de la prochaine ligne du fichier
	}
	if (ft_char_find(last_line, '0'))//si ya un 0 a la derniere ligne il faut free 
	{
		free (last_line);
		return (0);
	}
	free (last_line);
	return (i); //nb de fois que cest passe dans la boucle et va donc me donner le nb de ligne et donc la hauteur
}
