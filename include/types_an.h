/*************************************************************************
	> File Name: types_an.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月30日 星期日 13时14分57秒
 ************************************************************************/

#ifndef _TYPES_AN_H_
#define _TYPES_AN_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define TRUE    1
#define FALSE   0

#define BUF_SIZE		10
#define BUF_TEMP_SIZE	1024
/* 标识符的最大长度 */
#define IDEN_LEN		30
/* 常量串的最大长度 */
#define CONST_LEN		30
/* 分隔符的最大长度 */
#define SEPARA_LEN      10


#define KEEPWF_NAME		"./lib/keepwords" 
#define IDENTF_NAME		"./lib/identifier" 
#define CONSTF_NAME		"./lib/constant" 
#define SEPARATOR_NAME	"./lib/separator"


typedef unsigned char   bool;

int open_file (const char *file_name, int flags, mode_t mode);
/* open file and define file descriptor */
#define OPEN_FILE(file_name, flags, name, mode) \
	int fd ##name = open_file (file_name, flags, mode)

int read_file (int fd, char *buf, size_t size); 
#define READ_FILE(fd, buf) \
        read_file (fd, buf, BUF_SIZE) 


#define  LAST       0
# define ENTERN     1
# define SPACE		2
# define POINT      3
# define SIGN       4
# define DIGIT		5
# define UNDERLINE  6 
# define LETTER		7 
# define BRACKET	8
# define OPERATOR	9
# define STRING		10
#define  OTHER		11


/* 类别码的范围 */
#define NOT_FIND    -1
/* 标识符的类别码 */
# define IDENTIFIER     1 
/* 常数的类别码 */
# define CONSTANT       2 
/* 保留字类别码的起始 */
# define KEEPWORD       11 
/* 分隔符的起始 */
#define  SEPARATOR      51 

/* 判断属于那类串 */
#define IS_IDENTIFIER(type) \
	(IDENTIFIER == type ? 1 : 0)
#define IS_CONSTANT(type) \
	(CONSTANT == type ? 1 : 0)
#define IS_KEEPWORD(type) \
	((KEEPWORD <= type && SEPARATOR > type) ? 1 : 0)
#define IS_SEPARATOR(type) \
	(SEPARATOR <= type ? 1 : 0)


/* check character type */ 
int check_ch (char ch); 

#define  SUCCESS	0x1
# define FAILER		0x2 
# define SCAN_END	0x4
#define  HALF_CONST	0x8

/* * * *
 * 将扫描串的状态存入高字节
 * 将状态结果存到低字节 
 * * * */
#define GET_STAT(stat) \
	(stat >> 16)
#define SET_STAT(stat) \
	(stat << 16)


/* 状态的标号 */
#define  STATA1		0x01
# define STATA2		0x02
# define STATA3		0x03
# define STATA4		0x04
# define STATA5		0x05
# define STATA6		0x06
# define STATA7		0x07
# define STATA8		0x08
# define STATA9		0x09
# define STATA10	0x0a
# define STATA11	0x0b
# define STATA12	0x0c
# define STATA13	0x0d
# define STATA14	0x0e
# define STATA15	0x0f
#define  STATA16	0x10
/* 状态函数的类型 */
typedef int (*STATA_F)(const char*, size_t *, size_t);



#endif

