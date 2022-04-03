/* Blind Escape RPG in C++ 
 English Version
 
 * Created on: 2021. 12. 16.  / 2022. 1. 6 / 
 *     Author: CSY
       Support: BDS

item 2개 이상
SPLIT cin .. item -> inventory

수정할것 : get item 부분 inventory[0]을
          인벤토리에 저장된 아이템의 양만큼 가변시키기 /1.13


 */

#include <iostream>
#include <string> 
#include <map>
#include <vector>
#include <sstream>

using namespace std;

//define function prototype(함수의 형태를 선언)
vector<string> split(string Text, char Delimiter);
void showVector(vector<string> &vect);

template <class myCollection, class myItem>  
int findIndex(const myCollection &arr, myItem item);
void help(void);
void door(void);


/*
//class define student 
class student{
public:
string name;
double result;
};


int main(){

vector<student> record;

student data;

data.name = "";
data.result = 3.2;
record.push_back(data);

data.name = "";
data.result = 2.9;
record.push_back(data);



for(int i; i<r)

//record[i].result;
*/


vector<string> item{"key","uselesskey","poison","potion",
                    "dust","juice","prawn","rottenbanana"};

vector<string> inventory;
//inventory.push_back("key");
 // cout << "inventory = " << inventory[0] <<endl;


//room pos(use L/R) and items 
map<string, map<string, string>> gameMap;
map<string, string> hall;
hall["left"] = "kitchen";
hall["right"] = "bedroom";
hall["item"] = "juice dust";
// how

map<string, string> kitchen;
kitchen["left"] = "toilet";
kitchen["right"] = "hall";
kitchen["item"] = "prawn rottenbanana";

map<string, string> toilet;
toilet["left"] = "bedroom";
toilet["right"] = "kitchen";
toilet["item"] = "key poison";

map<string, string> bedroom;
bedroom["left"] = "hall";
bedroom["right"] = "toilet";
bedroom["item"] = "uselesskey potion";

gameMap["hall"]=hall;
gameMap["kitchen"]=kitchen;
gameMap["toilet"]=toilet;
gameMap["bedroom"]=bedroom;

