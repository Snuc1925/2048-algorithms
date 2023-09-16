#include<bits/stdc++.h>
#include <time.h>
#include "2048.h"
#include "Move.h"
#include "Greedy.h"
#include "Expectimax.h"
#include "Minimax.h"

using namespace std;

int main() {
	// freopen("inp.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);

	srand(time(0));

	calPow2();
	PreCalHeuristicScore();
	PreCalMove();

	int grid[4][4];	

	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4; j++) 
			grid[i][j] = 0;

	// first, generate 2 cells in grid

	random_gen(grid);
	random_gen(grid);	


	// 3 algos:

	// greedy(grid); 
	// Minimax(grid);
	Expectimax(grid);
}
