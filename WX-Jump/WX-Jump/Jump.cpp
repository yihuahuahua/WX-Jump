#include <iostream>
#include <Windows.h>
#include <graphics.h>
#include "atlimage.h"
#include <cmath>
#include <strstream>
using namespace std;
IMAGE image, img;
int xy[800][700], x, y, x11 = 0, y11 = 0, x22 = 0, y22 = 0, ttime;
BOOL ColorFun(COLORREF color1, COLORREF color2, int deff);
BOOL isNewBox(int color);
double dis;
char a[100] = "adb shell input swipe 100 100 100 100 ", str[100];
int main()
{
	for (;;)
	{
		cout << "开始截图......" << endl;
		system("adb shell screencap -p /sdcard/screen.png");
		system("adb pull /sdcard/screen.png");
		cout << "图片已保存，正在转换格式......" << endl;
		CImage cimage;
		cimage.Load(L"screen.png");
		cimage.Save(L"screen.jpg");
		cout << "转换格式成功，正在读取下一个盒子的位置......" << endl;
		loadimage(&image, L"screen.jpg");
		SetWorkingImage(&image);
		getimage(&img, 100, 600, 800, 700);
		SetWorkingImage(&img);

		for (y = 0; y < 700; y++)
		{
			for (x = 0; x < 800; x++)
			{
				xy[x][y] = getpixel(x, y);
				if (isNewBox(xy[x][y]))
				{
					x11 = x; y11 = y;
					goto next1;
				}
			}
		}
	next1:cout << "盒子已经找到，正在找小人位置" << endl;
		for (y = 699; y > 0; y--)
		{
			for (x = 0; x < 800; x++)
			{
				xy[x][y] = getpixel(x, y);
				if (ColorFun(xy[x][y], RGB(55, 60, 100), 5))
				{
					x22 = x; y22 = y;
					goto next2;
				}
			}
		}
	next2:cout << "位置如下" << x11 << ' ' << y11 << ' ' << x22 << ' ' << y22 << endl << "我要跳了" << endl;
		dis = sqrt(double((x22 - x11) * (x22 - x11) + (y22 - y11) * (y22 - y11)));
		ttime = dis * 1.25;
		ostrstream strout(str, sizeof(str));
		strout << a << ttime << '\0';
		system(str); cout << "执行完毕！！！";
		x11 = x22 = y11 = y22 = 0;
		system("cls");
		Sleep(1500);
	}
	return 0;
}
BOOL ColorFun(COLORREF color1, COLORREF color2, int deff)
{
	int r1 = GetRValue(color1);
	int g1 = GetGValue(color1);
	int b1 = GetBValue(color1);
	int r2 = GetRValue(color2);
	int g2 = GetGValue(color2);
	int b2 = GetBValue(color2);
	if (double((r1 - r2) * (r1 - r2) + (g1 - g2) * (g1 - g2) + (b1 - b2) * (b1 - b2)) <= deff * deff)
		return TRUE;
	return FALSE;
}
BOOL isNewBox(int color)
{
	int g = GetGValue(color);
	int b = GetBValue(color);
	int r = GetRValue(color);
	if (ColorFun(color, RGB(246, 246, 246), 10))	//浅白色
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(250, 250, 250), 10))
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(255, 255, 255), 0))	//纯白色
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(100, 148, 106), 20))	//墨绿色  100 148 106
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(113, 113, 113), 10))	//深灰色 
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(245, 128, 58), 10))	//橙色
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(186, 239, 69), 10))	//浅绿色
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(234, 203, 174), 10))	//木质桌子
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(254, 240, 89), 10))	//黄色
	{
		return TRUE;
	}
	else if (r > 124 && r < 134 && g>111 && g < 121 && b > 219 && b < 229)	//紫色相间
		//else if (r == 129 && g == 116 && b == 224)
	{
		return TRUE;
	}
	else if (r > 75 && r < 85 && g>158 && g < 165 && b > 85 && b < 95)	//大圆绿柱子
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(254, 74, 83), 10))	//红色
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(152, 114, 111), 10))	//华岩石
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(117, 117, 117), 10))	//马桶
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(225, 199, 142), 10))
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(241, 241, 241), 10))	//书本
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(255, 172, 178), 10))	//粉色盒子
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(73, 73, 73), 3))	//奶茶杯子
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(147, 147, 147), 10))	//唱片机
	{
		return TRUE;
	}
	return FALSE;
}