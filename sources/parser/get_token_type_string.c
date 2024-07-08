/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:52:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 17:29:14 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print the token type as a string
const char *get_token_type_string(t_tokentype type)
{
	if (type == UNKNOWN)
		return "UNKNOWN";
	else if (type == WORD)
		return "WORD";
	else if (type == ASSIGNMENT_WORD)
		return "ASSIGNMENT_WORD";
	else
		return (get_token_operator_type_string(type));
}

const char *get_token_operator_type_string(t_tokentype type)
{
	if (type == LPAREN)
		return "LPAREN";
	else if (type == RPAREN)
		return "RPAREN";
	else if (type == AND_IF)
		return "AND_IF";
	else if (type == OR_IF)
		return "OR_IF";
	else if (type == PIPE)
		return "PIPE";
	else if (type == LESS)
		return "LESS";
	else if (type == GREAT)
		return "GREAT";
	else if (type == DLESS)
		return "DLESS";
	else if (type == DGREAT)
		return "DGREAT";
	else
		return "NEWLINE";
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
//         case CMD_WORD: return "CMD_WORD";
//         case CMD_PREFIX: return "CMD_PREFIX";
//         case CMD_PREFIX_: return "CMD_PREFIX_";
//         case CMD_SUFFIX: return "CMD_SUFFIX";
//         case REDIRECT_LIST: return "REDIRECT_LIST";
//         case IO_REDIRECT: return "IO_REDIRECT";
//         case IO_FILE: return "IO_FILE";
//         case FILENAME: return "FILENAME";
//         case IO_HERE: return "IO_HERE";
//         case HERE_END: return "HERE_END";
//         default: return "UNKNOWN";
//     }
// }

// // Recursive function to print the AST
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
//         printf("  Token Type: %s\n", get_token_type_string(node->token->type));
//         for (int i = 0; i < depth; i++)
//             printf("  ");
//         printf("  Token String: %s\n", node->token->str);
//     }
//     for (size_t i = 0; node->child != NULL && i < node->child_num; i++)
//         print_ast(node->child[i], depth + 1);
// }
