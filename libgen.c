#include <string.h>

char *basename(char *path)
{
	char *ptr;

	/* If path is NULL or the empty string, return "." */
	if (path == NULL || path[0] == '\0')
		return ".";
	
	/* If path is "/", return "/" */
	if (path[0] == '/' && path[1] == '\0')
		return path;

	/* If path does not contain a '/' then return path */
	if ((ptr = strrchr(path, '/')) == NULL)
		return path;

	/* Path contains a slash so return the string following the last
	   slash. */
	return ++ptr;
}

