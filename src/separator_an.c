/*************************************************************************
	> File Name: separator_an.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年04月08日 星期二 10时14分53秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <separator_an.h>


// 状态的个数 
#define  STAT_CNT	SEPA_STAT_CNT
// 状态函数数组, 用０填充空余的状态 
static STATA_F		stat_fun[STAT_CNT+1] = {
	0, stata_1, stata_2, stata_3, 
	stata_4, stata_5, stata_6, stata_7, 
	stata_8, stata_9
};


// 取当前字符
#define ch          str[*pos] 
// pos自增并且判断是否越界
#define add_pos()     if (++*pos >= len) break;
    
// 判断扫描是否结束
#define IS_SCAN_END(pos, len, stat) \
        do {if (pos >= len) { \
                rs |= SCAN_END; \
                rs |= stat << 16; \
            } \
        }while (0) 

// 每个状态都有的头部
#define STATA_HEAD(pos, len, stat) \
        int     rs = 0; \
        IS_SCAN_END (pos, len, stat) 

// 判断是否需要退回
#define IS_BACK() \
        do{if (!(rs&SCAN_END) && (rs&FAILER)) \
                *pos = __pre; \
          }while (0)

// 调用某个状态 
#define CALL_STATA(name, str, pos, len) \
        do { \
            int __pre = (*pos)++; \
            rs = stata_ ##name (str, pos, len); \
            IS_BACK (); \
        }while (0)

#define CALL_STATA_NAME(name) \
        CALL_STATA (name, str, pos, len) 


static inline int stata_9 (const char *str, size_t *pos, size_t len)
{
	STATA_HEAD (*pos, len, STATA9);
    rs |= SUCCESS;

    return rs;
}

static inline int stata_8 (const char *str, size_t *pos, size_t len)
{
    STATA_HEAD (*pos, len, STATA8);

    if (IS_EQ (ch)) {
        
        CALL_STATA_NAME (9);
    }else {

        rs |= SUCCESS;
    }
    return rs;
}

static inline int stata_7 (const char *str, size_t *pos, size_t len)
{
    STATA_HEAD (*pos, len, STATA7);
    
    if (IS_EQ (ch)) {

        CALL_STATA_NAME (9);
    }else if (IS_MORE (ch)) {

        CALL_STATA_NAME (8);
    }else {

        rs |= SUCCESS;
    }
    return rs;
}

static inline int stata_6 (const char *str, size_t *pos, size_t len)
{
    STATA_HEAD (*pos, len, STATA6);

    if (IS_EQ (ch)) {

        CALL_STATA_NAME (9);
    }else if (IS_LESS (ch)) {

        CALL_STATA_NAME (8);
    }else {

        rs |= SUCCESS;
    }
    return rs;
}

static inline int stata_5 (const char *str, size_t *pos, size_t len)
{
    STATA_HEAD (*pos, len, STATA5);

    if (IS_G (ch)) {
        
        CALL_STATA_NAME (9);
    }else {

        rs |= SUCCESS;
    }
    return rs;
}

static inline int stata_4 (const char *str, size_t *pos, size_t len)
{
    STATA_HEAD (*pos, len, STATA4);
    if (IS_D (ch)) {
        
        CALL_STATA_NAME (9);
    }else {

        rs |= SUCCESS;
    }

    return rs;
}
static inline int stata_3 (const char *str, size_t *pos, size_t len)
{
    STATA_HEAD (*pos, len, STATA3);

    if (IS_C (ch)) {
        
        CALL_STATA_NAME (9);
    }else {

        rs |= SUCCESS;
    }
    return rs;
}

static inline int stata_2 (const char *str, size_t *pos, size_t len)
{
    STATA_HEAD (*pos, len, STATA2);

    if (IS_B (ch)) {
        
        CALL_STATA_NAME (9);
    }else {

        rs |= SUCCESS;
    }
    return rs;
}

static inline int stata_1 (const char *str, size_t *pos, size_t len)
{
    STATA_HEAD (*pos, len, STATA1);

    if (IS_SUB (ch)) {
        
        CALL_STATA_NAME (2);
    }else if (IS_ADD (ch)) {

        CALL_STATA_NAME (3);
    }else if (IS_A (ch) || IS_EQ (ch)) {
        
        CALL_STATA_NAME (9);
    }else if (IS_AND (ch)) {

        CALL_STATA_NAME (4);
    }else if (IS_OR (ch)) {
        
        CALL_STATA_NAME (5);
    }else if (IS_LESS (ch)) {

        CALL_STATA_NAME (6);
    }else if (IS_MORE (ch)) {
        
        CALL_STATA_NAME (7);
    }else if (IS_G (ch)) {

        CALL_STATA_NAME (8);
        CALL_STATA_NAME (9);
    }else {
        rs |= FAILER;
    }

    return rs;
}

size_t separator_an (const char *str, size_t *pos, size_t len, int stat) 
{
    int     rs = 0;

    rs = stat_fun[stat] (str, pos, len);

    return rs;
}

/**
* @brief is_sepa : 判断是否是分割符
*
* @param str ： 要判断的字符串
*
* @return ：类型码
*/
int is_sepa (const char *str)
{
    int i;
    for (i = 0; i < sepa_t.size; i++) {
        if (0 == strncmp (str, sepa_t.table[i].sepa, strlen (str)+1))
            return sepa_t.table[i].typeCode;
    }

    return NOT_FIND;
}

/**
* @brief create_sepat : 创建符号表
*/
void create_sepat (void)
{
    OPEN_FILE (SEPARATOR_NAME, O_RDONLY, _in, 0);
    FILE *fp = fdopen (fd_in, "r");

    int max_len, i, t;
    fscanf (fp, "%d\n", &(sepa_t.size));

    sepa_t.table = (struct _SEPARATOR *)malloc 
        (sizeof (struct _SEPARATOR) * sepa_t.size);

    for (i = 0; i < sepa_t.size; i++) {
        fscanf (fp, "%d %s\n", &sepa_t.table[i].typeCode, 
               sepa_t.table[i].sepa);
    }

    close (fd_in);
}

/**
* @brief free_sepa : 释放符号表
*/
void free_sepa (void)
{
    free (sepa_t.table);
    sepa_t.table = NULL;
}
