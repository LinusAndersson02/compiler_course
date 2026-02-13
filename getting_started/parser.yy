/* Skeleton and definitions for generating a LALR(1) parser in C++ */
%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

/* Required code included before the parser definition begins */
%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.
}

/* Code included in the parser implementation file */
%code{
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;

  static Node* mk(const std::string& t, const std::string& v="") {
    return new Node(t, v, yylineno);
  }
  static Node* mk1(const std::string& t, Node* a) {
    Node* n = mk(t); n->children.push_back(a); return n;
  }
  static Node* mk2(const std::string& t, Node* a, Node* b) {
    Node* n = mk(t); n->children.push_back(a); n->children.push_back(b); return n;
  }
  static Node* mk3(const std::string& t, Node* a, Node* b, Node* c) {
    Node* n = mk(t); n->children.push_back(a); n->children.push_back(b); n->children.push_back(c); return n;
  }
}

/* Token definitions for the grammar */
/* Tokens represent the smallest units of the language, like operators and parentheses */
%token <std::string>
  ID INT FLOAT NEWLINE
  PLUSOP MINUSOP MULTOP DIVOP POWOP
  ASSIGN LT GT LE GE EQ NE
  AND OR NOT
  LP RP LBRACE RBRACE LBRACK RBRACK COMMA COLON DOT
  CLASS MAIN
  INT_TYPE FLOAT_TYPE BOOLEAN VOLATILE VOID
  IF ELSE FOR RETURN BREAK CONTINUE PRINT READ
  TRUE FALSE LENGTH
;

%token END 0 "end of file"




/* Operator precedence and associativity rules */
/* Used to resolve ambiguities in parsing expressions See https://www.gnu.org/software/bison/manual/bison.html#Precedence-Decl */ 
%left OR
%left AND
%nonassoc LT GT LE GE EQ NE
%nonassoc IF_NO_ELSE
%nonassoc ELSE
%left PLUSOP MINUSOP
%left MULTOP DIVOP
%right POWOP
%right NOT
%right UMINUS




/* Specify types for non-terminals in the grammar */
/* The type specifies the data type of the values associated with these non-terminals */
%type <Node *>
	program opt_newlines global_var_list
	class_list class_decl 
	class_body class_member
	class_member_tail
	class_member_list
	param_list_opt param_list param
	entry
	var_decl opt_init
	type base_type array_opt
	stmt stmt_list stmt_block stmt_end
	lvalue lvalue_tail_list lvalue_tail
	expr expr_or expr_and expr_cmp expr_add expr_mul expr_pow expr_unary expr_postfix primary
	args_opt args
	for_init_opt for_init for_cond_opt

/* Grammar rules section */
/* This section defines the production rules for the language being parsed */
%%
program
  :  global_var_list class_list entry opt_newlines END
  {
    root = mk("Progam");
    root -> children.push_back($1);
    root -> children.push_back($2);
    root -> children.push_back($3);
    }
  ;

global_var_list
	: { $$ = mk("Globals"); }
	| global_var_list NEWLINE { $$ = $1; } // eat newlines
	| global_var_list var_decl stmt_end
		{ $$ = $1; $$ -> children.push_back(mk1("GlobalVar", $2)); }
	;
opt_newlines
	:        { $$ = mk("NLs"); }
	| opt_newlines NEWLINE { $$ = $1; }
	;

class_list
	:      { $$ = mk("Classes"); }
	| class_list class_decl { $$ = $1; $$->children.push_back($2); }
	;

class_decl
	: CLASS ID LBRACE class_body RBRACE opt_newlines
	{
	 $$ = mk("ClassDecl");
	 $$->children.push_back(mk("Id", $2));
	 $$ -> children.push_back($4); /* classbody */
	}
	;

class_body
	: class_member_list { $$ = $1; }
	;

class_member_list
	: /* empty */ { $$ = mk("ClassBody"); }
	| class_member_list NEWLINE { $$ = $1; }
	| class_member_list class_member { $$ = $1; $$->children.push_back($2); }
	;

class_member
  : ID class_member_tail
    {
      if ($2->type == "ClassVar") {
        Node* vd = $2->children.front(); 

        auto it = vd->children.begin();
        ++it;                
        (*it)->value = $1;  
      }
      else if ($2->type == "MethodDecl") {
        Node* idNode = $2->children.front();
        idNode->value = $1;
      }

      $$ = $2;
    }
  | VOLATILE ID COLON type opt_init stmt_end
    {
      Node* vd = mk("VarDecl");
      vd->children.push_back(mk("Volatile","true"));
      vd->children.push_back(mk("Id", $2));
      vd->children.push_back($4);
      if ($5) vd->children.push_back($5);

      $$ = mk1("ClassVar", vd);
    }
  ;

