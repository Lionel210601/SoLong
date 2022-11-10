/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserafim <rserafim@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:15:04 by rserafim          #+#    #+#             */
/*   Updated: 2022/11/08 16:47:21 by rserafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_monster_move(t_game *a, char *line, int i)//check position du monstre, si ya mur pas aller etc
{
	size_t	c_monster;
	size_t	o_monster;

	c_monster = a->index_monster;
	o_monster = -1;
	while (a->monster[c_monster].x != a->monster[++o_monster].x)
	{
		if (a->monster[c_monster].x + i == a->monster[o_monster].x)
			return (0);
	}
	a->index_coll = -1;
	while (++a->index_coll <= a->count_coll)
		if (a->monster[c_monster].x + i == a->coll[a->index_coll].x
			&& a->monster[c_monster].y == a->coll[a->index_coll].y)
			return (0);
	if (a->monster[c_monster].x == a->coll[a->index_coll].x
		&& a->monster[c_monster].y + i == a->coll[a->index_coll].y)
		return (0);
	if (line[a->monster[a->index_monster].x + i] == '1')
		return (0);
	if (line[a->monster[a->index_monster].x + i] == 'E')
		return (0);
	else
		return (1);
}

int	check_map(const char *map)	//check si .ber pour pas que dautre chose fonctionne
{
	const char	*check;

	check = ft_strrchr(map, '.');
	if (check == NULL)
		return(0);
	check++;
	if (ft_strncmp(check, "ber", 3) == 0)
		return (1);
	else
		return (0);
}

void	fill_map(t_game *p, char **map)//parcour la map et selon la case, je met limage qui correspond, monstre, perso, argent
{
	void	*g;
	t_mlx	*m;
	int		i;
	int		j;

	i = 0;
	m = &p->mlx;
	g = p->images.ground;
	while (i++ < p->mapi.y * 32)
	{
		j = 0;
		while (j++ < p->mapi.x)
			mlx_put_image_to_window(m->ptr, m->window, g, j * 32, i * 32);
	}
	p->index_coll = 0;
	p->index_monster = 0;
	p->mapi.y = 0;
	while (map[p->mapi.y] != NULL)
	{
		p->mapi.x = 0;
		fill_line(map[p->mapi.y], p); //remplir une ligne entiere
		p->mapi.y++;
	}
}

void	fill_line(char *line, t_game *a)//met la position de monstre, joueur, piece, image, la sortie du jeu, et les murs(1)
{
	//int	*x;
	//int	*y;

	//x = &a->mapi.x;
	//y = &a->mapi.y;
	while (line[a->mapi.x] != '\0')
	{
		if (line[a->mapi.x] == 'P')
		{
			put_image(&a->mlx, a->images.player, a->mapi.x, a->mapi.y);
			a->player.x = a->mapi.x;
			a->player.y = a->mapi.y;
		}
		if (line[a->mapi.x] == 'C')
			init_position(a, line[a->mapi.x]);
		if (line[a->mapi.x] == '1')
			put_image(&a->mlx, a->images.wall, a->mapi.x, a->mapi.y);
		if (line[a->mapi.x] == 'M')
			init_position(a, line[a->mapi.x]);
		if (line[a->mapi.x] == 'E')
			init_position(a, line[a->mapi.x]);
		a->mapi.x++;
	}
}

void	init_position(t_game *a, char c)//met limage et les cordonnees dans le tableau
{
	if (c == 'C')
	{
		put_image(&a->mlx, a->images.coin, a->mapi.x, a->mapi.y);
		a->coll[a->index_coll].x = a->mapi.x;
		a->coll[a->index_coll].y = a->mapi.y;
		a->index_coll++;
	}
	if (c == 'M')
	{
		put_image(&a->mlx, a->images.monster, a->mapi.x, a->mapi.y);
		a->monster[a->index_monster].x = a->mapi.x;
		a->monster[a->index_monster].y = a->mapi.y;
		a->index_monster++;
	}
	if (c == 'E')
	{
		put_image(&a->mlx, a->images.sortie, a->mapi.x, a->mapi.y);
		a->sortie.x = a->mapi.x;
		a->sortie.y = a->mapi.y;
	}
}
