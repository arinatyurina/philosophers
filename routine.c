/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:21:26 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/14 12:21:29 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_think(t_philo *philo)
{
	if (philo->vars->eat_nbr != -1 && philo->meals != 0)
	{
		philo->meals--;
		if (philo->meals == 0)
			philo_is_full(philo);
	}
	ft_stdout(philo->vars, "is sleeping", philo->nbr);
	ft_usleep(philo->vars->t_sleep);
	ft_stdout(philo->vars, "is thinking", philo->nbr);
	if (philo->vars->philo_nbr % 2 != 0)
		ft_usleep(2);
}

void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_usleep(philo->vars->t_eat);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->die_mutex);
	if (philo->vars->if_dead == true)
	{
		pthread_mutex_unlock(&philo->vars->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->vars->die_mutex);
	return (0);
}

int	odd_id(t_philo *philo)
{
	if (check_dead(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	ft_stdout(philo->vars, "has taken a fork", philo->nbr);
	if (philo->vars->philo_nbr == 1)
		(ft_usleep(philo->vars->t_die));
	if (check_dead(philo) == 1 || philo->vars->philo_nbr == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	ft_stdout(philo->vars, "has taken a fork", philo->nbr);
	if (check_dead(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	ft_stdout(philo->vars, "is eating", philo->nbr);
	update_meal(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	sleep_think(philo);
	return (0);
}

int	even_id(t_philo *philo)
{
	if (check_dead(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->left_fork);
	ft_stdout(philo->vars, "has taken a fork", philo->nbr);
	if (check_dead(philo) == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_stdout(philo->vars, "has taken a fork", philo->nbr);
	if (check_dead(philo) == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	ft_stdout(philo->vars, "is eating", philo->nbr);
	update_meal(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	sleep_think(philo);
	return (0);
}
