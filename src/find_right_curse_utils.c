/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_right_curse_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:31:38 by antofern          #+#    #+#             */
/*   Updated: 2024/12/10 16:39:56 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	return (0);
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

/*Inicializa t_course. sync_rotation() y async_rotation() usan esta funcion y realizan una comparacion con course->steps nada mas inicializarla,
por eso inicializamos con course->steps en el peor valor posible, para asegurar que los elementos recibira al menos una reaseignacion de valores*/
void clean_course(t_course *course)
{
	ft_memset(course, 0, sizeof(t_course));
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
void	try_rrr_way(t_place place_a , t_place place_b, t_course *course)
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
