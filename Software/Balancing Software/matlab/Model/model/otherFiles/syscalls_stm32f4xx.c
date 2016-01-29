/*
 * STM32F4-Discovery system calls
 *
 * Copyright 2013-2015 The MathWorks, Inc.
 */
#include <sys/stat.h>
#include <errno.h>

#undef errno
extern int errno;
 

__attribute__((weak)) int _close(int file) 
{ 
    return -1; 
}

__attribute__((weak)) int _fstat(int file, struct stat *st) 
{
    st->st_mode = S_IFCHR;
    return 0;
}

__attribute__((weak)) int _isatty(int file) 
{ 
    return 1; 
}

__attribute__((weak)) int _lseek(int file, int ptr, int dir) 
{ 
    return 0; 
}

__attribute__((weak)) int _open(const char *name, int flags, int mode) 
{ 
    return -1; 
}

__attribute__((weak)) int _read(int file, char *ptr, int len) 
{
    return 0;
}

__attribute__((weak)) void _exit(int status)
{
	while(1);
}

/* Used for malloc() */
extern unsigned int _sheap;  /* Start of HEAP */
extern unsigned int _eheap;  /* End of HEAP  */
caddr_t heap_end = 0;
__attribute__((weak)) caddr_t _sbrk(int incr) {
    caddr_t prev_heap_end;
    caddr_t tmp;
    
    if (heap_end == 0) {
        heap_end = (caddr_t) &_sheap;
    }
    prev_heap_end = heap_end;
    
    /* Always align to an eight byte boundary */
    tmp = (caddr_t) (((unsigned int)heap_end + incr + 7) & ~7);
    if (tmp >= ((caddr_t)&_eheap)) {
        /* No more HEAP */
        errno = ENOMEM;
        return (caddr_t)-1;        
    }
    heap_end = tmp;
    
    return prev_heap_end;
}

__attribute__((weak)) int _write(int file, char *ptr, int len) 
{
    return len;
}