/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:52:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/21 21:27:03 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print the token type as a string
const char *get_token_type_string(t_tokentype type) {
    switch (type) {
        case UNKNOWN: return "UNKNOWN";
        case WORD: return "WORD";
        case ASSIGNMENT_WORD: return "ASSIGNMENT_WORD";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case AND_IF: return "AND_IF";
        case OR_IF: return "OR_IF";
        case PIPE: return "PIPE";
        case LESS: return "LESS";
        case GREAT: return "GREAT";
        case DLESS: return "DLESS";
        case DGREAT: return "DGREAT";
		case NEWLINE: return "NEWLINE";
        default: return "UNKNOWN";
    }
}

// Function to print the symbol type as a string
const char *get_symbol_type_string(t_symbol sym) {
    switch (sym) {
        case TERMINAL: return "TERMINAL";
        case AND_OR: return "AND_OR";
        case AND_OR_: return "AND_OR_";
        case PIPE_SEQUENCE: return "PIPE_SEQUENCE";
        case PIPE_SEQUENCE_: return "PIPE_SEQUENCE_";
        case COMMAND: return "COMMAND";
        case SUBSHELL: return "SUBSHELL";
        case SIMPLE_COMMAND: return "SIMPLE_COMMAND";
        case CMD_NAME: return "CMD_NAME";
        case CMD_WORD: return "CMD_WORD";
        case CMD_PREFIX: return "CMD_PREFIX";
        case CMD_PREFIX_: return "CMD_PREFIX_";
        case CMD_SUFFIX: return "CMD_SUFFIX";
        case REDIRECT_LIST: return "REDIRECT_LIST";
        case IO_REDIRECT: return "IO_REDIRECT";
        case IO_FILE: return "IO_FILE";
        case FILENAME: return "FILENAME";
        case IO_HERE: return "IO_HERE";
        case HERE_END: return "HERE_END";
        default: return "UNKNOWN";
    }
}

// Recursive function to print the AST
void print_ast(t_ast_node *node, int depth)
{
    if (node == NULL)
        return;

    // Print indentation for current depth
    for (int i = 0; i < depth; i++)
        printf("  ");
    // Print the current node's details
    printf("Node (Depth %d):\n", depth);
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("  Symbol: %s\n", get_symbol_type_string(node->sym));
	for (int i = 0; i < depth; i++)
        printf("  ");
	printf("  Child_num: %zu\n", node->child_num);

    if (node->token != NULL)
	{
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("  Token Type: %s\n", get_token_type_string(node->token->type));
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("  Token String: %s\n", node->token->str);
    }

    // Print the child nodes
    for (size_t i = 0; node->child != NULL && i < node->child_num; i++)
        print_ast(node->child[i], depth + 1);
}
