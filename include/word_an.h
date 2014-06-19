/*************************************************************************
	> File Name: word_an.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月30日 星期日 18时13分36秒
 ************************************************************************/

/** 
* word analyze
* */

#ifndef _WORD_AN_H_
#define _WORD_AN_H_

#include <stdlib.h>
#include <types_an.h>

/* define buffer */
#define CREATE_BUF(name) \
        char buf ##name[BUF_SIZE+1];



/**
* @brief word_an : word analyze code, input .c in the file 
*                  return binary table
*
* @param file_in : input file, (.c in the file)
* @param file_out : output file, (binary table)
*/
void word_an (int file_in, int file_out);

#endif
