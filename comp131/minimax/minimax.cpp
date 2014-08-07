int minimax(Board &theBoard, int depth) {
	/*
	 * in player.cpp in nextMove, 
	 * bestMove = legalMoves[minimax(theBoard, myDepth)] 
	 * 
	 * would not be calling this function if the game was over
	 */

	int bestScore = -100000000; //using in place of -infinity
	int chooseMove = 0;
	int numMoves = legalMoves.size();
	
	//choose first available move if search depth is 0
	if(depth == 0) {
		return chooseMove;
	}

	for(int i = 0; i < num_moves; i++) {
		//legalMoves is used by minValue / maxValue, recalculate
		legalMoves.clear();
		findmoves(theBoard, myPiece);
		Board clone = theBoard;
		clone.makeMove(legalMoves[i]);
		int newScore = minValue(&clone, depth, myPiece);
		if(newScore > bestScore) {
			bestScore = newScore;
			chooseMove = i;
		}
	}
	return chooseMove;
}

int minValue(Board &theBoard, int depth, char piece) {
	
	char thisPiece;
	if(piece == 'x') {
		thisPiece = 'o'; 
	} else {
		thisPiece = 'x';
	}
	

	legalMoves.clear();
	findMoves(theBoard, thisPiece);
	
	int bestScore = 100000000; //using in place of +infinity
	int chooseMove = 0;
	int numMoves = legalMoves.size();
	
	//terminal test
	if(numMoves == 0) {
		return 1000;
	}
	//depth test
	if(depth == 0) {
		return numMoves;
	}
	
	for(int i = 0; i < numMoves; i++) {
		legalMoves.clear();
		findMoves(theBoard, thisPiece);
		Board clone = theBoard;
		clone.makeMove(legalMoves[i]);
		newScore = maxValue(&clone, depth-1, piece);
		if(newScore < bestScore) {
			bestScore = newScore;
			chooseMove = i;
		}
	}
	return bestScore; 
}


int maxValue(Board &theBoard, int depth, char piece) {
	
	legalMoves.clear();
	findMoves(theBoard, piece);
	
	int bestScore = -100000000; //using in place of -infinity
	int chooseMove = 0;
	int numMoves = legalMoves.size();
	
	//terminal test
	if(numMoves == 0) {
		return -1000;
	}
	//depth test
	if(depth == 0) {
		return numMoves;
	}
	
	for(int i = 0; i < numMoves; i++) {
		legalMoves.clear();
		findMoves(theBoard, piece);
		Board clone = theBoard;
		clone.makeMove(legalMoves[i]);
		newScore = minValue(&clone, depth-1, piece);
		if(newScore > bestScore) {
			bestScore = newScore;
			chooseMove = i;
		}
	}
	return bestScore;
}

