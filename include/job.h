/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:46:01 by aroque            #+#    #+#             */
/*   Updated: 2021/03/07 01:30:45 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H

# include "libft.h"
# include "process.h"
# include "token.h"

typedef struct			s_job
{
	t_process			*process_list;
	struct s_job		*next;
}						t_job;

t_job					*parser(t_token *tokens);

#endif
