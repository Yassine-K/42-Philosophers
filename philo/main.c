/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:00 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/23 21:55:58 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <sys/time.h>
#include <time.h>

void	data_init(t_settings *settings, char **av, int ac)
{
	int	i;

	i = -1;
	settings->nbr_phil = ft_atoi(av[1]);
	settings->time_die = ft_atoi(av[2]);
	settings->time_eat = ft_atoi(av[3]);
	settings->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		settings->num_meals = ft_atoi(av[5]);
	else
		settings->num_meals = 0;
	get_time(settings, 0);
	settings->arr[0] = "is thinking";
	settings->arr[1] = "has taken a fork";
	settings->arr[2] = "is eating";
	settings->arr[3] = "is sleeping";
	settings->arr[4] = "died";
	settings->progress = 1;
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

void	sit_arround_table(t_settings *settings, int seats)
{
	int	i;

	i = -1;
	settings->philos = malloc(sizeof(t_single_p));
	while (++i < seats)
	{
		add_back(&settings->philos, new_phil(i + 1));
		if (!settings->philos)
			break ;
	}
	if (settings->philos)
	{
		find_last(settings->philos)->next = settings->philos;
		create_thread(&settings->philos, settings);
		wait_for_thread(&settings->philos);
	}
}

void	bouncer(t_settings *settings)
{
	t_single_p		*tmp;
	struct timeval	time;
	time_t			curr_time;

	tmp = settings->philos;
	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (settings->progress)
	{
		if (curr_time - settings->start_sec >= settings->time_die)
			settings->progress = 0;
		else
			tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_settings	settings;

	if (ac < 5 || ac > 6 || !check_errors(av))
	{
		printf("Invalid Input!");
		return (2);
	}
	data_init(&settings, av, ac);
	sit_arround_table(&settings, settings.nbr_phil);
	if (!settings.philos)
	{
		no_cash_to_pay(&settings.philos);
		return (2);
	}
	bouncer(&settings);
	no_cash_to_pay(&settings.philos);
	return (0);
}
