/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:04:00 by antofern          #+#    #+#             */
/*   Updated: 2024/12/10 23:58:51 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	handle_error(void *to_free, void (*free_func)(void *))
{
	if (to_free != NULL)
		free_func(to_free);
	write(2, "Error\n", 6);
	exit (EXIT_FAILURE);
}
