#include "ParserTest.hpp"
#include "../../../src/compiler/lexer/Lexer.hpp"
#include "../../../src/compiler/parser/Parser.hpp"
#include "../../../src/compiler/Compiler.hpp"

#include <cassert>
#include <sstream>
#include <iostream>

void ParserTest::test ( void ) {
    {
      std::istringstream iss ( "bigger(elephant, mouse)." );
      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "is_bigger(X, Y) :- bigger(X, Y).\n"
        "is_bigger(X, Y) :- bigger(X, Z), is_bigger(Z, Y)." );
      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "bigger(whale, _).\n"
        "prolog_is_beautiful.\n" 
        "is_smaller(X, Y) :- is_bigger(Y, X).\n"
        "aunt(Aunt, Child) :-\n"
        "\tsister(Aunt, Parent),"
        "\tparent(Parent, Child).");
      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "vodorovna(usecka(bod(a,b), bod(b, c))).\n");
      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "bt_identical(empty, empty).\n"
        "bt_identical(t(_, A, AA), t(_, B, BB)) :-\n"
        "\tbt_identical(A, B),\n"
        "\tbt_identical(AA, BB).\n\r"
      );
      
      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "vezmi(Item) :-\n"
        "\tplayer(X),\n"
        "\titem(X, Item),\n"
        "\tnot(enemy(_, X, _)),\n"
        "\tnot(inventory(Item)),\n"
        "\tassert(inventory(Item)),\n"
        "\tretract(item(X, Item)),\n"
        "\trefresh, nl.\n"
      );
      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "a( b( c( d( e( f, g ( h ) ) ) ) ) )."
      );
      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "can_x_defend(H,T) :-\n"
        "append(_,Y,H,T),"
        "H=H,"
        "H=Y,"
        "test(X)=test,"
        "s(X,Y)=p(Y,ahoj)."
      );
      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "add(Y,Y).\n"
        "sub(Y,Y).\n"
        "add(s(X),Y,s(Y))."
        "add(s(X),Y,s(Z)):- add(X,Y,Z).\n"
        "sub(s(X),Y,s(Z)):- sub(X,Y,Z).\n"
        "test :- X=y(X).\n"
      );

      Lexer lex ( iss );
      Parser parser ( lex );
      assert ( parser.parse() );
    }

    {
      std::istringstream iss 
      ( "add(Y,Y).\n"
        "add(s(X),Y,s(Y))."
        "add(s(X),Y,s(Z)):- add(X,Y,Z).\n"
      );


      Compiler comp(iss, std::cout);
      comp.compile();
      /**/
      std::cout << std::endl;

      //Lexer lex ( iss );
      //Parser parser ( lex );
      //assert ( parser.parse() );
    }

}
