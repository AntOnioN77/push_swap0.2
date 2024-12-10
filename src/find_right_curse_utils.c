/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_right_curse_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:31:38 by antofern          #+#    #+#             */
/*   Updated: 2024/12/11 00:48:22 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Searches in stack_a for a place to fit n, such that x < n < y.
Returns the level we should rotate to the top before placing n on top.
The stack must contain at least the largest and smallest number in the list */
t_level	find_place_for(t_ring *stack_a, int n)
{
	int	i;

	if (stack_a->fill == 0 || stack_a->fill == 1)
		return (0);
	i = 0;
	while (i < stack_a->fill)
	{
		if (ring_get_level(stack_a, i) >= n
			&& ring_get_level(stack_a, i - 1) <= n)
			return (i);
		i++;
	}
	return (0);
}

t_place	setup_place(t_ring *stack, t_level level, char stack_name)
{
	t_place	new_place;

	new_place.stack_name = stack_name;
	new_place.level = level;
	if (level == 0)
		new_place.reverse_level = 0;
	else
		new_place.reverse_level = stack->fill - level;
	return (new_place);
}

/* Initializes t_course. sync_rotation() and async_rotation() use this function
and perform a comparison with course->steps right after initializing it, which
is why we initialize with course->steps at the worst possible value, to ensure
that the elements will receive at least one reassignment of values */
void	clean_course(t_course *course)
{
	ft_memset(course, 0, sizeof(t_course));
	course->steps = INT_MAX;
}


/* Assigns to <course> the steps necessary to place both deeper and higher
at the head of their respective stacks. It does this with non-reverse rotations,
trying to maximize the number of simultaneous rotations (rr) */
void	try_rr_way(t_place deeper, t_place higher, t_course *course)
{
	course->steps = deeper.level + 1;
	course->rr = higher.level;
	course->rrr = 0;
	if (deeper.stack_name == 'a')
	{
		course->ra = deeper.level - higher.level;
		course->rb = 0;
	}
	if (deeper.stack_name == 'b')
	{
		course->rb = deeper.level - higher.level;
		course->ra = 0;
	}
	course->rra = 0;
	course->rrb = 0;
	course->pa = 1;
}

/* Assigns to <course> the steps necessary to place both <place_a> and <place_b>
at the head of their respective stacks. It does this with reverse rotations,
trying to maximize the number of simultaneous rotations (rrr) */
void	try_rrr_way(t_place place_a, t_place place_b, t_course *course)
{
	if (place_a.reverse_level > place_b.reverse_level)
		course->steps = place_a.reverse_level + 1;
	else
		course->steps = place_b.reverse_level + 1;
	course->rr = 0;
	if (place_a.reverse_level >= place_b.reverse_level)
		course->rrr = place_b.reverse_level;
	else
		course->rrr = place_a.reverse_level;
	course->ra = 0;
	if (place_a.reverse_level > place_b.reverse_level)
	{
		course->rra = place_a.reverse_level - place_b.reverse_level;
		course->rrb = 0;
	}
	else
	{
		course->rra = 0;
		course->rrb = place_b.reverse_level - place_a.reverse_level;
	}
}
