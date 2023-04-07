/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:00:19 by gothmane          #+#    #+#             */
/*   Updated: 2023/03/31 18:24:34 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_destroyer(pthread_mutex_t *mt,
	int nbr_philo, pthread_mutex_t *mine)
{
	int	i;

	i = -1;
	while (++i < nbr_philo)
		pthread_mutex_destroy(&(mt[i]));
	pthread_mutex_destroy(mine);
	return (1);
}
