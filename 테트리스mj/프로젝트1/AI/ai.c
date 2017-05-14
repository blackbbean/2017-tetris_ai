#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define bool int
#define true 1
#define false 0
#include <math.h>
#include <string.h>

#define DECLSPEC_EXPORT __declspec(dllexport)
#define WINAPI __stdcall

char gName[64];
double check_score(char board[], int x, int y, int r, int cur_block_num);
bool out_range_func(char board[], int x, int y, int r, int curblock_num);
bool already_block_func(char board[], int x, int y, int r, int curBlockNum);
char gPieceBitmap[8][4][4][4] =
{
	// NULL
	{
		{
			{0},
		},
	},
	// O
	{
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		},
	},
	// I
	{
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
		},
	},
	// S
	{
		{
			{0, 0, 0, 0},
			{0, 0, 1, 1},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 1},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 1},
			{0, 0, 0, 0},
		},
	},
	// Z
	{
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 1},
			{0, 0, 1, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 1},
			{0, 0, 1, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
		},
	},
	// L
	{
		{
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 1, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 1},
			{0, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
		},
	},
	// J
	{
		{
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 1},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 1, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		},
	},
	// T
	{
		{
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
		},
	},
};

#ifdef __cplusplus
extern "C" {
#endif

// AI�̸� ǥ�ø� ���� ����
// ������ �й����� �� ��.
DECLSPEC_EXPORT
char* WINAPI Name()
{
	strcpy(gName, "2015113458");
	return gName;
}

/*
 * board�� boardW*boardH�� ������ ���ڿ��� �̷���� �ִ�.
 * ���� ���, 8*3ũ���� ��죺
 * 00000000
 * 00011001
 * 01111111
 * board�� ������ ���� �־����� ��"011111110001100100000000".
 *
 * curPiece�� ���� ������� "OISZLJT" �� �ϳ��� ���ڿ��� �־�����.
 * nextPiece�� �̸����⸦ ����� ��� OISZLJT �� �ϳ��� �׷��� ���� ��� ������ �־�����.
 * curR�� ���� ���� ������ ��Ÿ���� 1�� �ʱ� ���⣬2�� 90�� ȸ����3��180�� ȸ����4�� 270�� ȸ���� ���̴�.
 * curX,curY�� 4*4 ������ 1, 2�� ��ġ�� �������� ���� ���� ��ġ�� ��Ÿ���� ��ǥ���̴�.
 *		board���� x=1,y=1�� ���� �ϴ�,
 *		board���� x=boardW,y=1�� ������ �ϴ�,
 *		board���� x=1,y=boardH�� ���� ����̴�.
 *		���丮�� pieces_orientations.jpg ���� ����.
 *		�⺻ �ʱ� ��ġ�� curY==boardH-1, curX==boardW/2+1�̴�.
 *
 * bestX,bestRotation �� �����ϸ� �ȴ�. (curX,curR�� ���� ��Ģ�� ����)
 *
 * ����ȸ���� ���� �̷������ ���� x��ǥ�� �̵��� �� ����Ʈ����.
 *		�� �Լ��� ��ϴ� 1ȸ ȣ�� �ȴ�.
 */
int AI(int boardW, int boardH,
	char board[],
	char curPiece,
	int curX, int curY,
	int curR,
	char nextPiece,
	int* bestX, int* bestRotation)
{
	int curBlockNum;	

/*

* ������ ���� ���ڷ� ġȯ�Ѵ�. ���Ŀ� gPieceBitmap�� �����ϱ� ���� �ϱ� ���Ͽ�.

*/
switch (curPiece)
	{
	case 'O':
		curBlockNum = 1;
		break;
	case 'I':
		curBlockNum = 2;
		break;
	case 'S':
		curBlockNum = 3;
		break;
	case 'Z':
		curBlockNum = 4;
		break;
	case 'L':
		curBlockNum = 5;
		break;
	case 'J':
		curBlockNum = 6;
		break;
	case 'T':
		curBlockNum = 7;
		break;
	default:
		break;
	}


/*

* �⺻������ ����� �� �������� ���� �� ���� �� ���� ������ �˻��ϴ� ����̴�.

* �ִ��� x�� �������� �پ����� y�� �Ʒ��� ���� �� ���� �� ���� ������.

*/
	int x = curX;
	int y = curY;
	double best_score = -1000;
	for (int r = 0; r < 4; r++) {
		while (true) { //�� �������� �̵�
			x = x - 1;
			if (out_range_func(board, x, y, r, curBlockNum)) {
				x = x + 1;
				break;
			}
		}
		while (true)
		{
			y = curY;
			if (out_range_func(board, x, y, r, curBlockNum))//x�� ������ ������ �Ѿ�� �ǵ����ش�.
			{
				break;
			}
			while (true) {
				y = y - 1;
				if (out_range_func(board, x, y, r, curBlockNum) || already_block_func(board, 20-y, x-1, r, curBlockNum))
				{
					y = y + 1;
					double score = 0;
					score = check_score(board, 20-y, x-1, r, curBlockNum);
					if (score > best_score) {
						best_score = score;
						*bestX = x;
						*bestRotation = r + 1;
					}
					break;
				}
			}
			x = x + 1;
		}
	}
	return 0;
}

/*
* path�� �����ϴ� ��ɾ ���� ����
*      'l': �� ĭ �������� �̵�
*      'r': �� ĭ ���������� �̵�
*      'd': �� ĭ �Ʒ��� �̵�
*      'L': ������ ���� �������� �̵�
*      'R': ������ ���� ���������� �̵�
*      'D': ������ ���� �Ʒ��� �̵����� �� �߰� �̵� ���ɣ�
*      'z': �� �ð�������� ȸ��
*      'c': �ð�������� ȸ��
* path ���ڿ� ����'\0'�� �ϵ� ������ ��Ÿ����.
*
* ���� ��ɾ �̿��Ͽ� ������ �̵��� �����ϸ� �Ʒ��� ��ü �ڵ带 �����Ͽ��� �Ѵ�.
*/
DECLSPEC_EXPORT
int WINAPI AIPath(int boardW, int boardH,
	char board[],
	char curPiece,
	int curX, int curY,
	int curR,
	char nextPiece,
	char path[])
{
	//if (0)
	{
		int bestX = 0;
		int bestRotation = 1;
		AI(boardW, boardH,
			board,
			curPiece,
			curX, curY,
			curR,
			nextPiece,
			&bestX, &bestRotation
		);
		while (curR != bestRotation)
		{
			strcat(path, "z");
			curR = curR % 4 + 1;
		}
		while (curX > bestX)
		{
			strcat(path, "l");
			curX -= 1;
		}
		while (curX < bestX)
		{
			strcat(path, "r");
			curX += 1;
		}
	}
	//strcpy(path, "ddddddddddcccrrrrrrDL");
	return 0;
}


/*

* ���� ���� �� �ִ� ��ġ�� ã�� �Լ�.

* ���� ���� ���� ���� ������ ���� ���� �ִ� ��ġ�� ��� ������ ������.


*/


bool out_range_func(char board[], int x, int y, int r, int curblock_num) 
{


	bool flag_out_range;

		flag_out_range = false;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int tempX = x + j - 2;
				int tempY = y - i + 1;
				if (tempX < 1 || tempX>10 || tempY > 20 || tempY < 1)
				{
					if (gPieceBitmap[curblock_num][r][i][j] == '\x1')
					{
						flag_out_range = true;
						break;
					}
				}
				if (i == 3 && j == 3)
					flag_out_range = false;
			}
			if (flag_out_range == true)
				break;
		}

	
	if (flag_out_range)
		return true;
	else
		return false;

}

