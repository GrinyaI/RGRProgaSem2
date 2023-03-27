#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <cmath>
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
HPEN CreatePen(int fnPenStyle, int nWidth, COLORREF crColor);
COLORREF SetPixel(HDC hdc, int X, int Y, COLORREF crColor);
HBRUSH CreateSolidBrush(COLORREF crColor);
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj);

const double PI = 3.14159265358979323846;
const double E = 2.7182818284;

void gotoxy(short x, short y) 
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void Screen()
{
	SetConsoleTextAttribute(hStdOut ,BACKGROUND_BLUE + BACKGROUND_INTENSITY + FOREGROUND_BLUE + FOREGROUND_INTENSITY + FOREGROUND_RED + FOREGROUND_GREEN);

	const char Snow = 15;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	const int WindowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	const int WindowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	for (int i = 0; i < WindowWidth * WindowHeight; i++)
		cout << " ";

	COORD orig = { 0, 0 };

	SetConsoleCursorPosition(hStdOut, orig);

	COORD snowflake[1000];

	for (int i = 0; i < WindowWidth; i++)
	{
		snowflake[i].X = i;
		snowflake[i].Y = rand() % WindowHeight;
	}

	int time = 50;
	while (time > 0)
	{
		for (int i = 0; i < WindowWidth; i++)
		{
			SetConsoleCursorPosition(hStdOut, snowflake[i]);
			cout << ' ';
			snowflake[i].Y++;
			if (snowflake[i].Y == WindowHeight)
				snowflake[i].Y = 0;
			SetConsoleCursorPosition(hStdOut, snowflake[i]);
			cout << Snow;
		}
		SetConsoleCursorPosition(hStdOut, orig);
		Sleep(150);
		time--;
	}
}

void Me()
{
	gotoxy(58, 19);
	cout << "<----------------------------->" << endl;
	gotoxy(60, 20);
	cout << "Расчётно-графическая работа" << endl;
	gotoxy(60, 21);
	cout << "  студента группы ПИН-222" << endl;
	gotoxy(60, 22);
	cout << "  Гриневич Ильи Олеговича" << endl;
	gotoxy(58, 23);
	cout << "<----------------------------->" << endl;

}

void Table()
{
	int n = 16;
	float F1[16], F2[16], x, dx, x1[16], a = 0, b = PI, minF1 = INT_MAX, maxF1 = INT_MIN, minF2 = INT_MAX, maxF2 = INT_MIN;
	dx = fabs(b - a) / (n - 1);
	x = a;
	x1[0] = a;
	int xdr = 58, ydr = 12;
	SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
	gotoxy(xdr, ydr);
	cout << " ===================================\n";
	gotoxy(xdr, ydr + 1);
	cout << "|  I  |    X    |    F1   |    F2   | \n";
	gotoxy(xdr, ydr + 2);
	cout << "|=====|=========|=========|=========|\n";
	for (int i = 0; i < n; i++) 
	{
		F1[i] = pow(E, -2 * x);
		F2[i] = sqrt(1 + pow(sin(x), 2));
		x1[i] = x;
		x += dx;
	}
	for (int i = 0; i < n; i++) 
	{
		minF1 = min(F1[i], minF1);
		maxF1 = max(F1[i], maxF1);
		if (F2[i] != -INFINITY) 
		{
			minF2 = min(F2[i], minF2);
		}
		maxF2 = max(F2[i], maxF2);
	}
	for (int i = 1; i <= n; i++) 
	{
		gotoxy(xdr, ydr + 2 + i);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
		printf("|%3d  |%8.3f |", i, x1[i - 1]);
		if (F1[i - 1] == minF1) 
		{
			SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY);
			printf("%8.4f", F1[i - 1]);
		}
		else 
			if (F1[i - 1] == maxF1) 
			{
				SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 4);
				printf("%8.4f", F1[i - 1]);
			}
		else
		{
			SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
			printf("%8.4f", F1[i - 1]);
		}
		SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
		cout << " |";
		if (F2[i - 1] == minF2) 
		{
			SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY);
			printf("%8.4f", F2[i - 1]);
		}
		else 
			if (F2[i - 1] == maxF2) 
			{
				SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 4);
				printf("%8.4f", F2[i - 1]);
			}
		else
		{
			if (F2[i - 1] == -INFINITY) 
			{
				SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
				printf("%8s", "ERROR");
			}
			else 
			{
				SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
				printf("%8.4f", F2[i - 1]);
			}
		}
		SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
		cout << " |\n";
	}
	gotoxy(xdr, ydr + 3 + n);
	cout << "|=====|=========|=========|=========| \n";
	_getch;
}

