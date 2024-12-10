/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_right_course.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:34:49 by antofern          #+#    #+#             */
/*   Updated: 2024/12/11 00:45:11 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"
#include "libft/headers/libft.h"
#include "libft/headers/ring.h"

/*Temporarily stores in this_course the course needed to rotate stacks
a and b to the position place_a for stack A and to the position place_b
for stack B, trying to rotate both stacks in the same direction.
First, it emulates rotating in the normal direction with try_rr_way() and then
in the reverse direction with try_rrr_way. Both are successively compared with
best_course, if the number of steps needed is lower, it overwrites best_course
with this_course*/
void	synch_rotation(t_place place_a, t_place place_b, t_course *best_course)
{
	t_course	this_course;

	clean_course(&this_course);
	if (place_a.level > place_b.level)
		try_rr_way(place_a, place_b, &this_course);
	else
		try_rr_way(place_b, place_a, &this_course);
	if (this_course.steps < best_course->steps)
		ft_memcpy(best_course, &this_course, sizeof(t_course));
	clean_course(&this_course);
	try_rrr_way(place_a, place_b, &this_course);
	if (this_course.steps < best_course->steps)
		ft_memcpy(best_course, &this_course, sizeof(t_course));
}

/*Calculates the movements necessary to rotate position to the top of its
stack with simple rotations in the normal direction. Adds the result to course*/
static void	rotate_stack(t_course *course, t_place position)
{
	course->steps += position.level;
	if (position.stack_name == 'a')
		course->ra = position.level;
	if (position.stack_name == 'b')
		course->rb = position.level;
}

/*Calculates the movements necessary to rotate position to the top of its
stack with simple reverse rotations. Adds the result to course*/
static void	reverse_rotate_stack(t_course *course, t_place position)
{
	course->steps += position.reverse_level;
	if (position.stack_name == 'a')
		course->rra = position.reverse_level;
	if (position.stack_name == 'b')
		course->rrb = position.reverse_level;
}

/*Calculates the movements to place position_in_a and position_in_b at the
top of their respective stacks. It does so in such a way that one rotates in one
direction and the other rotates in the opposite direction. It evaluates which
direction would be less costly and calculates the exact instructions, storing
them in this_course. If this_course requires fewer instructions than best_course,
it overwrites best_course. */
void	asynch_rotation(t_place position_in_a, t_place position_in_b,
	t_course *best_course)
{
	t_course	this_course;

	clean_course(&this_course);
	this_course.pa = 1;
	this_course.steps = 0;
	if (position_in_a.level + position_in_b.reverse_level
		< position_in_b.level + position_in_a.reverse_level)
	{
		rotate_stack(&this_course, position_in_a);
		reverse_rotate_stack(&this_course, position_in_b);
	}
	else
	{
		reverse_rotate_stack(&this_course, position_in_a);
		rotate_stack(&this_course, position_in_b);
	}
	if (this_course.steps < best_course->steps)
		ft_memcpy(best_course, &this_course, sizeof(t_course));
}

/*Iterates through the entire stack_b checking which element is the least
costly to place in its position in stack_a*/
void	find_rigth_course(t_ring *stack_a, t_ring *stack_b,
t_course *best_course)
{
	t_level	level_a;
	t_level	level_b;
	t_place	position_in_a;
	t_place	position_in_b;

	level_b = 0;
	while (level_b < stack_b->fill)
	{
		level_a = find_place_for(stack_a, ring_get_level(stack_b, level_b));
		position_in_a = setup_place(stack_a, level_a, 'a');
		position_in_b = setup_place(stack_b, level_b, 'b');
		synch_rotation(position_in_a, position_in_b, best_course);
		asynch_rotation(position_in_a, position_in_b, best_course);
		level_b++;
	}
}
