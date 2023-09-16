// #include<bits/stdc++.h>
// #include "2048.h"
// #include "Move.h"

// using namespace std;


void greedy(int state[][4]) {
	printState(state);
	int state_left[4][4], state_right[4][4], state_up[4][4], state_down[4][4];
	int score = 0;

	MoveLeft(state_left, state, score);
	MoveRight(state_right, state, score);
	MoveUp(state_up, state, score);
	MoveDown(state_down, state, score);

	double score_left = eval_grid(state_left);
	double score_right = eval_grid(state_right);
	double score_up = eval_grid(state_up);
	double score_down = eval_grid(state_down);

	double max_score = 0.0;
	bool finalState = true;

	if (!checkTwoStatesEqual(state, state_left)) {
		finalState = false;
		max_score = max(max_score, score_left);
	}

	if (!checkTwoStatesEqual(state, state_right)) {
		finalState = false;
		max_score = max(max_score, score_right);
	}

	if (!checkTwoStatesEqual(state, state_up)) {
		finalState = false;
		max_score = max(max_score, score_up);
	}

	if (!checkTwoStatesEqual(state, state_down)) {
		finalState = false;
		max_score = max(max_score, score_down);
	}

	if (finalState) return;

	if (max_score == score_left) {
		random_gen(state_left);
		cout << "L\n";
		greedy(state_left);
	} else if (max_score == score_right) {
		random_gen(state_right);
		cout << "R\n";
		greedy(state_right);
	} else if (max_score == score_up) {
		random_gen(state_up);
		cout << "U\n";
		greedy(state_up);
	} else if (max_score == score_down) {
		random_gen(state_down);
		cout << "D\n";
		greedy(state_down);
	}

	return;
}