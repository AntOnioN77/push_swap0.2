/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_right_course.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:34:49 by antofern          #+#    #+#             */
/*   Updated: 2024/12/10 11:23:44 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> //borrar, es de prueba
#include <string.h> //borrar
#include <stdio.h> //borrar
#include <limits.h>
#include "push_swap.h"
#include "libft/headers/libft.h"
#include "libft/headers/ring.h"

/*Busca en stack_a, un lugar donde encajar n. de tal manera que quede x < n < y. Retorna el nivel que deberiamos hacer rotar hasta el top antes de colocar n encima. 
  El stack debe contener al menos el numero mas grande y el numero mas pequeño de la lista */
t_level		find_place_for(t_ring *stack_a, int n)
{
	int i;

	if (stack_a->fill == 0 || stack_a->fill == 1)
		return (0);
	i = 0;
	while (i < stack_a->fill)
	{
		if (ring_get_level(stack_a, i) >= n
			&& ring_get_level(stack_a, i-1) <= n)
			return(i);
		i++;
	}
	assert(0);//no deberia llegar nunca. BORRAR el assert()
	return (0);
}

/*Inicializa t_course. sync_rotation() y async_rotation() usan esta funcion y realizan una comparacion con course->steps nada mas inicializarla,
por eso inicializamos con course->steps en el peor valor posible, para asegurar que los elementos recibira al menos una reaseignacion de valores*/
void clean_course(t_course *course)
{
	memset(course, 0, sizeof(t_course));
	course->steps = INT_MAX;
}

//no separar esta funcion de sync_rotation()
/*Asigna a <course> los pasos necesarios para situar tanto deeper como higher en el head de sus respectivos stacks,
Y lo hace con rotaciones no-inversas, y tratando de maximizar el numero de rotaciones simultaneas (rr)*/
void	try_rr_way(t_place deeper , t_place higher, t_course *course)
{
	course->steps = deeper.level + 1; //+1 por el pa
	// TO DO arregla esto:
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
	course->pa	= 1;
}

//no separar esta funcion de sync_rotation()
/*Asigna a <course> los pasos necesarios para situar tanto <a> como <place_b> en el head de sus respectivos stacks,
Y lo hace con rotaciones inversas, y tratando de maximizar el numero de rotaciones simultaneas (rrr)*/
static void	try_rrr_way(t_place place_a , t_place place_b, t_course *course)
{
	if (place_a.reverse_level > place_b.reverse_level)
		course->steps = place_a.reverse_level + 1; //+1 por pa.
	else
		course->steps = place_b.reverse_level + 1; //+1 por pa.
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

/*Almacena temporalmente en this_course el curso necesario para rotar los stacks
a y b hasta la posicion place_a para el stack A y hasta la posicion place_b
para el stack B, tratando de rotar ambas pilas en la misma direccion.
primero emula rotar en sentido normal con try_rr_way() y despues en sentido inverso con
try_rrr_way. Amabas son comparadas sucesivamente con best_course, si el numero de steps
necesarios es inferior sobreescribe best_course con this_course*/
void synch_rotation(t_place place_a, t_place place_b, t_course *best_course)
{
	t_course this_course;

	clean_course(&this_course);
	//this_course.trying_level = best_course->trying_level;
	if (place_a.level > place_b.level)
		try_rr_way(place_a, place_b, &this_course);
	else
		try_rr_way(place_b, place_a, &this_course);
	if (this_course.steps < best_course->steps)
		ft_memcpy(best_course, &this_course, sizeof(t_course));// pasar place_a ft_!!!
	clean_course(&this_course);
	try_rrr_way(place_a, place_b, &this_course);
	if (this_course.steps < best_course->steps)
		ft_memcpy(best_course, &this_course, sizeof(t_course));// pasar a ft_!!!
}

//no separar de async_rotation
/*Calcula los movimientos necesarios para rotar position, hasta el top de su pila con 
rotaciones simples en sentido normal. Añade el resultado a course*/
static void	rotate_stack(t_course *course, t_place position)
{
	course->steps += position.level;
	if (position.stack_name == 'a')
		course->ra = position.level;
	if (position.stack_name == 'b')
		course->rb = position.level;
}

//no separar de async_rotation
/*Calcula los movimientos necesarios para rotar position, hasta el top de su pila con 
rotaciones simples en sentido inverso. Añade el resultado a course*/
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
y la otra rote en el sentido inverso. Evalua en que direccion sería menos costoso,
y calcula las instrucciones exactas almacenandolas en this_course.
si this_course requiere un numero de instruciones inferior a best_course, lo sobreescribe. */
void	asynch_rotation(t_place position_in_a, t_place position_in_b,
	t_course *best_course)
{
	t_course this_course;
	
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
		ft_memcpy(best_course, &this_course, sizeof(t_course));// pasar a ft_!!!
}


t_place setup_place(t_ring *stack, t_level level, char stack_name)
{
    t_place new_place;

    new_place.stack_name = stack_name;
    new_place.level = level;
    new_place.middel_of_stack = stack->fill / 2;

    new_place.stack_size = stack->fill;
	if (level == 0)
		new_place.reverse_level = 0;
	else
    	new_place.reverse_level = stack->fill - level;
    return new_place;
}

/*Recorre todo el stack_b comprobando qué elemento es menos costoso colocar
en su lugar en el stack_a*/
void find_rigth_course(t_ring *stack_a, t_ring *stack_b ,t_course *best_course)
{
	t_level level_a;
	t_level level_b;
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
