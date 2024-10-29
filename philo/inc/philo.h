/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:09 by sting             #+#    #+#             */
/*   Updated: 2024/10/29 10:09:41 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define INVALID_ARG 1
# define YES 1
# define NO 0

typedef struct s_args
{
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;

}			t_args;


typedef struct s_program t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	// t_args			args;
	t_program		*program;

	pthread_mutex_t	l_fork; // ! ptr or no?
	pthread_mutex_t	r_fork;
	size_t 			start_time;
	size_t			last_meal;
	int				eat_flag;
}					t_philo;


typedef struct s_program
{
	t_args			args;
	t_philo			*philos;
	pthread_t		monitor_thread;
	pthread_mutex_t *forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t do_flag_mutex;
	pthread_mutex_t eat_flag_mutex;
	
	int				start_time;
	int				do_flag; // do_routine or don't

}					t_program;


// init
void 				init_args(t_program *program, char **argv, int argc);
int					init_mutexes(t_program *program);
void				init_philo_struct(t_program	*program, int index);
int 				init_philos(t_program *program);

// philo routine
void				*philo_routine(void *ptr);

// monitor
void *monitor_philos(void *ptr);

// utils
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
void print_message(t_philo *philo, char *message);

// libft
int					ft_atoi(const char *str);
void				*ft_calloc(size_t num_elements, size_t element_size);

// ! tmp
void print_current_time_millis_micro(void);

#endif