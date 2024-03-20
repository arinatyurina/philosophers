/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:57:59 by atyurina          #+#    #+#             */
/*   Updated: 2024/02/21 16:14:06 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h> 
# include <stdatomic.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}		t_fork;

typedef struct s_philo
{
	int				nbr;
	long int		meals;
	long long int	time_last_meal;
	atomic_bool		alive;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	t_data			*vars;
}	t_philo;

struct s_data
{
	pthread_t		*thread;
	int				philos_to_eat;
	int				if_dead;
	pthread_mutex_t	mute_ph_to_eat;
	pthread_mutex_t	stdout_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	start_mutex;
	long long int	philo_nbr;
	long long int	t_die;
	long long int	t_eat;
	long long int	t_sleep;
	long long int	eat_nbr;
	long long int	begin_time;
	int				all_full;
	long long int	forks_nbr;
	int				i;
	int				j;
	int				flag;
	t_fork			*forks;
	t_philo			*philo;
};

long long int	get_time(void);
void			ft_usleep(long long int time);

int				ft_strlen(const char *str);
long long int	ft_atoll(const char *nptr);

void			ft_stdout(t_data *vars, char *str, int i);

void			monitoring(t_data *vars);
int				is_dead(t_philo *philo);
void			philo_is_full(t_philo *philo);

int				check_argc(int argc);
int				set_argc(int argc, char **argv, t_data *vars);
int				set_argc_meal(int argc, char **argv, t_data *vars);

int				main(int argc, char **argv);
int				join_threads(t_data *vars);
int				thread_loop(t_philo *philo);
void			*routine(void *data);

int				thread_loop(t_philo *philo);
void			sleep_think(t_philo *philo);
int				odd_id(t_philo *philo);
int				even_id(t_philo *philo);
void			update_meal(t_philo *philo);
int				check_dead(t_philo *philo);

void			forks_pointers(t_philo *vars);
void			forks_init(t_data *vars);
void			free_forks(t_data *vars);

void			init(t_data *vars);
void			monitoring(t_data *vars);
void			destroy(t_data *vars);
void			free_memory(t_data *vars);

int				is_dead(t_philo *philo);

#endif