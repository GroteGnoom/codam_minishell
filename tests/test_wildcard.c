/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wildcard.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:35:14 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/15 14:35:20 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	main(void)
{
	char	*result;

	result = ft_wildcard("test_wi*c");
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard("test_wi*.c");
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard("*wildcard.c");
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard("*wild*a*r*.c");
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard("*wild**.c");
	printf("%s\n\n", result);
	free(result);
}
