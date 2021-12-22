/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wildcard.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:35:14 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/16 15:55:32 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../Libft/libft.h"

int	main(void)
{
	char	*result;

	result = ft_wildcard(ft_strdup("test_wi*c"));
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("test_wi*.c"));
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("*wildcard.c"));
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("*wild*a*r*.c"));
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("*wild**.c"));
	printf("%s\n\n", result);
	free(result);
}
