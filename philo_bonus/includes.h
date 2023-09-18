/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:24 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/18 13:16:04 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/_pthread/_pthread_t.h>
# include <sys/semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <signal.h>

typedef struct s_settings{
	int				nbr_phil;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	int				num_rounds;
	int				id;
	int				eating;
	int				rounds;
	int				progress;
	char			*arr[5];
	sem_t			*forks;
	sem_t			*ko;
	sem_t			*print;
	sem_t			*pay_now;
	time_t			start_sec;
	time_t			last_meal;
	time_t			curr;
	pthread_t		bouncer;
	pid_t			*pids;
}	t_settings;

void		print_state(int id, t_settings *settings, int state, time_t t);
void		*routine(void *data);
void		create_proc(t_settings *settings);
void		wait_for_proc(t_settings *settings);
void		no_cash_to_pay(t_settings *settings);
void		get_time(t_settings *settings, int type);
void		ft_usleep(time_t t, t_settings *t_settings);
int			ft_atoi(char *s);
void		*bouncer(void *data);

#endif