/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_has_duplicates.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:21:51 by antofern          #+#    #+#             */
/*   Updated: 2024/08/28 12:22:07 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ring.h"

/*Compara todos los elementos de la lista buscando duplicados.*/
bool	ring_has_duplicates(t_ring *a)
{
	t_level current;
	t_level	compare;
	int end;

	end = (a->fill -1);
	current = 0;
	while(current < end)
	{
		compare = current +1;
		while(compare <= end)
		{
			if (ring_get_level(a, current) == ring_get_level(a, compare))
				return (TRUE);
			compare++;
		}
		current++;
	}
	return(FALSE);
}