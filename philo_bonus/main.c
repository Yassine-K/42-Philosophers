/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:00 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/18 15:32:00 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <sys/fcntl.h>
#include <sys/semaphore.h>

void	data_init(t_settings *settings, char **av, int ac)
{
	settings->nbr_phil = ft_atoi(av[1]);
	settings->time_die = ft_atoi(av[2]);
	settings->time_eat = ft_atoi(av[3]);
	settings->time_sleep = ft_atoi(av[4]);
	settings->num_rounds = 0;
	settings->num_meals = 0;
	settings->progress = 1;
	if (ac == 6)
		settings->num_meals = ft_atoi(av[5]);
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
	settings->forks = sem_open("/Forks", O_CREAT | O_EXCL, 0644, settings->nbr_phil);
	settings->print = sem_open("/Death", O_CREAT | O_EXCL, 0644, 1);
	settings->ko = sem_open("/Print", O_CREAT | O_EXCL, 0644, 0);
	settings->pay_now = sem_open("/Pay", O_CREAT | O_EXCL, 0644);
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
	struct timeval	time;
	t_settings		*settings;
	time_t			mil;
	time_t			start;

	settings = (t_settings *) data;
	while (1)
	{
		gettimeofday(&time, NULL);
		mil = time.tv_sec * 1000 + time.tv_usec / 1000 - settings->start_sec;
		start = settings->last_meal - settings->start_sec;
		if (start < 0)
			start = 0;
		if (mil - start >= settings->time_die || !settings->progress)
		{
			settings->progress = 0;
			print_state(settings->id, settings, 4, mil);
		}
	}
	return (data);
}

void	sit_arround_table(t_settings *settings)
{
	settings->curr = 0;
	settings->last_meal = 0;
	settings->rounds = 0;
	create_proc(settings);
	//wait_for_proc(settings);
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
