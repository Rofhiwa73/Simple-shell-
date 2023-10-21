#include "shell.h"

/**
 * get_hist_file - Retrieves the history file path
 * @info: Parameter struct
 *
 * Return: Allocated string containing the history file path
 */
char *get_hist_file(info_t *info)
{
	char *homeDir, *filePath;

	homeDir = _getenv(info, "HOME=");
	if (!homeDir)
		return NULL;

	filePath = malloc(sizeof(char) * (_strlen(homeDir) + _strlen(HIST_FILE) + 2));
	if (!filePath)
		return NULL;

	filePath[0] = 0;
	_strcpy(filePath, homeDir);
	_strcat(filePath, "/");
	_strcat(filePath, HIST_FILE);

	return filePath;
}

/**
 * write_hist - Creates a new history file or appends to an existing one
 * @info: Parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int write_hist(info_t *info)
{
	ssize_t fileDescriptor;
	char *fileName = get_hist_file(info);
	list_t *node = NULL;

	if (!fileName)
		return -1;

	fileDescriptor = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fileName);

	if (fileDescriptor == -1)
		return -1;

	for (node = info->history; node; node = node->next)
	{
		writes_str_to_fd(node->str, fileDescriptor);
		_write_to_fd('\n', fileDescriptor);
	}

	_write_to_fd(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);

	return 1;
}

/**
 * read_hist - Reads the history from a file
 * @info: Parameter struct
 *
 * Return: The new history count (histcount) on success, 0 on failure
 */
int read_hist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fileDescriptor, bytesRead, fileSize = 0;
	struct stat fileStat;
	char *buffer = NULL, *fileName = get_hist_file(info);

	if (!fileName)
		return 0;

	fileDescriptor = open(fileName, O_RDONLY);
	free(fileName);

	if (fileDescriptor == -1)
		return 0;

	if (!fstat(fileDescriptor, &fileStat))
		fileSize = fileStat.st_size;

	if (fileSize < 2)
		return 0;

	buffer = malloc(sizeof(char) * (fileSize + 1));

	if (!buffer)
		return 0;

	bytesRead = read(fileDescriptor, buffer, fileSize);
	buffer[fileSize] = 0;

	if (bytesRead <= 0)
		return free(buffer), 0;

	close(fileDescriptor);

	for (i = 0; i < fileSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			add_hist_list(info, buffer + last, linecount++);
			last = i + 1;
		}

	if (last != i)
		add_hist_list(info, buffer + last, linecount++);

	free(buffer);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		del_node_at_index(&(info->history), 0);

	update_hist(info);
	return info->histcount;
}

/**
 * add_hist_list - Adds an entry to the history linked list
 * @info: Parameter struct
 * @buf: Buffer to add
 * @linecount: The history line count (histcount)
 *
 * Return: Always 0
 */
int add_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return 0;
}

/**
 * update_hist - Updates history numbering after changes
 * @info: Parameter struct
 *
 * Return: The new history count (histcount)
 */
int update_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return info->histcount = i;
}
