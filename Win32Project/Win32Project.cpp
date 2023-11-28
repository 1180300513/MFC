// Win32Project.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Win32Project.h"
#include <string>
#include <atlstr.h>
LRESULT Wndproc(
	HWND unnamedParam1, //消息所属的窗口句柄
	UINT unnamedParam2, //具体消息名称  WM_XXXX
	WPARAM unnamedParam3, //附加信息，如键盘附加消息
	LPARAM unnamedParam4  //附加信息，如鼠标附加消息
)
{	//6.处理消息（窗口过程）
	switch (unnamedParam2)
	{
	case WM_CLOSE:
		DestroyWindow(unnamedParam1); //发送另一个消息WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);  //导致 if (GetMessage(&msg, NULL, 0, 0) == 0)，退出进程
		break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(unnamedParam4);
		int y = HIWORD(unnamedParam4);
		//char buf[1024];
		CString str;
		str.Format(_T("x = %d , y = %d"), x, y);
		//wsprintf(buf, TEXT("x = %d , y = %d"), x, y);
		MessageBox(unnamedParam1, str, TEXT("这是一个弹出标题"), MB_OKCANCEL);
		break;
	}
	case WM_KEYDOWN:
		MessageBox(unnamedParam1, TEXT("键盘按下"), TEXT("这是一个弹出标题"), MB_OKCANCEL);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;//绘图的结构体 ,相当于painterevent
		HDC hdc = BeginPaint(unnamedParam1, &ps);
		//绘图
		TextOut(hdc, 100, 100, TEXT("hello"), strlen("hello"));
		EndPaint(unnamedParam1, &ps);
		break;
	}

	}
	//返回值用默认处理方式
	return DefWindowProcW(unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4);
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance, //应用程序实例句柄
	_In_opt_ HINSTANCE hPrevInstance, //上一个应用程序实例句柄
	_In_ LPSTR lpCmdLine, //命令行参数 Char* argv[]
	_In_ int nShowCmd)//窗口显示的样式
{ 
	//1.设计窗口类
	WNDCLASS wc;
	wc.cbClsExtra = 0;//类的额外的内存，，通常为0
	wc.cbWndExtra = 0;//窗口的额外内存，通常为0
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//设置背景颜色
	wc.hCursor = LoadCursor(NULL, IDC_SIZEALL);//设置光标
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//设置图标
	wc.hInstance = hInstance;//应用程序实例句柄
	wc.lpfnWndProc = Wndproc;//回调函数 窗口过程
	wc.lpszClassName = TEXT("mywindow");//窗口类类名
	wc.lpszMenuName = NULL;//	指定菜单资源的名字。如果设置为NULL，那么基于这个窗口类创建的窗口将没有默认菜单。
	wc.style = 0;//默认显示风格

	//2.注册窗口类
	RegisterClass(&wc);

	//3.创建窗口
	HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("这是一个标题"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	//4.显示和更新窗口
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	//5.循环取消息
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}