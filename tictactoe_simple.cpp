/*
 *  tictactoe_simple.cpp
 * Created on: 2021. 10. 27.
 *     Author: CSY, KLY

 *  ---업데이트 내용---
 *  새로운 checkwinner 알고리즘 실험
 *  winner를 마지막에 디스플레이
 *   */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h> /*for sleep(), usleep()  */

#include<iostream>
#include<string>

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define clear() printf("\033[H\033[j]")
#define yellow() printf("\033[0;33m]")

using namespace std;

int getch(void);


enum player{
	PLAYER_A =0,
	PLAYER_B =1
};

class ReplayInfo{
  public:
    player PlayerName;
    unsigned char  wherePosition;
};

class Position{
public:
	int y;
	int x;
};


class tictactoe{
private:
	unsigned char GameCount;
	int x; //player1 first
	int o; //player2
	Position cursorPos;
	unsigned char wherePosition;
	Position LUT_1dto2d[9] = {  {0,0}, {0,1}, {0,2},
									{1,0}, {1,1}, {1,2},
									{2,0}, {2,1}, {2,2} };

	player nextPlayer = PLAYER_A;
	player currentPlayer;
	player winnerPlayer;
	bool gameover = false;

	char gameboard[3][3] = {{ '1', '2', '3' },
	{ '4', '5', '6' },
	{ '7', '8', '9' } };

	void getCursor (void);
	void SetGameover(bool result);
	bool checkLine(char cell1, char cell2, char cell3);


public:
	tictactoe(void); //constructor
	void drawBoard(void);
	bool inputPos(void);
	int checkGameover(void);
	bool GetGameover(void);
	player getWinner(void);
  unsigned char getGameCount(void);
	void writeReplayData(void);
  void readReplayData(int recordIndex);
  void resetgameboard(void);

	ReplayInfo PlayData[9];
};

void tictactoe::resetgameboard(void){

  for(int j=0; j<3; j++){
    for(int i=0; i<3; i++){
    gameboard[j][i] = '_';
    }
  }
}

void tictactoe::readReplayData(int recordIndex){
  ReplayInfo readData;
  readData = PlayData[recordIndex];

  cursorPos.x=LUT_1dto2d[readData.wherePosition-1].x;
	cursorPos.y=LUT_1dto2d[readData.wherePosition-1].y;

  if(readData.PlayerName==PLAYER_A){
    gameboard[cursorPos.y][cursorPos.x]='o';

  }else{
    gameboard[cursorPos.y][cursorPos.x]='x';
  }
}

unsigned char tictactoe::getGameCount(void){
  return GameCount;
}

//
void tictactoe::writeReplayData(void){
	PlayData[GameCount].PlayerName = currentPlayer;
	PlayData[GameCount].wherePosition = wherePosition;

  gotoxy(1,13);
  cout<< "currentPlayer = " << currentPlayer << endl;
  
  cout<< "wherePosition = ";
  //char 변수는 1-byte 정수(integer)다. 그러나 char 자료형이 정수 일지라도 일반 정수와는 다른 방식으로 사용한다. 그래서 char 값을 //정수로 해석하는 대신 ASCII code 문자로 해석한다.
  //출처: https://boycoding.tistory.com/154 [소년코딩]
  cout << static_cast<int> (wherePosition) << endl;

  GameCount++;
}

player tictactoe::getWinner(void){
  return winnerPlayer;
}

bool  tictactoe::checkLine(char cell1, char cell2, char cell3){
  if(cell1== cell2 && cell2 == cell3){
    return true;
  }else {
    return false;
  }
}

int tictactoe::checkGameover(void){
    char firstValue;
    for(int j=0; j<3; j++){
      for(int i=0; i<3; i++){
        if (gameboard[i][j] == 'o' || gameboard[i][j] == 'x'){
          if (i==0){
            firstValue = gameboard[i][j];
          }else{
            if(firstValue != gameboard[i][j]){
              break;
            }
            else if ((firstValue == gameboard[i][j]) && (i==2)){
              SetGameover(true);
              winnerPlayer = currentPlayer;
            }
          }
        }else{
          break;
        }
      }
    }

    for(int i=0; i<3; i++){
      if(checkLine(gameboard[i][0],gameboard[i][1],gameboard[i][2])){
        SetGameover(true);
        break;
      }
    }
    /*
    for(int j=0; j<3; j++){
      if(checkLine(gameboard[0][j],gameboard[1][j],gameboard[2][j])){
        SetGameover(true);
        winnerPlayer = currentPlayer;
        break;
      }
    }*/
    if(checkLine(gameboard[0][0],gameboard[1][1] ,gameboard[2][2])){
      SetGameover(true);
      winnerPlayer = currentPlayer;
      return 0;
    }

    if(checkLine(gameboard[0][2],gameboard[1][1] ,gameboard[2][0])){
      SetGameover(true);
      winnerPlayer = currentPlayer;
      return 0;
    }

    return 0;
}

