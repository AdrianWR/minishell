/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:47:46 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 09:01:12 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <unistd.h>
# include <stdbool.h>
# include "hash.h"

typedef struct	s_variable
{
	char		*value;
	bool		env;
}				t_variable;

t_hashtable		*load_env(char *envp[]);
char			**unload_env(t_hashtable *env, size_t *envp_size);
char			*get_value(t_hashtable *env, const char *key);
char			*set_value(t_hashtable *env, const char *pair, bool is_env);
char			**local_envp(char **local_envp, char **envp, size_t envp_size);
void			set_exit_status(t_hashtable *env, int status);

#endif
