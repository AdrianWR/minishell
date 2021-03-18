/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:33:42 by aroque            #+#    #+#             */
/*   Updated: 2021/03/17 22:34:48 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_buffer(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		free(buffer[i++]);
}

void	freemat(char **mat)
{
	free_buffer(mat);
	free(mat);
}
