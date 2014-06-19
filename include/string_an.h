/*************************************************************************
	> File Name: string_an.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年04月09日 星期三 16时30分41秒
 ************************************************************************/

#ifndef _STRING_AN_H_
#define _STRING_AN_H_ 

#define IS_AYH(ch) \
	('\'' == ch)
#define IS_DYH(ch) \
	('\"' == ch)
#define IS_OBLINE(ch) \
	('\\' == ch)
#define IS_ENTERN_(ch) \
    ('\n' == ch)
#define IS_GENERAL(ch) \
	(!IS_ENTERN_(ch) && !IS_OBLINE (ch) && \
     !IS_DYH (ch))
#define IS_ZHUANYI(ch) \
	('a' == ch || 'b' == ch || \
	 'f' == ch || 'n' == ch || \
	 'r' == ch || 't' == ch || \
	 'v' == ch || IS_OBLINE (ch) || \
	 IS_AYH (ch) || IS_DYH (ch))
#define IS_DO_(ch) \
	(!(ch >> 3))
#define IS_x_(ch) \
	('x' == ch)

#define __START		2
// 1 号被初始化是的状态1所占用
#define GENERAL		2
# define OBLINE		3
# define DYH		4
# define ZHUANYI	5
#define HEXAD		6
#define __END		6

int string_an (const char *str, size_t *pos, size_t len, int stat);
#endif
