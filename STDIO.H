/*			- STDIO.H -

   Subset of ANSI standard I/O function declarations.

   Version: 3.20 [ICLM]
	   
*/

#ifndef _STDIO_INCLUDED
#define _STDIO_INCLUDED

#ifndef NULL
#define	NULL	(void *) 0
#endif

#ifndef EOF
#define	EOF	(-1)
#endif

#ifndef size_t
#if	sizeof((char*)0 - (char*)0) == sizeof(int)
#define	size_t	unsigned int
#else
#define	size_t 	unsigned long 
#endif
#endif

/* ===

#if __TID__ & 0x8000
#pragma function=intrinsic(0)
#endif

=== */

int 	puts(const char *);
int	putchar(int);
int	getchar(void);
int	sprintf(char *,const char *,...);
int	printf(const char *,...);
int	scanf(const char *,...);
int	sscanf(const char *, const char *,...);
char	*gets(char *);
int memcmp(void *, void *, size_t);
void *memset(void *, int, size_t);
size_t strlen(const char *);
char *strcpy(char *, const char *);


#if __TID__ & 0x8000
#pragma function=default
#endif

#endif



