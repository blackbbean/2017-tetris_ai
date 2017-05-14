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

// AI이름 표시를 위해 지정
// 본인의 학번으로 할 것.
DECLSPEC_EXPORT
char* WINAPI Name()
{
	strcpy(gName, "2015113458");
	return gName;
}

/*
 * board는 boardW*boardH의 길이의 문자열로 이루어져 있다.
 * 예를 들어, 8*3크기의 경우：
 * 00000000
 * 00011001
 * 01111111
 * board에 다음과 같이 주어진다 ："011111110001100100000000".
 *
 * curPiece는 블럭의 모양으로 "OISZLJT" 중 하나의 문자열이 주어진다.
 * nextPiece는 미리보기를 사용할 경우 OISZLJT 중 하나가 그렇지 않을 경우 공백이 주어진다.
 * curR은 현재 블럭의 방향을 나타내며 1이 초기 방향，2는 90도 회전，3는180도 회전，4는 270도 회전된 것이다.
 * curX,curY는 4*4 블럭에서 1, 2의 위치를 기준으로 블럭의 현재 위치를 나타내는 좌표값이다.
 *		board에서 x=1,y=1은 왼쪽 하단,
 *		board에서 x=boardW,y=1은 오른쪽 하단,
 *		board에서 x=1,y=boardH은 왼쪽 상단이다.
 *		디렉토리에 pieces_orientations.jpg 파일 참고.
 *		기본 초기 위치는 curY==boardH-1, curX==boardW/2+1이다.
 *
 * bestX,bestRotation 을 지정하면 된다. (curX,curR과 같은 규칙을 따름)
 *
 * 참고：회전이 먼저 이루어지며 이후 x좌표를 이동한 후 떨어트린다.
 *		이 함수는 블록당 1회 호출 된다.
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

* 내려올 블럭을 숫자로 치환한다. 이후에 gPieceBitmap에 접근하기 쉽게 하기 위하여.

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

* 기본적으로 블록은 맨 왼쪽으로 보낼 수 있을 때 까지 보낸후 검사하는 방식이다.

* 최대한 x가 왼쪽으로 붙었으면 y를 아래로 내릴 수 있을 때 까지 내린다.

*/
	int x = curX;
	int y = curY;
	double best_score = -1000;
	for (int r = 0; r < 4; r++) {
		while (true) { //맨 왼쪽으로 이동
			x = x - 1;
			if (out_range_func(board, x, y, r, curBlockNum)) {
				x = x + 1;
				break;
			}
		}
		while (true)
		{
			y = curY;
			if (out_range_func(board, x, y, r, curBlockNum))//x가 오른쪽 끝으로 넘어가면 되돌려준다.
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
* path를 지정하는 명령어에 대한 설명：
*      'l': 한 칸 왼쪽으로 이동
*      'r': 한 칸 오른쪽으로 이동
*      'd': 한 칸 아래로 이동
*      'L': 가능한 가장 왼쪽으로 이동
*      'R': 가능한 가장 오른쪽으로 이동
*      'D': 가능한 가장 아래로 이동（이 후 추가 이동 가능）
*      'z': 반 시계방향으로 회전
*      'c': 시계방향으로 회전
* path 문자열 끝에'\0'이 하드 랜딩을 나타낸다.
*
* 위의 명령어를 이용하여 임의의 이동이 가능하며 아래의 전체 코드를 수정하여야 한다.
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

* 블럭을 놓을 수 있는 위치를 찾는 함수.

* 블럭이 보드 밖을 빠져 나가도 실제 블럭이 있는 위치랑 상관 없으면 괜찮다.


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

* 이전 out_range_func()함수를 통해 좁해진 범위에 대해서 이미 블럭이 있는지 없는지를 조사하는 함수.

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

*out_range_func()와 already_block_func()을 통해 범위를 좁힌 후 점수 계산을 하는 함수.

* 점수 계산 요소로는
1. 각 열의 최대 높이의 합(aggregate_height)
2. 각 열의 가장 밑에서부터 최고 높이까지의 빈 공간의 합.(hole_num)
3. 지울 수 있는 라인의 갯수(delete_line)
4. 만약 한 열이 통째로 비워져 있을 때 'L'이나 'I'같은 블럭으로 지우기 쉽게 할 수 있는 부분(bumpiness)

4가지를 활용했습니다.

(참고: 점수 계산 요소는 https://codemyroad.wordpress.com/2013/04/14/tetris-ai-the-near-perfect-player/ 이분의 블로그 참고.)

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


	// * 검사하려는 블럭을 가상으로 내려보기.

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