/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:43:53 by nsahinog          #+#    #+#             */
/*   Updated: 2023/11/15 17:31:00 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# define EXEC 0
# define HEREDOC 1
# define PIPE 2
# define GREAT 3
# define GREATER 4
# define LESS 5
# define STDINN 0
# define STDOUT 1
# define STDERR 2
# define PURPLE "\033[35m"

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

typedef struct s_data
{
	char	*read_data;
}				t_data;

typedef struct s_lexer
{
	t_list	*lex;
}				t_lexer;

typedef struct s_mparse
{
	char			*cmd;
	char			**text;
	int				type;
	int				outfile;
	int				infile;
	int				fd;
	int				pid;
	int				control;
	int				std_in;
	struct s_mparse	*next;
}				t_mparse;

typedef struct s_shell
{
	t_mparse	*mparse;
	t_list		*env;
	char		*cmd;
	t_lexer		*lex_list;
	t_list		*parse;
	char		*heredoc;
	int			exec_status;
	int			kill;
}				t_shell;

extern int	g_does_have_heredoc;

int			is_space(char *cmd);
void		_create_dup(t_shell *m_shell);
void		ft_newlstiter(t_list *lst, void (*f)(), t_shell *shell);
void		fd_init(int *fd);
void		create_dup_two(t_mparse *parse, int *fd);
void		create_dup_one(t_mparse *parse, int *fd);
int			create_in_files_me(t_mparse *mparse);
int			ignore_quote(char const *cmd, int i);
int			check_what_is(const char *cmd, int i);
char		*ft_make_words(char *word, char const *s, int j, int word_ln);
void		mini_parse(t_list *lex, t_shell *m_shell, int a[3]);
t_mparse	*parse_(int *j, t_list *new, int *i);
char		*after_dark2(char *key, char *tmp);
char		*quote_control(char *tmp);
char		*set_build(char *str);
char		*before_dollar(char *tmp);
char		*_search_path(t_shell *m_shell);
int			ft_ultimatestrcmp(char *key, char *tmp, int i);
int			quote_len(char *data);
int			check(t_shell *m_shell);
int			is_builtin(t_mparse *tmp);
int			single_or_multi_command(t_shell *m_shell);
int			ft_parser(t_shell *m_shell);
int			create_files(void);
int			create_files_m(t_shell *m_shell);
int			create_in_files(t_mparse *data3, t_list *tmp3);
int			quote_check(char *data);
int			print_error(void);
int			create_files(void);
void		signals(int sig);
void		signals_control(void);
void		free_str1(char *str1, int flag);
int			quate_len(const char *str);
void		free_tmps(char *str, char *str2, char *str_tmp);
void		_ft_exit_status(t_list *data, char *str1);
void		set_heredoc(int sig);
void		killer(int sig);
void		clear_pipe(int *fd);
void		env_get(char **env, t_shell **shell);
void		get_readline(t_shell *m_shell);
void		lexer(t_shell *m_shell);
void		expander(t_shell *m_shell);
void		get_env_to_lexlist(t_shell *m_shell, int i,
				char *lex_c, t_list *lex);
void		print_list(void *data, t_shell *m_shell);
void		exec(char **env, t_shell *m_shell);
void		loop_heredoc(t_shell *m_shell);
void		run_single_command(char **env, t_mparse *data, t_shell *m_shell);
void		free_env(t_shell *m_shell);
void		free_parser(t_shell *m_shell);
void		free_loop(int control, t_shell *m_shell);
void		free_lexer(void);
void		free_text(char **text);
void		free_(t_shell *m_shell);
void		erase_after(char *tmp, t_list *data, int i);
void		free_tmp_tmp2(char *tmp, char *tmp2);
void		ft_tilde_build1(t_list *data, char *key, char *tmp);
void		ft_tilde_build2(t_list *data, char *str);
void		get_after_num(char *tmp, t_list *data, int i);
void		quote_build(char **tmp, char **data, int *i, int *j);
void		ft_exit_status(char *tmp, t_list *data, t_shell *m_shell);
void		free_node(t_list *node);
void		welcome_to_parse(t_list	*node, int i, int j, int flag);
void		get_text(t_mparse **parse, char *str, int j, int a);
void		tokenize_type(t_mparse **parse, const char *str);
void		free_parse(t_mparse *parse);
void		parse_init(void);
void		does_dollar_make_sense(char *tmp, t_list *data,
				t_list *shell_data, int i);
void		_does_dollar_make_sense(t_env *y, char *before,
				char *after, t_list *data);
void		exec_echo(t_mparse *data, t_shell *m_shell);
void		exec_env(t_shell *m_shell);
void		exec_export(t_mparse *data, t_shell *m_shell);
void		exec_unset(t_mparse *data, t_shell *m_shell, int i, int x);
void		exec_pwd(t_mparse *data, t_shell *m_shell);
void		exec_cd(t_mparse *data, t_shell *m_shell);
void		create_dup(t_shell *m_shell, t_mparse *parse);
void		clear_pipe(int *fd);
int			*create_pipe(void);
void		switch_pipe(int **fd);
void		wait_all(t_shell *m_shell);
void		execute_builtin_command(t_mparse *tmp, t_shell *m_shell);
void		exec_others(t_mparse *data, char **env, int *fd, t_shell *m_shell);
char		*get_home(t_shell *m_shell);
char		**get_args(t_mparse *data);
void		execve_child_free(char **str, t_shell *m_shell);
int			*create_pipe(void);
t_mparse	*_next_command(t_mparse **parse);
char		*ft_mini_strdup2(size_t len, char *s, int i, const char *str);
void		env_lex_list_(t_list **lex, char **lex_c, int i, t_shell *m_shell);
int			check_env(t_list *lex, char *lex_c, int i, t_shell *m_shell);
void		ft_count_words_(char const *cmd, int *i);
void		edit_env_(t_list *node, char *key, char *value, t_shell *m_shell);
void		dont_change_oldpwd(char *str, t_shell *m_shell);
void		_(t_env **env);
void		oldpwd_(char *oldpwd, t_shell *m_shell);
void		exec_cd1(char *str, t_mparse *data, t_shell *m_shell);
void		ft_change(t_mparse *data, t_shell *m_shell, char *str);
void		change_pwd(t_mparse	*data, t_shell *m_shell);
void		change_old(char *str, t_shell *m_shell);
void		_change_pwd(t_env **env);

#endif
