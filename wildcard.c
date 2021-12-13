/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 13:32:35 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 14:42:09 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <dirent.h>

static char	**ft_get_args(struct dirent *dir, t_part *args, DIR *open_dir);

static char	*ft_get_wildcard(t_part *args);

static char	*ft_is_wild(char *file, char *wildcard);

int	ft_wildcard(t_part *args)
{
	struct dirent	*dir;
	DIR				*open_dir;
	char			**new_args;

	open_dir = opendir(".");
	if (!open_dir)
		return (1);
	dir = readdir(open_dir);
	new_args = ft_get_args(dir, args, open_dir);
	if (!new_args)
		return (1);
	ft_redir_args(new_args);
	return (0);
}

static char	**ft_get_args(struct dirent *dir, t_part *args, DIR *open_dir)
{
	char	**new_args;
	char	*wildcard;
	int		i;
	int		j;

	i = 0;
	j = 2;
	new_args = malloc(1);
	wildcard = ft_get_wildcard(args);
	if (!wildcard)
		return (0);
	while (dir)
	{
		new_args = ft_realloc(new_args, (j * sizeof(char *)), \
		((j - 1) * sizeof(char *)));
		new_args[j - 1] = NULL;
		new_args[j - 2] = ft_is_wild(dir->d_name, wildcard);
		if (new_args[j - 2])
			j++;
		dir = readdir(open_dir);
	}
	closedir(open_dir);
	return (new_args);
}

static char	*ft_get_wildcard(t_part *args)
{
	int	i;

	i = 0;
	while (args->part[0])
	{
		while (args->part[i])
		{
			if (args->part[i] == '*')
				return (args->part);
			i++;
		}
		args++;
	}
	return (0);
}

static char	*ft_is_wild(char *file, char *wildcard)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (wildcard[i] && file[j])
	{
		if (wildcard[i] == '*')
		{
			i++;
			while (file[j] && file[j] != wildcard[i])
				j++;
		}
		if (wildcard[i] != file[j])
			return (0);
		i++;
		j++;
	}
	copy = ft_strdup(file);
	return (copy);
}
