/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:45:01 by antofern          #+#    #+#             */
/*   Updated: 2024/12/11 00:38:14 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ring.h"
#include "../headers/libft.h"

// Places the first element (head) in the last position
int	ring_rotate(t_ring *ring)
{
	if (ring->fill < 2)
		return (ERROR);
	ring->tail = ring_next_index(ring->tail, ring->slots);
	ring->buff[ring->tail] = ring_get_head(ring);
	ring->head = ring_next_index(ring->head, ring->slots);
	return (OK);
}
