/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:36:03 by aroque            #+#    #+#             */
/*   Updated: 2020/12/28 23:57:13 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRCODE_H
# define ERRCODE_H

# include <errno.h>

typedef enum	e_errcode {
	__ERRNONE,
	ERRSYS,
	ECMDNF,
	__ERRMAX
}				t_errcode;

char			*g_errstr[__ERRMAX] = {
	"__ERRNONE",
	"System error",
	"Command not found..."
};

void			message_and_exit(t_errcode code, char *note);

#endif
