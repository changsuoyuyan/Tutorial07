#include "FlashPicture.h"


#include"WindDrawD3D.h"




#include <windows.h>
#include <process.h>  
#include <assert.h>  
#include <iostream>


#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

#include <d3dx9.h>

#include <xnamath.h>
#include "resource.h"

#include<stdio.h>
#include<stdlib.h> 
#include <io.h>

#include <fcntl.h>

#include <iostream>
#include <string>
#include <map>
#include <vector>

FILE *fpOutputThreadID;


HANDLE  g_HEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
bool g_bSingleInstance = true;
bool g_isERp = false;

WindDrawD3D *windDrawD3d;//���飬0��ʼ�ģ�  0��1��2��3��4��5
int g_windowsNumber = 0;

int  loopCount=6;//erpѭ���ĵڼ�����ʼ
int  g_loopCountLeft = 6;//erpѭ���ĵڼ�����ʼ

UINT WINAPI  RunSubThread(void* ptr)
{
	int nThreadID = *((int*)ptr);
	printf("ThreadID: %d  is   run____RunSubThread\n", nThreadID);
	SetEvent(g_HEvent);
	//WindDrawD3D   windDrawD3d;
	windDrawD3d[nThreadID].StartThreadMainFunc(&nThreadID,g_isERp);
	int i = 0;
	printf("ThreadID: %d  is   End911_911911911911____RunSubThread\n", nThreadID);
	g_windowsNumber--;
	if (g_windowsNumber==0)
	{
		SetEvent(g_HEventQuit);
	}
	return 0;
}

//����ERP �õ��߳�
UINT WINAPI  RunControlERP(void* ptr)
{
	// 	int nThreadID = *((int*)ptr);
	// 
	// 	SetEvent(g_HEvent);
	// 	//WindDrawD3D   windDrawD3d;
	// 	windDrawD3d[nThreadID].StartThreadMainFunc(&nThreadID, g_isERp);
	bool  No_0 = false;
	bool  No_1 = false;
	bool  No_2 = false;
	bool  No_3 = false;
	bool  No_4 = false;
	bool  No_5 = false;
BeginPlaySixPicture:  
	//printf("begin play six picture ");           //������ 6�� ͼƬ-------------------------------------
	//ResetEvent(g_HEventQuit);//����������
	if (g_loopCountLeft == 6)
	{
		No_0 = false;
		No_1 = false;
		No_2 = false;
		No_3 = false;
		No_4 = false;
		No_5 = false;
	}

beginRand:									//��� �ظ�����ǰ��ѡ��������ѡ��һ�� 0~5�������----------------------------
	int randNumber = rand() % 6;

	if (randNumber == 0)
	{
		if (No_0)
		{
			goto beginRand;
		}
		No_0 = true;
		windDrawD3d[0].setBeginPlay(true);
		g_loopCountLeft--;
	}

	if (randNumber == 1)
	{
		if (No_1)
		{
			goto beginRand;
		}
		No_1 = true;
		windDrawD3d[1].setBeginPlay(true);
		g_loopCountLeft--;
	}

	if (randNumber == 2)
	{
		if (No_2)
		{
			goto beginRand;
		}
		No_2 = true;
		windDrawD3d[2].setBeginPlay(true);
		g_loopCountLeft--;
	}

	if (randNumber == 3)
	{
		if (No_3)
		{
			goto beginRand;
		}
		No_3 = true;
		windDrawD3d[3].setBeginPlay(true);
		g_loopCountLeft--;
	}

	if (randNumber == 4)
	{
		if (No_4)
		{
			goto beginRand;
		}
		No_4 = true;
		windDrawD3d[4].setBeginPlay(true);
		g_loopCountLeft--;
	}

	if (randNumber == 5)
	{
		if (No_5)
		{
			goto beginRand;
		}
		No_5 = true;
		windDrawD3d[5].setBeginPlay(true);
		g_loopCountLeft--;
	}

	if (g_loopCountLeft == 0)
	{
		g_loopCountLeft = 6;//һ��С���ֽ�����
	}
	WaitForSingleObject(g_HEventQuit, INFINITE);
	goto BeginPlaySixPicture;
	return 0;
}

int addPictureAndFrameNum(int NumberPicture, char * strImagePictureName,int numFrame)
{
	windDrawD3d[NumberPicture].addPictureAndTime(strImagePictureName, numFrame);//���� ����ӿ�
	return 0;
}

