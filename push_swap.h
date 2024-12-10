/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:01:26 by antofern          #+#    #+#             */
/*   Updated: 2024/12/08 15:00:02 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stddef.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include "libft/headers/ring.h"


// Cambiar nombre de documento a push swap. Circular array esta en libft

typedef struct s_place
{
	char	stack_name;
	t_level	level;
	t_level	reverse_level; //reverse level es un valor positivo aunque represente una posicion inversa a level
	t_level	middel_of_stack; //PARECE EN DESUSO
	int		stack_size; //PARECE EN DESUSO
}	t_place;

typedef struct s_course
{
	int steps;
	int	rr;
	int	rrr;
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int pa;
}	t_course;

void	sa(t_ring *a);
void	sb(t_ring *b);
void	ss(t_ring *a, t_ring *b);
void	pa(t_ring *b, t_ring *a);
void	pb(t_ring *a, t_ring *b);
void	ra(t_ring *a);
void	rb(t_ring *b);
void	rr(t_ring *a, t_ring *b);
void	rra(t_ring *a);
void	rrb(t_ring *b);
void	rrr(t_ring *a, t_ring *b);
t_level	find_place_for(t_ring *stack_a, int n);
void	try_rr_way(t_place deeper , t_place higher, t_course *course);
void	synch_rotation(t_place a, t_place b, t_course *best_course);
void	asynch_rotation(t_place position_in_a, t_place position_in_b, t_course *best_course);
t_place	setup_place(t_ring *stack, t_level level, char stack_name);
void	find_rigth_course(t_ring *stack_a, t_ring *stack_b ,t_course *best_course);
void	clean_course(t_course *course);
void	preorder(t_ring *a, t_ring *b);
bool	are_valid_int(int argc, char **argv);
void	parsargs(int argc, char **argv, t_ring **a, t_ring **b);
void	handle_error(void *to_free, void (*free_func)(void *));

#endif /* CIRCULAR_ARRAY_H */
