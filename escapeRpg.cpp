/* Blind Escape RPG in C++
 * Created on: 2021. 12. 16. 
 *     Author: CSY
       Support: BDS

item 2개 이상
SPLIT cin .. item -> inventory

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

int main(){

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
string nextRoom;
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
    
    cout << "   Move : [go (left/right)]\n   Item : [get (item name)]"<<endl;
  while (true){

    // cout << "CAN YOU GET OUT? FIND CORRECT ITEM AND ESCAPE"  <<endl;
      //cout << "   Move : [go (left/right)]\n   Item : [get (item name)]"<<endl;


      //cout << "---------string split test----------"<<endl;
      //vector<string> splitWord;
      //splitWord =  split("get bottle abcd", ' ');
      //cout << "splitWord[0] = " << splitWord[0] <<endl;
      //cout << "splitWord[1] = " << splitWord[1] <<endl;
      //cout << "splitWord[2] = " << splitWord[2] <<endl;

      cout << "--------------------------------------" <<endl;

      cout<< "현재위치는 " << currentRoom << " 이며," <<endl;

      vector<string> items;
      string itemString = gameMap[currentRoom]["item"];
      items = split(itemString, ' ');
      cout<< "여기에 있는 아이템은 ";
      showVector(items);
      cout<< "입니다."<<endl;

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
      }else if (cmd == "get"){
          //if param in gameMap[currentRoom]['item']:
          items = split(gameMap[currentRoom]["item"], ' ');
          int index = findIndex( items, param);
          if (index >= 0){
            inventory.push_back(param); //add to inventory

            
            vector <string> tempItem;
            // 게임맵[현재방]에 있는 아이템 문자열을 분리해서 템프라는 벡터에 넣기 
            tempItem = split(gameMap[currentRoom]["item"], ' ');
            // 템프벡터에서 플레이어가 잡은 아이템을 삭제하기 
            tempItem.erase(tempItem.begin()+ index);

            //*** 아래에 더 구현 필요 (템프벡터에 있는 모든 아이템을 
            //문자열로 변환하고 다시 게임맵[현재방]에 있는 아이템에 넣기 ***
            /* 여기에 더 구현하시오~~~~~~~~ 해보세요 ㅜㅜ ----
            
            */
            
          


          }else{
            cout<<"try again" <<endl;
          }
      }else{
        cout << "잘못입력하셨습니다.";
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

/*
    +----------------------=---+
     You Are In..[Room]      
     You Have..  [inventory]                           
    +--------------------------+*/
