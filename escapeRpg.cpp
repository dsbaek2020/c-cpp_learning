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


vector<string> split(string Text, char Delimiter);

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

 // cout << "CAN YOU GET OUT? FIND CORRECT ITEM AND ESCAPE"  <<endl;
    cout << "   Move : [go (left/right)]\n   Item : [get (item name)]"<<endl;


  //cout << "---------string split test----------"<<endl;
  //vector<string> splitWord;
  //splitWord =  split("get bottle abcd", ' ');
  //cout << "splitWord[0] = " << splitWord[0] <<endl;
  //cout << "splitWord[1] = " << splitWord[1] <<endl;
  //cout << "splitWord[2] = " << splitWord[2] <<endl;

  cout<< "현재위치는 " << currentRoom << " 이며," <<endl;

  vector<string> items;
  string itemString = gameMap[currentRoom]["item"];
  items = split(itemString, ' ');
  cout<< "여기에 있는 아이템은 ";
  for(int i=0; i<items.size(); i++){
    if(i != items.size()-1){
      cout<< items[i]<< ", ";
    }else{
      cout<< items[i];
    }
  }
  cout<< "입니다."<<endl;

  cout<< "inventory = [";
  for(int i=0; i<inventory.size(); i++){
    if(i != inventory.size()-1){ 
      cout<< inventory[i]<< ", ";
    }else{
      cout<< inventory[i];
    }
  }
  cout<< "]"<<endl;

  
  cout << "--------------------------------------" <<endl;

  string yourInput;
  getline(cin, yourInput);

  vector<string> cmdPram;
  cmdPram =  split(yourInput, ' ');

  string cmd = cmdPram[0];

  if(cmd == "go"){
      string direction = cmdPram[1];
      if(direction == "left" ||direction == "right"){
        nextRoom = gameMap[currentRoom][direction];
      }
  }else if (cmdPram[0] == "get"){

  }else{
    cout << "잘못입력하셨습니다.";
  }


}

//문자열 분리해서 백터로 만들어 주는 함수 
//-출처: https://www.lifencoding.com/language/22?p=1
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
