// #include<bits/stdc++.h>
// #include "Move.h"
// #include "2048.h"

// using namespace std;

pair<int, double> findMoveMinimax(int state[][4], bool isPlayer, int depth) {
	if (!depth) return {-1, eval_grid(state)};

	if (isPlayer) {
		int dir = 0;
		double res = 0;

		bool finalState = true;

		for (int move = 0; move < 4; move++) {
			int newState[4][4];
			getMove(move, newState, state);
			if (checkTwoStatesEqual(newState, state)) continue;
			finalState = false;
			double cur = findMoveMinimax(newState, false, depth - 1).second;
			if (cur > res) {
				res = cur;
				dir = move;
			}
		}

		if (finalState) return {-1, eval_grid(state)};
		return {dir, res};
	} else {
		double res = inf;

		int newState[4][4];

		bool finalState = true;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				newState[i][j] = state[i][j];
				if (state[i][j]) 
					finalState = false;
			}

		if (finalState) return {-1, eval_grid(state)};


		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (state[i][j]) continue;
				newState[i][j] = 1;
				res = min(res, findMoveMinimax(newState, true, depth - 1).second);
				newState[i][j] = 2;
				res = min(res, findMoveMinimax(newState, true, depth - 1).second);
				newState[i][j] = 0;
			}	
		return {-1, res};	
	}

}

void Minimax(int state[][4]) {
	printState(state);
	while(true) {
		int newState[4][4];
		pair<int,double> p = findMoveMinimax(state, true, MAX_DEPTH);		
		int dir = p.first;
		if (dir == -1) break;
		getMove(dir, newState, state);

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				state[i][j] = newState[i][j];
		if (dir == 0) cout << "L\n";
		else if (dir == 1) cout << "R\n";
		else if (dir == 2) cout << "U\n";
		else cout << "D\n";
		random_gen(state);
		printState(state);
	}	
}