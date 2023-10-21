#include "shell.h"

/**
 * input_buffer - Buffers chained commands for processing
 * @info: Parameter struct
 * @buf: Address of the buffer
 * @len: Address of the length variable
 *
 * Return: Number of bytes read
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; 
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			add_hist_list(info, *buf, info->histcount++);
			*len = r;
			info->cmd_buf = buf;
		}
	}
	return (r);
}

/**
 * _get_input - Retrieves a line of input without the newline character
 * @info: Parameter struct
 *
 * Return: Number of bytes read
 */
ssize_t _get_input(info_t *info)
{
	static char *buf; 
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buffer(info, &buf, &len);
	if (r == -1) 
		return (-1);
	if (len) 
	{
		j = i;		
		p = buf + i; 

		check_chain(info, buf, &j, i, len);
		while (j < len) 
		{
			if (check_chain_delim(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;	  
		if (i >= len) 
		{
			i = len = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;		   
		return (_strlen(p)); 
	}

	*buf_p = buf; 
	return (r);	  
}

/**
 * read_buffer - Reads a buffer from a file descriptor
 * @info: Parameter struct
 * @buf: Buffer
 * @i: Size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of a pointer to a buffer, preallocated or NULL
 * @length: Size of the preallocated buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_handler - Blocks Ctrl-C signal
 * @sig_num: The signal number
 *
 * Return: Void
 */
void sigint_handler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
