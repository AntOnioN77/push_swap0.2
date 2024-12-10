
#include "push_swap.h"
#include "libft/headers/ring.h"

#include <stdio.h>//borrar


/*retorna el numero, que quedara en la nºesima posicion cuando el stack esté ordenado*/
int find_nth(t_ring *ring, int n_elements, int nth)
{
	int i;
	int j;
	int counter;

	j = 0;
	while (j < n_elements)
	{
		i = 0;
		counter = 0;
		while (i < n_elements)
		{
			if (ring_get_level(ring, j) > ring_get_level(ring, i))
				counter++;
			i++;
		}
		if(counter == nth)
			return (ring_get_level(ring, j));
		j++;
	}
	return (0);
}


//envia a la pila b el tercer chunk, acumulado en el back de la pila a*/
void pb_lasts(t_ring *a, t_ring *b, int bigest, int smalest)
{
	while (a->fill > 2)
	{
		if (ring_get_head(a) == bigest || ring_get_head(a) == smalest)
			ra(a);
		else
			pb(a, b);
	}
}

//Envia a la pila b tres chunks, con los valores medios maximos y minimos.
void preorder_many(t_ring *a, t_ring *b, int bigest, int smalest)
{
	int first_terctil;
	int second_terctil;
	int check;

	first_terctil = find_nth(a, a->fill, a->fill / 3);
	second_terctil = find_nth(a, a->fill, (a->fill / 3) * 2);
	check = a->fill;
	while (check > 0)
	{
		if (ring_get_head(a) == bigest || ring_get_head(a) == smalest)
			ra(a);
		else if (ring_get_head(a) > second_terctil) //mayores
			ra(a);
		else if (ring_get_head(a) > first_terctil) //medios
 		{
			pb(a, b);
			rb(b);
		}
		else if (ring_get_head(a) <= first_terctil) // mas bajos
			pb(a, b);
		check --;
	}
	pb_lasts(a, b, bigest, smalest);
}

void preorder_few(t_ring *a, t_ring *b, int bigest, int smalest)
{
	while (a->fill > 3)
	{
		if (ring_get_head(a) == bigest || ring_get_head(a) == smalest)
			ra(a);
		else
			pb(a, b);
	}
	
	if (!((ring_get_level(a, 0) < ring_get_level(a, 1) && ring_get_level(a, 1) < ring_get_level(a, 2)) ||
	(ring_get_level(a, 1) < ring_get_level(a, 2) && ring_get_level(a, 2) < ring_get_level(a, 0)) ||
	(ring_get_level(a, 2) < ring_get_level(a, 0) && ring_get_level(a, 0) < ring_get_level(a, 1))))
		sa(a);
}

int is_correlative(t_ring *a, int smalest)
{
	t_level level;
	int check;

	level = ring_find_value(a, smalest);

	check = a->fill;
	while (check > 0)
	{
		level++;
		if (ring_get_level(a, level - 1) > ring_get_level(a, level))
			break;
		check--;
	}
	if (check == 1)
		return (1);
	return (0);
}

void preorder(t_ring *a, t_ring *b)
{
	int bigest;
	int smalest;

	bigest = ring_find_bigest(a);
	smalest = ring_find_smallest(a);
//printf("is correlative %d\n", is_correlative(a, smalest));
	if (!is_correlative(a, smalest))
	{
		if(a->fill > 70)
			preorder_many(a, b, bigest, smalest);
		else
			preorder_few(a, b, bigest, smalest);
	}
}