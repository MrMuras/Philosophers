/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:43:59 by snocita           #+#    #+#             */
/*   Updated: 2023/06/28 22:18:21 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_usleep(uint64_t sleep_time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(50);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

unsigned long	get_timestamp(void)
{
	struct timeval	current_time;
	unsigned long	milliseconds;

	gettimeofday(&current_time, NULL);
	milliseconds = (unsigned long)(current_time.tv_sec)*1000
		+ (unsigned long)(current_time.tv_usec) / 1000;
	return (milliseconds);
}
