#include <iostream>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

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

char trip(string l){
  char s = 'x';
  int count = 0;
  for(int i = 0; i < l.size(); i++){
    if(l[i] == s){
      count++;
      if(count == 3) return s;
    } else {
      s = l[i];
      count = 1;
    }
  }
  return 'x';
}

string p2md5(string in){
  string out = in;
  for(int i = 0; i < 2016; i++) out = md5sum(out);
  return out;
}

int itr(string input, vector<string>& hashes, bool x = true){
  int index = 0;
  vector<string> keys;

  while(keys.size() < 64){
    while(hashes.size() <= index) hashes.push_back(md5sum((x)?(input + to_string(index)):p2md5(input + to_string(index))));
    char t = trip(hashes[index++]);
    if(t == 'x') continue;
    for(int i = 0; i < 1000; i++){
      if(hashes.size() <= index + i) hashes.push_back(md5sum((x)?(input + to_string(index+i)):p2md5(input + to_string(index+i))));
      string s = "";
      for(int j = 0; j < 5; j++) s += t;
      if(hashes[index+i].find(s) != string::npos){
        keys.push_back(hashes[index]);
        break;
      }
    }
  }

  return index - 1;
}


int main(){
  string input = "ahsbgdzn";
  vector<string> hashes;

  cout << itr(input, hashes) << endl;

  for(int i = 0; i < hashes.size(); i++) hashes[i] = p2md5(hashes[i]);

  cout << itr(input, hashes, false) << endl;

  return 0;
}
