#include<stdarg.h>
#include<errno.h>
#include<stdio.h>
const char EMPTY_TAG[] = "";

struct logger {
	const char *tag;
	void (*writer)(struct logger *this, const char *msg, ...);
	int (*ctor)(struct logger *this, const char *tag, const void *writer);
};

struct stdout_logger {
	struct logger _logger;
};

struct file_logger {
	struct logger _logger;
	FILE *fd;
	int (*ctor)(struct file_logger *this, const char *tag, const char *file);
	int (*dtor)(struct file_logger *this);
};

int logger_ctor(struct logger *this, const char *tag, const void *writer)
{
	if (this == NULL)
		return(-EINVAL);

	if (tag == NULL)
		this->tag = EMPTY_TAG;
	else
		this->tag = tag;
}

void file_logger_writer(struct logger *_this, const char *msg, ...)
{
	struct file_logger *this = (struct file_logger*)_this;
	if (this != NULL) {
		va_list va;
		va_start(va, msg);
		fprintf(this->fd, msg, va);
		va_end(va);
	}
}

int file_logger_ctor(struct file_logger *this, const char *tag, const char *file)
{
	if (this == NULL || file == NULL)
		return(-EINVAL);

	this->fd = fopen(file, "a+");
	if (this->fd == NULL)
		return(errno);

	return(this->_logger.ctor(&this->_logger, tag, file_logger_ctor));
}

int file_logger_dtor(struct file_logger *this)
{
        if (this == NULL)
                return(-EINVAL);
	fclose(this->fd);
	return(0);
}

int main(void)
{
	struct file_logger *fl = NULL;
	
}
