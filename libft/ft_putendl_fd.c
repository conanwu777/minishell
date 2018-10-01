/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 20:06:36 by cwu               #+#    #+#             */
/*   Updated: 2018/04/17 20:06:38 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char const *s, int fd)
{
	if (!s)
		return (-1);
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	return (0);
}
