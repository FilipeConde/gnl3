#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define CAPTURE_PRINT(file, count_var, function, ...) \
	do { \
		freopen((file), "w+", stdout); \
		(count_var) = (function)(__VA_ARGS__); \
		freopen("/dev/tty", "w", stdout); \
	} while (0)

char	*read_file_to_str(const char *filename);

#endif