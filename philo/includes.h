/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:24 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/23 21:55:47 by ykhayri          ###   ########.fr       */
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
	int					rounds;
	time_t		last_meal;
	time_t		curr;
	pthread_mutex_t		mutex;
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
	int				progress;
	time_t			start_sec;
	t_single_p		*philos;
}	t_settings;

typedef struct s_void_arg{
	t_settings	*settings;
	t_single_p	*tmp;
}	t_void_args;

void		add_back(t_single_p **philo_list, t_single_p *new_p);
void		print_state(int id, t_settings *settings, int state, time_t t);
void		*routine(void *data);
void		no_cash_to_pay(t_single_p **philos);
void		create_thread(t_single_p **philos, t_settings *settings);
void		wait_for_thread(t_single_p **philos);
void		get_time(void *ptr, int type);
void		ft_usleep(time_t t, t_settings *t_settings);
int			ft_atoi(char *s);
t_single_p	*new_phil(int id);
t_single_p	*find_last(t_single_p *philo_list);
t_single_p	*find_prev(t_single_p **philo_list, int id);

#endif