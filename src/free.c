/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:37:39 by gariadno          #+#    #+#             */
/*   Updated: 2021/01/20 02:37:40 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freemat(char **mat)
{
	int i;

	i = 0;
	while (mat && mat[i])
	{
		free(mat[i]);
		mat[i++] = NULL;
	}
	if (mat)
	{
		free(mat);
		mat = NULL;
	}
}
