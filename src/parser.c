/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:40:35 by llechert          #+#    #+#             */
/*   Updated: 2025/07/11 13:36:12 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	parser(t_game *game)
{
	if (access(game->name, F_OK | R_OK) == -1)
	{
		free(game);
		ft_putstr_fd("Error\nCould not access or read map file !", 2);
		exit(1);
	}
	if (parse_name(game->name))
	{
		free(game);
		ft_putstr_fd("Error\nMap name is unsupported !", 2);
		exit(1);
	}
	if (parse_game(game))
	{
		free_tab_str(game->map);
		free(game);
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
		return (1);//cas ou le fichier s'appelle juste .ber et se situe dans le dossier map : on passe map/.ber en arg et on veut pas l'accepter
	return (0);
}

int	parse_map(t_game *game)
{
	int	fd;

	fd = open(game->name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCould not open map file !", 2), 1);
	if (check_size(game, fd))
		return (1);//messages d'erreurs dans check_size
	close(fd);
	fd = open(game->name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCould not open map !", 2), 1);
	if (duplicate_map(game, fd))
		return (ft_putstr_fd("Error\nCould not dup map !", 2), 1);
	if (check_map_characteristics(game))//messages d'erreur inclus
		return (1);
}

int	check_size(t_game *game, int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	while (line[0] != '\n')//on passe toutes les lignes vides
		line = get_next_line(fd);
	line = get_next_line(fd);//on refait un gnl sur la ligne apres les lignes vides -> taille standard
	if (!line)
		return (ft_putstr_fd("Error\nEmpty map !", 2), 1);
	game->h_size = ft_strlen(line) - 1;//-1 car pas le \n
	game->v_size = 1;
	while (line && line[0] != '\n')
	{
		game->v_size++;
		if (game->h_size != ft_strlen(line))
			return (ft_putstr_fd("Error\nAll rows are not of the same size", 2), 1);
		line = get_next_line(fd);
	}
	return (0);
}

int	duplicate_map(t_game *game, int fd)
{
	int		i;
	char	*line;

	i = 0;
	game->map = ft_calloc(game->v_size + 1, sizeof(char *));
	if (!game->map)
		return (1);
	line = get_next_line(fd);
	while (line[0] != '\n')
		line = get_next_line(fd);
	line = get_next_line(fd);
	while (line && line[0] != '\n')//remplacer par i < v_size ?
	{
		game->map[i] = ft_strdup(line);//attention en faisant ca on prend le \n a la fin de la ligne --> on ne fait pas un strndup car sur la derniere ligne de la map il peut ne pas y avoir de \n
		if (!game->map[i])
			return (free_tab_str(game->map), 1);
		i++;
	}
	game->map[i] = NULL;
	return (0);
}
