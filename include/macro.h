#ifndef CD06B507_970E_4EE3_86A9_31072F8D4AA3
#define CD06B507_970E_4EE3_86A9_31072F8D4AA3
#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)    /* Don't do anything in release builds */
#endif

#endif /* CD06B507_970E_4EE3_86A9_31072F8D4AA3 */
