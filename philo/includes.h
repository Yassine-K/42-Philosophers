/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:24 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/23 16:28:17 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_single_p{
	int					id;
	int					eating;
	int					sleeping;
	int					thinking;
	int					dead;
	struct timeval		last_meal;
	pthread_t			thread;
	struct s_single_p	*next;
}	t_single_p;

typedef struct s_settings{
	int				nbr_phil;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	char			*arr[5];
	int				*forks;
	struct timeval	start_sec;
	struct timeval	curr_sec;
	struct timezone	zone;
	t_single_p		*philos;
	pthread_mutex_t	mutex;
}	t_settings;

typedef struct s_void_arg{
	t_settings	*settings;
	t_single_p	tmp;
}	t_void_args;

void		add_back(t_single_p **philo_list, t_single_p *new_p);
void		print_state(int id, t_settings *settings, int state);
void		*routine(void *data);
void		no_cash_to_pay(t_single_p **philos);
void		create_thread(t_single_p **philos, t_settings *settings);
void		wait_for_thread(t_single_p **philos);
t_single_p	*new_phil(int id);
t_single_p	*find_last(t_single_p *philo_list);

enum	e_hands{
	left,
	right
};

#endif