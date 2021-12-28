/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_line_nr.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 14:56:00 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/28 14:56:16 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

void	ft_print_line_nr(int line_nr)
{
	ft_putstr_fd(": line ", 2);
	ft_putnbr_fd(line_nr, 2);
	ft_putstr_fd(": ", 2);
}
