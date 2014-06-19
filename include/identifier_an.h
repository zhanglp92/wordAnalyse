/*************************************************************************
	> File Name: identifier_an.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月30日 星期日 13时12分08秒
 ************************************************************************/

/** 
* analyze identifier
* */
#ifndef _IDENTIFIER_AN_H_ 

#if     1
# define _IDENTIFIER_AN_H_      1
# include "types_an.h"
#endif


#define IS_UNDER_LINE(ch)	\
	('_' == ch)
#define IS_LETTER(ch) \
	(isalpha (ch))
#define IS_DIGIT(ch) \
	(isdigit (ch))


struct _KEEPW {
	int		typeCode;	// type code 
	char	*word;		// keey word 
};

struct _KEEPT {
	struct _KEEPW	*keepw;
	int		size;
};
// 保留字表
static struct _KEEPT 	keept = {0}; 

struct _IDEN {
	char 	word[IDEN_LEN];
};
struct _IDENT { 
    // 标识符
	struct _IDEN 	*iden; 
    // 实际的标识符个数
	int 			size; 
    // 标识符表的空间大小
	int 			cnt;
};
// 标识符表 
static struct _IDENT 	ident = {0}; 

size_t identifier_an (const char *str, size_t *pos, size_t len, int stat); 
int save_iden (int fd_out, const char *str);
int is_keepw (const char *str);
void create_keepw (void); 
void free_space (void); 


#define IDEN_STAT_CNT   2
#if 1
static inline int stata_1 (const char *, size_t *, size_t);
static inline int stata_2 (const char *, size_t *, size_t);
#endif

#endif