/*

* ���� out_range_func()�Լ��� ���� ������ ������ ���ؼ� �̹� ���� �ִ��� �������� �����ϴ� �Լ�.

*/


bool already_block_func(char board[], int x, int y, int r, int curBlockNum) 
{

	char simul_board[20][10];
	int k = 0;


	for (int i = 19; i >= 0; i--)
	{
		for (int j = 0; j < 10; j++)
			simul_board[i][j] = board[k++];
	}

	bool flag_already_full = false;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int tempX = x + i - 1;
			int tempY = y + j - 2;
			if (simul_board[tempX][tempY] == '1')
			{
				if (gPieceBitmap[curBlockNum][r][i][j] == '\x1')
				{
					flag_already_full = true;
					break;
				}
			}
			if (i == 3 && j == 3)
				flag_already_full = false;
		}
		if (flag_already_full)
			break;
	}
	if (flag_already_full)
		return true;
	else
		return false;

}


/*

*out_range_func()�� already_block_func()�� ���� ������ ���� �� ���� ����� �ϴ� �Լ�.

* ���� ��� ��ҷδ�
1. �� ���� �ִ� ������ ��(aggregate_height)
2. �� ���� ���� �ؿ������� �ְ� ���̱����� �� ������ ��.(hole_num)
3. ���� �� �ִ� ������ ����(delete_line)
4. ���� �� ���� ��°�� ����� ���� �� 'L'�̳� 'I'���� ������ ����� ���� �� �� �ִ� �κ�(bumpiness)

4������ Ȱ���߽��ϴ�.

(����: ���� ��� ��Ҵ� https://codemyroad.wordpress.com/2013/04/14/tetris-ai-the-near-perfect-player/ �̺��� ��α� ����.)

*/



