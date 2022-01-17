/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:05 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/17 16:41:21 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME "bash"

enum e_part_type {
	SPACES,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	NORMAL,
	SPECIAL
};

typedef struct s_part {
	char				*part;
	enum e_part_type	type;
}	t_part;

typedef struct s_pipe
{
	int		len;
	int		size;
	int		iter;
	int		term_out;
	int		term_in;

	int		pipefd[4];

	char	**paths;

	char	*cmd;
	t_part	*cmd_flag;
}	t_pipe;

typedef struct s_env
{
	char	**env;
	int		size;
	int		line_nr;
}	t_env;

int		ft_pipex(int nr_parts, t_part *parts, t_env *s_env);
int		ft_do_forks(t_pipe pipex, t_part *parts, t_env *s_env, int status);
t_part	*ft_get_cmd_flag(t_part *parts, t_pipe pipex, \
t_env *s_env, int *status);
t_part	*get_commands_between_pipes(t_part *parts, t_pipe pipex, \
t_env *s_env);
int		ft_find_first_command(t_pipe pipex, t_part *parts);

int		ft_is_redir(t_part part);
int		is_pipe(t_part part);
int		is_input_redir(t_part part);
int		is_output_redir(t_part part);
int		is_here_doc(t_part part);

int		ft_do_redir(t_part *parts, int line_nr, int i, t_pipe pipex);
int		here_doc(char *final, int line_nr, t_part *parts, t_pipe pipex);

void	signals(void);
void	sigint_handler(int sig);

int		ft_echo(int nr_parts, t_part *parts);
int		ft_pwd(void);
int		ft_cd(t_part *parts, int line_nr);
int		ft_env(char **envp);
int		ft_export(t_part *parts, t_env *s_env);
int		ft_exit(int nr_parts, t_part *parts, int line_nr);
int		ft_unset(t_part *parts, t_env *s_env);
void	copy_env(char **envp, t_env *s_env);

char	*ft_wildcard(char *args, int *wild_quoted);
char	**ft_split_unquoted(char const *s, char c, const int *quoted);

int		ft_executable(int nr_parts, t_part *parts, t_env *s_env);
void	ft_try_paths(char **paths, char **args, t_env *s_env, t_part *parts);
char	**ft_get_paths(char **env);

t_part	*quote_split(char *s);
t_part	*ft_shell_split(char *s, int last_exit_status, t_env *s_env);

void	expand_args(char **sp, int last_exit_status, t_env *s_env, \
			int next_is_quoted);
void	expand_unquoted_args(t_part *parts, int last_exit_status, t_env *s_env);
void	expand_wildcard(t_part **parts, int **wild_quoted);
void	ft_replace(char **sp, int start, int len, char *rep);
int		replace_parts(t_part **parts, int i);
char	**parts_to_strings(t_part *parts);

int		count_parts(t_part *s);
void	ft_free_parts(t_part *parts);
int		get_env_name_length(char *env);

char	*ft_search_name(t_env *s_env, char *envname, int envlen);
int		is_built_in(char *str, int nr_parts, t_part *parts, t_env *s_env);
int		check_for_redirections(int *last_exit_status, t_part *parts, \
t_env *s_env, int nr_parts);
int		check_identifier(char *str, int unset);

int		ft_syntax_error(t_part *parts, int i, int line_nr, char *token);
int		ft_syntax_error_eof(int line_nr);
int		ft_redir_error(char *str, char *str2, int line_nr);
int		ft_invalid_identifier(t_part *parts, int i, int line_nr);
int		ft_exit_error(int too_many, char *arg, int line_nr);
void	ft_print_line_nr(int line_nr);

void	print_parts(t_part *parts);
int		print_parts_error(t_part *parts);
void	print_strs(char **strs);
int		ft_export_print(char **envp);
#endif
