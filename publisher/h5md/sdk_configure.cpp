/** @file
* ����Demo.�������ļ�
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/

#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
#include "sdk_util.h"

//ȥǰ��ո�.
string& HqSdkUtil::trim(string &s) 
{
	if (s.empty()) 
	{
		return s;
	}

	// "�ո�\t,�ո�" ���ܵĻ���Ҫȥ����ô��
	s.erase(0, s.find_first_not_of(' '));
	s.erase(0, s.find_first_not_of('\t'));
	s.erase(0, s.find_first_not_of(' '));
	//����Ŀհף�Ҳ����ͬ�ϡ�
	s.erase(s.find_last_not_of(' ') + 1);
	s.erase(s.find_last_not_of('\t') + 1);
	s.erase(s.find_last_not_of(' ') + 1);
	return s;
}
//ȡһ������
bool HqSdkUtil::get_line(FILE *pFile, string& line)
{
	if(pFile == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return false;
	}

	line = "";
	char buf[2];
	buf[1] = 0;
	while(1)
	{
		int num = fread(buf, 1, 1, pFile);
		if(buf[0] == '\n' || buf[0] == '\r' || num != 1/*�ļ�β*/)
		{
			trim(line);
			int pos = line.find('#');
			if(pos >= 0)
			{
				line.erase(pos);
				trim(line);
			}
			if(line.size() > 0)
			{
				return true;
			}

			if(num != 1)//�ļ�β
			{
				return false;
			}

			continue;//û�����ݣ�����ȡ
		}

		line += buf;
	}


	return false;
}
/*
	ȡ����.  "user = xyz #user"
*/
string HqSdkUtil::get_cfg_str(string& line)
{
	line.erase(0, line.find_first_of('=') + 1);
	trim(line);
	return line;
}
/*
	ȡ����.  "user = xyz #user"
*/
int HqSdkUtil::get_cfg_int(string& line)
{
	line.erase(0, line.find_first_of('=') + 1);
	trim(line);
	return atoi(line.c_str());
}

/*
	���ļ��ȡ������Ϣ
*/
bool HqSdkUtil::ReadConfigure(void)
{
	FILE* file;
	if((file = fopen("configure", "r")) == NULL)
	{
		my_log("configure�ļ����Ķ���?\r\n");
		return false;
	}

	string line;
	while(get_line(file, line))
	{
		#define my_find(str) strncmp(line.c_str(), str, strlen(str)) == 0
		if(my_find("user"))
		{
			m_strUser = get_cfg_str(line);
		}
		else if(my_find("pass"))
		{
			m_strPass = get_cfg_str(line);
		}
		else if(my_find("app_key"))
		{
			m_strAppKey = get_cfg_str(line);
		}
		else if(my_find("app_secret"))
		{
			m_strAppSecret = get_cfg_str(line);
		}
		else if(my_find("ip_1"))
		{
			m_strIp1 = get_cfg_str(line);
		}
		else if(my_find("port_1"))
		{
			m_iPort1 = get_cfg_int(line);
		}
		else if(my_find("ip_2"))
		{
			m_strIp2 = get_cfg_str(line);
		}
		else if(my_find("port_2"))
		{
			m_iPort2 = get_cfg_int(line);
		}
		else if(my_find("maxNumberTest"))
		{
			m_iMaxNumberTest = get_cfg_int(line);
		}
		else
		{
			continue;
		}
	}
	fclose(file);
	return true;
}