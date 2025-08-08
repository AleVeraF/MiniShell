#include "minishell.h"

#ifndef PARSER_H
# define PARSER_H

t_cmd   *parse_tokens(t_token *token_list, t_shell *shell);
int		check_initial_token(t_token *token_list);
int		check_all_redirections(t_token *token_list);
int		check_all_pipe(t_token *token_list);
char	**super_split(char const *s, char c, char b);
t_cmd	*one_word_command(t_token *token_list);
t_cmd	*words_plus_cmd(t_token *token_list); 
#endif