void graphicki()
{
	system("CLS");
	const int WIDTH = 1100;
	const int HEIGHT = 900;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HPEN pen2 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdc, pen);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	cout << "\n\n\ty = e^(-2*x)";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	cout << "\n\n\ty = sqrt(1+(sin(x))^2";
	MoveToEx(hdc, 0, HEIGHT / 2, NULL);
	LineTo(hdc, WIDTH, HEIGHT / 2);
	MoveToEx(hdc, WIDTH / 2, 0, NULL);
	LineTo(hdc, WIDTH / 2, HEIGHT);

	SelectObject(hdc, pen2);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOutA(hdc, WIDTH / 2 - 10, 0, "y", 2);
	TextOutA(hdc, WIDTH, HEIGHT / 2, "x", 2);

	TextOutA(hdc, WIDTH / 2 + (WIDTH / 4) + 200, HEIGHT / 2 + 2, "5", 1);
	TextOutA(hdc, WIDTH / 2 + (WIDTH / 4) + 100, HEIGHT / 2 + 2, "4", 1);
	TextOutA(hdc, WIDTH / 2 + (WIDTH / 4), HEIGHT / 2 + 2, "3", 1);
	TextOutA(hdc, WIDTH / 2 + (WIDTH / 4) - 100, HEIGHT / 2 + 2, "2", 1);
	TextOutA(hdc, WIDTH / 2 + (WIDTH / 4) - 200, HEIGHT / 2 + 2, "1", 1);

	TextOutA(hdc, WIDTH / 2 - 10, HEIGHT / 2 + 2, "0", 1);

	TextOutA(hdc, WIDTH / 2 - (WIDTH / 4) + 200 - 4, HEIGHT / 2 + 2, "-1", 2);
	TextOutA(hdc, WIDTH / 2 - (WIDTH / 4) + 100 - 4, HEIGHT / 2 + 2, "-2", 2);
	TextOutA(hdc, WIDTH / 2 - (WIDTH / 4) - 4, HEIGHT / 2 + 2, "-3", 2);
	TextOutA(hdc, WIDTH / 2 - (WIDTH / 4) - 100 - 4, HEIGHT / 2 + 2, "-4", 2);
	TextOutA(hdc, WIDTH / 2 - (WIDTH / 4) - 200 - 4, HEIGHT / 2 + 2, "-5", 2);

	TextOutA(hdc, WIDTH / 2 - 13, HEIGHT / 2 + (HEIGHT / 4) + 150, "-5", 2);
	TextOutA(hdc, WIDTH / 2 - 13, HEIGHT / 2 + (HEIGHT / 4) + 75, "-4", 2);
	TextOutA(hdc, WIDTH / 2 - 13, HEIGHT / 2 + (HEIGHT / 4), "-3", 2);
	TextOutA(hdc, WIDTH / 2 - 13, HEIGHT / 2 + (HEIGHT / 4) - 75, "-2", 2);
	TextOutA(hdc, WIDTH / 2 - 13, HEIGHT / 2 + (HEIGHT / 4) - 150, "-1", 2);

	TextOutA(hdc, WIDTH / 2 - 10, HEIGHT / 2 - (HEIGHT / 4) + 150, "1", 1);
	TextOutA(hdc, WIDTH / 2 - 10, HEIGHT / 2 - (HEIGHT / 4) + 75, "2", 1);
	TextOutA(hdc, WIDTH / 2 - 10, HEIGHT / 2 - (HEIGHT / 4), "3", 1);
	TextOutA(hdc, WIDTH / 2 - 10, HEIGHT / 2 - (HEIGHT / 4) - 75, "4", 1);
	TextOutA(hdc, WIDTH / 2 - 10, HEIGHT / 2 - (HEIGHT / 4) - 150, "5", 1);

	for (int i = 0; i <= WIDTH; i++) {
		double x = (double)(i - WIDTH / 2) * PI / (WIDTH / 2);
		double y1 = pow(E, -2 * x);
		double y2 = sqrt(1 + pow(sin(x), 2));
		int j1 = HEIGHT / 2 - y1 * HEIGHT / 2 / PI;
		int j2 = HEIGHT / 2 - y2 * HEIGHT / 2 / PI;
		SetPixel(hdc, i, j1, RGB(255, 0, 0));
		SetPixel(hdc, i, j2, RGB(0, 255, 0));
	}

	DeleteObject(pen);
	DeleteObject(pen2);
	ReleaseDC(hwnd, hdc);
}

double eqf(double x) 
{
	return 2 * x * log10(x) - 3;
}

