/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserafim <rserafim@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:15:16 by eschmid           #+#    #+#             */
/*   Updated: 2022/11/07 18:41:01 by rserafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_coord {
	int				x;
	int				y;
}			t_coord;

typedef struct s_mlx {
	void		*ptr;
	void		*window;
}			t_mlx;

typedef struct s_image {
	void		*ground;
	void		*player;
	void		*coin;
	void		*wall;
	void		*sortie;
	void		*monster;
	int			width;
	int			height;
}			t_image;

typedef struct s_game {
	t_mlx			mlx;
	t_image			images;
	t_coord			mapi;
	t_coord			mouse;
	char			**map;
	t_coord			player;
	t_coord			sortie;
	size_t			count_coll;
	t_coord			*coll;
	size_t			count_monster;
	t_coord			*monster;
	size_t			index_monster;
	size_t			index_coll;
	int				player_moves;
}				t_game;

int		so_long(const char *map);
int		check_map(const char *map);
int		map_size_error(const char *map_name, t_coord *p);
int		ft_char_find(const char *str, int to_find);
int		ft_check_line(const char *line, char *need);
int		check_mid_map(char *line, char *need, int fd);
int		check_need(char c, char *need);
char	**maplloc(const char *arg, int y_size);
void	window_init(t_game a);
void	init_image(t_image *i, t_mlx *m);
void	fill_map(t_game *p, char **map);
void	fill_line(char *line, t_game *a);
int		key_sort(int key, t_game *a);
int		close_game(t_game a, int i);
void	player_up(t_game *a);
void	player_down(t_game *a);
void	player_left(t_game *a);
void	player_right(t_game *a);
void	clear_image(t_mlx mlx, t_coord player, t_image img);
void	entity_counter(t_game *x);
void	init_entity(t_game *a);
void	coin_collected(t_game *a);
void	init_position(t_game *a, char c);
void	event_manager(t_game *a);
void	monster_ia(t_game *a);
int		monster_move_ud(t_game *a, int i);
int		monster_move_lr(t_game *a, int i);
int		check_monster_move(t_game *a, char *line, int i);
void	check_monster_pos(t_game *a, char *line, char *up, char *down);
void	init_struct(t_game *struc);
int		close_button(t_game a);
void	put_image(t_mlx *a, void *img, int x, int y);
void	count_to_window(t_mlx *a, void *img, int *moves);
void	ft_free_struct(char **tab,t_coord *coll, t_coord *monster, int y_size);

#endif
