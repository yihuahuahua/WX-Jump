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
		cout << "��ʼ��ͼ......" << endl;
		system("adb shell screencap -p /sdcard/screen.png");
		system("adb pull /sdcard/screen.png");
		cout << "ͼƬ�ѱ��棬����ת����ʽ......" << endl;
		CImage cimage;
		cimage.Load(L"screen.png");
		cimage.Save(L"screen.jpg");
		cout << "ת����ʽ�ɹ������ڶ�ȡ��һ�����ӵ�λ��......" << endl;
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
	next1:cout << "�����Ѿ��ҵ���������С��λ��" << endl;
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
	next2:cout << "λ������" << x11 << ' ' << y11 << ' ' << x22 << ' ' << y22 << endl << "��Ҫ����" << endl;
		dis = sqrt(double((x22 - x11) * (x22 - x11) + (y22 - y11) * (y22 - y11)));
		ttime = dis * 1.25;
		ostrstream strout(str, sizeof(str));
		strout << a << ttime << '\0';
		system(str); cout << "ִ����ϣ�����";
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
	if (ColorFun(color, RGB(246, 246, 246), 10))	//ǳ��ɫ
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(250, 250, 250), 10))
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(255, 255, 255), 0))	//����ɫ
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(100, 148, 106), 20))	//ī��ɫ  100 148 106
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(113, 113, 113), 10))	//���ɫ 
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(245, 128, 58), 10))	//��ɫ
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(186, 239, 69), 10))	//ǳ��ɫ
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(234, 203, 174), 10))	//ľ������
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(254, 240, 89), 10))	//��ɫ
	{
		return TRUE;
	}
	else if (r > 124 && r < 134 && g>111 && g < 121 && b > 219 && b < 229)	//��ɫ���
		//else if (r == 129 && g == 116 && b == 224)
	{
		return TRUE;
	}
	else if (r > 75 && r < 85 && g>158 && g < 165 && b > 85 && b < 95)	//��Բ������
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(254, 74, 83), 10))	//��ɫ
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(152, 114, 111), 10))	//����ʯ
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(117, 117, 117), 10))	//��Ͱ
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(225, 199, 142), 10))
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(241, 241, 241), 10))	//�鱾
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(255, 172, 178), 10))	//��ɫ����
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(73, 73, 73), 3))	//�̲豭��
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(147, 147, 147), 10))	//��Ƭ��
	{
		return TRUE;
	}
	return FALSE;
}