string currentRoom = "hall";
string nextRoom = currentRoom;
/*
 gameMap["hall"]=hall;
  cout << "[hall][item] = " << gameMap["hall"]["item"] <<endl;
  cout << "\n";
  cout << "\n";
*/
    cout << "+-------------------------------------------------+" <<endl;
    cout << "|                                                 |" <<endl;                   
    cout << "|  CAN YOU GET OUT? FIND CORRECT ITEM AND ESCAPE  |"  <<endl;                   
    cout << "|                                                 |"  <<endl;               
    cout << "+-------------------------------------------------+" <<endl;
    
   help();
   cout << "if need help : input <help me> " <<endl;
    
  while (true){

    // cout << "CAN YOU GET OUT? FIND CORRECT ITEM AND ESCAPE"  <<endl;
      


      //cout << "---------string split test----------"<<endl;
      //vector<string> splitWord;
      //splitWord =  split("get bottle abcd", ' ');
      //cout << "splitWord[0] = " << splitWord[0] <<endl;
      //cout << "splitWord[1] = " << splitWord[1] <<endl;
      //cout << "splitWord[2] = " << splitWord[2] <<endl;

      cout << "--------------------------------------" <<endl;

      cout<< "You are in " << currentRoom << " ..." <<endl;

      vector<string> items;
      string itemString = gameMap[currentRoom]["item"];
      items = split(itemString, ' ');
      cout<< "here's item : ";
      showVector(items);
      cout<< " "<<endl;

      cout<< "inventory = [";
      showVector(inventory);
      cout<< "]"<<endl;

      
      cout << "--------------------------------------" <<endl;

      string yourInput;
      getline(cin, yourInput);

      vector<string> cmdPram;
      cmdPram =  split(yourInput, ' ');

      string cmd = cmdPram[0];
      string param = cmdPram[1];

      if(cmd == "go"){
          string direction = param;
          if(direction == "left" ||direction == "right"){
            nextRoom = gameMap[currentRoom][direction];
          }
      }else if (cmd == "help"){
        help();
      }else if (cmd == "door"){
        door();
        break;
      
      }else if (cmd == "get"){
          //if param in gameMap[currentRoom]['item']:
          items = split(gameMap[currentRoom]["item"], ' ');
          int index = findIndex( items, param);
          if (index >= 0){
            inventory.push_back(param); //add to inventory


            //인벤토리 ++ 수정
            
            //GET ITEM 
            if(inventory[0] == "dust"){
              cout<< "this room is so dusty" <<endl;
            }else if(inventory[0] == "juice"){
              cout<< "this juice was poison...\n you got poisoned. \n GAME OVER" <<endl;
              break;
            }else if(inventory[0] == "prawn"){
              cout<< "you have shellfish allergy.. \n GAME OVER "<<endl;
              break;
            }else if(inventory[0] == "rottenbanana"){
              cout<< "this banana is rotten.. you got food poisoning... \n GAME OVER" <<endl;
              break;
            }else if(inventory[0] == "key"){
              cout<< "say door open" <<endl;
            }else if(inventory[0] == "poison"){
              cout<< "why? i said poison.. \n GAME OVER" <<endl;
              break;
            }else if(inventory[0] == "uselesskey"){
              cout<< "useless key is useless" <<endl;
            }else if(inventory[0] == "potion"){
              cout<< "you will healthy" <<endl;
            }

          
             
            

            
            vector <string> tempItem;
            // 게임맵[현재방]에 있는 아이템 문자열을 분리해서 템프라는 벡터에 넣기 
            tempItem = split(gameMap[currentRoom]["item"], ' ');
            // 템프벡터에서 플레이어가 잡은 아이템을 삭제하기 
            tempItem.erase(tempItem.begin()+ index);

            //*** 아래에 더 구현 필요 (템프벡터에 있는 모든 아이템을 
            //문자열로 변환하고 다시 게임맵[현재방]에 있는 아이템에 넣기 ***
            
            string witem;
            for( int i =0; i< tempItem.size(); i++){
              if( i>0 && i<(tempItem.size()-1) ){
                witem += tempItem[i]+' ';
              }else{
                witem += tempItem[i];
              }
            }
            gameMap[currentRoom]["item"] = witem;

          }else{
            cout<<"TRY AGAIN" <<endl;
          }
      }else{
        cout << "잘못입력하셨습니다."<<endl;
      }

      currentRoom = nextRoom;

  }//end while

}// end main()

//출처: https://www.delftstack.com/ko/howto/cpp/find-in-vector-in-cpp/
template <class myCollection, class myItem>  
int findIndex(const myCollection &arr, myItem item) {

    for (auto i = 0; i < arr.size(); ++i) {
        if (arr[i] == item)
            return i;
    }

    return -1;
}


void showVector(vector<string> &vect){
    for(int i=0; i<vect.size(); i++){
      if(i != vect.size()-1){ 
        cout<< vect[i]<< ", ";
      }else{
        cout<< vect[i];
      }
    }
}

vector<string> split(string Text, char Delimiter){
  istringstream iss(Text);             // istringstream에 str을 담는다.
  string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼

  vector<string> result;

  // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
  while (getline(iss, buffer, Delimiter)) {
      result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
  }
  return result;

}

void help(void){
   cout << "   Move : [go (left/right)]\n   Item : [get (item name)]"<<endl;
}


void door(void){
   cout << "congratulations you escaped!\n"<<endl;
  cout <<  " /]_____/] " <<endl;
  cout << "/  o   o  ] " <<endl;
  cout <<"( ==  ^  == ) " <<endl;
  cout << " )         ( " <<endl;
  cout <<"(           ) " <<endl;
  cout <<"( (  )   (  ) ) "<<endl;
 cout <<"(__(__)___(__)__) "<<endl;
 
}
/*
    +----------------------=---+
     You Are In..[Room]      
     You Have..  [inventory]                           
    +--------------------------+*/
