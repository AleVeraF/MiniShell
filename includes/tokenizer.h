#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "minishell.h"

t_token *create_token(t_token_type type, char *str);
t_token *tokenize_line(char *line,t_shell *shell);
t_token *handle_quotes(char *line, int *i, t_shell *shell);
t_token *redir_operators_app_her(char *line, int *i);
t_token *simple_redir(char *line, int *i);
t_token *words(char *line, int *i, t_shell *shell);
void	free_tokens(t_token *token_list);
void print_token_list(t_token *token_list); // funcion a eliminar es de debuggin
t_token *create_token_safe(t_token_type type, char *line_token);
t_token *handle_double(char *line, int *i, t_shell *shell);
t_token *handle_single(char *line, int *i);
int		is_token_word(t_token *token_list);
t_token	 *words_and_quotes(char *line, int *i, t_shell *shell);
char	 *handle_quotes_join(char *line, int *i, t_shell *shell);
char	 *handle_single_join(char *line, int *i);
char	 *handle_double_join(char *line, int *i, t_shell *shell);
char *words_join(char *line, int *i, t_shell *shell);


#endif
