/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserafim <rserafim@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:17:43 by rserafim          #+#    #+#             */
/*   Updated: 2022/11/07 16:16:28 by rserafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	monster_move_lr(t_game *a, int i)//mouvements monstre gauche et droite
{
	size_t	j;

	j = a->index_monster;
	if (i == 'L')
	{
		clear_image(a->mlx, a->monster[j], a->images);
		a->monster[a->index_monster].x -= 1;
		put_image(&a->mlx, a->images.monster, a->monster[j].x, a->monster[j].y);
		return (1);
	}
	if (i == 'R')
	{
		clear_image(a->mlx, a->monster[j], a->images);
		a->monster[a->index_monster].x += 1;
		put_image(&a->mlx, a->images.monster, a->monster[j].x, a->monster[j].y);
		return (1);
	}
	return (0);
}

void	count_to_window(t_mlx *a, void *img, int *moves)//peetite fenetre en haut a gauche qui compte nb de mouvements (bonus)
{
	int		i;
	char	*str;
	char	*coll_str;

	i = 0;
	coll_str = "";
	str = "";
	str = ft_itoa(*moves);
	coll_str = ft_strjoin("Player moves = ", str);
	while (i <= 4)
	{
		put_image(a, img, i, 0);
		i++;
	}
	mlx_string_put(a->ptr, a->window, 4, 16, 0x000000, coll_str);
	free (str);
	free(coll_str);
}
