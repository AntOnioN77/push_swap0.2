/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:54:36 by antofern          #+#    #+#             */
/*   Updated: 2024/12/08 15:00:04 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_array.h"
#include "libft/headers/ring.h"

/*Recive best_course, con las instrucciones necesarias para colocar el
siguiente elemento y las lleva a cabo*/
static void	take_course(t_course *course, t_ring *a, t_ring *b)
{
	int	i;

	i = 0;
	while (i++ < course->rr)
		rr(a, b);
	i = 0;
	while (i++ < course->rrr)
		rrr(a, b);
	i = 0;
	while (i++ < course->ra)
		ra(a);
	i = 0;
	while (i++ < course->rb)
		rb(b);
	i = 0;
	while (i++ < course->rra)
		rra(a);
	i = 0;
	while (i++ < course->rrb)
		rrb(b);
	i = 0;
	while (i++ < course->pa)
		pa(b, a);
}

/*Rota la pila A hasta situar el numero mas pequeño en la parte superior.
Lo hace por el camino mas corto (con ra o rra)*/
static void	raise_head(t_ring *a)
{
	t_level	first_in_level;

	first_in_level = ring_find_value(a, ring_find_smallest(a));
	while (first_in_level < 0)
	{
		rra(a);
		first_in_level++;
	}
	while (first_in_level > 0)
	{
		ra(a);
		first_in_level--;
	}
}

int	main(int argc, char **argv)
{
	t_ring		*a;
	t_ring		*b;
	t_course	best_course;

	parsargs(argc, argv, &a, &b);
	preorder(a, b);
	while (b->fill > 0)
	{
		clean_course(&best_course);
		find_rigth_course(a, b, &best_course);
		take_course(&best_course, a, b);
	}
	raise_head(a);
	ring_free(a);
	ring_free(b);
	return (0);
}
