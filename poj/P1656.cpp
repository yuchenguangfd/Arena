/*
 * Problem: Counting Black
 * http://poj.org/problem?id=1656
 */

#include <cstdio>
#include <cstring>

class Board {
public:
	const static int BLACK = 1;
	const static int WHITE = 0;
	Board() {
		memset(mBoard, 0, sizeof(mBoard));
	}
	void Paint(int x, int y, int size, int color) {
		for (int i = x; i < x + size; ++i) {
			for (int j = y; j < y + size; ++j) {
				mBoard[i][j] = color;
			}
		}
	}
	int Count(int x, int y, int size, int color) {
		int count = 0;
		for (int i = x; i < x + size; ++i) {
		   for (int j = y; j < y + size; ++j) {
			   if (mBoard[i][j] == color) {
				   ++count;
			   }
		   }
		}
		return count;
	}
private:
	int mBoard[128][128];
};


int main(){
	int numCommand;
	scanf("%d", &numCommand);
	Board board;
	while (numCommand--) {
		char command[8];
		int x, y, size;
		scanf("%s%d%d%d", command, &x, &y, &size);
		switch (command[0]) {
			case 'B':
				board.Paint(x, y, size, Board::BLACK);
				break;
			case 'W':
				board.Paint(x, y, size, Board::WHITE);
				break;
			case 'T':
				printf("%d\n", board.Count(x, y, size, Board::BLACK));
				break;
		}
	}
	return 0;
}
