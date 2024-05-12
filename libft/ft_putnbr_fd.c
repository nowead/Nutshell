/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:03:15 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/07 19:36:23 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -INT_MAX -1)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 10)
	{
		write(fd, &"0123456789"[n % 10], 1);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
}

// int	main()
// {
// 	ft_putnbr_fd(456, 1);
// }
