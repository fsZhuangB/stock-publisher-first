/** @file
* 行情Demo.键盘输入线程
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#include "my_vld.h"

#include "main_message_queue.h"
#include "sdk_util.h"
#include "main_environment.h"

#ifdef WIN32
#include <conio.h>
#else
//#include <curses.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <ctype.h>
#endif

int KeyboardInputThread::MainFun()
{
	while(IsActive(20))
	{
#ifdef WIN32
		if(kbhit())//如果有键盘输入
		{
			char ch = getch();//获取输入
			ch = toupper(ch);
			MyEnvironment::PostMainMessage(Command_KeyInput, ch);//发消息，给主线程。
		}
#else
		{
			//设置非阻塞模式
			struct termios oldt, newt;  
			tcgetattr(STDIN_FILENO, &oldt);  
			newt = oldt;  
			newt.c_lflag &= ~(ICANON | ECHO);  
			tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
			int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);  
			fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);  
			//非阻塞模式，取键盘输入
			int ch = getchar();
			ch = toupper(ch);
			MyEnvironment::PostMainMessage(Command_KeyInput, ch);//发消息，给主线程。
			//设置回去.如果不及时设置回去，ctrl_c结束程序，就痛苦了。
			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
			fcntl(STDIN_FILENO, F_SETFL, oldf);  
		}
#endif
	}

	return 0;
}