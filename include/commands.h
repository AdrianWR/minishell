/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:57:42 by aroque            #+#    #+#             */
/*   Updated: 2021/01/20 19:30:56 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "hash.h"

void			export(char *const *args, t_hashtable *env);
void			unset(char *const *args, t_hashtable *env);
void			env(char *const *args, t_hashtable *env);
void			echo(const char **args);
void			pwd(char *const *args);
void			cd(char *const *args);
void			exit_(void);

typedef struct	s_command
{
	char		*name;
	void		(*builtin)();
}				t_command;

t_command		g_commands[] = {
	{ "echo", echo },
	{ "cd", cd }
};

#endif
