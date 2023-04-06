/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:24:56 by gothmane          #+#    #+#             */
/*   Updated: 2023/04/01 15:36:04 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_philo(t_philo *ph)
{
	if (!ph)
		return (1);
	free(ph);
	return (0);
}

int	free_threads(pthread_t *thread)
{
	if (!thread)
		return (1);
	free(thread);
	return (0);
}

int	free_mutexes(pthread_mutex_t *forks, pthread_mutex_t *mine)
{
	if (!forks || !mine)
		return (1);
	free(forks);
	free(mine);
	return (0);
}

int	frees_wrapper(t_philo *ph, pthread_t *thread,
	pthread_mutex_t *forks, pthread_mutex_t *mine)
{
	free_philo(ph);
	free_threads(thread);
	free_mutexes(forks, mine);
	return (0);
}
