/*************************************************************************
	> File Name: identifier_an.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月30日 星期日 14时53分22秒
 ************************************************************************/

#include <stdio.h>
#include <identifier_an.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// 状态的标号
#define  STAT_CNT	IDEN_STAT_CNT
static STATA_F		stat_fun[STAT_CNT+1] = {
	0, stata_1, stata_2
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


static inline int stata_2 (const char *str, size_t *pos, size_t len)
{
	STATA_HEAD (*pos, len, STATA2);

	if (IS_UNDER_LINE (ch) || IS_LETTER (ch) || 
			IS_DIGIT (ch)) {
		CALL_STATA_NAME (2);
	}else {

		rs |= SUCCESS;
	}

    return rs;
}

static inline int stata_1 (const char *str, size_t *pos, size_t len)
{
	STATA_HEAD (*pos, len, STATA1);

	if (IS_UNDER_LINE (ch) || IS_LETTER (ch)) {

		CALL_STATA_NAME (2);
	}else {

		rs |= FAILER;
	}

    return rs;
}

/**
 * @brief identifier_an : discern identifier , 
 *						  but don't discern keep word
 *
 * @param str : source string 
 * @param pos : current location 
 * @param len : length of source string 
 *
 * @return : location of end 
 */
size_t identifier_an (const char *str, size_t *pos, size_t len, int stat) 
{ 
	int 	rs = 0;

	rs = stat_fun[stat] (str, pos, len);

	return rs;
}

/* *
 * 添加标识符到标识符表
 * */
int save_iden (int fd_out, const char *str) 
{
	// 扩展标识符表
	if (ident.size >= ident.cnt) {
		ident.cnt = (ident.cnt + 1)*2;
		ident.iden = (struct _IDEN *)realloc (ident.iden, 
				sizeof (struct _IDEN) * ident.cnt+1);
	}

	int 	i;
	int 	len = strlen (str); 
	for (i = 0; i < ident.size; i++) 
		if (0 == strncmp (str, ident.iden[i].word, len+1)) 
			return i; 

	// 将标识符加入表中, 并保存到文件中
	strncpy (ident.iden[ident.size].word, str, len); 
    char    buf[BUF_TEMP_SIZE+1];
    snprintf (buf, sizeof (buf), "%-8d %s\n", ident.size, str); 
    write (fd_out, buf, strlen (buf));

//	ident.iden[ident.size++].word[len]; 
    // 返回在表中的序号
	return ident.size++;
}

/* *
 * 判断是否是保留字
 * */
int is_keepw (const char *str) 
{
	int	 i; 
	for (i = 0; i < keept.size; i++) 
		if (0 == strncmp (str, keept.keepw[i].word, strlen (str)+1)) 
			return keept.keepw[i].typeCode; 

	return IDENTIFIER; 
}

/* *
 * 创建保留字表
 * */
void create_keepw (void) 
{
	OPEN_FILE (KEEPWF_NAME, O_RDONLY, _in, 0); 
	FILE *fp = fdopen (fd_in, "r"); 

	int		max_len, i, t; 
	fscanf (fp, "%d %d\n", &(keept.size), &max_len); 

	keept.keepw = (struct _KEEPW *)malloc 
		(sizeof (struct _KEEPW) * keept.size);

	for (i = 0; i < keept.size; i++) {
		keept.keepw[i].word = (char *)malloc (sizeof (char) * max_len);
		fscanf (fp, "%d %s\n", &keept.keepw[i].typeCode, 
				keept.keepw[i].word); 
	}

	close (fd_in);
}

/* *
 * 释放动态空间
 * */
void free_space (void)
{
	int		i; 

	for (i = 0; i < keept.size; i++) {
		free (keept.keepw[i].word); 
		keept.keepw[i].word = NULL;
	}
	free (keept.keepw); 
	keept.keepw = NULL;  

	free (ident.iden);
	ident.iden = NULL;
}