double check_score(char board[], int x, int y, int r, int cur_block_num)
{
	char simul_board[20][10];
	int k = 0;

	for (int i = 19; i>=0 ; i--)
	{
		for (int j = 0; j < 10; j++)
			simul_board[i][j] = board[k++];
	}


	// * �˻��Ϸ��� ���� �������� ��������.

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int tempX = x + i - 1;
 			int tempY = y + j - 2 ;
		if (gPieceBitmap[cur_block_num][r][i][j] == '\x1')
				simul_board[tempX][tempY] = '1';
		}
	}

	// * aggregate_height 

	int aggregate_height = 0;
	char c = '1';
	for (int i = 0; i<10; i++)
	{
		int height = -1;
		for (int j =0; j<20; j++)
		{
 			if(simul_board[j][i]=='1')
				break;
			height++;
		}
		aggregate_height += 19 - height;
	}

	// * hole_num

	int hole_num = 0;
	for (int i = 0; i < 10; i++)
	{
		int j;
		for (j = 0; j<20; j++)
		{
			if (simul_board[j][i] == '1')
				break;
		}
		for (int k = j; k<20; k++) 
		{
			if (simul_board[k][i] == '0')
				hole_num++;
		}
	}

	// * delete_line

	int delete_line = 0;
	for (int i = 19; i >= 0; i--)
	{
		int index = -1;
		for (int j = 0; j < 10; j++)
		{
			if (simul_board[i][j] == '1')
				index++;
		}
		if (index == 9)
			delete_line++;
	}

	// * bumpiness

	int bumpiness = 0;
	
	for (int i = 0; i < 9; i++)
	{
		int j;
		int temp_space_left = 0;
		int temp_space_right = 0;
		for (j = 0; j<20; j++)
		{
			if (simul_board[j][i] == '1')
				break;
		}

		temp_space_left = 20 - j;
	
		for (j = 0; j<20; j++)
		{
			if (simul_board[j][i+1] == '1')
				break;
		}
	
		temp_space_right = 20 - j;

		bumpiness+=abs(temp_space_left - temp_space_right);
	}

	double score = (aggregate_height)-(hole_num * 2) + (delete_line)*1.2 - (bumpiness)*0.3;

	return score;


}