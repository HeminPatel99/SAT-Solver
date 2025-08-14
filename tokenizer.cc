#include <iostream>
#include "tokenizer.h"
#include <regex>
#include <vector>
#include <string>
#include <exception>
using namespace std;

Tokenizer::Tokenizer(std::string ln) {
  // complete the constructor
  curr = 0;// initialize the index that will be incremented using advancetoken
  int i=0, j, k=0, count1=0, count2=0, twovarcheck=0 ;
  string arr[1000];//temp array to store the tokens
  int t[1000] = {0}; // 1 = constant, 2 = variable, 3 = operator
  string myvar,mystr,var;

  regex regexp1("[A-Za-z0-9]");
  regex regexp2("[A-Za-z]");

  char checksymbol[] = {'(', ')','+','*','-', ':',','};// 7 operator symbols
  while (i < int(ln.length())) {
    //cout << ln[i] << "<-ln[i]\n";
    myvar += ln[i];
    if (ln[i] == ' '){//ignore spaces
      //cout << "space\n";
      i += 1;
      myvar = "";
    }
    else if (ln[i] == '0' ||ln[i] == '1'){// check if its a valid constant
      j = i + 1;
      if (j >= int(ln.size())){
        arr[k]= ln[i];
        t[k] = 1;
        k += 1;
        break;
      }
      mystr += ln[j];
      if(regex_search(mystr, regexp1)){
        //cout << "in tokenizer" << endl;
        throw invalid_argument("invalid input");
      }
      else{
        arr[k]= ln[i];
        t[k] = 1;
        k += 1;
        i += 1;
      }
      mystr = "";
      myvar = "";
    }
    else if (regex_search(myvar, regexp2)){// get the variablename
      //cout << myvar << "<- myvar" ;
      bool c = true;
      int varlen = 0;
      while (c){
        var += ln[i];
        varlen += 1;
        i = i + 1;
        myvar = "";
        myvar += ln[i];
        if (!regex_search(myvar, regexp1) || i >= int(ln.size() )){
          c = false;
        }
      }
      if (varlen > 10){
        throw invalid_argument("invalid input");
      }
      twovarcheck += 1;
      if (twovarcheck == 2){
        throw invalid_argument("invalid input");
      }
      arr[k] = var;
      t[k] = 2;
      //cout << var <<"\n";
      k += 1;
      var = "";
      myvar = "";
    }
    else{
      for (int g = 0; g < int(sizeof(checksymbol)); g++){// get the operator
        if (ln[i] == checksymbol[g]){
          twovarcheck -= 1;
          arr[k] = ln[i];
          t[k] = 3;
          k += 1;
          break;
        }
        else if (g == (int(sizeof(checksymbol)) - 1)){
          //cout << "lower tokenizer" << endl;
          throw invalid_argument("invalid input");
        }
      }
      i += 1;
      myvar = "";
    }
  }
  size = k;
  //cout << "K=" << k << endl;
  for (int g =0; g < k; g++){
    //cout << "g--" << g << endl;
    arrt[g] = new Token();
    arrt[g]->content = arr[g];
    //cout << "TKNZR= arr[g] " << arr[g] << endl;
    if(arr[g] == "("){
      count1 += 1;
    }
    else if (arr[g] == ")"){
      count2 +=1;
    }
    if (t[g] == 1){
      arrt[g]->type = "Const";
    }
    else if (t[g] == 2){
      arrt[g]->type = "Var";
    }
    else if (t[g] == 3){
      arrt[g]->type = "OP";
    }
  }
  if (count1 != count2){
    throw invalid_argument("invalid input");
  }
}

bool Tokenizer::advanceToken() {
  // your code starts here
  //cout << "fk adv" << endl;
  curr += 1;
  return true;
}

bool Tokenizer::hasToken() const {
  // your code starts here
  //cout << "fk hastoken" << endl;
  if (curr < size && curr != EOF){// troubleshoot for later
    return true;
  }
  return false;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  Token resultToken;
  //cout << "fk gettoken" << endl;
  // your code starts there
  if (hasToken()){
    resultToken.content = arrt[curr]->content;
    resultToken.type = arrt[curr]->type;
  }
  return resultToken;
}
