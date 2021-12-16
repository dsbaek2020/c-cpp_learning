/*
jelly coding. 2021.12.16
This program test vector, map, nested map
*/
#include <iostream>
#include <string> 
#include <map>
#include <vector>
#include <sstream>

using namespace std;

//define function prototype ----------------------------------

//문자열 분리해서 백터로 만들어 주는 함수 
//-출처: https://www.lifencoding.com/language/22?p=1
vector<string> split(string Text, char Delimiter);
//------------------------------------------------------------

int main() {

  //vector test ------------------------------------------------
  cout << "----------vector test---------------"<<endl;
  vector<string> inventory;
  inventory.push_back("key");
  cout << "inventory = " << inventory[0] <<endl;
  cout << "\n";
  cout << "\n";
  //------------------------------------------------------------

  //flat map test(simple map) --------------------------------------------
  cout << "----------flat map test-------------"<<endl;
  map<string, string> myMap;
  myMap["ATL"] = "Hartsfield–Jackson Atlanta International Airport";
  myMap["HKG"] = "Hong Kong International Airport ";

  string airportCode="ATL";
  if(myMap.count(airportCode) >0){ // 키가 있는지 검사 후 실행 
    cout << airportCode << " = "  << myMap["ATL"] <<endl;
  }
  cout << "\n";
  cout << "\n";
  //------------------------------------------------------------

  //Nested map test --------------------------------------------
  cout << "---------Nested map test------------"<<endl;
  map<string, map<string, string>> gameMap;
  map<string, string> hall;
  hall["west"] = "workspace";
  hall["item"] = "driver";

  gameMap["hall"]=hall;
  cout << "[hall][item] = " << gameMap["hall"]["item"] <<endl;
  cout << "\n";
  cout << "\n";
  //------------------------------------------------------------


  //--문자열 split 함수 테스트 ----------------------------------
  cout << "---------string split test----------"<<endl;
  vector<string> splitWord;
  splitWord =  split("get bottle abcd", ' ');
  cout << "splitWord[0] = " << splitWord[0] <<endl;
  cout << "splitWord[1] = " << splitWord[1] <<endl;
  cout << "splitWord[2] = " << splitWord[2] <<endl;
  //------------------------------------------------------------


} 

//--------출처: https://www.lifencoding.com/language/22?p=1 ---------------
vector<string> split(string Text, char Delimiter) {
    istringstream iss(Text);             // istringstream에 str을 담는다.
    string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
 
    vector<string> result;
 
    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
    }
 
    return result;
}
//------------------------------------------------------------------------

//참고 자료 ---------------------------------------

//nested map 만들기 
//https://newbedev.com/c-c-nested-map-code-example

//맵에 객체(클래스, 구조체) 를 value로 넣기
//https://knowingispower.tistory.com/5

