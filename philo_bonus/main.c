/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:00 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/25 19:58:09 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <unistd.h>

void	data_init(t_settings *settings, char **av, int ac)
{
	settings->nbr_phil = ft_atoi(av[1]);
	settings->time_die = ft_atoi(av[2]);
	settings->time_eat = ft_atoi(av[3]);
	settings->time_sleep = ft_atoi(av[4]);
	settings->num_rounds = 0;
	settings->n_meals = 0;
	settings->progress = 1;
	if (ac == 6)
		settings->n_meals = ft_atoi(av[5]);
	get_time(settings, 0);
	settings->arr[0] = "is thinking";
	settings->arr[1] = "has taken a fork";
	settings->arr[2] = "is eating";
	settings->arr[3] = "is sleeping";
	settings->arr[4] = "died";
	sem_unlink("/Forks");
	sem_unlink("/Death");
	sem_unlink("/Print");
	sem_unlink("/Pay");
	sem_unlink("/Time");
	settings->forks = sem_open("/Forks", O_CREAT
			| O_EXCL, 0644, settings->nbr_phil);
	settings->print = sem_open("/Print", O_CREAT | O_EXCL, 0644, 1);
	settings->ko = sem_open("/Death", O_CREAT | O_EXCL, 0644, 0);
	settings->pay_now = sem_open("/Pay", O_CREAT | O_EXCL, 0644, 0);
}

int	check_errors(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		if (!ft_atoi(av[i]))
			return (0);
	return (1);
}

void	*bouncer(void *data)
{
	t_settings		*s;
	struct timeval	time;
	time_t			t[2];

	s = (t_settings *) data;
	while (1)
	{
		sem_wait(s->timer);
		gettimeofday(&time, NULL);
		t[mil] = time.tv_sec * 1000 + time.tv_usec / 1000 - s->start_sec;
		t[start] = s->last_meal - s->start_sec;
		sem_post(s->timer);
		if (t[start] < 0)
			t[start] = 0;
		if (t[mil] - t[start] >= s->time_die || !s->progress)
		{
			print_state(s->id, s, 4, t[mil]);
			if (s->n_meals)
				my_sem(s->pay_now, s->nbr_phil, sem_post);
		}
		else if (s->n_meals && s->num_rounds == s->n_meals && ++s->done == 1)
			sem_post(s->pay_now);
		usleep(100);
	}
	return (data);
}

void	sit_arround_table(t_settings *settings)
{
	settings->curr = 0;
	settings->last_meal = 0;
	settings->done = 0;
	settings->timer = sem_open("/Time", O_CREAT | O_EXCL, 0644, 1);
	create_proc(settings);
}

int	main(int ac, char **av)
{
	t_settings	*settings;

	if (ac < 5 || ac > 6 || !check_errors(av))
	{
		printf("Invalid Input!");
		return (2);
	}
	settings = (t_settings *) malloc(sizeof(t_settings));
	data_init(settings, av, ac);
	sit_arround_table(settings);
	no_cash_to_pay(settings);
	return (0);
}
