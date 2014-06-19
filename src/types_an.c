/*************************************************************************
	> File Name: types_an.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月30日 星期日 18时30分38秒
 ************************************************************************/

#include <stdio.h>
#include <types_an.h>
#include <string.h>


/**
* @brief open_file : pack open
*
* @param file_name : file name 
* @param flags 
*
* @return : file descriptor 
*/
int open_file (const char *file_name, int flags, mode_t mode) 
{
	int		fd;

	if (flags & O_CREAT) 
		fd = open (file_name, flags, mode); 
	else
		fd = open (file_name, flags); 

	if (0 > fd) {
        int     len = strlen (file_name) + strlen ("open()") + 1; 
        char    buf[len];
        snprintf (buf, len, "open(%s)", file_name); 
        perror (buf); 
	}

    return fd; 
}

/**
* @brief read_file : read file to buffer, size is size
*
* @param fd : file descriptor 
* @param buf : buffer
* @param pos : start posiation 
* @param size : size
*
* @return : if less than 0 meas error, 
*           if equal 0 meas readding end of file
*/
int read_file (int fd, char *buf, size_t size)
{
	memset (buf, 0, size);
    size_t  cnt = read (fd, buf, size);
	if (0 < cnt) buf[cnt] = 0;
/*
    if (0 <= cnt) 
        cnt < size ? cnt = 0 : cnt;
	*/
    return cnt;
}

inline int check_ch (char ch) 
{
	if ('\n' == ch)                     return ENTERN; 
	else if (isspace (ch))              return SPACE; 
	else if ('.' == ch)                 return POINT; 
	else if ('+' == ch || '-' == ch)    return SIGN;
	else if (isdigit (ch))              return DIGIT; 
	else if (isalpha (ch))              return LETTER; 
	else if ('_' == ch)                 return UNDERLINE; 
    else if ('(' == ch || ')' == ch || 
            '[' == ch || ']' == ch || 
            '{' == ch || '}' == ch || 
            '<' == ch || '>' == ch || 
            '&' == ch || '|' == ch || 
            '?' == ch || ':' == ch || 
            '.' == ch || ',' == ch || 
            '!' == ch || '~' == ch || 
            '=' == ch)                  return OPERATOR;
    else if ('\"' == ch)                return STRING;
	else return OTHER; 
}
