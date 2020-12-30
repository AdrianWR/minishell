/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:36:03 by aroque            #+#    #+#             */
/*   Updated: 2020/12/29 11:44:02 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRCODE_H
# define ERRCODE_H

# include <errno.h>

typedef enum	e_errcode {
	ERRSYS,
	ECMDNF,
	__ERRMAX
}				t_errcode;

static char * const			g_errstr[__ERRMAX] = {
	"__ERRSYS",
	"Command not found..."
};

void			message_and_exit(t_errcode code, char *note);

#endif
