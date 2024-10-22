/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:09 by sting             #+#    #+#             */
/*   Updated: 2024/10/22 11:28:36 by sting            ###   ########.fr       */
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

typedef struct s_args
{
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;

}			t_args;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_args			args;

	pthread_mutex_t	l_fork; // ! ptr or no?
	pthread_mutex_t	r_fork;
}					t_philo;


typedef struct s_program
{
	t_args			args;
	t_philo			*philos;
	pthread_mutex_t *forks;
	int philo_count;
	// pthread_mutex_t	write_lock;
}					t_program;

int					ft_atoi(const char *str);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
void				*ft_calloc(size_t num_elements, size_t element_size);

#endif