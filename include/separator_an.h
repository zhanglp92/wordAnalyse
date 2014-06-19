/*************************************************************************
	> File Name: separator_an.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年04月08日 星期二 10时14分37秒
 ************************************************************************/

#ifndef _SEPARATOR_H_
#define _SEPARATOR_H_

#include <types_an.h>

// 符号表类型
struct _SEPARATOR {
    int     typeCode;
    char    sepa[SEPARA_LEN];
};
struct _SEPA_T {
    struct _SEPARATOR   *table;
    int     size;
};

// 符号表
static struct _SEPA_T   sepa_t = {0};

void create_sepat (void);
void free_sepa (void);

#define IS_EQ(ch) \
	('=' == ch)
#define IS_MORE(ch) \
	('>' == ch)
#define IS_LESS(ch) \
	('<' == ch)
#define IS_SUB(ch) \
	('-' == ch)
#define IS_ADD(ch) \
	('+' == ch)
#define IS_AND(ch) \
	('&' == ch)
#define IS_OR(ch) \
	('|' == ch)
#define IS_G(ch) \
	(IS_OR (ch) || IS_EQ (ch))
#define IS_D(ch) \
	(IS_AND (ch) || IS_EQ (ch))
#define IS_C(ch) \
	(IS_ADD (ch) || IS_EQ (ch))
#define IS_B(ch) \
	(IS_MORE (ch) || IS_SUB (ch) || IS_EQ (ch))
#define IS_A(ch) \
	('(' == ch || ')' == ch || \
	 '[' == ch || ']' == ch || \
	 '{' == ch || '}' == ch || \
	 '.' == ch || '!' == ch || \
	 '~' == ch || '?' == ch || \
	 ':' == ch || ';' == ch || \
	 ',' == ch)

#define SEPA_STAT_CNT	9
static inline int stata_9 (const char *, size_t *, size_t);
static inline int stata_8 (const char *, size_t *, size_t);
static inline int stata_7 (const char *, size_t *, size_t);
static inline int stata_6 (const char *, size_t *, size_t);
static inline int stata_5 (const char *, size_t *, size_t);
static inline int stata_4 (const char *, size_t *, size_t);
static inline int stata_3 (const char *, size_t *, size_t);
static inline int stata_2 (const char *, size_t *, size_t);
static inline int stata_1 (const char *, size_t *, size_t);

size_t separator_an (const char *, size_t *, size_t, int);
int is_sepa (const char *str);
void create_sepat (void);
void free_sepa (void);

#endif
