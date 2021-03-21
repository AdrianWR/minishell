/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 09:02:26 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 09:07:35 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

void			freemat(char **mat);
void			free_array(void **array);
void			free_buffer(char **buffer);
void			free_variable(void *v);
void			free_shell(t_session *session);

#endif
