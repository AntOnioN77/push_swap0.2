/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_pb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:45:55 by antofern          #+#    #+#             */
/*   Updated: 2024/09/02 12:57:59 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/headers/ring.h"

void	pa(t_ring *b, t_ring *a)
{

	if (ring_push(b, a) == ERROR)
		return ;
	write(1, "pa\n", 3);
}

void	pb(t_ring *a, t_ring *b)
{
	if (ring_push(a, b) == ERROR)
		return ;
	write(1, "pb\n", 3);
}
