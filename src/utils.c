/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:23:37 by aroque            #+#    #+#             */
/*   Updated: 2021/02/03 21:24:53 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool		ft_streq(const char *s1, const char *s2)
{
	return (!(ft_strncmp(s1, s2, ft_strlen(s2) + 1)));
}
