/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 00:11:02 by aroque            #+#    #+#             */
/*   Updated: 2021/03/15 00:14:45 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

# define MAX_STRING_SIZE 64

static void	sort(char **array, int size)
{
	int i;
	int j;
	char *key;

	j = 1;
	while (j < size)
	{
		i = j - 1;
		key = array[j];
		while (i >= 0 && ft_strncmp(key, array[i], MAX_STRING_SIZE) < 0)
		{
			array[i + 1] = array[i];
			array[i] = key;
			i--;
		}
		j++;
	}
}

static void	export_raw(char **envp, int size, int out)
{

	sort(envp, size - 1);
	while (*envp)
	{
		ft_putstr_fd("export ", out);
		ft_putendl_fd(*envp++, out);
	}
}

int			ft_export(char **argv, char **envp, int size, int out)
{
	if (!argv[1])
		export_raw(envp, size,  out);
	return (0);
}
