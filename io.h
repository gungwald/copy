#ifndef CUI_H
#define CUI_H

#include <stdio.h>	/* FILENAME_MAX */
/**
 * FilePath is a cc65 platform independent type because the
 * FILENAME_MAX constant is defined for each platform in 
 * stdio.h. It includes space for a string terminator.
 */
typedef char FilePath[FILENAME_MAX];

extern bool inputFileName(const char *prompt, FilePath name);

#endif

