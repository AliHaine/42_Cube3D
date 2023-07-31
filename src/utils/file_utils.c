/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:05:04 by ayagmur           #+#    #+#             */
/*   Updated: 2023/07/31 17:05:05 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	go_to_line(t_file *file, int line)
{
	while (line-- > 0)
		get_next_line(file);
}

void	close_file(t_file *file)
{
	close(file->fd);
	file->line_num = 0;
	if (file->storage)
		free(file->storage);
	if (file->line)
		free(file->line);
}

void	reopen_file(t_file *file, int line, int flags)
{
	close_file(file);
	open_file(file, file->file_path, flags);
	if (line > 0)
		go_to_line(file, line);
}

bool	open_file(t_file *file, char *file_path, int flags)
{
	file->fd = open(file_path, flags);
	if (file->fd == -1)
		return (false);
	file->file_path = file_path;
	file->line_num = 0;
	file->line = 0;
	file->storage = 0;
	return (true);
}
