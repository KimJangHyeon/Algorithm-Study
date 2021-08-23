# 20210823

## 김장현

https://programmers.co.kr/learn/courses/30/lessons/60061

```c++
0.#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int board[204][204] = {0, };
int N;
const static int PILLAR = 0;
const static int WALL = 1;

const static int REMOVE = 0;
const static int BUILD = 1;

bool compare(vector<int> v1, vector<int> v2) {
	// x
	if (v1[0] < v2[0]) {
		return true;
	}
	if (v1[0] > v2[0]) {
		return false;
	}

	// y
	if (v1[1] < v2[1]) {
		return true;
	}
	if (v1[1] > v2[1]) {
		return false;
	}

	return v1[2] < v2[2];
}

bool existConditionPillar(int y, int x) {
	//바닥 위
	if (y == 1) {
			return true;
	}
	//왼쪽에 보가 있음
	if (board[y - 1][x - 1] == 1) {
		return true;
	}
	//오른쪽에 보가 있음
	if (board[y - 1][x + 1] == 1) {
		return true;
	}

	// 밑에 기둥
	if (y - 2 >= 0 && board[y - 2][x] == 1) {
		return true;
	}

	return false;
}

bool existConditionWall(int y, int x) {
	// 바닥엔 보가 없기 때문에 예외처리 안함 + x는 홀수
	//왼쪽에 기둥
	if (board[y - 1][x - 1] == 1) {
		return true;
	}
	//오른쪽에 기둥
	if (board[y - 1][x + 1] == 1) {
		return true;

	}

	// 양쪽에 보
	if (0 > x - 2) {
		return false;
	}
	if (board[y][x - 2] == 1 && board[y][x + 2] == 1) {
		return true;
	}

	return false;
}

void buildPillar(int y, int x) {
	// 기둥을 세울 수 없음
	if (existConditionPillar(y, x)) {
		board[y][x] = 1;
		return;
	}
	cout << "FAIL" << endl;
}

void removePillar(int y, int x) {
	// 위 기둥에 영향
	board[y][x] = 0;
	// 위 왼쪽 보에 영향
	if ((x - 1 >= 0) && board[y + 1][x - 1] == 1) {
		if (!existConditionWall(y + 1, x - 1)) {
			board[y][x] = 1;
			return;
		}
	}
	// 위 오른쪽 보에 영향
	if (board[y + 1][x + 1] == 1) {
		if (!existConditionWall(y + 1, x + 1)) {
			board[y][x] = 1;
			return;
		}
	}
	// 위 기둥에 영향
	if (board[y + 2][x] == 1) {
		if (!existConditionPillar(y + 2, x)) {
			board[y][x] = 1;
			return;
		}
	}
}

void removeWall(int y, int x) {
	board[y][x] = 0;
	// 왼쪽 보
	if (x - 2 >= 0 && board[y][x - 2] == 1) {
		if (!existConditionWall(y, x - 2)) {
			board[y][x] = 1;
			return;
		}
	}
	// 왼쪽 기둥
	if (x - 1 >= 0 && board[y + 1][x - 1] == 1) {
		if (!existConditionPillar(y + 1, x - 1)) {
			board[y][x] = 1;
			return;
		}
	}
	//오른쪽 보
	if (board[y][x + 2] == 1) {
		if (!existConditionWall(y, x + 2)) {
			board[y][x] = 1;
			return;
		}
	}
	// 오른쪽 기둥
	if (board[y + 1][x + 1] == 1) {
		if (!existConditionPillar(y + 1, x + 1)) {
			board[y][x] = 1;
			return;
		}
	}
}


void buildWall(int y, int x) {
	if (existConditionWall(y, x)) {
		board[y][x] = 1;
		return;
	}
	cout << "FAIL" << endl;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frames) {

	N = n;
	for (vector<int> build_frame : build_frames) {
		int x = build_frame[0];
		int y = build_frame[1];
		int structure_type = build_frame[2];
		int build_remove = build_frame[3];

		// 기둥
		if (structure_type == PILLAR) {
			y = 2*y + 1;
			x = 2*x;
			cout << "(" << x << ", " << y << ")" << endl;
			if (BUILD == build_remove) {
				cout << "BUILD PILLAR" << endl;
				buildPillar(y, x);
			} else {
				cout << "REMOVE PILLAR" << endl;
				removePillar(y, x);
			}

		}

		// 보
		else {
			y = 2 * y;
			x = 2 * x + 1;
			cout << "(" << x << ", " << y << ")" << endl;
			if (BUILD == build_remove) {
				cout << "BULID WALL" << endl;
				buildWall(y, x);
			} else {
				cout << "REMOVE WALL " << endl;
				removeWall(y, x);
			}
		}
	}

	vector<vector<int>> answer;
	for (int i = 0; i < 2 * n + 2; i++) {

		for (int j = 0; j < 2 * n + 2; j++) {
			if (board[i][j] == 1) {
				vector<int> v;
				//기둥
				if (i%2 == 1) {
					v = {j / 2, i / 2, PILLAR};
				} else {
					v = {j / 2, i / 2, WALL};
				}
                answer.push_back(v);
			}
		}
	}

	sort(answer.begin(), answer.end(), compare);
	
	return answer;
}
```

