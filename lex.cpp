#include <iostream>
#include "lex.h"
#include <string>
#include <algorithm>
using namespace std;


LexItem getNextToken(istream& in, int& linenumber){
  string word = "";
  bool wordPresent = false;
  while(!in.eof()){
    
    //it is a coment
    char ch = in.get();

    if(ch == -1){
      return LexItem(DONE,"DONE",linenumber);
    }

    if(ch == '\n'){
      linenumber ++;
      continue;
    }

    if(ch == '#'){
      getline(in, word);
      linenumber++;
      word = "";
      continue;
    }
    if(ch == ' ' || ch == '\t'){
      continue;
    }
    //it is a string
    if(ch == '\"'){
      string w = "";
      w += "\"";
      while(!in.eof()){
        ch = in.get();
        if(ch == '\n'){
          return LexItem(ERR,w,linenumber);
        }

        if(ch == '\"'){
          w+= "\"";
          break;
        }
        w += ch;
      }
      if(in.eof()){
        return LexItem(ERR,w,linenumber);
      }
      return LexItem(SCONST, w ,linenumber);
    }
    
    //it is a number
    if(isdigit(ch) || ch == '.'){
      bool rCons = false;
      string num = "";
      if(ch == '.' && isdigit(in.peek())){
        rCons = true;
      }
      else if (ch == '.' && !isdigit(in.peek())){
        num+=ch;
        num+= in.get();
        return LexItem(ERR, num,linenumber);
      }
      num +=ch;
      while(!in.eof()){
        ch = in.get();
        if(isspace(ch)){
          if(ch == '\n'){
            in.putback(ch);
          }
          if(rCons)
            return LexItem(RCONST,num,linenumber);
          return LexItem(ICONST,num,linenumber);
        }
        else if (ch == '.'){
          if(!isdigit(in.peek())){
            num+= ch;
            return LexItem(ERR,num,linenumber);
          }
          rCons = true;
          num += ch;
        }
        else if (isdigit(ch)){
          
          num += ch;
        }
        else {
          in.putback(ch);
          if(rCons)
            return LexItem(RCONST,num,linenumber);
          return LexItem(ICONST,num,linenumber);
        }
      }
    }

    // it is a IDENT or KEYWORD
    if(isalpha(ch)){
      string ki = "";
      ki += ch;
      while(!in.eof()){
        ch = in.get();
        if(isalnum(ch) > 0 || ch == '_'){
          ki += ch;
        }
        else{
          in.putback(ch);
          return id_or_kw(ki,linenumber);
        }
      }
    }


    if( wordPresent == false){
      if(ch == ';'){
        return LexItem(SEMICOL,"SEMICOL",linenumber);
      }
      if(ch == '>'){
        return LexItem(GTHAN,"GTHAN",linenumber);
      }
      if(ch == ','){
        return LexItem(COMMA,"COMMA",linenumber);
      }
      if(ch == '('){
        return LexItem(LPAREN,"LPAREN",linenumber);
      }
      if(ch == ')'){
        return LexItem(RPAREN,"RPAREN",linenumber);
      }
      if(ch == '/'){
        return LexItem(DIV,"DIV",linenumber);
      }
      if(ch == '*'){
        return LexItem(MULT,"MULT",linenumber);
      }
      if(ch == '-'){
        return LexItem(MINUS,"MINUS",linenumber);
      }
      if(ch == '+'){
        return LexItem(PLUS,"PLUS",linenumber);
      }
      if(ch == '%'){
        return LexItem(REM,"REM",linenumber);
      }
      if(ch == '='){
        if(in.peek() == '='){
          in.get();
          return LexItem(EQUAL,"EQUAL",linenumber);
        }
        return LexItem(ASSOP,"ASSOP",linenumber);
      }
      else{
        string s = "";
        s +=ch;
        return LexItem(ERR,s,linenumber);
      }

    }
    else {
    word += ch;
    wordPresent= true;
    }
  }
  return LexItem(DONE,"DONE",linenumber);
}

LexItem id_or_kw(const string& lexeme, int linenum){
  bool alu = false;

  string allUp = lexeme;
  std::transform(allUp.begin(), allUp.end(),allUp.begin(), ::toupper);

  Token t;
  auto itr = kwmap.find(allUp);
  if(itr == kwmap.end()){
    t= IDENT;
  }
  else{
    alu = true;
    t = kwmap[allUp];
  }

  if(alu){
    return LexItem(t,allUp,linenum);
  }
  return LexItem(t,allUp,linenum);
}

ostream& operator<<(ostream& out, const LexItem& tok){
   //if one of these IDENT, ICONST, RCONST, or SCONST print lexemes
    if(tok.GetToken() == IDENT || tok.GetToken() == ICONST || tok.GetToken() == RCONST){
      out << tokenPrint[tok.GetToken()]<<"(" << tok.GetLexeme() << ")"<<endl; 
    }
    else if(tok.GetToken() == SCONST){
      string s = ""; s = tok.GetLexeme();
      s = s.substr(1,s.length()-2);
      out<< tokenPrint[tok.GetToken()] << "(" << s << ")" << endl;
    }
    else
      out << tokenPrint[tok.GetToken()] << endl;
  return out;
}
