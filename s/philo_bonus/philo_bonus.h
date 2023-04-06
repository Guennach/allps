/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:08:37 by gothmane          #+#    #+#             */
/*   Updated: 2023/04/06 20:32:48 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS
# define PHILO_BONUS

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

typedef struct s_res
{
	int		*pid;
}				t_res;

typedef struct s_philo
{
	int			time_to_eat;
	int			time_to_die;
	int			id;
	int			time_to_sleep;
	int			eating_counter;
	sem_t 		*chops;
	sem_t		*pr;
	long long 	start_time;
	long long	last_meal_time;
	int			check;
	int			*point;
	int			nbr_ph;
	int			pid;
	t_res		*res;
}				t_philo;

int	ft_atoi(char *str);


#endif