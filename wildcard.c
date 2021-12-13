/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 13:32:35 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 16:34:17 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <dirent.h>
#include <stdio.h>

static char	*ft_get_args(struct dirent *dir, char *args, DIR *open_dir);

static char	*ft_get_wildcard(char *file, char *wildcard);

char	*ft_wildcard(char *args)
{
	struct dirent	*dir;
	DIR				*open_dir;
	char			*new_args;

	open_dir = opendir(".");
	if (!open_dir)
		return (0);
	dir = readdir(open_dir);
	new_args = ft_get_args(dir, args, open_dir);
	if (!new_args)
		return (0);
	return (new_args);
}

static char	*ft_get_args(struct dirent *dir, char *args, DIR *open_dir)
{
	char	*new_args;
	char	*file;
	int		i;
	int		j;

	i = 0;
	j = 2;
	new_args = NULL;
	while (dir)
	{
		file = ft_get_wildcard(dir->d_name, args);
		if (file)
		{
			if (!new_args)
			{
				printf("args = %s\n", args);
				new_args = ft_strdup(file);
				printf("post args = %s\n", args);
			}
			else
				ft_strjoin_free(&new_args, file);
			ft_strjoin_free(&new_args, " ");
		}
		dir = readdir(open_dir);
	}
	closedir(open_dir);
	return (new_args);
}

static char	*ft_get_wildcard(char *file, char *wildcard)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("w = %s\n", wildcard);
	while (wildcard[i] && file[j])
	{
		if (wildcard[i] == '*')
		{
			i++;
			while (file[j] && file[j] != wildcard[i])
			{
				j++;
			}
		}
		if (wildcard[i] != file[j])
			return (0);
		i++;
		j++;
	}
	if (wildcard[i] != file[j])
		return (0);
	printf("w2 = %s\n", wildcard);
	copy = ft_strdup(file);
	printf("file = %s\n", copy);
	return (copy);
}
