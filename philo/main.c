/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:00 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/22 19:06:41 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	ft_atoi(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i] && s[i] < 33)
		i++;
	if (s[i] == '-')
		return (0);
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + s[i++] - 48;
	if (s[i])
		res = 0;
	return (res);
}

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
	gettimeofday(&settings->start_sec, &settings->zone);
	settings->arr[0] = "is thinking";
	settings->arr[1] = "has taken a fork";
	settings->arr[2] = "is eating";
	settings->arr[3] = "is sleeping";
	settings->arr[4] = "died";
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

void	sit_in_table(t_settings *settings, int seats)
{
	int	i;

	i = -1;
	while (++i < seats)
	{
		add_back(&settings->philos, new_phil(i + 1));
		if (!settings->philos)
			break ;
		print_state(i + 1, settings, 0);
	}
	if (settings->philos)
		find_last(settings->philos)->next = settings->philos;
}

int	main(int ac, char **av)
{
	t_settings	settings;

	settings.philos = malloc(sizeof(t_single_p));
	if (ac < 5 || ac > 6 || !check_errors(av))
	{
		printf("Invalid Input!");
		return (2);
	}
	data_init(&settings, av, ac);
	sit_in_table(&settings, settings.nbr_phil);
	if (!settings.philos)
		return (2);
	// while (!settings.philos->dead)
	// {
	// }
	return (0);
}
