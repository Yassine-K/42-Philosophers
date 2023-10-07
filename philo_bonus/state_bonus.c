/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:22 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/25 19:49:21 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <sys/semaphore.h>
#include <unistd.h>

void	take_forks(t_settings *settings)
{
	settings->eating = 0;
	if (settings->progress)
	{
		get_time(settings, 2);
		print_state(settings->id, settings, 0, settings->curr);
		get_time(settings, 2);
		print_state(settings->id, settings, 1, settings->curr);
		if (settings->nbr_phil > 1)
		{
			sem_wait(settings->forks);
			sem_wait(settings->forks);
			get_time(settings, 2);
			print_state(settings->id, settings, 1, settings->curr);
			get_time(settings, 2);
			print_state(settings->id, settings, 2, settings->curr);
			ft_usleep(settings->time_eat, settings);
			get_time(settings, 1);
			settings->eating = 1;
			sem_post(settings->forks);
			sem_post(settings->forks);
		}
	}
}

void	start_eating(t_settings *settings)
{
	if (settings->progress)
	{
		if (settings->eating)
		{
			settings->num_rounds++;
			settings->eating = 0;
			sem_wait(settings->timer);
			get_time(settings, 2);
			sem_post(settings->timer);
			print_state(settings->id, settings, 3, settings->curr);
			if (settings->progress)
				ft_usleep(settings->time_sleep, settings);
		}
	}
}

void	*routine(void *data)
{
	t_settings		*s;

	s = (t_settings *) data;
	get_time(s, 2);
	while (s->curr < s->start_sec)
	{
		usleep(200);
		get_time(s, 2);
	}
	pthread_create(&s->bouncer, NULL, &bouncer, s);
	while (1)
	{
		take_forks(s);
		start_eating(s);
		if (s->nbr_phil == 1)
		{
			ft_usleep(s->time_die, s);
			get_time(s, 2);
			if (s->curr - s->start_sec >= s->time_die)
				print_state(s->id, s, 4, s->curr - s->start_sec);
		}
	}
	return (data);
}

void	my_sem(sem_t *sem, int nbr, int (*ft_sem) (sem_t *))
{
	int	i;

	i = -1;
	while (++i < nbr)
		ft_sem(sem);
}

void	create_proc(t_settings *settings)
{
	int		i;
	pid_t	pid;

	i = -1;
	settings->id = -1;
	settings->start_sec += 300;
	settings->pids = malloc(sizeof(int) * settings->nbr_phil);
	while (++settings->id < settings->nbr_phil)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (!pid)
			routine(settings);
		else if (pid > 0)
			settings->pids[settings->id] = pid;
	}
	if (!settings->n_meals)
		sem_wait(settings->ko);
	else
		my_sem(settings->pay_now, settings->nbr_phil, sem_wait);
	i = -1;
	while (++i < settings->nbr_phil)
		kill(settings->pids[i], 15);
}
