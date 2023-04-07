/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:47:21 by gothmane          #+#    #+#             */
/*   Updated: 2023/04/04 20:12:17 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char	**av, int ac)
{
	int	c;

	c = 0;
	while (++c < ac)
	{
		if (ft_atoi(av[c]) <= 0)
			return (1);
	}
	return (0);
}

void	clean_all(t_vars var, pthread_t *th,
			pthread_mutex_t *forks, pthread_mutex_t *mine)
{
	forks_destroyer(forks, var.nbr_ph, mine);
	frees_wrapper(var.ph, th, forks, mine);
}

int	main(int ac, char **av)
{
	t_vars			var;
	pthread_mutex_t	*mine;
	pthread_t		*th;
	pthread_mutex_t	*forks;

	init_vars_main(&var, &mine, &th, &forks);
	if (ac == 5 || ac == 6)
	{
		if (check_args(av, ac) == 1)
			return (1);
		var.nbr_ph = ft_atoi(av[1]);
		init_philo_memory(&var.ph, &var.nbr_ph, &mine, &th);
		forks = philos_main_init(var, mine, av);
		create_threads(var.nbr_ph, var.ph, th);
		if (!forks || checker_philo(var.ph, av) == 0)
		{
			if (ft_atoi(av[1]) > 1 && !join_threads(var.nbr_ph, th))
				return (0);
			clean_all(var, th, forks, mine);
			return (1);
		}
		clean_all(var, th, forks, mine);
	}
	return (0);
}
