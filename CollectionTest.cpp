/*
jelly coding. 2021.12.16
This program test vector, map, nested map
*/
#include <iostream>
#include <string> 
#include <map>
#include <vector>

using namespace std;
int main() {

  //vector test ------------------------------------------------
  vector<string> inventory;
  inventory.push_back("key");
  cout << "inventory = " << inventory[0] <<endl;
  //------------------------------------------------------------

  //flat map test(simple map) --------------------------------------------
  map<string, string> myMap;
  myMap["ATL"] = "Hartsfield–Jackson Atlanta International Airport";
  myMap["HKG"] = "Hong Kong International Airport ";

  string airportCode="ATL";
  if(myMap.count(airportCode) >0){ // 키가 있는지 검사 후 실행 
    cout << airportCode << " = "  << myMap["ATL"] <<endl;
  }
  //------------------------------------------------------------

  //Nested map test --------------------------------------------
  map<string, map<string, string>> gameMap;
  map<string, string> hall;
  hall["west"] = "workspace";
  hall["item"] = "driver";

  gameMap["hall"]=hall;
  cout << "[hall][item] = " << gameMap["hall"]["item"] <<endl;
  //------------------------------------------------------------

} 
//참고 자료 ---------------------------------------

//nested map 만들기 
//https://newbedev.com/c-c-nested-map-code-example

//맵에 객체(클래스, 구조체) 를 value로 넣기
//https://knowingispower.tistory.com/5
