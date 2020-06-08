/** @file
* ����Demo.���������߳�
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
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
		if(kbhit())//����м�������
		{
			char ch = getch();//��ȡ����
			ch = toupper(ch);
			MyEnvironment::PostMainMessage(Command_KeyInput, ch);//����Ϣ�������̡߳�
		}
#else
		{
			//���÷�����ģʽ
			struct termios oldt, newt;  
			tcgetattr(STDIN_FILENO, &oldt);  
			newt = oldt;  
			newt.c_lflag &= ~(ICANON | ECHO);  
			tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
			int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);  
			fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);  
			//������ģʽ��ȡ��������
			int ch = getchar();
			ch = toupper(ch);
			MyEnvironment::PostMainMessage(Command_KeyInput, ch);//����Ϣ�������̡߳�
			//���û�ȥ.�������ʱ���û�ȥ��ctrl_c�������򣬾�ʹ���ˡ�
			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
			fcntl(STDIN_FILENO, F_SETFL, oldf);  
		}
#endif
	}

	return 0;
}