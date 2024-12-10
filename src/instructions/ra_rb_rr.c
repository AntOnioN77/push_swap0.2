/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_rb_rr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:54:45 by antofern          #+#    #+#             */
/*   Updated: 2024/12/11 00:22:37 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/headers/ring.h"

void	ra(t_ring *a)
{
	if (a == NULL)
		return ;
	if (ring_rotate(a) == ERROR)
		return ;
	write(1, "ra\n", 3);
}

void	rb(t_ring *b)
{
	if (b == NULL)
		return ;
	if (ring_rotate(b) == ERROR)
		return ;
	write(1, "rb\n", 3);
}

void	rr(t_ring *a, t_ring *b)
{
	if (a == NULL)
		return ;
	if (b == NULL)
		return ;
	if (ring_rotate(a) == ERROR)
		return ;
	if (ring_rotate(b) == ERROR)
	{
		ring_reverse_rotate(a);
		return ;
	}
	write(1, "rr\n", 3);
}