int  setPicturePosition(int NumberPicture, int x, int y, int width, int height)
{
	windDrawD3d[NumberPicture].setWindowPosition(x, y, width, height);//���� ����ӿ�
	return 0;
}

int 	setWindowAlpha(int alpha)
{
	for (int n=0;n<6;n++)
	{
		windDrawD3d[n].setWindowAlpha(alpha);
	}
	return 1;
}



int   runFlashPicture(unsigned   int  hWnd)//_TCHAR    //������������main��������������  int argc, char* argv[]
{
	if (g_bSingleInstance==true)
	{
		g_bSingleInstance = false;
	}
	else
	{
		return 0;
	}

	int nThreadCount = 6;
	g_windowsNumber = 6;
	HANDLE* phaThread = new HANDLE[nThreadCount];
	windDrawD3d=new WindDrawD3D[nThreadCount];

	fpOutputThreadID = fopen("OutputThreadID.txt", "w+");
	unsigned OutputThreadID[6];
	int nErr = 0;
	for (int i = 0; i < nThreadCount; i++)
	{
// 		typedef unsigned(__stdcall* _begin thread ex_proc_type)(void*);// 		_beginthreadex_proc_type  func;
		phaThread[i] = (HANDLE)_beginthreadex(NULL, 0, RunSubThread, &i, 0, &OutputThreadID[i]);
		if (phaThread[i] == 0)
		{
			nErr = GetLastError();
			if (nErr == 8)
			{
				printf("Open thread failure, insufficient storage space !\n");
			}
			else
			{
				printf("Open thread failure, wrong number %d\n", nErr);
			}
			break;
		}
		fprintf(fpOutputThreadID, "%d\n", OutputThreadID[i]);//��� OutputThreadID �� �ļ� file
		WaitForSingleObject(g_HEvent, INFINITE);
	}
	fclose(fpOutputThreadID);
	Sleep(300);
	//windDrawD3d[5].addPictureAndTime("1234.png", 60);//���� ����ӿ�
	//windDrawD3d[4].setWindowPosition(1188, 888, 44, 44);//���� ����ӿ�


	HWND  hwnd = (HWND)hWnd;
	if (hwnd==NULL)
	{
		return 0;
	}
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	return 0;//�˳���
}




int   runFlashPictureERP(unsigned   int  hWnd)//_TCHAR    //������������main��������������  int argc, char* argv[]
{
	if (g_bSingleInstance == true)
	{
		g_bSingleInstance = false;
	}
	else
	{
		return 0;
	}
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	std::cout << "ssssb333333333333bb" << std::endl;

	int nThreadCount = 6;
	g_windowsNumber = 6;
	HANDLE* phaThread = new HANDLE[nThreadCount];
	windDrawD3d = new WindDrawD3D[nThreadCount];
	g_isERp = true;
	unsigned OutputThreadID[6];
	int nErr = 0;
	for (int i = 0; i < nThreadCount; i++)
	{
		phaThread[i] = (HANDLE)_beginthreadex(NULL, 0, RunSubThread, &i, 0, &OutputThreadID[i]);

		if (phaThread[i] == 0)
		{
			nErr = GetLastError();
			if (nErr == 8)
			{
				printf("Open thread failure, insufficient storage space !\n");
			}
			else
			{
				printf("Open thread failure, wrong number %d\n", nErr);
			}
			break;
		}

		WaitForSingleObject(g_HEvent, INFINITE);
	}
	Sleep(30);

	HWND  hwnd = (HWND)hWnd;
	if (hwnd == NULL)
	{
		//return 0;
	}
	else
	{
		SetForegroundWindow(hwnd);
		SetActiveWindow(hwnd);
		SetFocus(hwnd);
	}

	unsigned threadIDss;
	int arglist;
	(HANDLE)_beginthreadex(NULL, 0, RunControlERP, &arglist, 0, &threadIDss);
	//WaitForSingleObject(g_HEventQuit, INFINITE);	//	//������������ȴ������ط��������ܣ���������Ϸ���ڲ��ܶ��˿ӵ����������������룬����Ҳ��������������̲��˳���   //  ΪERP����Ϊ������  ��  ��ǩ����
	return 0;//�˳� ��6�����ڵ��������
}



