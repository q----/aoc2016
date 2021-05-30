#include <iostream>

using namespace std;

const string operator!(const string& a){
  string o;
  for(char c : a) o+= (c=='0')?'1':'0';
  return o;
}

const string operator~(const string& a){
  string o;
  for(int i = a.size(); i >= 0; --i) o += a[i];
  return o;
}

string g(string i, int n){
  if(i.size() >= n) return i.substr(0,n);
  return g(i + !~i, n);
}

string c(string i){
  if(i.size() % 2) return i;
  string t;
  for(int x = 0; x < i.size() / 2; x++) t += (i[2*x] == i[2*x+1])?'1':'0';
  return c(t);
}

int main(){
  string i = "11011110011011101";
  int n = 272;
  int n2 = 35651584;

  cout << c(g(i, n)) << endl;
  cout << c(g(i, n2)) << endl;

  return 0;
}
