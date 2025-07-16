/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:40:35 by llechert          #+#    #+#             */
/*   Updated: 2025/07/16 12:53:50 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	parser(t_map *map)
{
	if (access(map->name, F_OK | R_OK) == -1)
	{
		free(map);
		ft_putstr_fd("Error\nCould not access or read map file! \n", 2);
		exit(1);
	}
	if (parse_name(map->name))
	{
		free(map);
		ft_putstr_fd("Error\nMap name is unsupported! \n", 2);
		exit(1);
	}
	if (parse_map(map))//message d'erreur inclus dans le parser
	{
		free_tab_str(map->map);
		free(map);
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
		return (1);//cas ou le fichier s'appelle juste .ber et se situe dans le dossier map : on passe map/.ber en arg et on veut pas l'accepter
	return (0);
}

int	parse_map(t_map *map)
{
	int	fd;

	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCould not open map file! \n", 2), 1);
	if (check_size(map, fd))
	{
		free_gnl_buffer(fd);
		close(fd);
		return (1);//messages d'erreurs dans check_size
	}
	close(fd);//ou remplacer par un free total de gnl ?
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCould not open map! \n", 2), 1);
	if (duplicate_map(map, fd))
		return (ft_putstr_fd("Error\nCould not dup map! \n", 2), 1);
	if (check_map_characteristics(map))//messages d'erreur inclus
		return (1);
	return (0);
}

int	check_size(t_map *map, int fd)
{
	char	*line;
	
	line = skip_nl(fd);//dedans on fait un gnl donc faut free plus bas
	if (!line)
		return (free(line), ft_putstr_fd("Error\nEmpty map! \n", 2), 1);//faut-il free si line est vide ou risque de invalid free ? --> test avec empty map
	map->h_size = ft_strlen(line) - 1;
	map->v_size = 1;
	free(line);//free du skip_nl
	line = get_next_line(fd);//on passe a la deuxieme ligne de la map
	while (line && line[0] != '\n')
	{
		map->v_size++;
		if (map->h_size != (int)ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n'))//exclut le \n a la fin du calcul
		{
			free(line);//on free si error
			// line = get_next_line(-42);
			// free_gnl_buffer(fd);//on finit par vider le buffer de gnl
			return (ft_putstr_fd("Error\nMap is not rectangular! \n", 2), 1);
		}
		free(line);//on free avant de passer au suivant
		line = get_next_line(fd);
	}
	free(line);//on free la derniere ligne
	if (map->v_size < 3 || map->h_size < 3)
		return (ft_putstr_fd("Error\nNot enough rows or columns! \n", 2), 1);
	return (0);
}

int	duplicate_map(t_map *map, int fd)
{
	int		i;
	char	*line;

	i = 0;
	map->map = ft_calloc(map->v_size + 1, sizeof(char *));
	if (!map->map)
		return (1);
	line = skip_nl(fd);
	while (i < map->v_size)//remplacer par i < v_size ?
	{
		map->map[i] = ft_strdup(line);
		if (!map->map[i])
			return (1);//on free dans parser juste apres etre revenu de parse_map --> est-ce necessaire de remettre le free_gnl_buffer ici ?
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);//free-gnl-buffer aussi ??
	map->map[i] = NULL;
	close(fd);
	return (0);
}
