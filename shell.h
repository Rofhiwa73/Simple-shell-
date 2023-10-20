#ifndef SHELL_H
#define SHELL_H

char *_getline(void);
char **split_line(char *line);
int execute(char **args);

#endif /* SHELL_H */
