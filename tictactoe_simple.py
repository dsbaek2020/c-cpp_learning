/*
 *  tictactoe_simple.cpp
 * Created on: 2021. 10. 27.
 *     Author: CSY, KLY
 */

#include <iostream>
#include <string>

using namespace std;

enum player{
	PLAYER_A =0,
	PLAYER_B =1
};

class Position{
public:
	int y;
	int x;
};


class tictactoe{
private:
	int x; //player1 first
	int o; //player2
	Position cursorPos;
	Position LUT_1dto2d[9] = { {0,0}, {0,1}, {0,2},
					                	{1,0}, {1,1}, {1,2},
				                		{2,0}, {2,1}, {2,2} };
	player currentPlayer = PLAYER_A;
	bool gameover = false;

	char gameboard[3][3] = {{ '1', '2', '3' },
							{ '4', '5', '6' },
							{ '7', '8', '9' } };
	//char field[3][3];
	// field[9] = {1,2,3,4,5,6,7,8,9}
void SetGameover(bool result);
bool checkLine(char cell1, char cell2, char cell3);

public:
	tictactoe(void); //constructor
	void drawBoard(void);
	void inputPos(void);
	int checkGameover(void);
  bool GetGameover(void);
};

bool  tictactoe::checkLine(char cell1, char cell2, char cell3){
  if(cell1== cell2 && cell2 == cell3){
    return true; 
  }else {
    return false; 
  }
}

int tictactoe::checkGameover(void){
    for(int i=0; i<3; i++){
      if(checkLine(gameboard[i][0],gameboard[i][1],gameboard[i][2])){
        SetGameover(true);
        break;
      }
    }
    for(int j=0; j<3; j++){
      if(checkLine(gameboard[0][j],gameboard[1][j],gameboard[2][j])){
        SetGameover(true);
        break;
      }
    }
    if(checkLine(gameboard[0][0],gameboard[1][1] ,gameboard[2][2])){
      SetGameover(true);
      return 0;
    }

    if(checkLine(gameboard[0][2],gameboard[1][1] ,gameboard[2][0])){
      SetGameover(true);
      return 0;
    }

    return 0;
}
bool tictactoe::GetGameover(void){return gameover;}
void tictactoe::SetGameover(bool result){gameover = result;}
void tictactoe::drawBoard(void){

	for(int i =0; i<3; i++){
		cout << gameboard[i][0] <<'|'<<gameboard[i][1] << '|' << gameboard[i][2]<< endl;
	}
}
void tictactoe::inputPos(void){
	int pos;
	cout << "위치를 입력하세요(1~9) : ";
	cin >> pos;
	cursorPos.x=LUT_1dto2d[pos-1].x;
	cursorPos.y=LUT_1dto2d[pos-1].y;

  if((gameboard[cursorPos.y][cursorPos.x]!='o')&&
     (gameboard[cursorPos.y][cursorPos.x]!='x')){
    if(currentPlayer == PLAYER_A){
      gameboard[cursorPos.y][cursorPos.x]='o';
      currentPlayer = PLAYER_B;
    }else {
      gameboard[cursorPos.y][cursorPos.x]='x';
      currentPlayer = PLAYER_A;
    }
  }
}


tictactoe::tictactoe(void){
	cursorPos.x = 0;
	cursorPos.y = 0;
}


// T E M P
int main(void){
	char gb;
	int i;
	tictactoe game;
	while(game.GetGameover()==false){
		game.drawBoard();
		game.inputPos();
    game.checkGameover();
	}

/*
for(i=0; i<3; i++){
	if(gb[i][0] == 'x' or 'o'){
		if(gb[i][0] == gb[i][1] == gb[i][2]){
			break;
		   }
	   }
    }
    */
}
