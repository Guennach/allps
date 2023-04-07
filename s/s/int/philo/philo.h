/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:00:28 by gothmane          #+#    #+#             */
/*   Updated: 2023/04/01 15:33:04 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct v_time
{
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	long long		birth;
}			t_time;

typedef struct v_info
{
	struct timeval	first;
	long			start;
}				t_info;

typedef struct v_lock
{
	pthread_mutex_t	mtx;
}				t_lock;

typedef struct v_infos
{
	int	eating_counter;
}				t_infos;

typedef struct v_philo
{
	int				id;
	int				lf;
	int				checker;
	int				eating_counter;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	pthread_mutex_t	*forks;
	long long		start_time;
	long long		last_meal_time;
	t_info			*tinf;
	pthread_mutex_t	*mtxa;
	int				rf;
	int				check;
	int				eating_check;
	int				*point;
	int				*eating_point;
	int				eating_c;
}				t_philo;

typedef struct v_vars{
	int				i;
	t_philo			*ph;
	int				nbr_ph;
	t_info			*time_philo;
	pthread_mutex_t	*mtxa;
}				t_vars;

// Args checker
int				ft_atoi(char *str);

// Routines
void			*routine(void *data);

// Init variables
void			philosopher_init(char **av, t_philo *ph,
					int id, pthread_mutex_t *mt);

// threads and mutex init
int				create_threads(int nbr_ph, t_philo *ph, pthread_t *thread);
pthread_mutex_t	*forks_init(int nbr_philo);

// time
long long		getcurrenttime(t_info *tv);
void			ft_usleep(long long time_to_do, t_info *tf, int *check);
int				checker_philo(t_philo *ph, char **av);
int				join_threads(int nbr_ph, pthread_t *thread);

//frees
int				free_philo(t_philo *ph);
int				free_threads(pthread_t *thread);
int				free_mutexes(pthread_mutex_t *forks, pthread_mutex_t *mine);
int				frees_wrapper(t_philo *ph, pthread_t *thread,
					pthread_mutex_t *forks, pthread_mutex_t *mine);

//initvars.c

void			init_vars(
					pthread_mutex_t **mtx, int *nbr_ph);
void			init_variables(t_philo **ph,
					t_info **tp, int *i);
void	init_philo_memory(t_philo **ph, int *nbr, pthread_mutex_t **mine, pthread_t **th);

void			philo_init_loop(t_philo *ph, pthread_mutex_t **mt,
					t_info **tf, int i);
pthread_mutex_t	*philos_main_init(t_vars var, pthread_mutex_t *mine, char **av);

//init.c
void	init_vars_main(t_vars *var, pthread_mutex_t	**mine, pthread_t **th, pthread_mutex_t **forks);

//destroyers.c
int				forks_destroyer(pthread_mutex_t *mt,
					int nbr_philo, pthread_mutex_t *mine);

#endif