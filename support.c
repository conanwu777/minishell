/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:55:11 by cwu               #+#    #+#             */
/*   Updated: 2018/09/07 14:55:13 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*remove_space(char *line)
{
	int i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	line = cw_strchop(line, i);
	return (line);
}

char	**split_args(char *line, t_var v)
{
	v.res = (char**)malloc(sizeof(char*) * ft_strlen(line));
	v.i = 0;
	v.st = 0;
	while (line[v.st])
	{
		v.sep = (line[v.st] == '"' || line[v.st] == '\'') ? line[v.st] : ' ';
		if (v.sep != ' ')
			v.st++;
		v.end = v.st;
		while (line[v.end] && line[v.end] != v.sep
			&& !(v.sep == ' ' && line[v.end] == '\t'))
			v.end++;
		if (!line[v.end] && (v.sep == '"' || v.sep == '\''))
		{
			ft_printf("{R}🤐  Missing quote in arguments\n");
			return (NULL);
		}
		line[v.end] = '\0';
		v.res[v.i++] = &line[v.st];
		v.st = v.end + 1;
		while (ft_isspace(line[v.st]))
			v.st++;
	}
	v.res[v.i] = NULL;
	return (v.res);
}

char	*findenv(char **env, char *name)
{
	int i;
	int j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], name, j))
			return (&env[i][j + 1]);
		i++;
	}
	return (NULL);
}

int		findenvnum(char **env, char *name)
{
	int i;
	int j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], name, j))
			return (i);
		i++;
	}
	return (-1);
}
