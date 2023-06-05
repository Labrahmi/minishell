/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:43:06 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/06/04 19:02:20 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

enum token_type
{
	TYPE_ARG,
	TYPE_RED_IN,
	TYPE_RED_OUT,
	TYPE_RED_APP,
	TYPE_RED_HER,
	TYPE_RED_PIP,
};

typedef struct s_env
{
	char			*index;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_check_arg
{
	int		i;
	char	*stack;
	int		top;
	int		s_quote;
	int		d_quote;
	char	*content;
}	t_check_arg;

typedef struct s_pre_tokens
{
	char				*content;
	enum token_type		type;
	int					contain_quotes;
	struct s_pre_tokens	*next;
	struct s_pre_tokens	*prev;
}	t_pre_tokens;

typedef struct tokenizer_s
{
	int 			in_double_quotes;
	char			*user_input;
	int 			in_quotes;
	t_pre_tokens 	*head;
	int 			start;
	int 			end;
}	tokenizer_t;

typedef struct s_user_data
{
	char	**spl_inp;
	char	*user_input;
}   t_user_data;


// - - - - - - - - - - - - - - 
// typedef struct s_arguments
// {
// 	char				*content;
// 	struct s_arguments	*next;
// }	t_arguments;

// - - - - - - - - - - - - - - 
// typedef struct s_command
// {
// 	char				*cmd;
// 	t_pre_tokens		*args;
// 	t_pre_tokens		*output_files;
// 	t_pre_tokens		*input_files;
// 	t_pre_tokens		*append_files;
// 	t_pre_tokens		*herdoc_files;
// 	struct s_command	*next;
// 	// char				*command_path;
// 	// char				**command_args;
// 	// char				*input_file;
// 	// char				*output_file;
// 	// char				*append_file;
// 	// char				*herdoc_data;
// 	// char				*herdoc_limiter;
// 	// int					quote_type;
// 	// int					is_valid_command;
// 	// int					is_input;
// 	// int					is_appendn
// 	// int					is_output;
// 	// int					is_herdoc;
// }	t_command;
// echo hello > 1 > 2 > 3 < 4 << 5 >> 6 < 7 > 8 < 9
typedef struct s_command
{
		char				*cmd;
		int					cmd_type;
		t_pre_tokens		*args;
		t_pre_tokens		*output_files;
		t_pre_tokens		*input_files;
		t_pre_tokens		*append_files;
		t_pre_tokens		*herdoc_files;
		int					out_type;
		int					in_type;
		char				**db_args;
		char				*path;
		char				*here_doc_data;
		struct s_command	*next;
}	t_command;

void			ft_error(char *message);
void			free_double(char **array);
char			*ft_colorize(char *message, char *color);
int				add_pre_t(t_pre_tokens **head, char *content, int state);
int				add_pre_t_2(t_pre_tokens **head, char *content, t_pre_tokens *node);
void			free_linked(t_pre_tokens **head);
void			ft_remove_quotes(t_pre_tokens **head, t_env *head_env);
t_env			*ft_set_env(char **env);
t_command		*ft_fill_commands(t_pre_tokens **head);
void			printf_linked(t_pre_tokens *head);
void			ft_lexer(t_command **head);
t_pre_tokens	*ft_tokenizer(char *user_input);
int				ft_tokenizer_loop(tokenizer_t *tok);
void 			*ft_init_zeros(tokenizer_t *tok);
void			free_commands(t_command **head);
void			free_linked(t_pre_tokens **head);
int				add_symbol(t_pre_tokens **head, char *user_input, int start, int *end);
int				is_symbol(char symbol);
int				sub_and_add(char *user_input, int start, int end, t_pre_tokens **head);
void			printf_env(t_env *head);
void			printf_commands(t_command *head);
void			printf_linked(t_pre_tokens *head);
char			*ft_read_input();
int 			ft_cnt(char *string);
void			print_leaks();
t_command		*get_first_command(char *user_input, t_env *env_head);
int				valid_arguments(t_pre_tokens **head_args);
int				valid_commands(t_command **head_commands);
void			print_error(char *error_msg);
void			conver_l_args_to_p(t_command *head_command);
char			**get_path(char **envp);
void			set_path(t_command *head_command, char **env);
int				calculate_num_of_cmd(t_command *all_cmd);
int				calculate_number_of_args_in_node(t_command *all_cmd);
int				calculate_len_of_w(t_command *all_cmd, int i);
void			fill(t_command *all_cmd, int i, char *ev_word);
void			fill_it(char **arr_of_ev_cmd, t_command *all_cmd);
void			fill_arr_of_all(char ***arr_of_all_cmd, t_command *all_cmd);
char			***convert_linked_list_to_tr_p(t_command *head_command);
void			exec(char ***all_cmd, t_command *head, char **envp);
void			ft_read_heredoc(t_command **command_ix);
// builtsins
int				ft_echo(t_command *command);
void			ft_exit();
