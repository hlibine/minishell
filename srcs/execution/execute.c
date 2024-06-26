/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:01:09 by pberset           #+#    #+#             */
/*   Updated: 2024/06/24 17:30:37 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_core *core, char **env)
{
	int		child_pid;
	int		status;
	char	*exec_path;

	if (core->pipe_count == 0)
	{
		exec_path = find_exec_path(core->pipeline->params[0], core->env->paths);
		child_pid = fork();
		if (child_pid == -1)
			ms_error("fork error");
		if (child_pid == 0)
		{
			if (execve(exec_path, core->pipeline->params, env) == -1)
				ms_error("execve error\n");
		}
		else
			waitpid(child_pid, &status, 0);
	}
	else
		exec_pipes(core, env);
}

/* TODO
If core->pipe_count > 0, we need to handle pipes
en gros, while pipe_count pipeline
dup2() to redirect stdout to the write end of the pipe
dup2() to redirect stdin to the read end of the pipe
close the read end of the pipe
close the write end of the pipe
fork() and exec() the command
*/