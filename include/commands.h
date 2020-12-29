/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:57:42 by aroque            #+#    #+#             */
/*   Updated: 2020/12/29 11:02:40 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

void			echo(const char **args);
void			cd(char *path);
void			pwd(void);
void			export(char *env);
void			unset(char *path);
void			env(char *path);
void			exit_(void);

typedef struct	s_command
{
	char		*name;
	void		(*builtin)();
}				t_command;

t_command		g_commands[] = {
	{ "echo", echo },
	{ "cd", cd }
	//{ "pwd", pwd },
	//"cd",
	//"pwd",
	//"export",
	//"unset",
	//"env",
	//"exit"
};

#endif
