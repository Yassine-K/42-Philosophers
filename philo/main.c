/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:00 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/26 18:22:04 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	data_init(t_settings *settings, char **av, int ac)
{
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
	pthread_mutex_init(&settings->mutex, NULL);
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

void	bouncer(t_settings *settings)
{
	t_single_p		*tmp;
	struct timeval	time;
	time_t			mil;
	
	tmp = settings->philos;
	while (settings->progress)
	{
		gettimeofday(&time, NULL);
		mil = time.tv_sec * 1000 + time.tv_usec / 1000 - settings->start_sec;
		if (mil - tmp->last_meal - settings->start_sec >= settings->time_die)
		{
			pthread_mutex_lock(&settings->mutex);
			settings->progress = 0;
			pthread_mutex_unlock(&settings->mutex);
			printf("%ld %d %s\n", mil, tmp->id, "is dead");
		}
		else
			tmp = tmp->next;
	}
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
		bouncer(settings);
		wait_for_thread(&settings->philos);
	}
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
	sit_arround_table(settings, settings->nbr_phil);
	if (!settings->philos)
	{
		no_cash_to_pay(&settings->philos);
		pthread_mutex_destroy(&settings->mutex);
		return (2);
	}
	pthread_mutex_destroy(&settings->mutex);
	no_cash_to_pay(&settings->philos);
	free(settings);
	return (0);
}
