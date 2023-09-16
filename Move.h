// #include<bits/stdc++.h>
// #include "2048.h"

int *MoveLeft(int f[][4], int fgrid[][4], int &score) {
	for (int i = 0; i < 4; i++) {
		auto res = Processs({fgrid[i][3], fgrid[i][2], fgrid[i][1], fgrid[i][0]}, score);
		f[i][3] = res[0];
		f[i][2] = res[1];
		f[i][1] = res[2];
		f[i][0] = res[3];
	}	
	return reinterpret_cast<int *>(f);
}

int *MoveRight(int f[][4], int fgrid[][4], int &score) {
	for (int i = 0; i < 4; i++) {
		auto res = Processs({fgrid[i][0], fgrid[i][1], fgrid[i][2], fgrid[i][3]}, score);
		f[i][0] = res[0];
		f[i][1] = res[1];
		f[i][2] = res[2];
		f[i][3] = res[3];
	}	
	return reinterpret_cast<int *>(f);
}

int *MoveUp(int f[][4], int fgrid[][4], int &score) {
	for (int i = 0; i < 4; i++) {
		auto res = Processs({fgrid[3][i], fgrid[2][i], fgrid[1][i], fgrid[0][i]}, score);
		f[3][i] = res[0];
		f[2][i] = res[1];
		f[1][i] = res[2];
		f[0][i] = res[3];
	}	
	return reinterpret_cast<int *>(f);
}

int *MoveDown(int f[][4], int fgrid[][4], int &score) {
	for (int i = 0; i < 4; i++) {
		auto res = Processs({fgrid[0][i], fgrid[1][i], fgrid[2][i], fgrid[3][i]}, score);
		f[0][i] = res[0];
		f[1][i] = res[1];
		f[2][i] = res[2];
		f[3][i] = res[3];
	}	
	return reinterpret_cast<int *>(f);
}

int *getMove(int move, int newState[][4], int curState[][4]) {
	int score = 0;
	if (move == 0) 
		MoveLeft(newState, curState, score);
	else if (move == 1)
		MoveRight(newState, curState, score);
	else if (move == 2)
		MoveUp(newState, curState, score);
	else 
		MoveDown(newState, curState, score);
	return reinterpret_cast<int *>(newState);
}


int *getMoveWithScore(int move, int newState[][4], int curState[][4], int &score) {
	if (move == 0) 
		MoveLeft(newState, curState, score);
	else if (move == 1)
		MoveRight(newState, curState, score);
	else if (move == 2)
		MoveUp(newState, curState, score);
	else 
		MoveDown(newState, curState, score);
	return reinterpret_cast<int *>(newState);
}