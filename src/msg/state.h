#include <string>

struct State{	
	// game state
	bool isHitting;
	int playerId;
	int player1Score;
	int player2Score;

	//ball state;
	float ballX;
	float ballY;
	float ballZ;

	// player1 state
	int player1X;
	int player1Y;
	int player1Z;

	// player2 state
	int player2X;
	int player2Y;
	int player2Z;    
};

/*
struct State{	
	// game state
	int gameState;
	int playerId;
	int player1Score;
	int player2Score;

	//ball state;
	float ballX;
	float ballY;
	float ballZ;

	float ballVx;
	float ballVy;
	float ballVz;

	// player1 state
	float player1X;
	float player1Y;
	float player1Z;

	// player2 state
	float player2X;
	float player2Y;
	float player2Z;    
};
*/