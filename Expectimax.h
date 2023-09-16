// #include<bits/stdc++.h>
// #include "Move.h"
// #include "2048.h"

double score_tilechoose_node(int state[][4], int depth, double prob);
double score_move_node(int state[][4], int depth, double prob);

double score_tilechoose_node(int state[][4], int depth, double prob) {
	if (prob < CPROB_THRESH_BASE || depth >= MAX_DEPTH) 
		return eval_grid(state);

	int cnt_empty = count_empty(state);

	if (!cnt_empty) 				
		return eval_grid(state);

	prob /= cnt_empty;

	double res = 0.0;
	
	int newState[4][4];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			newState[i][j] = state[i][j];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (state[i][j]) continue;

			newState[i][j] = 1;
			res += score_move_node(newState, depth, prob * 0.9) * 0.9;

			newState[i][j] = 2;
			res += score_move_node(newState, depth, prob * 0.1) * 0.1; 

			newState[i][j] = 0;
		}

	res /= cnt_empty;

	return res;
}

double score_move_node(int state[][4], int depth, double prob) {
	double best = 0.0;
		
	int newState[4][4];

	for (int move = 0; move < 4; move++) {
		getMove(move, newState, state);
		if (checkTwoStatesEqual(newState, state)) continue;
		double cur = score_tilechoose_node(newState, depth + 1, prob);
		best = max(best, cur);
	}	

	return best;
}

void Expectimax(int state[][4]) {
	printState(state);
	int totalScore = 0;
	while (true) {
		int dir = -1;
		double res = 0.0;
		int newState[4][4];
		for (int move = 0; move < 4; move++) {
			getMove(move, newState, state);

			if (checkTwoStatesEqual(newState, state)) continue;

			double cur = score_tilechoose_node(newState, 0, 1.0);

			if (cur > res) {
				res = cur;
				dir = move;
			}
		}

		if (dir == -1) break;

		getMoveWithScore(dir, newState, state, totalScore);

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				state[i][j] = newState[i][j];

		printDirection(dir);
		random_gen(state);
		printState(state);
	}	

	cout << "Total Score: " << totalScore;
} 
