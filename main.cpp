#include <iostream>
#include "lex.h"
#include <fstream>
#include <string>
#include <typeinfo>
#include <list>
using namespace std;
/*
-v: if  present,  every  token  is  printed  when  it  is  seenfollowed  by  its lexeme between parentheses. 

-intconst: if present, prints outall the unique integer constants in numeric order.

-fconst: if  present,  prints  out  all  the  unique realconstants  in  numeric order.

-strconst: if  present,  prints  out  all  the  unique stringconstants  in alphabetical order 

-ident:if present, prints out all of the unique identifiers in alphabetical order. 
*/
int main(int argc,char *argv[] ) {
  
  int lines = 1;
  int tokens = 0;

  list<LexItem> allLexes;

  bool v = true;
  bool intConst = true;
  bool fConst = true;
  bool sConst = true;
  bool ident = true;
  
  string a;
  string file = "";

  for(int i = 1; i < argc; i++ ){
    string arg = argv[i];
    if(arg.at(0) == '-'){

      if(arg == "-iconst"){
        intConst = true;
      }
      else if(arg == "-v"){
        v = true;
      }
      else if(arg == "-fconst"){
        fConst = true;
      }
      else if(arg == "-strconst"){
        sConst = true;
      }
      else if(arg == "-ident"){
        ident = true;
      }
      else {
        cout<< "UNRECOGNIZED FLAG" << arg <<endl;
        exit(1);
      }
    }
    else{
      if(file != ""){
        cout << "ONLY ONE FILE NAME ALLOWED" <<endl;
        exit(1);
      }
      file = arg;
    }
  }
  if(file == ""){
    cout << "NO SPECIFIED INPUT FILE NAME." <<endl;
    exit(1);
  }
  ifstream user(file);
  if(!user){
    cout << "CANNOT OPEN the File"<<file <<endl;
    exit(1);
  }

  while(!user.eof()){
    LexItem test = getNextToken(user, lines);
    if(test.GetToken() == DONE){
      break;
    }
    else if (test.GetToken() == ERR){

      cout<< "Error in line " << test.GetLinenum() << " (" << test.GetLexeme()<< ")"<<endl;
      exit(1);
    }
    allLexes.push_back(test);

    tokens++;
    
    if(v){
    cout << test ;
    }
  }

  if(allLexes.size() == 0){
    cout << "Lines: " << 0 << endl;
    exit(1);
  }
  cout << "Lines: " << lines-1 << endl;
  cout << "Tokens: " << tokens << endl;


  if(intConst){
    list<int> intLexes;
    list<LexItem> :: iterator itr = allLexes.begin();
    //creating a list with only ICONST tokens
    while(itr != allLexes.end()){
      LexItem inte = *itr;
      if(inte.GetToken() == ICONST){
        intLexes.push_back(stoi(inte.GetLexeme()));
      }
      itr++;
    }

    if(intLexes.size()>0){
      cout << "INTEGERS:" <<endl;
      intLexes.sort();
      intLexes.unique();
      int last = intLexes.back();
      intLexes.pop_back();
      list<int> :: iterator itr2 = intLexes.begin();
      while(itr2 != intLexes.end()){
        cout<< *itr2 << endl;
        itr2++;
      }
      cout << last << endl;
    }
  }




  
  if(fConst){
    list<double> fLexes;
    list<LexItem> :: iterator itr = allLexes.begin();
    //creating a list with only ICONST tokens
    while(itr != allLexes.end()){
      LexItem flo = *itr;
      if(flo.GetToken() == RCONST){
        fLexes.push_back(stod(flo.GetLexeme()));
      }
      itr++;
    }

    if(fLexes.size()>0){
      cout << "FLOATS:" <<endl;
      fLexes.sort();
      fLexes.unique();
      double last = fLexes.back();
      fLexes.pop_back();
      list<double> :: iterator itr2 = fLexes.begin();
      while(itr2 != fLexes.end()){
        cout<< *itr2 << endl;
        itr2++;
      }
      cout << last << endl;
    }
  }
  

  if(sConst){
    list<string> sLexes;
    list<LexItem> :: iterator itr = allLexes.begin();
    map<string,int> present;

    //creating a list with only SCONST tokens
    while(itr != allLexes.end()){
      LexItem str = *itr;
      if(str.GetToken() == SCONST){
        sLexes.push_back(str.GetLexeme());
      }
      itr++;
    }

    if(sLexes.size()>0){
      cout << "STRINGS:" <<endl;
      sLexes.sort();
      sLexes.unique();
      string last = sLexes.back();
      sLexes.pop_back();
      list<string> :: iterator itr2 = sLexes.begin();

      while(itr2 != sLexes.end()){
        cout<< *itr2 <<endl;
        itr2++;
      }
      cout << last << endl;
    }
  }


  //ident
  if(ident){
    list<string> idLexes;
    list<LexItem> :: iterator itr = allLexes.begin();
    while(itr != allLexes.end()){
      LexItem ident = *itr;
      if(ident.GetToken() == IDENT){
        //check if it is in the map
        idLexes.push_back(ident.GetLexeme());
      }
     itr++;
    }
    if(idLexes.size()>0){
      cout << "IDENTIFIERS:" <<endl;
      idLexes.sort();
      idLexes.unique();
      string last = idLexes.back();
      idLexes.pop_back();
      list<string> :: iterator itr2 = idLexes.begin();
      while(itr2 != idLexes.end()){
      
        cout<< *itr2 << ", ";
        itr2++;
      }
      cout << last << endl;
    }
  }
 }
