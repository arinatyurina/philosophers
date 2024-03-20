/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:09:11 by atyurina          #+#    #+#             */
/*   Updated: 2024/02/21 17:09:12 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("You have to pass 4 or 5 arguments");
		return (1);
	}
	return (0);
}

int	set_argc_meal(int argc, char **argv, t_data *vars)
{
	if (argc == 6)
	{
		vars->eat_nbr = ft_atoll(argv[5]);
		if (vars->eat_nbr == -1)
		{
			printf("You have to pass positive numbers as arguments\n");
			return (1);
		}
		else if (vars->eat_nbr == 0)
		{
			printf("Why would you organize a dinner if no one wants to eat?\n");
			return (1);
		}
		vars->all_full = 0;
		vars->philos_to_eat = vars->philo_nbr;
		vars->flag = true;
	}
	else
	{
		vars->eat_nbr = -1;
		vars->all_full = -1;
		vars->flag = false;
	}
	return (0);
}

int	set_argc(int argc, char **argv, t_data *vars)
{
	vars->philo_nbr = ft_atoll(argv[1]);
	if (vars->philo_nbr == 0)
	{
		printf("Why would you organize a dinner without any philosophers?\n");
		return (1);
	}
	vars ->forks_nbr = vars->philo_nbr;
	vars->t_die = ft_atoll(argv[2]);
	vars->t_eat = ft_atoll(argv[3]);
	vars->t_sleep = ft_atoll(argv[4]);
	if (vars->philo_nbr == -1 || vars->t_die == -1)
	{
		printf("You have to pass positive numbers as arguments\n");
		return (1);
	}
	if (vars->t_eat == -1 || vars->t_sleep == -1)
	{
		printf("You have to pass positive numbers as arguments\n");
		return (1);
	}
	if (set_argc_meal(argc, argv, vars) == 1)
		return (1);
	vars->if_dead = false;
	return (0);
}
