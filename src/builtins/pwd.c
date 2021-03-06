/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:36:27 by gariadno          #+#    #+#             */
/*   Updated: 2021/03/20 19:38:21 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "minishell.h"
#include "errcode.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*get_pwd(void)
{
	char	cwd[4096 + 1];
	char	*pwd;

	pwd = NULL;
	if (getcwd(cwd, 4096) == NULL)
		return (NULL);
	pwd = ft_strdup(cwd);
	return (pwd);
}

int			ft_pwd(char **argv, int fd, char **note)
{
	int		status;
	char	*pwd;

	status = 0;
	(void)argv;
	(void)note;
	pwd = get_pwd();
	if (pwd == NULL)
		return (ERRSYS);
	ft_putendl_fd(pwd, fd);
	free(pwd);
	return (status);
}
