%top{
    #include "parser.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
    #include "Node.h"
    int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack 

DIGIT     [0-9]
ID_START  [a-zA-Z_]
ID_CHAR   [a-zA-Z0-9_]

%%


":=" { if(USE_LEX_ONLY) { printf("ASSIGN "); }   else { return yy::parser::make_ASSIGN(yytext); } }
"<=" { if(USE_LEX_ONLY) { printf("LE "); }       else { return yy::parser::make_LE(yytext); } }
">=" { if(USE_LEX_ONLY) { printf("GE "); }       else { return yy::parser::make_GE(yytext); } }
"!=" { if(USE_LEX_ONLY) { printf("NE "); }       else { return yy::parser::make_NE(yytext); } }

"<"  { if(USE_LEX_ONLY) { printf("LT "); }       else { return yy::parser::make_LT(yytext); } }
">"  { if(USE_LEX_ONLY) { printf("GT "); }       else { return yy::parser::make_GT(yytext); } }
"="  { if(USE_LEX_ONLY) { printf("EQ "); }       else { return yy::parser::make_EQ(yytext); } }

"&"  { if(USE_LEX_ONLY) { printf("AND "); }      else { return yy::parser::make_AND(yytext); } }
"|"  { if(USE_LEX_ONLY) { printf("OR "); }       else { return yy::parser::make_OR(yytext); } }
"!"  { if(USE_LEX_ONLY) { printf("NOT "); }      else { return yy::parser::make_NOT(yytext); } }

"+"  { if(USE_LEX_ONLY) { printf("PLUSOP "); }   else { return yy::parser::make_PLUSOP(yytext); } }
"-"  { if(USE_LEX_ONLY) { printf("MINUSOP "); }  else { return yy::parser::make_MINUSOP(yytext); } }
"*"  { if(USE_LEX_ONLY) { printf("MULTOP "); }   else { return yy::parser::make_MULTOP(yytext); } }
"/"  { if(USE_LEX_ONLY) { printf("DIVOP "); }    else { return yy::parser::make_DIVOP(yytext); } }
"^"  { if(USE_LEX_ONLY) { printf("POWOP "); }    else { return yy::parser::make_POWOP(yytext); } }

"("  { if(USE_LEX_ONLY) { printf("LP "); }       else { return yy::parser::make_LP(yytext); } }
")"  { if(USE_LEX_ONLY) { printf("RP "); }       else { return yy::parser::make_RP(yytext); } }
"{"  { if(USE_LEX_ONLY) { printf("LBRACE "); }   else { return yy::parser::make_LBRACE(yytext); } }
"}"  { if(USE_LEX_ONLY) { printf("RBRACE "); }   else { return yy::parser::make_RBRACE(yytext); } }
"["  { if(USE_LEX_ONLY) { printf("LBRACK "); }   else { return yy::parser::make_LBRACK(yytext); } }
"]"  { if(USE_LEX_ONLY) { printf("RBRACK "); }   else { return yy::parser::make_RBRACK(yytext); } }
","  { if(USE_LEX_ONLY) { printf("COMMA "); }    else { return yy::parser::make_COMMA(yytext); } }
":"  { if(USE_LEX_ONLY) { printf("COLON "); }    else { return yy::parser::make_COLON(yytext); } }
"."  { if(USE_LEX_ONLY) { printf("DOT "); }      else { return yy::parser::make_DOT(yytext); } }

"class"     { if(USE_LEX_ONLY) { printf("CLASS "); }      else { return yy::parser::make_CLASS(yytext); } }
"main"      { if(USE_LEX_ONLY) { printf("MAIN "); }       else { return yy::parser::make_MAIN(yytext); } }
"void"      { if(USE_LEX_ONLY) { printf("VOID "); }       else { return yy::parser::make_VOID(yytext); } }
"int"       { if(USE_LEX_ONLY) { printf("INT_TYPE "); }   else { return yy::parser::make_INT_TYPE(yytext); } }
"float"     { if(USE_LEX_ONLY) { printf("FLOAT_TYPE "); } else { return yy::parser::make_FLOAT_TYPE(yytext); } }
"boolean"   { if(USE_LEX_ONLY) { printf("BOOLEAN "); }    else { return yy::parser::make_BOOLEAN(yytext); } }
"volatile"  { if(USE_LEX_ONLY) { printf("VOLATILE "); }   else { return yy::parser::make_VOLATILE(yytext); } }

"if"        { if(USE_LEX_ONLY) { printf("IF "); }         else { return yy::parser::make_IF(yytext); } }
"else"      { if(USE_LEX_ONLY) { printf("ELSE "); }       else { return yy::parser::make_ELSE(yytext); } }
"for"       { if(USE_LEX_ONLY) { printf("FOR "); }        else { return yy::parser::make_FOR(yytext); } }
"return"    { if(USE_LEX_ONLY) { printf("RETURN "); }     else { return yy::parser::make_RETURN(yytext); } }
"break"     { if(USE_LEX_ONLY) { printf("BREAK "); }      else { return yy::parser::make_BREAK(yytext); } }
"continue"  { if(USE_LEX_ONLY) { printf("CONTINUE "); }   else { return yy::parser::make_CONTINUE(yytext); } }
"print"     { if(USE_LEX_ONLY) { printf("PRINT "); }      else { return yy::parser::make_PRINT(yytext); } }
"read"      { if(USE_LEX_ONLY) { printf("READ "); }       else { return yy::parser::make_READ(yytext); } }

"true"      { if(USE_LEX_ONLY) { printf("TRUE "); }       else { return yy::parser::make_TRUE(yytext); } }
"false"     { if(USE_LEX_ONLY) { printf("FALSE "); }      else { return yy::parser::make_FALSE(yytext); } }
"length"    { if(USE_LEX_ONLY) { printf("LENGTH "); }     else { return yy::parser::make_LENGTH(yytext); } }

(0\.[0-9]+|[1-9][0-9]*\.[0-9]+) { if(USE_LEX_ONLY) { printf("FLOAT "); } else { return yy::parser::make_FLOAT(yytext); } }

0[0-9]+ {
        if(!lexical_errors) fprintf(stderr, "Lexical errors found! See logs below:\n");
        fprintf(stderr, "Lexical error at line %d: leading zero in integer %s\n", yylineno, yytext);
        lexical_errors = 1;
	exit(1);
    }

(0|[1-9][0-9]*) { if(USE_LEX_ONLY) { printf("INT "); } else { return yy::parser::make_INT(yytext); } }

{ID_START}{ID_CHAR}* { if(USE_LEX_ONLY) { printf("ID "); } else { return yy::parser::make_ID(yytext); } }

[ \t\r]+      {}

"//"[^\n]*    {}

\n+           { if(USE_LEX_ONLY) { printf("NEWLINE "); } else { return yy::parser::make_NEWLINE(yytext); } }

. {
    if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n");
    fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext);
    lexical_errors = 1;
}

<<EOF>> {
    if(USE_LEX_ONLY) { printf("\n"); fflush(stdout); }
    return yy::parser::make_END();
}

%%
