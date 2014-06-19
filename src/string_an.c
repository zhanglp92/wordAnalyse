/*************************************************************************
	> File Name: string_an.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年04月09日 星期三 16时25分32秒
 ************************************************************************/

#include <stdio.h>
#include <string_an.h>
#include <types_an.h>


// 取当前字符
#define ch          str[*pos] 
// pos自增并且判断是否越界
#define add_pos()     if (++*pos >= len) break;
    

int check_ch_string (char x)
{
    if (IS_OBLINE (x))			return OBLINE;
	else if (IS_DYH (x))		return DYH;
    else if (IS_GENERAL (x))    return GENERAL;
	else if (IS_ENTERN_ (x))	return ENTERN;
}

int string_an (const char *str, size_t *pos, size_t len, int stat)
{
    // 表示双引号的个数
    int     Dyinhao = 1;
    int     rs = 0;

    // 重置stat防止和别的状态图里的状态混合
    if (__START > stat || __END < stat) stat = 0;

    while (2 != Dyinhao && !(FAILER & rs)) {
    
        if (++*pos >= len) { 

            rs |= SCAN_END;
            break;
        }

        switch (stat ? stat : check_ch_string (ch)) {

            // 如果是普通字符则继续
            case GENERAL : {  }break;

            // 如果是转移字符 
            case OBLINE : {
                    
                stat = ZHUANYI;
            }break;

            case HEXAD : {

                stat = 0;
            }break;

            // 是转义字符
            case ZHUANYI : {
                
                if (IS_ZHUANYI (ch)) {

                    stat = 0;
                }else if (IS_DO_ (ch)) {
                    
                    stat = 0;
                }else if (IS_x_ (ch)) {

                    stat = HEXAD;
                }else {
                    
                    rs |= FAILER;
                }

            }break;

            // 如果遇到后双引号，则匹配成功
            case DYH : {
                
                rs |= SUCCESS;
                Dyinhao = 2;
                ++*pos;
            }break;

			// 是\n时结束
            default : {
                
                rs |= FAILER;
            }
        }
    }

    rs = (rs & 0xffff) + SET_STAT (stat);
    return rs;
}
