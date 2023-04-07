/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initvars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:57:41 by gothmane          #+#    #+#             */
/*   Updated: 2023/04/01 16:11:40 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_variables(t_philo **ph, t_info **tp, int *i)
{
	*i = 0;
	*ph = NULL;
	*tp = malloc(sizeof(t_info));
}

void	init_philo_memory(t_philo **ph, int *nbr,
			pthread_mutex_t **mine, pthread_t **th)
{
	(*ph) = malloc(sizeof(t_philo) * (*nbr));
	(*mine) = malloc(sizeof(pthread_mutex_t));
	(*th) = malloc(sizeof(*th) * (*nbr));
	pthread_mutex_init((*mine), NULL);
}

void	philo_init_loop(t_philo *ph, pthread_mutex_t **mt, t_info **tf, int i)
{
	ph[i].tinf = *tf;
	ph[i].start_time = getcurrenttime((*tf));
	ph[i].mtxa = *mt;
	ph[i].check = 0;
	ph[i].eating_check = -1;
	ph[i].point = &ph->check;
	ph[i].eating_point = &ph->eating_check;
}

pthread_mutex_t	*philos_main_init(t_vars var, pthread_mutex_t *mine, char **av)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(forks) * (var.nbr_ph));
	while (++i < var.nbr_ph)
		pthread_mutex_init(&forks[i], NULL);
	while (var.i < var.nbr_ph)
	{
		philo_init_loop(var.ph, &mine, &var.time_philo, var.i);
		philosopher_init(av, var.ph, (var.i++), forks);
	}
	return (forks);
}
