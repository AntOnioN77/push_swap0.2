/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:31:07 by antofern          #+#    #+#             */
/*   Updated: 2024/12/11 00:00:27 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/headers/ring.h"
#include "../libft/headers/parsing.h"
#include "../push_swap.h"
#include <limits.h>

/*Checks that all values passed as arguments are convertible to int,
tolerates only one sign(+-), tolerates spaces at the beginning of
each string but no other characters, accepts only decimal notation*/
t_bool	are_valid_int(int argc, char **argv)
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

static int	fill_stack(t_ring *arr, int n_args, char **args)
{
	int	i;

	i = 0;
	while (i < n_args)
	{
		arr->buff[i] = 0;
		i++;
	}
	i = n_args;
	while (i > 0)
	{
		ring_add_head(arr, ft_atoi(args[i - 1]));
		i--;
	}
	return (OK);
}

int	countargs(char **argv)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	while (argv[i])
	{
		n = n + ft_count_substr(argv[i], ' ');
		if (!ft_count_substr(argv[i], ' '))
			n++;
		i++;
	}
	return (n);
}

void	split_all(int argc, char **argv, char **args)
{
	int		i;
	int		j;
	int		q;
	char	**tmp;

	i = 1;
	q = 0;
	while (i < argc)
	{
		j = 0;
		tmp = ft_split(argv[i], ' ');
		if (tmp == NULL)
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
		free(tmp);
		i++;
	}
}

void	parsargs(int argc, char **argv, t_ring **a, t_ring **b)
{
	int		n_args;
	char	**args;

	n_args = countargs(argv);
	if (n_args == 0)
		exit (EXIT_FAILURE);
	args = malloc((n_args + 1) * sizeof(char *));
	ft_bzero(args, (n_args + 1) * sizeof(char *));
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
