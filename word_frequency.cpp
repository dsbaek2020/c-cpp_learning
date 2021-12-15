#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std; 


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


int main() {
    map<string, int> wordCount;
    string Text;
    string word;

    ifstream file("Text.txt");
    cout << "-------Start-------"<<endl;

    while (getline(file, Text)){
      cout << Text << '\n';
      //cout << "........"<<endl;

      vector<string> result = split(Text, ' ');

      for (int i = 0; i < result.size(); i++) {
          word=result[i];
          if(word.find(",") != string::npos ){
            int pos = word.find(",");
            word.erase(pos,1);
          }
          if(word.find(".") != string::npos ){
            int pos = word.find(".");
            word.erase(pos,1);
          }
          //str.erase(remove(str.begin(), str.end(), ','), str.end());


          if (wordCount.count(word) >0 ){
            wordCount[word]+=1;
          }else{
            wordCount[word]=1;
          }
      }

    } 
 
//C++에서 맵을 반복하는 방법
//https://www.delftstack.com/ko/howto/cpp/how-to-iterate-over-map-in-cpp/
//https://www.delftstack.com/ko/howto/cpp/

//C++ Map을 value 기준으로 정렬하기
//https://unluckyjung.github.io/cpp/2020/05/07/Sort_map_by_value/

//특정 문자만 제거하는 방법
//https://popawaw.tistory.com/52
//http://daplus.net/c-c-의-문자열에서-특정-문자를-제거하는-방법은-무엇/

//특정문자의 위치 찾기
//https://sweetnew.tistory.com/85
//

//output formating.    #include <iomanip>
//http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node83.html


    cout  << "\n\ntotal word"  << " = " << wordCount.size() << "\n";
    cout  << " word" << setw(16) << " : " << setw(3) << "num" << "\n";
   

    for (const auto& [key, value] : wordCount){
      cout << "[" << key << setw(20-key.size()) << " : " << setw(3) << value << "]\n";
    }
    cout << "-------end--------" << endl;
}

  
