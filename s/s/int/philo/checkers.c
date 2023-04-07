/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:44:59 by gothmane          #+#    #+#             */
/*   Updated: 2023/04/01 16:10:53 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_checker(t_philo *ph, int *a, int *c, int i)
{
	long	check;

	check = getcurrenttime(ph->tinf) - ph[i].last_meal_time;
	if (check > ph[i].time_to_die)
	{
		*a = 1;
		*c = 1;
		pthread_mutex_lock(ph->mtxa);
		usleep(500);
		if (ph[i].eating_c)
			printf("%lld %d died\n", getcurrenttime(ph->tinf)
				- ph[i].start_time, ph[i].id);
		pthread_mutex_unlock(ph->mtxa);
		return (0);
	}
	return (1);
}

void	var_init_checkers(int *checker_eat, int *a, int *i, int *c)
{
	*checker_eat = 0;
	*a = 0;
	*c = 0;
	*i = 0;
}

int	checker_philo(t_philo *ph, char **av)
{
	int	a;
	int	checker_eat;
	int	j;

	var_init_checkers(&checker_eat, &a, &j, &ph->check);
	while (a == 0)
	{
		j = -1;
		while (++j < ft_atoi(av[1]))
		{	
			if (ph[j].last_meal_time > 0
				&& death_checker(ph, &a, &ph->check, j) == 0)
				return (0);
		}
	}
	return (1);
}
