/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:59:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/11 11:58:09 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse(const char	*input, int *incomplete_cmd, t_shell_ctx *shell_ctx)
{
	t_tokenlist			*tokenlist;
	t_ast				*ast;
	t_ast_err			err;

	tokenlist = tokenize(input, incomplete_cmd);
	if (tokenlist == NULL)
		return (NULL);
	if (expand_parameter(tokenlist, shell_ctx))
		return (clear_tokenlist(tokenlist));
	err = (t_ast_err){};
	ast = program(tokenlist, &err);
	if (err.errnum == INCOMPLETE_CMD)
		*incomplete_cmd = 1;
	else if (err.errnum == ENOMEM)
	{
		errno = err.errnum;
		perror("ENOMEM");
	}
	else if (err.token != NULL)
		ft_dprintf(2, "syntax error near unexpected token \'%s\'\n", \
		get_token_type_string(err.token->type));
	if (ast == NULL)
		clear_tokenlist(tokenlist);
	return (ast);
}

// Function to print the token type as a string
const char	*get_token_type_string(t_tokentype type)
{
	if (type == TOK_UNKNOWN)
		return ("TOK_UNKNOWN");
	else if (type == TOK_WORD)
		return ("TOK_WORD");
	else if (type == TOK_ASSIGNMENT_WORD)
		return ("TOK_ASSIGNMENT_WORD");
	else
		return (get_token_operator_type_string(type));
}

const char	*get_token_operator_type_string(t_tokentype type)
{
	if (type == TOK_LPAREN)
		return ("TOK_LPAREN");
	else if (type == TOK_RPAREN)
		return ("TOK_RPAREN");
	else if (type == TOK_AND_IF)
		return ("TOK_AND_IF");
	else if (type == TOK_OR_IF)
		return ("TOK_OR_IF");
	else if (type == TOK_PIPE)
		return ("TOK_PIPE");
	else if (type == TOK_LESS)
		return ("TOK_LESS");
	else if (type == TOK_GREAT)
		return ("TOK_GREAT");
	else if (type == TOK_DLESS)
		return ("TOK_DLESS");
	else if (type == TOK_DGREAT)
		return ("TOK_DGREAT");
	else
		return ("TOK_NEWLINE");
}

// // Function to print the symbol type as a string
// const char *get_symbol_type_string(t_symbol sym) {
//     switch (sym) {
//         case TERMINAL: return "TERMINAL";
//         case AND_OR: return "AND_OR";
//         case AND_OR_: return "AND_OR_";
//         case PIPE_SEQUENCE: return "PIPE_SEQUENCE";
//         case PIPE_SEQUENCE_: return "PIPE_SEQUENCE_";
//         case COMMAND: return "COMMAND";
//         case SUBSHELL: return "SUBSHELL";
//         case SIMPLE_COMMAND: return "SIMPLE_COMMAND";
//         case CMD_NAME: return "CMD_NAME";
//         case CMD_TOK_WORD: return "CMD_TOK_WORD";
//         case CMD_PREFIX: return "CMD_PREFIX";
//         case CMD_PREFIX_: return "CMD_PREFIX_";
//         case CMD_SUFFIX: return "CMD_SUFFIX";
//         case REDIRECT_LIST: return "REDIRECT_LIST";
//         case IO_REDIRECT: return "IO_REDIRECT";
//         case IO_FILE: return "IO_FILE";
//         case FILENAME: return "FILENAME";
//         case IO_HERE: return "IO_HERE";
//         case HERE_END: return "HERE_END";
//         default: return "TOK_UNKNOWN";
//     }
// }

// Recursive function to print the AST
// void print_ast(t_ast_node *node, int depth)
// {
//     if (node == NULL)
//         return;
//     for (int i = 0; i < depth; i++)
//         printf("  ");
//     printf("Node (Depth %d):\n", depth);
//     for (int i = 0; i < depth; i++)
//         printf("  ");
//     printf("  Symbol: %s\n", get_symbol_type_string(node->sym));
// 	for (int i = 0; i < depth; i++)
//         printf("  ");
// 	printf("  Child_num: %zu\n", node->child_num);

//     if (node->token != NULL)
// 	{
//         for (int i = 0; i < depth; i++)
//             printf("  ");
//         printf("  Token Type: %s\n", \
// 		get_token_type_string(node->token->type));
//         for (int i = 0; i < depth; i++)
//             printf("  ");
//         printf("  Token String: %s\n", node->token->str);
//     }
//     for (size_t i = 0; node->child != NULL && i < node->child_num; i++)
//         print_ast(node->child[i], depth + 1);
// }
