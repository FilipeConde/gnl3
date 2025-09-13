
#include "utils.h"

char	*read_file_to_str(const char *filename)
{
	FILE	*f;
	long	fsize;
	char	*str;

	f = fopen(filename, "rb");
	if (!f)
		return (NULL);
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	str = malloc(fsize + 1);
	if (!str)
		return (NULL);
	fread(str, fsize, 1, f);
	fclose(f);
	str[fsize] = '\0';
	return (str);
}