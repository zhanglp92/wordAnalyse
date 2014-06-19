/*************************************************************************
	> File Name: constant_an.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年04月04日 星期五 09时20分39秒
 ************************************************************************/

#include <stdio.h>
#include <constant_an.h>
#include <string.h>
#include <stdlib.h>


// 状态的个数
#define  STAT_CNT	CONST_STAT_CNT
// 状态函数数组, 用０填充空余的状态 
static STATA_F		stat_fun[STAT_CNT+2] = {
	0, stata_1, stata_2, stata_3, 
	stata_4, stata_5, stata_6, stata_7, 
	stata_8, stata_9, stata_10, stata_11, 
	0, stata_13, stata_14, stata_15, stata_16 
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

static inline int stata_10 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, 10);
//    printf ("end code 10\n");
    rs |= SUCCESS;

    return rs;
}

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

static inline int stata_7 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA7); 

    if (IS_DO (ch)) {   // 到状态 7

        CALL_STATA_NAME (7);
    }else if (IS_INT_LAST (ch)){     // 到状态 10

        CALL_STATA_NAME (10); 
    }else {

//        printf ("end code 7\n"); 
        rs |= SUCCESS;
    }

    return rs;
}

static inline int stata_14 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA14); 

    if (IS_DD_0 (ch)) {     // 到状态 14

        CALL_STATA_NAME (14);
    }else if (IS_FLOAT_LAST (ch)) {     // 到状态 10

        CALL_STATA_NAME (10);
    }else {

//        printf ("end code 14\n"); 
        rs |= SUCCESS;
    }

    return rs;
}

static inline int stata_13 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA13);

    if (IS_DD_0 (ch)) {     // 到状态 14 

        CALL_STATA_NAME (14);
    }else {

//        printf ("error code 13\n"); 
        rs |= FAILER;
    }

    return rs;
}

static inline int stata_9 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA9);

    if (IS_DD_0 (ch)) {     // 到状态 9

        CALL_STATA_NAME (14);
    }else if (IS_SINGN (ch)) {  // 到状态 13

        CALL_STATA_NAME (13);
    }else {
        
//        printf ("error code 9\n"); 
        rs |= FAILER;
    }

    return rs;
}

static inline int stata_16 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA16);

    if (IS_DX (ch)) {   // 到状态 16 

        CALL_STATA_NAME (16);
    }else if (IS_DX_P (ch)) {   // 到状态 9

        CALL_STATA_NAME (9);
    }else {
        
//        printf ("error code 16\n");
        rs |= FAILER;
    }

    return rs;
}

static inline int stata_15 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA15);

    if (IS_DX (ch)) {   // 到状态 15

        CALL_STATA_NAME (15);
    }else if (IS_DX_P (ch)) {   // 到状态 9
        
        CALL_STATA_NAME (9);
    }else if (IS_INT_LAST (ch)) {   // 到状态 10 

        CALL_STATA_NAME (10);
    }else if (IS_POINT (ch)) {  // 到状态 16

        CALL_STATA_NAME (16);
    }else {

    //    printf ("end code 15\n");
        rs |= SUCCESS;
    }

    return rs;
}

static inline int stata_11 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA11);

    if (IS_DX (ch)) {   // 到状态 15

        CALL_STATA_NAME (15); 
    }else {
        
    //    printf ("error code 11\n");
        rs |= FAILER;
    }

    return rs;
}

static inline int stata_8 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA8);

    if (IS_DD_0 (ch)) {

        CALL_STATA_NAME (8);
    }else if (IS_FLOAT_LAST (ch)) {
        
        CALL_STATA_NAME (10);
    }else if (IS_E (ch)) {

        CALL_STATA_NAME (9);
    }else {
        
    //    printf ("end code 8\n");
        rs |= SUCCESS;
    }

    return rs;
}

