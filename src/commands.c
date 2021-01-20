/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:36:27 by gariadno          #+#    #+#             */
/*   Updated: 2021/01/20 02:38:19 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	echo(char **args)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(*args, "-n", 2))
		flag = 1;
	if (!flag)
		args++;
	while (*args)
		ft_putstr_fd(*args++, STDOUT_FILENO);
	if (flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	cd(char *const *args)
{
	if (chdir(args[1]) != 0)
		return ;
}

void	exit_(char **args)
{
	(void)args;
	ft_putendl_fd("exit", STDOUT_FILENO);
}

void	pwd(char **args)
{
	char	cwd[4096 + 1];

	(void)args;
	if (getcwd(cwd, 4096) == NULL)
		return ;
	ft_putendl_fd(cwd, STDOUT_FILENO);
}
