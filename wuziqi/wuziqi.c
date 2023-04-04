#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 

#define ROW 15
#define COL 15

char board[ROW][COL]; // 棋盘

int i = 0;

// 初始化棋盘
void InitBoard()
{
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			board[i][j] = '-';
		}
	}
}

// 显示棋盘
void DisplayBoard()
{
	printf("  ");
	for(int i = 0; i < COL; i++)
	{
		printf("%d ", i);
	}
	printf("\n");

	for(int i = 0; i < ROW; i++)
	{
		printf("%d ", i);
		for(int j = 0; j < COL; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

// 判断是否下满棋子
bool IsFull()
{
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			if(board[i][j] == '-')
			{
				return false;
			}
		}
	}
	return true;
}

// 判断胜利
bool IsWin(char ch)
{
	// 横向判断
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL-4; j++)
		{
			if(board[i][j] == ch && board[i][j+1] == ch && board[i][j+2] == ch && board[i][j+3] == ch && board[i][j+4] == ch)
			{
				return true;
			}
		}
	}

	// 纵向判断
	for(int i = 0; i < ROW-4; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			if(board[i][j] == ch && board[i+1][j] == ch && board[i+2][j] == ch && board[i+3][j] == ch && board[i+4][j] == ch)
			{
				return true;
			}
		}
	}

	// 斜向判断（左上到右下）
	for(int i = 0; i < ROW-4; i++)
	{
		for(int j = 0; j < COL-4; j++)
		{
			if(board[i][j] == ch && board[i+1][j+1] == ch && board[i+2][j+2] == ch && board[i+3][j+3] == ch && board[i+4][j+4] == ch)
			{
				return true;
			}
		}
	}

	// 斜向判断（右上到左下）
	for(int i = 0; i < ROW-4; i++)
	{
		for(int j = 4; j < COL; j++)
		{
			if(board[i][j] == ch && board[i+1][j-1] == ch && board[i+2][j-2] == ch && board[i+3][j-3] == ch && board[i+4][j-4] == ch)
			{
				return true;
			}
		}
	}return false;}
// 玩家下棋
void PlayerMove(char ch)
{
	int row, col;
	//在函数内部，先输出提示信息要求玩家输入落子位置（行和列）。
	printf("请玩家 %c 下棋（行 列）：", ch);
	//使用 scanf 函数读取用户输入的行和列数，并将其存储在变量 row 和 col 中。
	scanf("%d %d", &row, &col);
	//如果输入错误或者该位置已经有棋子，则使用循环语句一直等待用户重新输入正确的位置。如果当前位置为空（即等于字符“-”），则跳出循环并进行下一步操作。
	while(row < 0 || row >= ROW || col < 0 || col >= COL || board[row][col] != '-')
	{
		printf("输入错误，请重新输入（行 列）：");
		scanf("%d %d", &row, &col);
	}
	//最后，在合法的情况下向棋盘数组中添加对应颜色(ch)的棋子，并结束函数执行。
	board[row][col] = ch;
}

// 电脑下棋
void ComputerMove(char ch)
{
	int row, col;
	while(true)
	{
		//在每次循环中，生成两个随机数 row 和 col 分别表示落子位置的行和列。这里使用了C标准库中的 rand() 函数生成随机数。
		row = rand() % ROW;
		col = rand() % COL;
		//判断该位置是否为空（即等于字符“-”），如果是，则向棋盘数组中添加对应颜色(ch)的棋子，并跳出循环；否则继续进行下一轮循环。
		if(board[row][col] == '-')
		{
			board[row][col] = ch;
			break;
		}
	}
}

int main()
{
	// 初始化随机数种子
	srand((unsigned int)time(NULL));
	// 初始化棋盘
	InitBoard();

	// 显示棋盘
	DisplayBoard();

	// 玩家先手，电脑后手
	char player = 'X';
	char computer = 'O';

	while(true)
	{
		// 玩家下棋
		PlayerMove(player);

		// 显示棋盘
		DisplayBoard();

		// 判断玩家是否胜利
		if(IsWin(player))
		{
			printf("玩家 %c 获胜！\n", player);
			break;
		}

		// 判断是否下满棋子
		if(IsFull())
		{
			printf("棋盘已满，游戏结束！\n");
			break;
		}

		// 电脑下棋
		ComputerMove(computer);

		// 显示棋盘
		DisplayBoard();

		// 判断电脑是否胜利
		if(IsWin(computer))
		{
			printf("电脑获胜！\n");
			break;
		}

		// 判断是否下满棋子
		if(IsFull())
		{
			printf("棋盘已满，游戏结束！\n");
			break;
		}
	}

	return 0;
}
