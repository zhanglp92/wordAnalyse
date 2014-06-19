/*************************************************************************
	> File Name: word_an.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月30日 星期日 18时16分06秒
 ************************************************************************/

#include <stdio.h>
#include <word_an.h>
#include <space.h>
#include <identifier_an.h> 
#include <constant_an.h>
#include <separator_an.h>
#include <string_an.h>
#include <string.h>

void result_an (int file_out, int type, int num) 
//void result_an (int file_out, int type, char *str) 
{
    char    buf[BUF_TEMP_SIZE+1]; 

    if (IS_IDENTIFIER (type)) {

        snprintf (buf, sizeof (buf), "%-8d %d\n", type, num); 
    }else if (IS_KEEPWORD (type)) { 

        snprintf (buf, sizeof (buf), "%-8d %d\n", type, num); 
    }else if (IS_CONSTANT (type)) {
        
        snprintf (buf, sizeof (buf), "%-8d %d\n", type, num); 
    }else if (IS_SEPARATOR (type)) {
        
        snprintf (buf, sizeof (buf), "%-8d %d\n", type, num); 
    }

    write (file_out, buf, strlen (buf));
}

void word_an (int file_in, int file_out) 
{
    // 创建保留字表 , 分隔符表
    create_keepw (); 
    create_sepat ();

    // 创建标识符和常数存储文件
    OPEN_FILE (IDENTF_NAME, O_WRONLY | O_CREAT | O_TRUNC, 
               _iden, 0666); 
    OPEN_FILE (CONSTF_NAME, O_WRONLY | O_CREAT | O_TRUNC, 
               _const, 0666); 

    CREATE_BUF (1);
    CREATE_BUF (2);


	#define SWAP_INT(x, y) \
		do{ \
			x = x + y; \
			y = x - y; \
			x = x - y; \
		}while(0)

    size_t  start   = 0;		// 起点指示器
    size_t  cur     = BUF_SIZE; // 索引指示器 
	int		temp_cur = 0;		// temp 的指示器
	int		temp_start = 0; 
	int		temp_cnt = 0;
	unsigned char	temp_cur_buf = 0;
	bool	temp_f = FALSE;		// 有没有识别 temp 
    
    // 存储识别的串
    char    temp[BUF_TEMP_SIZE+1];	
    char    temp_temp[BUF_TEMP_SIZE+1];	
    // 当前缓冲区和刚使用过的缓冲区指针
	// temp 当识别错误，退回时重新从temp中判断
    char    *buf[3] = {buf1, buf2, temp_temp}; 
	#define TEMP_BUF	2
    // 文件是否已经读完
    bool    flags = FALSE;
    // 当前使用的缓冲区
    unsigned char   cur_buf = 1; 
    // 当前读取的缓冲区中有效字符个数
    int cnt = BUF_SIZE;


    /** 
     * 向缓冲区里加载数据
     * 跳转到下一个缓冲区
     * 往缓冲区里读数据
     * 读完整个文件
     * 将索引器置 0
     **/
    #define LOAD_BUF() \
        do {                                            \
            cur_buf = (++cur_buf) & 1;                  \
            cnt = READ_FILE (file_in, buf[cur_buf]);    \
            if (BUF_SIZE > cnt)                         \
                flags = TRUE;                           \
            start = cur = 0;                            \
        }while (0)

    bool    load_f;         // 标志有没有加载新的缓冲区
    bool    last = FALSE;   // 标志某个单词是否在两个缓冲区
    unsigned char   last_stat;
    unsigned int    rs = SET_STAT (STATA1); 

    while (TRUE) { 

        // 扫描文件结束
        if (flags && cnt <= cur) break; 

		// 当识别错误时，重新识别temp中的字符串
		#define USED_TEMP_BUF							\
		do{if (0 !=  strlen (temp)) {					\
			temp_cur = temp_start = temp_cur_buf = temp_cnt = 0; \
			temp_f = TRUE;								\
			SWAP_INT (cur, temp_cur);					\
			SWAP_INT (start, temp_start);				\
			start = cur = 0;							\
			SWAP_INT (cur_buf, temp_cur_buf);			\
			cur_buf = TEMP_BUF;							\
			SWAP_INT (cnt, temp_cnt);					\
			cnt = strlen (temp);						\
			strncpy (temp_temp, temp, strlen (temp));	\
		}}while(0)

		#define NOT_USED_TEMP_BUF					\
			do {if (TEMP_BUF == cur_buf) {			\
				SWAP_INT (cur, temp_cur);			\
				SWAP_INT (start, temp_start);		\
				SWAP_INT (cur_buf, temp_cur_buf);	\
				SWAP_INT (cnt, temp_cnt);           \
                temp_f = FALSE;}			        \
			}while (0)
        /* *
         * 判断是否加载新的缓冲区
         * 用前边定义的变量 load_f 来标识
         * */
        #define IS_LOAD_BUF()					\
            do {load_f = FALSE;                 \
            if ((!flags && cnt <= cur)) {       \
				if (FALSE == temp_f)			\
					LOAD_BUF ();                \
				else last = FALSE;				\
                load_f = TRUE;                  \
            }}while (0)

        IS_LOAD_BUF(); 


        // 若上次单词没有扫描完毕则继续 
        switch (TRUE == last ? last_stat : 
                check_ch (buf[cur_buf][cur])) { 

            // 去除空格 
            case ENTERN :
            case SPACE : { 
                filter_space (buf[cur_buf], &cur, cnt); 
                start = cur; 
            }break; 
            
            // 识别标识符或保留字
            case UNDERLINE : 
            case LETTER : { 

                if (FALSE == last)  memset (temp, 0, BUF_TEMP_SIZE+1); 
                else last = FALSE;   // 初始化 

                rs = identifier_an (buf[cur_buf], &cur, cnt, GET_STAT (rs)); 
                strncat (temp, buf[cur_buf]+start, cur-start); 

				if (cur >= cnt) NOT_USED_TEMP_BUF;
                if (cur >= cnt) { 

                    last_stat = LETTER; 
                    last = TRUE;    // 只有单词的一部分  

                }else { 

                    if (SUCCESS & rs) {

                        start = cur;    // 读取到的完整标识符 
                        int typeCode = is_keepw (temp); 
                        int num = -1;   // 在表中的序号
                        // 如果是标识符加入标识符表 
                        if (IS_IDENTIFIER (typeCode)) 
                            num = save_iden (fd_iden, temp); 

                        result_an (file_out, typeCode, num); 
                    }else {

                        rs = SET_STAT (STATA1); 
						USED_TEMP_BUF;
                        goto DIGIT_LABLE;
                    }
                    rs = SET_STAT (STATA1); 
                } 
            }break; 

            case STRING : {
                
                if (FALSE == last)  memset (temp, 0, BUF_TEMP_SIZE+1); 
                else last = FALSE;   // 初始化 

                // 串扫描完后得到的状态, 高字节为扫描时的起始状态
                rs = string_an (buf[cur_buf], &cur, cnt, GET_STAT (rs));
                strncat (temp, buf[cur_buf]+start, cur-start); 

				if (cur >= cnt) NOT_USED_TEMP_BUF;
                // 没有扫描完整
                if (cur >= cnt) { 
                    last_stat = STRING; 
                    last = TRUE; 
                }else { 

                    if (SUCCESS & rs) { 
                        start = cur; 
                        int num = save_const (fd_const, temp); 
                        result_an (file_out, CONSTANT, num); 
                    }else {
                    //    printf ("decide constant failer\n"); 
                        rs = SET_STAT (STATA1); 
						USED_TEMP_BUF;
                        goto OTHER_LABLE;
                    }
                    rs = SET_STAT (STATA1); 
                }

            }break;

            DIGIT_LABLE:
			// 常数的开始 
//            case SIGN :
            case POINT :
			case DIGIT : {

                if (FALSE == last)  memset (temp, 0, BUF_TEMP_SIZE+1); 
                else last = FALSE;   // 初始化 

                // 串扫描完后得到的状态, 高字节为扫描时的起始状态
                rs = constant_an (buf[cur_buf], &cur, cnt, GET_STAT (rs));
                strncat (temp, buf[cur_buf]+start, cur-start); 

				if (cur >= cnt) NOT_USED_TEMP_BUF;
                // 没有扫描完整
                if (cur >= cnt) { 
                    last_stat = DIGIT; 
                    last = TRUE; 
                }else { 
                    if (SUCCESS & rs) { 
                        start = cur; 
                        int num = save_const (fd_const, temp); 
                        result_an (file_out, CONSTANT, num); 
                    }else {
                    //    printf ("decide constant failer\n"); 
                        rs = SET_STAT (STATA1); 
						USED_TEMP_BUF;
                        goto SEPARA_LABLE;
                    }
                    rs = SET_STAT (STATA1); 
                }

			}break;

            SEPARA_LABLE :
    		case SIGN :
            case BRACKET :
            case OPERATOR : {

                if (FALSE == last)  memset (temp, 0, BUF_TEMP_SIZE+1); 
                else last = FALSE;   // 初始化 

                rs = separator_an (buf[cur_buf], &cur, cnt, GET_STAT (rs));
                strncat (temp, buf[cur_buf]+start, cur-start); 

				if (cur >= cnt) NOT_USED_TEMP_BUF;
                // 没有扫描完整 
                if (cur >= cnt) { 
                    last_stat = OPERATOR; 
                    last = TRUE; 
                }else { 
                    if (SUCCESS & rs) { 
                        start = cur; 
                        int typeCode = is_sepa (temp);
                        if (NOT_FIND != typeCode)
                            result_an (file_out, typeCode, -1); 
                    }else {
                        rs = SET_STAT (STATA1); 
						USED_TEMP_BUF;
                        goto OTHER_LABLE;
                    }
                    rs = SET_STAT (STATA1); 
                }

            }break;

            OTHER_LABLE:
            default : {

                printf ("have error!\n");
                start = ++cur;
            }break;
        }
    }

    close (fd_iden);
    close (fd_const);
    free_space ();
    free_constt ();
    free_sepa ();
}

int main (int argc, char **argv)
{
	if (2 != argc) {
		printf ("argument error!\n");
		return 0;
	}
  
	OPEN_FILE (argv[1], O_RDONLY, _in, 0);
	if (0 > fd_in) exit (1);
    OPEN_FILE ("./outfile", O_WRONLY | O_CREAT | O_TRUNC, _out, 0666);

    word_an (fd_in, fd_out); 

	close (fd_in);
    close (fd_out);
    return 0;
}
