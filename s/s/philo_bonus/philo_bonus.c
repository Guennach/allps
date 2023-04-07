/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:07:16 by gothmane          #+#    #+#             */
/*   Updated: 2023/04/07 18:13:57 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long getcurrenttime()
{
	long long time;
	struct timeval first;
	gettimeofday(&first, NULL);
	time = ((first.tv_sec * 1000) + (first.tv_usec / 1000));
	return (time);
}

void ft_usleep(long long time_to_do, int *check)
{
	long long ct;
	long long tmp;

	ct = getcurrenttime();
	tmp = getcurrenttime();
	while ((tmp - ct) < time_to_do)
	{
		if (*check == 1)
			return;
		usleep(1000);
		tmp = getcurrenttime();
	}
}

// int create_threads(int nbr_ph, t_philo *ph, pthread_t *thread)
// {
// 	int i;

// 	i = -1;
// 	if (!thread)
// 		return (0);
// 	while (++i < nbr_ph)
// 	{
// 		if (pthread_create(&thread[i], NULL, &routine, ((void *)&ph[i])))
// 			return (0);
// 		usleep(50);
// 	}
// 	return (1);
// }

int death_checker(t_philo *ph, int *a, int *c, int i)
{
	long long check;

	check = getcurrenttime() - ph[i].last_meal_time;
	if (check > ph[i].time_to_die)
	{
		printf("CHECK = %lld || las time eating = %lld \n", check, ph[i].last_meal_time);
		*a = 1;
		*c = 1;
		sem_wait(ph->pr);
		usleep(500);
		printf("%lld %d died\n", getcurrenttime() - ph[i].start_time, ph[i].id);
		sem_post(ph->pr);
		return (0);
	}
	return (1);
}

void var_init_checkers(int *checker_eat, int *a, int *i, int *c)
{
	*checker_eat = 0;
	*a = 0;
	*c = 0;
	*i = 0;
}

int checker_philo(t_philo *ph)
{
	int a;
	int checker_eat;
	int j;

	var_init_checkers(&checker_eat, &a, &j, &ph->check);
	while (a == 0)
	{
		j = -1;
		while (++j < ph[0].nbr_ph)
		{
			if (ph[j].last_meal_time > 0 && death_checker(ph, &a, &ph->check, j) == 0)
				return (0);
		}
	}
	return (1);
}

void *routine(void *data)
{
	t_philo *ph;
	int		c;

	c = 0;
	ph = data;
	while (1)
	{
		long long check;

		check = getcurrenttime() - ph->last_meal_time;
		if (check > ph->time_to_die)
		{
			// printf(">>>>>>>>>>>>>>>>>>>>>>>>>CHECK = %lld || las time eating = %lld<<<<<<<<<<<<<<<<<<<<<<<<<<\n", check, ph->last_meal_time);
			sem_wait(ph->pr);
			usleep(100);
			printf("%lld %d died\n", getcurrenttime() - ph->start_time, ph->id);
			exit(0);
			sem_post(ph->pr);
		}
		if (ph->eating_counter == -2)
		{
			exit(0);
			// printf(">>>>>>>>>>>>>>>>> ph->check = %d <<<<<<<<<<<<<<<\n", ph->eating_counter);
			// return(0);
		}
		usleep(100);
	}
	return (0);
}

void	philo(t_philo *phs, pthread_t *thread)
{
	sem_wait(phs->pr);
	pthread_create(thread, NULL, routine, phs);
	sem_post(phs->pr);
	usleep(100);
	while (1)
	{
		sem_wait(phs->pr);
		printf("%lld %d is thinking\n", (getcurrenttime() - phs->start_time), phs->id);
		sem_post(phs->pr);
		sem_wait(phs->chops);
		sem_wait(phs->pr);
		printf("%lld %d has taken a fork\n", (getcurrenttime() - phs->start_time), phs->id);
		sem_post(phs->pr);
		sem_wait(phs->chops);
		sem_wait(phs->pr);
		printf("%lld %d has taken a fork\n", (getcurrenttime() - phs->start_time), phs->id);
		sem_post(phs->pr);
		sem_wait(phs->pr);
		printf("%lld %d is eating\n", (getcurrenttime() - phs->start_time), phs->id);
		// phs->last_meal_time = getcurrenttime();
		if (phs->eating_counter != 10)
		{

			sem_wait(phs->vars);
			phs->eating_counter--;
			sem_post(phs->vars);
		}
		sem_post(phs->pr);
		usleep(phs->time_to_eat * 1000);
		sem_post(phs->chops);
		sem_post(phs->chops);
		sem_wait(phs->pr);
		printf("%lld %d is sleeping\n", (getcurrenttime() - phs->start_time), phs->id);
		sem_post(phs->pr);
		usleep(phs->time_to_sleep * 1000);
	}
}

void	freere(t_philo *ph, pthread_t *thread, int *pid)
{
	sem_close(ph->chops);
	sem_close(ph->pr);
	free(ph->res->pid);
	free(thread);
	free(pid);
}

int main(int ac, char **av)
{
	int 		i;
	int 		status;
	int 		nbr_ph;
	t_philo 	*phs;
	sem_t 		*chops;
	sem_t 		*ps;
	pthread_t 	*thread;
	int 		*pid;
	t_res		*res;
	sem_t 		*x;

	res->pid = malloc(sizeof(int) * ft_atoi(av[1]));
	thread = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	pid = malloc(sizeof(int) * ft_atoi(av[1]));
	x = NULL;
	i = -1;
	phs = NULL;
	chops = NULL;
	status = -1;

	
	// res = NULL;
	if (ac == 5 || ac == 6)
	{
		nbr_ph = ft_atoi(av[1]);
		phs = malloc(sizeof(t_philo) * nbr_ph);
		sem_unlink("/FORKS");
		chops = sem_open("/FORKS", O_CREAT | O_EXCL, 0644, nbr_ph);
		sem_unlink("/PS");
		ps = sem_open("/PS", O_CREAT | O_EXCL, 0644, 1);
		sem_unlink("/VARS");
		x = sem_open("/VARS", O_CREAT | O_EXCL, 0644, 1);
		if (chops == SEM_FAILED || ps == SEM_FAILED)
		{
			printf("FORKS\n");
			exit(0);
		}
		// sem_t	*f = NULL;

		// sem_unlink("/VARS");
		// f = sem_open("/VARS", O_CREAT | O_EXCL, 0644, 1)
		phs->check = 0;
		while (++i < nbr_ph)
		{
			phs[i].id = (i + 1);
			phs[i].start_time = getcurrenttime();
			phs[i].time_to_die = ft_atoi(av[2]);
			phs[i].time_to_eat = ft_atoi(av[3]);
			phs[i].time_to_sleep = ft_atoi(av[4]);
			phs[i].last_meal_time = getcurrenttime();
			phs[i].chops = chops;
			phs[i].point = &phs->check;
			phs[i].pr = ps;
			phs[i].vars = x;
			phs[i].nbr_ph = nbr_ph;
			phs[i].res = res;
			if (av[5])
				phs[i].eating_counter = ft_atoi(av[5]);
			else
				phs[i].eating_counter = -10;
		}
		i = 0;
		pid_t pi;
		while (i < nbr_ph)
		{
			pi = fork();
			if (pi == 0)
				philo(&phs[i], &thread[i]);
			else if (pi > 0)
				res->pid[i] = pi;
			i++;
		}
		waitpid(-1, &status, 0);
		if (status == 0)
		{
			int i = nbr_ph - 1;
			while (i >= 0)
				kill(res->pid[i--], SIGINT);
			usleep(100);
		}
		freere(phs, thread, pid);
		while (1);
	}
	return 0;
}