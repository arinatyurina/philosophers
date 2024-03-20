/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:14:47 by atyurina          #+#    #+#             */
/*   Updated: 2024/02/21 16:16:39 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_loop(t_philo *philo)
{
	if (philo->nbr % 2 != 0)
	{
		if (odd_id(philo) == 1)
			return (1);
	}
	else
	{
		if (even_id(philo) == 1)
			return (1);
	}
	if (check_dead(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->vars->full_mutex);
	if (philo->vars->all_full == true && philo->vars->eat_nbr != -1)
	{
		pthread_mutex_unlock(&philo->vars->full_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->vars->full_mutex);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->alive = true;
	forks_pointers(philo);
	pthread_mutex_init(&philo->last_meal_mutex, NULL);
	if (philo->vars->eat_nbr != -1)
		philo->meals = philo->vars->eat_nbr;
	philo->time_last_meal = philo->vars->begin_time;
	if (philo->nbr % 2 == 0)
	{
		ft_stdout(philo->vars, "is thinking", philo->nbr);
		ft_usleep(1);
	}
	while (philo->alive == true)
	{
		if (thread_loop(philo) == 1)
			break ;
	}
	return (NULL);
}

int	join_threads(t_data *vars)
{
	vars->i = 0;
	while (vars->i < vars->philo_nbr)
	{
		if (pthread_join(vars->thread[vars->i], NULL) != 0)
		{
			printf("Failed to join thread");
			return (1);
		}
		vars->i++;
	}
	return (0);
}

int	create_threads(t_data *vars)
{
	while (vars->i < vars->philo_nbr)
	{
		vars->philo[vars->i].vars = vars;
		vars->philo[vars->i].nbr = vars->i + 1;
		if (pthread_create(&vars->thread[vars->i], NULL,
				routine, &vars->philo[vars->i]) != 0)
		{
			printf("Failed to create thread");
			return (1);
		}
		vars->i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	vars;

	if (check_argc(argc) == 1)
		return (1);
	if (set_argc(argc, argv, &vars) == 1)
		return (1);
	init(&vars);
	vars.begin_time = get_time();
	create_threads(&vars);
	ft_usleep(vars.t_die / 2);
	monitoring(&vars);
	if (join_threads(&vars) == 1)
		return (0);
	destroy(&vars);
	return (0);
}
