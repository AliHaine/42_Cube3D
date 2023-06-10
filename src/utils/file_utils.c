#include "../../includes/includes.h"

void	go_to_line(t_file *file, int line)
{
	while (line)
	{
		get_next_line(file);
		line--;
	}
}

void	reopen_file(t_file *file, int line, int flags)
{
	close(file->fd);
	open(file->file_path, flags);
	if (line > 0)
		go_to_line(file, line);
}

bool	open_file(t_file *file, char *file_path, int flags)
{
	file->fd = open(file_path, flags);
	if (file->fd == -1)
		return (false);
	file->file_path = file_path;
	while (get_next_line(file))
		file->file_size++;
	reopen_file(file, 0, flags);
	file->line_num = 0;
	return (true);
}
