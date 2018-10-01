/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:55:24 by cwu               #+#    #+#             */
/*   Updated: 2018/09/07 14:55:25 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"

# define RED "\e[1;38;2;225;20;20m"
# define WHITE "\e[1;38;2;255;251;214m"
# define YELLO "\e[1;38;2;255;200;0m"
# define ORANGE "\e[1;38;2;255;120;10m"
# define GREEN "\e[1;38;2;0;175;117m"
# define REV "\e[7m"
# define CLR "\e[0m"
# define SCRC "\e[1;1H\e[2J"

typedef struct		s_var
{
	char			**res;
	char			sep;
	int				i;
	int				st;
	int				end;
}					t_var;

typedef struct		s_vp
{
	char			*tmp;
	char			*t;
	DIR				*dir;
	struct dirent	*entry;
	int				st;
	int				end;
}					t_vp;

typedef struct		s_mv
{
	char			**arg;
	char			**env;
	char			*line;
	t_var			v;
	int				b;
}					t_mp;

bool				ft_isspace(char c);
char				*remove_space(char *line);
char				**split_args(char *line, t_var v);
char				*findenv(char **env, char *name);
int					findenvnum(char **env, char *name);
char				**unset_env(char **arg, char **env);
char				**set_env(char **arg, char **env);
int					list_env(char **env);
int					cd(char **arg, char **env);
int					echo(char **args, char **env);
char				**check_existing(char **arg, char **env);

#endif
