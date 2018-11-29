#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#define handle_error(msg) \
	do                    \
	{                     \
		perror(msg);      \
		exit(-1);         \
	} while (0)

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n;
	do
	{
		if ((n = accept(fd, sa, salenptr)) < 0)
		{
			if ((errno == ECONNABORTED) || (errno == EINTR))
				continue;
			else
				handle_error("accept error");
		}
	} while (0);

	return n;
}

int Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	int n;

	if ((n = bind(fd, sa, salen)) < 0)
		handle_error("bind error");

	return n;
}

int Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	int n;

	if ((n = connect(fd, sa, salen)) < 0)
		handle_error("connect error");

	return n;
}

int Listen(int fd, int backlog)
{
	int n;

	if ((n = listen(fd, backlog)) < 0)
		handle_error("listen error");

	return n;
}

int Socket(int family, int type, int protocol)
{
	int n;

	if ((n = socket(family, type, protocol)) < 0)
		handle_error("socket error");

	return n;
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;

	do
	{
		if ((n = read(fd, ptr, nbytes)) == -1)
		{
			if (errno == EINTR)
				continue;
			else
				return -1;
		}

	} while (0);

	return n;
}

ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
	ssize_t n;
	do
	{
		if ((n = write(fd, ptr, nbytes)) == -1)
		{
			if (errno == EINTR)
				continue;
			else
				return -1;
		}

	} while (0);

	return n;
}

int Close(int fd)
{
	int n;
	if ((n = close(fd)) == -1)
		handle_error("close error");

	return n;
}
