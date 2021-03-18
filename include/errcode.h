/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:36:03 by aroque            #+#    #+#             */
/*   Updated: 2021/03/17 17:05:47 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRCODE_H
# define ERRCODE_H

# include <errno.h>

typedef enum		e_errcode {
	ERRSYS = 0,
	EUSAGE,
	ENOFDI,
	EPARSE,
	EUNFQT,
	EBADASS,
	ECMDNF,
	__ERRMAX
}					t_errcode;

static char *const	g_errstr[__ERRMAX] = {
	"__ERRSYS",
	"Usage: ./minishell",
	"No such file or directory: ",
	"Parse error",
	"Unfinished quote",
	"bad assignment",
	"command not found...",
};

static const int	g_errstatus[__ERRMAX] = {
	128,
	0,
	1,
	1,
	1,
	1,
	127,
};

int					error_message(t_errcode code, char *note);
void				message_and_exit(t_errcode code, char *note);

#endif
