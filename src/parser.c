/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:40:35 by llechert          #+#    #+#             */
/*   Updated: 2025/07/10 12:30:53 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	parser(t_map *map)
{
	if (access(map->name, F_OK | R_OK) == -1)
	{
		free(map);
		ft_putstr_fd("Error\nCould not access or read map file !", 2);
		exit(1);
	}
	if (parse_name(map->name))
	{
		free(map);
		ft_putstr_fd("Error\nMap name is wrong !", 2);
		exit(1);
	}
	if (parse_map(map))
	{
		free_struct(map);//a voir si on fait pas ce free dans parse_map
		// ft_putstr_fd("Error\nMap is wrong !", 2);//message d'erreur dans le parser aussi
		exit(1);
	}
}

int	parse_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5)
		return (1);
	if (ft_strncmp(name + len - 4, ".ber", 5))
		return (1);
	if (name[len - 5] == '/')
		return (1);//cas ou le fichier s'appelle juste .ber : on passe map/.ber en arg
	return (0);
}

int	parse_map(t_map *map)
{
	int	fd;

	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCould not open map !", 2), 1);
	if (check_size(map, fd))
		return (1);//messages d'erreurs dans check_size
	close(fd);
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCould not open map !", 2), 1);
	duplicate_map(map, fd);
	ft_putstr_fd("Error\nMap is wrong !", 2);

}

int	check_size(t_map *map, int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	while (!ft_strncmp(line, "\n", 2))//on passe toutes les lignes vides
		line = get_next_line(fd);
	line = 	line = get_next_line(fd);//on refait un gnl sur la ligne apres les lignes vides -> taille standard
	if (!line)
		return (ft_putstr_fd("Error\nEmpty map !", 2), 1);
	map->h_size = ft_strlen(line);
	map->v_size++;
	while (line && ft_strncmp(line, "\n", 2))
	{
		map->v_size++;
		if (map->h_size != ft_strlen(line))
			return (ft_putstr_fd("Error\nAll rows are not of same size", 2), 1);
		line = get_next_line(fd);
	}
	return (0);
}

int	duplicate_map(t_map *map, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line == "\n")
		line = get_next_line(fd);
	while ()
}