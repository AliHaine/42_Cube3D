#include "../../includes/includes.h"

void	msg_write(int fd, int exitVal, MsgType msg)
{
	const char *str;

	str = Messages[msg];
	while (*str)
		write(fd, str++, 1);
	if (exitVal >= 0)
		exit(exitVal);
}
