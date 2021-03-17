/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 00:11:02 by aroque            #+#    #+#             */
/*   Updated: 2021/03/16 23:08:35 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errcode.h"
#include "minishell.h"

#define MAX_STRING_SIZE 64

static void	sort(char **array, int size)
{
	int		i;
	int		j;
	char	*key;

	j = 1;
	while (j < size + 1)
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
	sort(envp, size);
	while (*envp)
	{
		ft_putstr_fd("export ", out);
		ft_putendl_fd(*envp++, out);
	}
}

int			ft_export(t_process *p, t_shell *shell, int out)
{
	unsigned	i;
	t_variable	*v;

	i = 1;
	if (!p->argv[i])
	{
		export_raw(shell->envp, shell->envp_size, out);
		return (0);
	}
	while (p->argv[i])
	{
		if (p->argv[i][0] == '=')
			return (EBADASS);
		if ((v = (t_variable *)ht_get(shell->env, p->argv[i])))
			v->env = true;
		else
			set_value(shell->env, p->argv[i], true);
		i++;
	}
	return (0);
}