bool tictactoe::GetGameover(void){
  return gameover;
}

void tictactoe::SetGameover(bool result){gameover = result;}

void tictactoe::drawBoard(void){
  clear();
  gotoxy(1,5);
	for(int i =0; i<3; i++){
		cout << gameboard[i][0] <<'|'<<gameboard[i][1] << '|' << gameboard[i][2]<< endl;
	}
}

void tictactoe::getCursor(void){
	int input;
	Position viewCursorPos;
	viewCursorPos.x =1;
	viewCursorPos.y =5;
	//cout <<"select your position "<< endl;

	while(1){
		gotoxy(viewCursorPos.x,viewCursorPos.y);
		input = getch();
		if(input == 10){
			break;
		}

		switch(input){
			case 65: //printf("U");
			viewCursorPos.y-=1;
			break;

			case 66: //printf ("D");
			viewCursorPos.y+=1;
			break;

			case 68: //printf("L");
			if(viewCursorPos.x >= 3){
				viewCursorPos.x-=2;
			}
			break;

			case 67: //printf("R");
			if(viewCursorPos.x <= 3){
				viewCursorPos.x+=2;
			}
			break;
			}
	}
	if(viewCursorPos.x > 2){
		cursorPos.x = (int)viewCursorPos.x * 0.5;
	}else{
		cursorPos.x = (int)viewCursorPos.x-1;
	}
	this->cursorPos.y = viewCursorPos.y-5;
}

bool tictactoe::inputPos(void){
	unsigned char  pos;
	//cout << "커서를 움직이세요 : ";
	//cin >> pos;
	//cursorPos.x=LUT_1dto2d[pos-1].x;
	//cursorPos.y=LUT_1dto2d[pos-1].y;
	getCursor();

  //todo pos계산이 스크린의 커서를 이용한 부분에 있어서 잘못 계산되고 있음 확인해야함
//pos = (cursorPos.y+1)*3 + (cursorPos.x+1);
  pos = (cursorPos.y  )*3   + (cursorPos.x+1);
	wherePosition = pos;

	if((gameboard[cursorPos.y][cursorPos.x]!='o')&&
	 (gameboard[cursorPos.y][cursorPos.x]!='x')){
		currentPlayer = nextPlayer;

		if(currentPlayer == PLAYER_A){
		  gameboard[cursorPos.y][cursorPos.x]='o';
		  nextPlayer = PLAYER_B;
		}else { //playerB
		  gameboard[cursorPos.y][cursorPos.x]='x';
		  nextPlayer = PLAYER_A;
		}
		return true;
	}else{
		return false;
	}

}

tictactoe::tictactoe(void){
	cursorPos.x = 1;
	cursorPos.y = 1;
	GameCount =0;
}

int main(void){
	char gb;
	int i;
  string answer;
	string playerID[2] ={"o", "x"};
	ReplayInfo replayInfo;

	//clear();
	//gotoxy(1,1);
	tictactoe game;
  

	while(game.GetGameover()==false){
		game.drawBoard();
		if( game.inputPos() == true ){
			game.writeReplayData();
		}
		game.checkGameover();
	}
	game.drawBoard();

	// y = 'A' or 'B' , x=winnerPlayer {PLAYER_A or PLAYER_B}
	cout<< playerID[game.getWinner()] << " is winner" <<endl;

  cout<<"show review?(yes or no)"<<endl;
  cin>>answer;
  
  unsigned char j=0;
  if(answer=="yes"){
    clear();
    game.resetgameboard();

    while(true){
      
      game.readReplayData(j);
      game.drawBoard();

      sleep(1);


      j++;
      if(j==game.getGameCount()){
        break;
      } 
    }


  }else{
    cout<<"게임이 끝났습니다"<<endl;
  }
}

int getch(void) {
    struct termios oldt,
    newt;
    int            ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

