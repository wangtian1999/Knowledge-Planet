#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ROW 15
#define COL 15

char board[ROW][COL];  //棋盘

//初始化棋盘
void InitBoard()
{
	//该段代码使用了两个嵌套循环，遍历整个棋盘数组。
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			board[i][j] = '-';
		}
	}
}

//显示棋盘
void DisplayBoard()
{
	printf("  ");
	for(int i = 0; i < COL; i++)
	{
		printf("%d ", i);
	}
	printf("\n");

	//该段代码使用了两个嵌套循环，遍历整个棋盘数组。
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

//判断是否下满棋子
bool IsFull()
{
	//函数中使用了两个嵌套的循环语句，遍历整个棋盘数组。
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			//在每个交点处，如果该位置上的棋子状态为“-”（表示空），则说明还有空位可以落子，此时函数返回false。
			if(board[i][j] == '-')
			{
				return false;
			}

		}
	}
	//如果在遍历完整个棋盘后都没有找到空位，则说明棋盘已经填满了所有格子，此时函数返回true。
	return true;
}

//判断胜利
bool IsWin(char ch)
{
	//横向判断
	//该段代码使用了两个嵌套循环，遍历整个棋盘数组。
	for(int i = 0; i < ROW; i++)
	{
		//在每一行内部，从左到右依次检查长度为5的连续区间（即board[i][j]到board[i][j+4])是否全部由相同颜色的棋子组成。
		for(int j = 0; j < COL-4; j++)
		{
			//如果发现某一行满足上述条件，则说明该方获胜，函数返回值为 true。
			if(board[i][j] == ch && board[i][j+1] == ch && board[i][j+2] == ch && board[i][j+3] == ch && board[i][j+4] == ch)
			{
				return true;
			}
		}
	}

	//纵向判断
	for(int i = 0; i < ROW-4; i++)
	{
		//在每一列内部，从上到下依次检查长度为5的连续区间（即board[i][j]到board[i+4][j])是否全部由相同颜色的棋子组成。
		for(int j = 0; j < COL; j++)
		{
			if(board[i][j] == ch && board[i+1][j] == ch && board[i+2][j] == ch && board[i+3][j] == ch && board[i+4][j] == ch)
			{
				return true;
			}
		}
	}

	//斜向判断（左上到右下）
	for(int i = 0; i < ROW-4; i++)
	{
		//在每一个以左上角为起点、长度为5的斜线内部，依次检查是否全部由相同颜色的棋子组成。
		for(int j = 0; j < COL-4; j++)
		{
			if(board[i][j] == ch && board[i+1][j+1] == ch && board[i+2][j+2] == ch && board[i+3][j+3] == ch && board[i+4][j+4] == ch)
			{
				return true;
			}
		}
	}

	//斜向判断（右上到左下）
	for(int i = 0; i < ROW-4; i++)
	{
		//在每一个以右上角为起点、长度为5的斜线内部，依次检查是否全部由相同颜色的棋子组成。
		for(int j = 4; j < COL; j++)
		{
			if(board[i][j] == ch && board[i+1][j-1] == ch && board[i+2][j-2] == ch && board[i+3][j-3] == ch && board[i+4][j-4] == ch)
			{
				return true;
			}
		}
	}
	return false;
}

//玩家下棋
void PlayerMove(char ch)
{
	int row,col;
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


//电脑下棋
void ComputerMove(char ch)
{
	int row, col;
	printf("请电脑 %c 下棋（行 列）：\n", ch);
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


int main(void) {

	//初始化随机数种子
	//这段代码是C语言中的随机数生成器初始化代码。它使用当前时间作为种子，以确保每次程序运行时都会产生不同的随机数序列。
	//在这里，srand()函数接受一个unsigned int类型的参数，并将其用作伪随机数生成器的种子。time(NULL)函数返回从1970年1月1日00:00:00 UTC到当前时间所经过的秒数，因此可以用来获得一个动态变化的值作为种子。
	//通过调用srand()并传递不同的种子值，我们可以使程序每次运行时产生不同、看起来更加随机和真实世界相关性更强的输出结果。
	srand((unsigned int)time(NULL));

	//初始化棋盘
	printf("+-----------------------------------+\n");
	printf("|       Welcome to Five Stones      |\n");
	printf("+-----------------------------------+\n");

	InitBoard();

	//显示棋盘
	DisplayBoard();

	//玩家先手，电脑后手
	char player = 'X';
	char computer = 'O';

	//实现游戏流程
	while(true)
	{
		//玩家下棋
		PlayerMove(player);

		//显示棋盘
		DisplayBoard();

		//判断玩家是否胜利
		if(IsWin(player))
		{
			printf("玩家 %c 获胜！\n", player);
			break;
		}

		//判断是否下满棋子
		if(IsFull())
		{
			printf("棋盘已满，游戏结束！\n");
			break;
		}

		//电脑下棋
		ComputerMove(computer);

		//显示棋盘
		DisplayBoard();

		//判断电脑是否胜利
		if(IsWin(computer))
		{
			printf("电脑 %c 获胜！\n", computer);
			break;
		}

		//判断是否下满棋子
		if(IsFull())
		{
			printf("棋盘已满，游戏结束！\n");
			break;
		}
	}

	return 0;
}
