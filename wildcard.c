/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 13:32:35 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/18 10:28:53 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <dirent.h>
#include <stdio.h>

static char	*ft_get_args(struct dirent *dir, char *args, DIR *open_dir,
				int *wild_quoted);

static char	*ft_get_wildcard(char *file, char *wildcard, int *wild_quoted);

static char	*ft_get_file2(char *file, char **wild_split, int split_len);

char	*ft_wildcard(char *args, int *wild_quoted)
{
	struct dirent	*dir;
	DIR				*open_dir;
	char			*new_args;

	open_dir = opendir(".");
	if (!open_dir)
		return (0);
	dir = readdir(open_dir);
	new_args = ft_get_args(dir, args, open_dir, wild_quoted);
	if (!new_args)
		return (args);
	free(args);
	return (new_args);
}

static char	*ft_get_args(struct dirent *dir, char *args, DIR *open_dir,
		int *wild_quoted)
{
	char	*new_args;
	char	*file;

	new_args = NULL;
	while (dir)
	{
		file = ft_get_wildcard(dir->d_name, args, wild_quoted);
		if (file)
		{
			if (!new_args)
				new_args = ft_strdup(file);
			else
			{
				ft_strjoin_free(&new_args, " ");
				ft_strjoin_free(&new_args, file);
			}
		}
		dir = readdir(open_dir);
	}
	closedir(open_dir);
	return (new_args);
}

static char	*free_ret_null(char **strs)
{
	ft_free_ptr_array((void **)strs);
	return (NULL);
}

static char	*ft_get_wildcard(char *file, char *wildcard, int *wild_quoted)
{
	char	**wild_split;
	int		split_len;
	int		i;
	char	*file2;

	if (file[0] == '.')
		return (NULL);
	wild_split = ft_split_unquoted(wildcard, '*', wild_quoted);
	split_len = ft_count_strs(wild_split);
	if ((wildcard[0] != '*' || wild_quoted[0])
		&& ft_strncmp(wild_split[0], file, ft_strlen(wild_split[0])))
		return (free_ret_null(wild_split));
	if (wildcard[ft_strlen(wildcard) - 1] != '*')
	{
		i = ft_strlen(wild_split[split_len - 1]);
		if ((int)ft_strlen(file) < i || \
		ft_strncmp(wild_split[split_len - 1], &file[ft_strlen(file) - i], i))
			return (free_ret_null(wild_split));
	}
	file2 = ft_get_file2(file, wild_split, split_len);
	if (!file2)
		return (NULL);
	ft_free_ptr_array((void **)wild_split);
	return (file);
}

static char	*ft_get_file2(char *file, char **wild_split, int split_len)
{
	char	*file2;
	int		i;

	i = 0;
	file2 = file;
	while (i < split_len)
	{
		file2 = ft_strnstr(file2, wild_split[i], ft_strlen(file2));
		if (!file2)
			return (free_ret_null(wild_split));
		file2 += ft_strlen(wild_split[i]);
		i++;
	}
	return (file2);
}
