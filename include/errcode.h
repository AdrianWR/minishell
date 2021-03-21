/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:36:03 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 19:00:21 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRCODE_H
# define ERRCODE_H

# include <errno.h>

typedef enum		e_errcode {
	ERRSYS = 0,
	EUSAGE,
	ENOFDI,
	ETMARGS,
	EPARSE,
	EUNFQT,
	ENOTVI,
	ECMDNF,
	ECOMMAND,
	ESYNTAX,
	ENUMARG,
	__ERRMAX
}					t_errcode;

static char *const	g_errstr[__ERRMAX] = {
	"__ERRSYS",
	"Usage: ./minishell",
	": no such file or directory",
	"too many arguments",
	"Parse error",
	"unfinished quote",
	"not a valid identifier",
	": command not found...",
	"not a built-in command",
	"",
	": requires numerical argument",
};

static const int	g_errstatus[__ERRMAX] = {
	128,
	0,
	127,
	1,
	1,
	1,
	1,
	127,
	0,
	2,
	2
};

int					error_message(t_errcode code, char *note);
void				message_and_exit(t_errcode code, char *note);

#endif