class_member_tail
  : COLON type opt_init stmt_end
    {
      Node* vd = mk("VarDecl");
      vd->children.push_back(mk("Volatile","false"));
      vd->children.push_back(mk("Id", ""));  /* placeholder; will be overwritten */
      vd->children.push_back($2);
      if ($3) vd->children.push_back($3);

      $$ = mk1("ClassVar", vd);
    }
  | LP param_list_opt RP COLON type stmt_block
    {
      $$ = mk("MethodDecl");
      $$->children.push_back(mk("Id", ""));   /* placeholder; will be overwritten */
      $$->children.push_back($2);             
      Node* rt = mk("ReturnType");
      rt->children.push_back($5);            
      $$->children.push_back(rt);
      $$->children.push_back($6);            
    }
  ;

param_list_opt
  : /* empty */ { $$ = mk("Params"); }
  | param_list  { $$ = $1; }
  ;

param_list
  : param                 { $$ = mk("Params"); $$->children.push_back($1); }
  | param_list COMMA param { $$ = $1; $$->children.push_back($3); }
  ;

param
  : ID COLON type
    {
      $$ = mk("Param");
      $$->children.push_back(mk("Id", $1));
      $$->children.push_back($3);
    }
  ;


entry
	  : MAIN LP RP COLON INT_TYPE stmt_block
	    { $$ = mk("Entry"); $$->children.push_back(mk("ReturnType", "int")); $$->children.push_back($6); }
	  ;

stmt_block
 : LBRACE stmt_list RBRACE 
 { $$ = mk("StmtBlock"); $$->children.push_back($2); }
 ;

stmt_list
  : /* empty */            { $$ = mk("Stmts"); }
  | stmt_list NEWLINE      { $$ = $1; }              /* allow blank lines */
  | stmt_list stmt         { $$ = $1; $$->children.push_back($2); }
  ;

/* NEWLINE terminator */
stmt_end
  : NEWLINE { $$ = mk("StmtEnd"); }
  ;

stmt
  : stmt_block { $$ = $1; }
  | var_decl stmt_end { $$ = mk1("VarStmt", $1); }
  | lvalue ASSIGN expr stmt_end { $$ = mk3("AssignStmt", $1, mk("Op", ":="), $3); }
  | expr stmt_end { $$ = mk1("ExprStmt", $1); }
  | IF LP expr RP stmt %prec IF_NO_ELSE              { $$ = mk2("IfStmt", $3, $5); }
  | IF LP expr RP stmt ELSE stmt     { $$ = mk3("IfElseStmt", $3, $5, $7); }
  | FOR LP for_init_opt COMMA for_cond_opt COMMA lvalue ASSIGN expr RP stmt
      {
        Node* n = mk("ForStmt");
        n->children.push_back($3);   /* init */
        n->children.push_back($5);   /* cond */
        n->children.push_back(mk3("Update", $7, mk("Op", ":="), $9));
        n->children.push_back($11);  /* body */
        $$ = n;
      }
  | PRINT LP expr RP stmt_end { $$ = mk1("PrintStmt", $3); }
  | READ  LP lvalue RP stmt_end { $$ = mk1("ReadStmt", $3); }
  | RETURN expr stmt_end { $$ = mk1("ReturnStmt", $2); }
  | BREAK stmt_end { $$ = mk("BreakStmt"); }
  | CONTINUE stmt_end { $$ = mk("ContinueStmt"); }
  ;

for_init_opt
  : /* empty */ { $$ = mk("ForInitEmpty"); }
  | for_init    { $$ = $1; }
  ;

for_init
  : var_decl                { $$ = mk1("ForInitVar", $1); }
  | lvalue ASSIGN expr      { $$ = mk3("ForInitAssign", $1, mk("Op", ":="), $3); }
  ;

for_cond_opt
  : /* empty */ { $$ = mk("ForCondEmpty"); }
  | expr        { $$ = $1; }
  ;
var_decl
  : ID COLON type opt_init
    {
      $$ = mk("VarDecl");
      $$->children.push_back(mk("Volatile","false"));
      $$->children.push_back(mk("Id", $1));
      $$->children.push_back($3);
      if ($4) $$->children.push_back($4);
    }
  | VOLATILE ID COLON type opt_init
    {
      $$ = mk("VarDecl");
      $$->children.push_back(mk("Volatile","true"));
      $$->children.push_back(mk("Id", $2));
      $$->children.push_back($4);
      if ($5) $$->children.push_back($5);
    }
  ;


