/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:36:16 by snocita           #+#    #+#             */
/*   Updated: 2023/06/29 20:16:48 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	philo_eats(t_phil	*philo)
{
	t_gen	*gen;

	gen = philo->gen;
	pthread_mutex_lock(&(gen->table->forks[philo->left_fork_id]));
	print_status(gen, philo->id, 1);
	pthread_mutex_lock(&(gen->table->forks[philo->right_fork_id]));
	print_status(gen, philo->id, 1);
	pthread_mutex_lock(&(gen->table->meal_check));
	print_status(gen, philo->id, 2);
	philo->t_last_meal = get_timestamp();
	pthread_mutex_unlock(&(gen->table->meal_check));
	smart_sleep(gen->table->t_eat, gen);
	pthread_mutex_lock(&(gen->table->meal_check));
	(philo->x_ate)++;
	pthread_mutex_unlock(&(gen->table->meal_check));
	pthread_mutex_unlock(&(gen->table->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(gen->table->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philosopher)
{
	int		i;
	t_phil	*philo;
	t_gen	*gen;

	i = 0;
	philo = (t_phil *)void_philosopher;
	gen = philo->gen;
	if (philo->id % 2)
		usleep(15000);
	while (!(gen->table->died))
	{
		philo_eats(philo);
		pthread_mutex_lock(&(gen->table->meal_check));
		if (gen->table->all_ate)
		{
			pthread_mutex_unlock(&(gen->table->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(gen->table->meal_check));
		print_status(gen, philo->id, 3);
		smart_sleep(gen->table->t_sleep, gen);
		print_status(gen, philo->id, 4);
		i++;
	}
	return (NULL);
}

void	death_checker(t_gen *r, t_phil *p)
{
	int	i;

	while (!(r->table->all_ate))
	{
		i = -1;
		while (++i < r->table->members && !(r->table->died))
		{
			pthread_mutex_lock(&(r->table->meal_check));
			if (time_diff(p[i].t_last_meal, get_timestamp()) > r->t_death)
			{
				print_status(r, i, 5);
				r->table->died = 1;
			}
			pthread_mutex_unlock(&(r->table->meal_check));
			usleep(100);
		}
		if (r->table->died == 1)
			break ;
		i = 0;
		pthread_mutex_lock(&(r->table->meal_check));
		while (r->table->repas != -1 && i < r->table->members
			&& p[i].x_ate >= r->table->repas)
			i++;
		if (i == r->table->members)
			r->table->all_ate = 1;
		pthread_mutex_unlock(&(r->table->meal_check));
	}
}

void	exit_starter(t_gen *gen, t_phil *philos)
{
	int	i;

	i = -1;
	while (++i < gen->table->members)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < gen->table->members)
		pthread_mutex_destroy(&(gen->table->forks[i]));
	pthread_mutex_destroy(&(gen->table->writing));
}

int	starter(t_gen *gen)
{
	int		i;
	t_phil	*phil;

	i = 0;
	phil = gen->table->philosophers;
	gen->table->first_timestamp = get_timestamp();
	while (i < gen->table->members)
	{
		if (pthread_create(&(phil[i].thread_id), NULL, p_thread, &(phil[i])))
			return (1);
		pthread_mutex_lock(&(gen->table->meal_check));
		phil[i].t_last_meal = get_timestamp();
		pthread_mutex_unlock(&(gen->table->meal_check));
		i++;
	}
	death_checker(gen, gen->table->philosophers);
	exit_starter(gen, phil);
	return (0);
}
