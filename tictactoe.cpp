
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

int getch(void);

using namespace std;

class position {
public : 
	int x;
	int y;
	
};

class TicTacToe {
	private :
		position selPos; 
		char currentPlayer; 
		string gameBoard[3][3];
		string inputMasg = " 위치를 선택하세요";
		string winMsg = "이겼습니다";
		string loseMsg = "졌습니다";

	public : 
		TicTacToe(char firstPlayer); 
		char drawBoard(void);
		void getUserInput(void);
		void checkGameOver(void);
		int gameOver = 'F';
		//char choose = 'X','O';
		

};
void TicTacToe :: checkGameOver(void){
	gameOver = 'T';
	
}

void TicTacToe :: getUserInput(void){
	int input;
	this->selPos.x =0;
	this->selPos.y =0; 
	cout <<"select your position "<< endl; 
	
	while(1){
		input = getch();
		if(input == 10){
			break;
		}

		switch(input){
			case 65: printf("U");
			this->selPos.y-=1;
				break;
			case 66: printf ("D");
			this->selPos.y+=1;
				break;
			case 68: printf("L");
			this->selPos.x-=1;
				break;
			case 67: printf("R");
			this->selPos.x+=1;
				break;
		}
		gotoxy(this->selPos.x,this->selPos.y);

	}
}

TicTacToe :: TicTacToe(char firstPlayer){
	this->selPos.x =0;
	this->selPos.y =0;
	currentPlayer =firstPlayer;
	cout << "game start" << endl; 
}

int getch(void);

int main(void) {
	char input;
	int x = 0;
	int y = 5;
	TicTacToe TTTgame('A');

	while(TTTgame.gameOver == 'F'){
		TTTgame.getUserInput();
	}
	return 0;
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