double hord(double a, double b, double eps)
{
	double t;
	do
	{
		t = a + (eqf(b) * (b - a)) / (eqf(b) - eqf(a));
		if (eqf(a) * eqf(t) < 0)
		{
			b = t;
		}
		else if (eqf(t) * eqf(b) < 0)
		{
			a = t;
		}
		else
			return t;
	}while (fabs(b - a) >= eps);
	return t;
}

double poldel(double a, double b, double eps)
{
	double f;
	do {
		f = (a + b) / 2;
		if (eqf(f) * eqf(a) < 0)
			b = f;
		else
			if (f == 0)
				return f;
			else
				a = f;
	} while (fabs(a - b) >= eps);
	return f;
}

void equation()
{
	double a, b, e, f;
	cout << "Введите А: ";
	cin >> a;
	cout << "Введите B: ";
	cin >> b;
	cout << "Введите погрешность: ";
	cin >> e;
	cout << "Метод половинного деления: " << poldel(a,b,e) << endl;
	cout << "Метод хорд: " << hord(a,b,e) << endl;
}

double inf(double x)
{
	return pow(E, x) + pow(E, -x);
}

double pramaug(double a, double b, double n)
{
	double h, S, x;
	int i;
	h = (b - a) * 1.0 / n;
	S = 0;
	for (i = 0; i < n - 1; i++)
	{
		x = a + i * h;
		S = S + inf(x);
	}
	S = h * S;
	return S;
}

double trapez(double a, double b, double n)
{
	double width = (b - a) / n;
	double trapez_integral = 0;
	for (int step = 0; step < n; step++) {
		double x1 = a + step * width;
		double x2 = a + (step + 1) * width;
		trapez_integral += 0.5 * (x2 - x1) * (inf(x1) + inf(x2));
	}
	return trapez_integral;
}

void integralinf()
{
	double a, b, n;
	cout << "Введите A: ";
	cin >> a;
	cout << "Введите B: ";
	cin >> b;
	cout << "Введите N (N>50): ";
	cin >> n;
	if (n <= 50)
	{
		cout << "Маленький интервал интегрирования, увеличте N";
	}
	else
	{
		cout << "Метод прямоугольников: " << pramaug(a, b, n) << "\n";
		cout << "Метод трапеций: " << trapez(a, b, n);
	}
}

int main()
{
	setlocale(LC_ALL, ".1251");
	ConsoleCursorVisible(false, 100);
	system("mode con cols=146 lines=45");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY);
	system("CLS");
	string Print_Menu[] = { "-->	Расчётная таблица", "-->	Графики", "-->	Решение уравнения", "-->	Решение интеграла", "-->	Заставка", "-->	Информация об авторе", "-->	Выход" };
	int Menu = 0;
	char key;
	system("title Расчётно-графическая работа, Гриневич Илья, ПИН-222");
	Screen();
	system("CLS");
	while (true)
	{
		int x = 60, y = 18;
		gotoxy(x, y);
		for (int i = 0; i < size(Print_Menu); i++)
		{
			if (i == Menu) 
				SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY);
			else 
				SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
			gotoxy(x, y++);
			cout << Print_Menu[i] << endl;
		}
		key = _getch();
		if (key == -32) 
			key = _getch();
		switch (key) 
		{
			case ESC:
				exit(0);
				break;
			case UP:
				if (Menu > 0)
					Menu--;
				break;
			case DOWN:
				if (Menu < size(Print_Menu) - 1)
					Menu++;
				break;
			case ENTER:
				switch (Menu)
				{
					case 0:
						system("CLS");
						gotoxy(67, 10);
						SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY);
						cout << "Минимальный элемент" << endl;
						gotoxy(67, 11);
						SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 4);
						cout << "Максимальный элемент" << endl;
						SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY);
						Table();
						_getch();
						system("CLS");
						break;
					case 1:
						system("CLS");
						SetConsoleTextAttribute(hStdOut, 0);
						graphicki();
						_getch();
						SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
						system("CLS");
						break;
					case 2:
						system("CLS");
						SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
						equation();
						_getch();
						system("CLS");
						break;
					case 3:
						system("CLS");
						SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
						integralinf();
						_getch();
						system("CLS");
						break;
					case 4:
						system("CLS");
						Screen();
						system("CLS");
						cout << "Для выхода нажмите любую клавишу";
						_getch();
						system("CLS");
						break;
					case 5:
						system("CLS");
						SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE + BACKGROUND_INTENSITY + 14);
						Me();
						_getch();
						system("CLS");
						break;
					case 6:
						exit(0);
				}
				break;
		}
	}
	_getch();
}