#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
void gotoxy(int x, int y);
void draw_star(int x, int y);
void erase_star(int x, int y);
void setcursor(bool visible);
void draw_ship(int x, int y);
void draw_bullet(int x, int y);
void clear_bullet(int x, int y);
char cursor(int x, int y);
void spawnstar(int n);
void draw_score(int x,int y);
void setcolor(int fg, int bg);
void erase_ship(int x, int y);
char ch = '.';
int x = 38, y = 20;
int bx, by, i,j;
int bullet = 0;
int movex = 0;
int score = 0;
int xran[20], yran[20];
bool checkdraw[999][999];
int main()
{
	draw_ship(x, y);
	setcursor(0);
	srand(time(NULL));
	spawnstar(20);
		do {
			if (_kbhit()) {
				ch = _getch();
				if (ch == 'a') 
				{ 
					//draw_ship(--x, y);
					movex = -1;
				
				}
				if (ch == 'd') 
				{ 
					//draw_ship(++x, y); 
					movex = 1;
					
				}
				if (ch == 's')
				{
					//draw_ship(++x, y); 
					movex = 0;

				}
				if (bullet != 1 && ch == ' ')
				{ 
					bullet = 1; bx = x + 3; by = y - 1; 
				}
				fflush(stdin);
			}
			if (bullet == 1) {

				clear_bullet(bx, by);
				if (by == 2) 
				{
					bullet = 0; 
				}
				else 
				{ 
					if (cursor(bx, by - 1) == '*')
					{
						Beep(700, 50);

						spawnstar(1);
						score++;
						clear_bullet(bx, by-1);
						bullet = 0;
						erase_star(bx, by-1);
					}
					else {
						draw_bullet(bx, --by);
					}
			
				}
			}
			if (movex == -1 && x >= 2)
			{
				erase_ship(x, y);
				draw_ship(--x, y);
			}
			if (movex == 1 && x <= 80)
			{
				erase_ship(x, y);
				draw_ship(++x, y);
			}
			if (movex == 0)
			{
				draw_ship(x, y);
			}
			draw_score(80, 0);
			Sleep(50);
		} while (ch != 'x');
		
	
	
	return 0;
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void spawnstar(int n)
{
	for (i = 0; i < n; )
	{
		xran[i] = rand() % 90;
		yran[i] = rand() % 10;
		
		for (j = 0; j != i; j++)
		{
			if (checkdraw[xran[i]][yran[i]] == checkdraw[xran[j]][yran[j]])
			{
				xran[i] = rand() % 90;
				yran[i] = rand() % 10;
				j = 0;
			}
		}
		if ((xran[i] >= 10 && xran[i] <= 70) && (yran[i] >= 2 && yran[i] <= 5))
		{
			draw_star(xran[i], yran[i]);
			checkdraw[xran[i]][yran[i]] = 1;
			i++;
		}
	}
}
void draw_score(int x, int y)
{
	gotoxy(x,y);
	setcolor(5, 14);
	printf("Scores %d",score);
}
void draw_star(int x, int y)
{
	gotoxy(x, y);
	setcolor(14, 0);
	printf("*");
}
void erase_star(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

void draw_ship(int x, int y)
{
	gotoxy(x, y); 
	setcolor(12, 0);
	printf(" <-0-> ");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("       ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); 
	setcolor(0, 2);
	printf("+");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); 
	setcolor(0, 0);
	printf(" ");
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
char cursor(int x, int y) 
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}