opt_init
  : /* empty */ { $$ = nullptr; }
  | ASSIGN expr { $$ = mk1("Init", $2); }
  ;

type
  : base_type array_opt { $$ = mk2("Type", $1, $2); }
  | ID                  { $$ = mk("TypeName", $1); }
  | VOID                { $$ = mk("Type", "void"); }
  ;

base_type
  : INT_TYPE   { $$ = mk("BaseType", "int"); }
  | FLOAT_TYPE { $$ = mk("BaseType", "float"); }
  | BOOLEAN    { $$ = mk("BaseType", "boolean"); }
  ;

array_opt
  : /* empty */          { $$ = mk("Array", "false"); }
  | LBRACK RBRACK        { $$ = mk("Array", "true"); }
  ;

/* lvalue ::= ID ( ("[" expr "]") | ("." ID) )* */
lvalue
  : ID lvalue_tail_list
    { $$ = mk("LValue"); $$->children.push_back(mk("Id", $1)); $$->children.push_back($2); }
  ;

lvalue_tail_list
  : /* empty */ { $$ = mk("LValueTails"); }
  | lvalue_tail_list lvalue_tail { $$ = $1; $$->children.push_back($2); }
  ;

lvalue_tail
  : LBRACK expr RBRACK { $$ = mk1("IndexTail", $2); }
  | DOT ID             { $$ = mk("FieldTail", $2); }
  | DOT LENGTH { $$  = mk("LengthTail"); }
  ;

/* Expression with precedence layers */
expr : expr_or { $$ = $1; } ;

expr_or
  : expr_or OR expr_and  { $$ = mk2("OrExpr", $1, $3); }
  | expr_and             { $$ = $1; }
  ;

expr_and
  : expr_and AND expr_cmp { $$ = mk2("AndExpr", $1, $3); }
  | expr_cmp              { $$ = $1; }
  ;

expr_cmp
  : expr_add LT expr_add { $$ = mk2("LtExpr", $1, $3); }
  | expr_add GT expr_add { $$ = mk2("GtExpr", $1, $3); }
  | expr_add LE expr_add { $$ = mk2("LeExpr", $1, $3); }
  | expr_add GE expr_add { $$ = mk2("GeExpr", $1, $3); }
  | expr_add EQ expr_add { $$ = mk2("EqExpr", $1, $3); }
  | expr_add NE expr_add { $$ = mk2("NeExpr", $1, $3); }
  | expr_add             { $$ = $1; }
  ;

expr_add
  : expr_add PLUSOP expr_mul  { $$ = mk2("AddExpr", $1, $3); }
  | expr_add MINUSOP expr_mul { $$ = mk2("SubExpr", $1, $3); }
  | expr_mul                  { $$ = $1; }
  ;

expr_mul
  : expr_mul MULTOP expr_pow { $$ = mk2("MulExpr", $1, $3); }
  | expr_mul DIVOP  expr_pow { $$ = mk2("DivExpr", $1, $3); }
  | expr_pow                 { $$ = $1; }
  ;

expr_pow
  : expr_unary POWOP expr_pow { $$ = mk2("PowExpr", $1, $3); } /* right-assoc */
  | expr_unary                { $$ = $1; }
  ;

expr_unary
  : NOT expr_unary            { $$ = mk1("NotExpr", $2); }
  | MINUSOP expr_unary %prec UMINUS { $$ = mk1("NegExpr", $2); }
  | expr_postfix              { $$ = $1; }
  ;

expr_postfix
  : expr_postfix LP args_opt RP
    {
      Node* n = mk("CallExpr");
      n->children.push_back($1);
      n->children.push_back($3 ? $3 : mk("Args"));
      $$ = n;
    }
  | primary
    { $$ = $1; }
  ;

primary
  : INT    { $$ = mk("Int", $1); }
  | FLOAT  { $$ = mk("Float", $1); }
  | TRUE   { $$ = mk("Bool", "true"); }
  | FALSE  { $$ = mk("Bool", "false"); }
  | lvalue { $$ = mk1("LValueExpr", $1); }
  | base_type LBRACK args RBRACK
    {
      Node* n = mk("ArrayLiteral");
      n->children.push_back($1);                       
      n->children.push_back($3);
      $$ = n;
    }
  
  | LP expr RP { $$ = $2; }
  ;





args_opt
  : /* empty */ { $$ = nullptr; }
  | args        { $$ = $1; }
  ;

args
  : expr                 { $$ = mk("Args"); $$->children.push_back($1); }
  | args COMMA expr      { $$ = $1; $$->children.push_back($3); }
  ;

%%
