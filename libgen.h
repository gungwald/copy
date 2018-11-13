#ifndef GUNGWALDS_LIBGEN_H
#define GUNGWALDS_LIBGEN_H

/* Conforms to POSIX but does not modify path. A pointer into path
   or a constant string value is returned. So don't attempt to
   modify the return value. */
char *basename(char *path);

#endif
