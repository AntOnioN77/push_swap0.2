/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:31:07 by antofern          #+#    #+#             */
/*   Updated: 2024/12/10 11:31:06 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/headers/ring.h"
#include "../libft/headers/parsing.h"
#include <limits.h>

/*Checks that all values passed as arguments are convertible to int,
tolerates only one sign(+-), tolerates spaces at the beginning of
each string but no other characters, accepts only decimal notation*/
bool	are_valid_int(int argc, char **argv)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (size_t)argc)
	{
		j = 0;
		while (argv[i] && argv[i][j] == ' ')
			j++;	
		if (!argv[i] || !ft_is_in_bounds_int(&argv[i][j]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}


static int	fill_stack(t_ring *arr, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)// NECESARIO?????
	{
		arr->buff[i] = 0;
		i++;
	}
	i = argc;
	while (i > 0)
	{
		ring_add_head(arr, ft_atoi(argv[i - 1]));
		i--;
	}
	return (OK);
}

int countargs(char **argv)
{
	int n;
	int	i;

	n = 0;
	i = 1;
	while(argv[i])
	{
		n = n + ft_count_substr(argv[i],' ');
		if (!ft_count_substr(argv[i],' '))
			n++;
		i++;
	}
	return(n);
}

//retorna 1 si 

void split_all(int argc, char **argv, char **args)
{
	int	i;
	int j;
	int q;
	char **tmp;

	i = 1;
	q = 0;
	while(i < argc)
	{
		j = 0;
		tmp = ft_split(argv[i], ' ');
		if(tmp == NULL)
		{
			ft_free_split(args);
			exit(EXIT_FAILURE);
		}
		while (tmp[j])
		{
			args[q] = tmp[j];
			q++;
			j++;			
		}
		free(tmp); //libera solo el array de cadenas creado por split, pero no las propias cadenas, que ahora estan referenciadas en argv
		i++;

	}
}

void handle_error(void *to_free, void (*free_func)(void *))
{
	if (to_free != NULL)
		free_func(to_free);
	write(2, "Error\n", 6);
	exit (EXIT_FAILURE);
}

void	parsargs(int argc, char **argv, t_ring **a, t_ring **b)
{
	int n_args;
	char **args;

	n_args = countargs(argv);
	if (n_args == 0)
		exit (EXIT_FAILURE);
	args = malloc((n_args + 1) * sizeof(char *));
	ft_bzero(args, (n_args + 1) * sizeof(char*));
	split_all(argc, argv, args);
	if (!are_valid_int(n_args, args))
		handle_error(args, (void (*)(void *))ft_free_split);
	*a = ring_init(n_args);
	if (*a == NULL)
		handle_error(args, (void (*)(void *))ft_free_split);
	fill_stack(*a, n_args, args);
	ft_free_split(args);
	if (ring_has_duplicates(*a))
		handle_error(*a, (void (*)(void *))ring_free);
	*b = ring_init(n_args);
	if (*b == NULL)
		ring_free(*a);
}