static inline int stata_6 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA6);

    if (IS_DD_0 (ch)) {

        CALL_STATA_NAME (6);
    }else if (IS_POINT (ch)) {
        
        CALL_STATA_NAME (8);
    }else if (IS_E (ch)) {

        CALL_STATA_NAME (9);
    }else {
    //    printf ("error code 6\n");
        rs |= FAILER;
    }

    return rs;
}

static inline int stata_5 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA5);

    if (IS_DD_0 (ch)) {

        CALL_STATA_NAME (8);
    }else {
    //    printf ("error code 5\n");
        rs |= FAILER;
    }

    return rs;
}

static inline int stata_4 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA4); 

    if (IS_DD_0 (ch)) {

        CALL_STATA_NAME (4);
    }else if (IS_INT_LAST (ch)) {
        
        CALL_STATA_NAME (10);
    }else if (IS_E (ch)) {

        CALL_STATA_NAME (9);
    }else if (IS_POINT (ch)) {
        
        CALL_STATA_NAME (8);
    }else {
    //    printf ("end code 4\n");
        rs |= SUCCESS;
    }

    return rs;
}

static inline int stata_3 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA3);

    // 分析如　00329.34时，首先碰到０会分两种情况
    // 所以需要把他两都进行判断
    if (IS_DO (ch)) 
        CALL_STATA_NAME (7);

    if (IS_DD_0 (ch)) 
        CALL_STATA_NAME (6);
    else if (IS_POINT (ch)) 
        CALL_STATA_NAME (8);
    else if (IS_E (ch))
        CALL_STATA_NAME (9);
    else if (IS_INT_LAST (ch)) 
        CALL_STATA_NAME (10);
    else if (IS_X (ch)) 
        CALL_STATA_NAME (11);
    else {
    //    printf ("end code 3\n");
        rs |= SUCCESS;
    }

    return rs;
}

static inline int stata_2 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA2);

    if (IS_DD (ch)) {

        CALL_STATA_NAME (4);
    }else if (IS_POINT (ch)) {
        
        CALL_STATA_NAME (5);
    }else if (IS_0 (ch)) {

        CALL_STATA_NAME (3);
    }else {
    //    printf ("error code 2\n");
        rs |= FAILER;
    }

    return rs;
}

static inline int stata_1 (const char *str, size_t *pos, size_t len) 
{
    STATA_HEAD (*pos, len, STATA1);

    if (IS_DD (ch)) {

        CALL_STATA_NAME (4);
    }else if (IS_SINGN (ch)) {
        
        CALL_STATA_NAME (2);
    }else if (IS_0 (ch)) {

        CALL_STATA_NAME (3);
    }else if (IS_POINT (ch)) {
        
        CALL_STATA_NAME (5);
    }else {
    //    printf ("error code 1\n");
        rs |= FAILER;
    }

    return rs;
}

size_t constant_an (const char *str, size_t *pos, size_t len, int stat) 
{
    int     rs = 0;

//    stat = 8;
    if (STATA8 == stat) 
        rs = stata_8 (str, pos, len);
    else
        rs = stat_fun[stat] (str, pos, len); 

    return rs;
}

int save_const (int fd_out, const char *str)
{
    // 扩展常量表
    if (constt.size >= constt.cnt) {
        constt.cnt = (constt.cnt + 1) * 2;
        constt.data = (struct _CONST_DATA *)realloc (constt.data, 
            sizeof (struct _CONST_DATA) * constt.cnt + 1);
    }

    int     i;
    int     len = strlen (str);
    for (i = 0; i < constt.size; i++) 
        if (0 == strncmp (str, constt.data[i].word, len+1))
            return i;
    
    // 加入到常量表中，并保存的文件
    strncpy (constt.data[constt.size].word, str, len);
    char    buf[BUF_TEMP_SIZE+1];
    snprintf (buf, sizeof (buf), "%-8d %s\n", constt.size, str);
    write (fd_out, buf, strlen (buf));

    // 返回在表中的序号
    return constt.size++;
}

void free_constt (void)
{
    free (constt.data);
    constt.data = NULL;
}
