/*************************************************************************
	> File Name: constant_an.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年04月04日 星期五 09时19分51秒
 ************************************************************************/

#ifndef _CONSTANT_H_ 
#define _CONSTANT_H_ 


#include <ctype.h>
#include <types_an.h>

#define IS_SINGN(ch) \
	(('+' == ch) || ('-' == ch))
#define IS_0(ch) \
    ('0' == ch)
#define IS_DD(ch) \
	('0' != ch ? isdigit (ch) : FALSE)
#define IS_DD_0(ch) \
	(isdigit (ch))
#define IS_DO(ch) \
	('0' <= ch && '8' > ch)
#define IS_DX(ch) \
	(isxdigit (ch))
#define IS_POINT(ch) \
	('.' == ch)
#define IS_E(ch) \
	('e' == (ch|0x20))
#define IS_INT_LAST(ch) \
	(('u' == (ch|0x20)) || ('l' == (ch|0x20)))
#define IS_FLOAT_LAST(ch) \
	(('f' == (ch|0x20)) || ('l' == (ch|0x20)))
#define IS_DX_P(ch) \
	('p' == (ch|0x20))
#define IS_X(ch) \
	('x' == (ch|0x20))

// 判断是否组成常数的字符
#define IS_CONST_CH(ch) \
		(IS_SINGN (ch) || \
		 IS_DX(ch) || \
		 IS_POINT (ch) || \
		 IS_E (ch) || \
		 IS_INT_LAST (ch) || \
		 IS_FLOAT_LAST (ch) || \
		 IS_DX_P (ch) || \
		 IS_X (ch)) 


// 常量表的定义
struct _CONST_DATA {
	char	word[CONST_LEN];
};
struct _CONST {
	// 常量表
	struct _CONST_DATA	*data;
	// 常量表中的有效个数
	int					size;
	// 常量表的大小
	int					cnt;
};
static struct _CONST	constt = {0};


/**
 * @brief constant_an : 识别常量
 *
 * @param str : 缓冲区里的字符串
 * @param pos : 当前的索引
 * @param len : 缓冲区中有效字符的长度
 *
 * @return : 当前的索引
 */
size_t constant_an (const char *str, size_t *pos, size_t len, int stat);


#define CONST_STAT_CNT  16
/**
 * @brief stata : 状态转换函数组
 *
 * @param : 需要扫描的字符串
 * @param : 字符串的当前位置
 * @param size_t : 字符串的总长度
 *
 * @return : 返回扫描后的状态
 */
#if 1
static inline int stata_1 (const char *, size_t *, size_t);
static inline int stata_2 (const char *, size_t *, size_t);
static inline int stata_3 (const char *, size_t *, size_t);
static inline int stata_4 (const char *, size_t *, size_t);
static inline int stata_5 (const char *, size_t *, size_t);
static inline int stata_6 (const char *, size_t *, size_t);
static inline int stata_7 (const char *, size_t *, size_t);
static inline int stata_8 (const char *, size_t *, size_t);
static inline int stata_9 (const char *, size_t *, size_t);
static inline int stata_10 (const char *, size_t *, size_t);
static inline int stata_11 (const char *, size_t *, size_t);
static inline int stata_13 (const char *, size_t *, size_t);
static inline int stata_14 (const char *, size_t *, size_t);
static inline int stata_15 (const char *, size_t *, size_t);
static inline int stata_16 (const char *, size_t *, size_t);
#endif



int save_const (int fd_out, const char *str);
void free_constt (void);

#endif 
