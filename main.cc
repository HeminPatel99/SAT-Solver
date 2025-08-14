#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"
#include <regex>
#include <exception>
using namespace std;

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const string &line, string &formulaStr, string &assignmentStr) {
  // your code starts here
  if (line.find(";") < line.size()){
    //cout << "TRUE" << endl;
    formulaStr = (line.substr(0, line.find(";")));
    assignmentStr = (line.substr(line.find(";")+1, line.size()));
  }
  else{
    //cout << "parseline" << endl;
    throw invalid_argument("invalid input");
  }
  
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true){ // continuously asking for new inputs from standard input
    string line; // store each input line
    string formulaStr; // store the formula string
    string assignmentStr; // store the assignment string
    // your code starts here
    //int count = 0;
    //bool check;
    string *fh,*sh,*lptr;
    map<string, bool> mapper;
    //cin >> line;
    getline(cin,line);
    if (cin.eof()){
      break;
    }
    //line = "1+0;";
    lptr = &line;
    sh = &assignmentStr;
    fh = &formulaStr;
    //cout << formulaStr << endl;
    //cout << assignmentStr << endl;
    try{
      parseLine(*lptr, *fh, *sh);
      FormulaParser *fp = new FormulaParser(formulaStr);
      //cout << "pass" << endl;
      AssignmentParser *ap = new AssignmentParser(assignmentStr);
      TreeNode *root = fp->getTreeRoot();
      mapper = ap->parseAssignment();
      cout << root->evaluate(mapper) << endl;
    }
    catch(invalid_argument& err){
      cout << "Error: " << err.what() << endl;
    }
    catch(out_of_range& err){
      cout << "Error: " << err.what() << endl;
    }
  }
  return 0;
}
