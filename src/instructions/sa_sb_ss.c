/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_sb_ss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:40:35 by antofern          #+#    #+#             */
/*   Updated: 2024/09/02 12:57:38 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/headers/ring.h"

void	sa(t_ring *a)
{
	if (a == NULL)
		return ;
	if (ring_swap(a) == ERROR)
		return ;
	write(1, "sa\n", 3);
}

void	sb(t_ring *b)
{
	if (b == NULL)
		return ;
	if (ring_swap(b) == ERROR)
		return ;
	write(1, "sb\n", 3);
}

void	ss(t_ring *a, t_ring *b)
{
	if (a == NULL)
		return ;
	if (b == NULL)
		return ;
	if (ring_swap(a) == ERROR)
		return ;
	if (ring_swap(b) == ERROR)
	{
		ring_swap(a);
		return ;
	}
	write(1, "ss\n", 3);
}
