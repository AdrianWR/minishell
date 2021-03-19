/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 00:11:02 by aroque            #+#    #+#             */
/*   Updated: 2021/03/19 08:24:23 by aroque           ###   ########.fr       */
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

static int	export_variable(t_process *p, t_shell *s, char **note)
{
	int			status;
	unsigned	i;
	char		*tmp;
	t_variable	*v;

	i = 1;
	status = 0;
	while (p->argv[i])
	{
		if (!ft_isalpha(p->argv[i][0]) || p->argv[i][0] == '=')
		{
			tmp = ft_strjoin("export: \'", p->argv[i]);
			*note = ft_strjoin(tmp, "\': ");
			free(tmp);
			status = ENOTVI;
		}
		else if ((v = (t_variable *)ht_get(s->env, p->argv[i])))
			v->env = true;
		else
			set_value(s->env, p->argv[i], true);
		i++;
	}
	return (status);
}

int			ft_export(t_process *p, t_shell *shell, int out, char **note)
{
	int status;

	status = 0;
	if (!p->argv[1])
	{
		export_raw(shell->envp, shell->envp_size, out);
		return (0);
	}
	status = export_variable(p, shell, note);
	return (status);
}
