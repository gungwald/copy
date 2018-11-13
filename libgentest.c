#include <stdio.h>
#include <string.h>
#include "libgen.h"

void assertStringEquals(char *s, char *t, char *name)
{
	if (strcmp(s, t) == 0)
		printf("Success - %s\n", name);
	else
		printf("FAILURE - %s\n", name);
}

void main(void)
{
	assertStringEquals(basename(NULL), ".", "NULL");
	assertStringEquals(basename(""), ".", "Empty");
	assertStringEquals(basename("/"), "/", "Slash");
	assertStringEquals(basename("/blah/"),"","Trailing slash");
	assertStringEquals(basename("/blah"), "blah", "Blah");
}
