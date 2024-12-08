/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra_rrb_rrr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:53:57 by antofern          #+#    #+#             */
/*   Updated: 2024/09/02 12:57:22 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/headers/ring.h"

void	rra(t_ring *a)
{
	if (a == NULL)
		return ;
	if (ring_reverse_rotate(a) == ERROR)
		return ;
	write(1, "rra\n", 4);
}

void	rrb(t_ring *b)
{
	if (b == NULL)
		return ;
	if (ring_reverse_rotate(b) == ERROR)
		return ;
	write(1, "rrb\n", 4);
}


void	rrr(t_ring *a, t_ring *b)
{
	if (a == NULL)
		return ;
	if (b == NULL)
		return ;
	if (ring_reverse_rotate(a) == ERROR)
		return ;
	if (ring_reverse_rotate(b) == ERROR)
	{
		ring_rotate(a);
		return ;
	}
	write(1, "rrr\n", 4);
}
