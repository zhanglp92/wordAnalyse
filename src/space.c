/*************************************************************************
	> File Name: space.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月31日 星期一 08时37分30秒
 ************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <space.h>

size_t filter_space (const char *str, size_t *pos, size_t len)
{
    while (++*pos < len && isspace (str[*pos])) ;
    return *pos;
}
