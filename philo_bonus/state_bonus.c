/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:22 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/23 16:10:10 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <sys/semaphore.h>

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
			settings->eating = 1;
			get_time(settings, 1);
			print_state(settings->id, settings, 2, settings->curr);
			ft_usleep(settings->time_eat, settings);
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
			settings->eating = 0;
			get_time(settings, 2);
			print_state(settings->id, settings, 3, settings->curr);
			if (settings->progress)
				ft_usleep(settings->time_sleep, settings);
			settings->num_rounds++;
		}
	}
}

void	*routine(void *data)
{
	t_settings		*settings;

	settings = (t_settings *) data;
	while (1)
	{
		get_time(settings, 2);
		if (settings->curr - settings->start_sec < 0)
			usleep((-settings->curr + settings->start_sec) * 499);
		else
			break ;
	}
	pthread_create(&settings->bouncer, NULL, &bouncer, settings);
	while (settings->progress)
	{
		take_forks(settings);
		start_eating(settings);
		if (settings->nbr_phil == 1)
		{
			ft_usleep(settings->time_die, settings);
			get_time(settings, 2);
			if (settings->curr - settings->start_sec >= settings->time_die)
				print_state(settings->id, settings, 4, settings->curr);
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
	if (!settings->num_meals)
		sem_wait(settings->ko);
	else
		my_sem(settings->pay_now, settings->nbr_phil, sem_wait);
	i = -1;
	while (++i < settings->nbr_phil)
		kill(settings->pids[i], 15);
}
