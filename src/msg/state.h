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
	double player1X;
	double player1Y;
	double player1Z;

	// player2 state
	double player2X;
	double player2Y;
	double player2Z;    
};
