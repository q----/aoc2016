#include <iostream>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

string md5sum(string in){
  unsigned char result[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)in.c_str(), in.size(), result);
  ostringstream oss;
  for(int i = 0; i < MD5_DIGEST_LENGTH; ++i){
    oss << hex << setw(2) << setfill('0') << +result[i];
  }
  return oss.str();
}

int main(){
  string input = "reyedfim";
  int num = 0;
  string m;

  string o;
  map<char,char> a;

  while(a.size() < 8){
    do{
      m = md5sum(input + to_string(num++));
    }while(m.substr(0,5) != "00000");
    if(o.size() < 8) o += m[5];
    if(m[5] < '8' && !a.count(m[5])) a[m[5]] = m[6]; 
  }

  cout << o << endl;

  for(char b = '0'; b < '8'; b++) cout << a[b];
  cout << endl;

  return 0;
}
