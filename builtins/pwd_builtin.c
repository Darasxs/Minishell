/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:59:02 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/25 18:14:52 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_builtin(t_ms *ms)
{
	char	*pwd;

	pwd = ft_getenv("PWD", ms);
	printf("%s\n", pwd);
	ms->exit_status = 0;
}
