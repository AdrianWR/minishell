/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 10:30:35 by aroque            #+#    #+#             */
/*   Updated: 2021/02/09 23:33:19 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

/*
** Backus-Naur Form for Shell Syntax
**
** pipe_sequence  	: command
**                	| pipe_sequence '|' command
**                	;
**
** command			: cmd_name	cmd_suffix
**                	| cmd_name
**                	;
**
** cmd_name			: WORD
**					;
**
** cmd_suffix		: WORD
** 					| cmd_suffix	WORD
** 					| io_redirect
** 					| cmd_suffix	io_redirect
** 					;
**
** io_redirect      :           io_file
**            	    | IO_NUMBER	io_file
**                	|           io_here
**                 	| IO_NUMBER io_here
**                 	;
**
** io_file          : '<'       filename
** 					| '>'       filename
**					| DGREAT    filename
**					| LESSGREAT	filename
**					;
**
** filename         : WORD
**					;
*/

//<command line>	:=	<job>
//					|	<job> ';'
//					|	<job> ';' <command line>
//					         
//<job>				:=	<command>
//					|	< job > '|' < command >
//					        
//<command			:=	<simple command>
//	        		|	<simple command> '<' <filename>
//	        		|	<simple command> '>' <filename>
//					        
//<simple command>	:=	<simple command>
//	        		|	<simple command>  <token>

t_astnode *ast_parser(t_list *tokens)
{
	t_astnode	*ast;
	t_astnode	*root;

	while (tokens)
	{

	}
	ast = ft_nodenew(0x0);
	root = ast;
	ast->type = PIPE_SEQUENCE;
	return (ast);
}
