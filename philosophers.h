/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:22:03 by snocita           #+#    #+#             */
/*   Updated: 2023/06/28 22:52:04 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define FORK "\033[0;32mhas taken a fork\033[0m"
# define EAT "\033[0;33mis eating\033[0m"
# define SLEEP "\033[0;35mis sleeping\033[0m"
# define THINK "\033[0;34mis thinking\033[0m"
# define DEAD "\033[0;31mdied\033[0m"

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

typedef struct s_phil
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_gen		*gen;
	pthread_t			thread_id;
}	t_phil;

typedef struct s_table
{
	int				members;
	int				repas;
	int				t_eat;
	int				all_ate;
	int				t_sleep;
	int				died;
	long long		first_timestamp;
	t_phil			philosophers[250];
	pthread_mutex_t	forks[250];
	pthread_mutex_t	x_ate_mutex[250];
	pthread_mutex_t	meal_check;
	pthread_mutex_t	mutex_all_ate;
	pthread_mutex_t	writing;
}	t_table;

typedef struct s_gen
{
	int		t_death;
	t_table	*table;
	t_phil	*phil;
}	t_gen;

void			msg_err(char *str);
void			msg(char *str);
int				ft_atoi(char *str);
int				catalysis(t_gen *gen, char **av);
unsigned long	get_timestamp(void);
void			print_status(t_gen *gen, int id, int strnum);
int				init_mutex(t_gen *gen);
int				error_manager(int error);
int				starter(t_gen *gen);
void			*p_thread(void *void_philosopher);
void			ft_usleep(uint64_t sleep_time);
long long		time_diff(long long past, long long pres);
void			death_checker(t_gen *r, t_phil *p);
void			exit_starter(t_gen *gen, t_phil *philos);
u_int64_t	get_time(void);

#endif