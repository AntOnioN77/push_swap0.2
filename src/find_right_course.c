/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_right_course.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:34:49 by antofern          #+#    #+#             */
/*   Updated: 2024/12/10 23:57:49 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"
#include "libft/headers/libft.h"
#include "libft/headers/ring.h"

/*Almacena temporalmente en this_course el curso necesario para rotar los stacks
a y b hasta la posicion place_a para el stack A y hasta la posicion place_b
para el stack B, tratando de rotar ambas pilas en la misma direccion.
primero emula rotar en sentido normal con try_rr_way() y despues en sentido
inverso con try_rrr_way. Amabas son comparadas sucesivamente con best_course,
si el numero de steps necesarios es inferior sobreescribe best_course con
this_course*/
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

/*Calcula los movimientos necesarios para rotar position, hasta el top de su
pila con rotaciones simples en sentido normal. Añade el resultado a course*/
static void	rotate_stack(t_course *course, t_place position)
{
	course->steps += position.level;
	if (position.stack_name == 'a')
		course->ra = position.level;
	if (position.stack_name == 'b')
		course->rb = position.level;
}

//no separar de async_rotation
/*Calcula los movimientos necesarios para rotar position, hasta el top de su
pila con rotaciones simples en sentido inverso. Añade el resultado a course*/
static void	reverse_rotate_stack(t_course *course, t_place position)
{
	course->steps += position.reverse_level;
	if (position.stack_name == 'a')
		course->rra = position.reverse_level;
	if (position.stack_name == 'b')
		course->rrb = position.reverse_level;
}

/*Calcula los movimientos para situar position_in_a y Position_in_b en el
top de sus respectivas pilas. Y lo hace de tal manera que una rote en un sentido
y la otra rote en el sentido inverso. Evalua en que direccion sería menos
costoso, y calcula las instrucciones exactas almacenandolas en this_course.
si this_course requiere un numero de instruciones inferior a best_course, lo
sobreescribe. */
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

/*Recorre todo el stack_b comprobando qué elemento es menos costoso colocar
en su lugar en el stack_a*/
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
