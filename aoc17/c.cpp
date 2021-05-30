#include <iostream>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <queue>

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

string d(string in){
  string s = md5sum(in).substr(0,4);
  for(int i = 0; i < 4; i++) s[i] = (s[i]<'b')?'0':'1';
  return s;
}

bool v(string in){
  int x = 0;
  int y = 0;
  for(int i = 0; i < in.size(); i++){
    if(in[i] == 'U') y--;
    if(in[i] == 'D') y++;
    if(in[i] == 'L') x--;
    if(in[i] == 'R') x++;
  }
  return (x >= 0 && x <= 3) && (y >= 0 && y <= 3);
}

bool f(string in){
  int x = 0;
  int y = 0;
  for(int i = 0; i < in.size(); i++){
    if(in[i] == 'U') y--;
    if(in[i] == 'D') y++;
    if(in[i] == 'L') x--;
    if(in[i] == 'R') x++;
  }
  return x == 3 && y == 3;
}

int main(){
  string i = "pxxbnzuo";
  queue<string> p;
  p.push("");

  bool q = false;
  int o;

  while(p.size() > 0){
    string s = p.front();
    p.pop();
    if(f(s)){
      if(!q){
        q = true;
        cout << s << endl;
      }
      o = s.size();
      continue;
    }
    string a = d(i+s);
    if(a[0] == '1' && v(s + 'U')) p.push(s+'U');
    if(a[1] == '1' && v(s + 'D')) p.push(s+'D');
    if(a[2] == '1' && v(s + 'L')) p.push(s+'L');
    if(a[3] == '1' && v(s + 'R')) p.push(s+'R');
  }

  cout << o << endl;

  return 0;
}
