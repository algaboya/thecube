/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:04:28 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/17 02:42:58 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
#  define EXIT_FAILURE -1
#  define EXIT_SUCCESS 0
#  define MALLOC_ERROR 4
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include "minilibx-linux/mlx.h"
# include "Libft/libft.h"

typedef struct s_config
{
	char *no_tex;
	char *so_tex;
	char *we_tex;
	char *ea_tex;
	int floor_color;
	int ceiling_color;
	char **map;
	int player_x;
	int player_y;
	char player_dir;
}				t_config;

void	error_msg_exit(char *msg, int status);
void	get_valid_data(char *input);
void	init_data(t_config *data);
void	check_name(char *input);
int		opened_file(char *file, t_config *data);
int		textures(int fd, t_config *data);
void	free_set_null(void *ptr);
bool	is_empty(char *str);
int		array_len(char **arr);
bool	is_valid(char *str);
int 	set_data(char *buff, t_config *data);
int		set_texture(t_config *data, char **splitted);
void	free_array(char **str);
void	free_data(t_config *data);
int		check_malloc(void *ptr);
char	*map_reading(int fd);
void	map(t_config *data, int fd);
char	*my_join(char const *s1, char const *s2);
void	empty_lines(t_config *data, char *map);
void	char_check(t_config *data, char *map);
void	clean_and_exit(char *error_msg, void *ptr, t_config *data);
void	map_to_matrix(char *map, t_config *data);
void	valid_walls(t_config *data);
void	check_walls(t_config *data, int i, int j);


//color
int valid_color(char **splitted);
int	get_color(char *color);
int	set_color(t_config *data, char **splitted);

// get_next_line

char	*get_next_line(int fd);
char	*ft_final(char *buffer);
char	*ft_clean(char *buffer);
char	*ft_read(char *buffer, int fd);
int		my_strchr(char *s);
char	*my_strjoin(char *s1, char *s2);

#endif