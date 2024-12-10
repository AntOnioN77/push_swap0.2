/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:16:27 by antofern          #+#    #+#             */
/*   Updated: 2024/12/11 00:49:25 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/headers/ring.h"

// sends the third chunk to stack b, accumulated at the back of stack a
void	pb_lasts(t_ring *a, t_ring *b, int bigest, int smalest)
{
	while (a->fill > 2)
	{
		if (ring_get_head(a) == bigest || ring_get_head(a) == smalest)
			ra(a);
		else
			pb(a, b);
	}
}

void	preorder_many(t_ring *a, t_ring *b, int bigest, int smalest)
{
	int	first_terctil;
	int	second_terctil;
	int	check;

	first_terctil = ring_find_nth(a, a->fill, a->fill / 3);
	second_terctil = ring_find_nth(a, a->fill, (a->fill / 3) * 2);
	check = a->fill;
	while (check > 0)
	{
		if (ring_get_head(a) == bigest || ring_get_head(a) == smalest)
			ra(a);
		else if (ring_get_head(a) > second_terctil)
			ra(a);
		else if (ring_get_head(a) > first_terctil)
		{
			pb(a, b);
			rb(b);
		}
		else if (ring_get_head(a) <= first_terctil)
			pb(a, b);
		check --;
	}
	pb_lasts(a, b, bigest, smalest);
}

void	preorder_few(t_ring *a, t_ring *b, int bigest, int smalest)
{
	while (a->fill > 3)
	{
		if (ring_get_head(a) == bigest || ring_get_head(a) == smalest)
			ra(a);
		else
			pb(a, b);
	}
	if (!((ring_get_level(a, 0) < ring_get_level(a, 1)
				&& ring_get_level(a, 1) < ring_get_level(a, 2))
			|| (ring_get_level(a, 1) < ring_get_level(a, 2)
				&& ring_get_level(a, 2) < ring_get_level(a, 0))
			|| (ring_get_level(a, 2) < ring_get_level(a, 0)
				&& ring_get_level(a, 0) < ring_get_level(a, 1))))
		sa(a);
}

int	is_correlative(t_ring *a, int smalest)
{
	t_level	level;
	int		check;

	level = ring_find_value(a, smalest);
	check = a->fill;
	while (check > 0)
	{
		level++;
		if (ring_get_level(a, level - 1) > ring_get_level(a, level))
			break ;
		check--;
	}
	if (check == 1)
		return (1);
	return (0);
}

void	preorder(t_ring *a, t_ring *b)
{
	int	bigest;
	int	smalest;

	bigest = ring_find_bigest(a);
	smalest = ring_find_smallest(a);
	if (!is_correlative(a, smalest))
	{
		if (a->fill > 70)
			preorder_many(a, b, bigest, smalest);
		else
			preorder_few(a, b, bigest, smalest);
	}
}
