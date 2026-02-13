// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 16 "parser.yy"

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

#line 67 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 140 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_program: // program
      case symbol_kind::S_global_var_list: // global_var_list
      case symbol_kind::S_opt_newlines: // opt_newlines
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_member_list: // class_member_list
      case symbol_kind::S_class_member: // class_member
      case symbol_kind::S_class_member_tail: // class_member_tail
      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param: // param
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_end: // stmt_end
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
      case symbol_kind::S_lvalue: // lvalue
      case symbol_kind::S_lvalue_tail_list: // lvalue_tail_list
      case symbol_kind::S_lvalue_tail: // lvalue_tail
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_postfix: // expr_postfix
      case symbol_kind::S_primary: // primary
      case symbol_kind::S_args_opt: // args_opt
      case symbol_kind::S_args: // args
        value.YY_MOVE_OR_COPY< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LBRACK: // LBRACK
      case symbol_kind::S_RBRACK: // RBRACK
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_VOLATILE: // VOLATILE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_LENGTH: // LENGTH
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_program: // program
      case symbol_kind::S_global_var_list: // global_var_list
      case symbol_kind::S_opt_newlines: // opt_newlines
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_member_list: // class_member_list
      case symbol_kind::S_class_member: // class_member
      case symbol_kind::S_class_member_tail: // class_member_tail
      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param: // param
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_end: // stmt_end
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
      case symbol_kind::S_lvalue: // lvalue
      case symbol_kind::S_lvalue_tail_list: // lvalue_tail_list
      case symbol_kind::S_lvalue_tail: // lvalue_tail
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_postfix: // expr_postfix
      case symbol_kind::S_primary: // primary
      case symbol_kind::S_args_opt: // args_opt
      case symbol_kind::S_args: // args
        value.move< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LBRACK: // LBRACK
      case symbol_kind::S_RBRACK: // RBRACK
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_VOLATILE: // VOLATILE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_LENGTH: // LENGTH
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_program: // program
      case symbol_kind::S_global_var_list: // global_var_list
      case symbol_kind::S_opt_newlines: // opt_newlines
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_member_list: // class_member_list
      case symbol_kind::S_class_member: // class_member
      case symbol_kind::S_class_member_tail: // class_member_tail
      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param: // param
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_end: // stmt_end
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
      case symbol_kind::S_lvalue: // lvalue
      case symbol_kind::S_lvalue_tail_list: // lvalue_tail_list
      case symbol_kind::S_lvalue_tail: // lvalue_tail
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_postfix: // expr_postfix
      case symbol_kind::S_primary: // primary
      case symbol_kind::S_args_opt: // args_opt
      case symbol_kind::S_args: // args
        value.copy< Node * > (that.value);
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LBRACK: // LBRACK
      case symbol_kind::S_RBRACK: // RBRACK
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_VOLATILE: // VOLATILE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_LENGTH: // LENGTH
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_program: // program
      case symbol_kind::S_global_var_list: // global_var_list
      case symbol_kind::S_opt_newlines: // opt_newlines
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_member_list: // class_member_list
      case symbol_kind::S_class_member: // class_member
      case symbol_kind::S_class_member_tail: // class_member_tail
      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param: // param
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_end: // stmt_end
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
      case symbol_kind::S_lvalue: // lvalue
      case symbol_kind::S_lvalue_tail_list: // lvalue_tail_list
      case symbol_kind::S_lvalue_tail: // lvalue_tail
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_postfix: // expr_postfix
      case symbol_kind::S_primary: // primary
      case symbol_kind::S_args_opt: // args_opt
      case symbol_kind::S_args: // args
        value.move< Node * > (that.value);
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LBRACK: // LBRACK
      case symbol_kind::S_RBRACK: // RBRACK
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_VOLATILE: // VOLATILE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_LENGTH: // LENGTH
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_program: // program
      case symbol_kind::S_global_var_list: // global_var_list
      case symbol_kind::S_opt_newlines: // opt_newlines
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_member_list: // class_member_list
      case symbol_kind::S_class_member: // class_member
      case symbol_kind::S_class_member_tail: // class_member_tail
      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param: // param
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_end: // stmt_end
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
      case symbol_kind::S_lvalue: // lvalue
      case symbol_kind::S_lvalue_tail_list: // lvalue_tail_list
      case symbol_kind::S_lvalue_tail: // lvalue_tail
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_postfix: // expr_postfix
      case symbol_kind::S_primary: // primary
      case symbol_kind::S_args_opt: // args_opt
      case symbol_kind::S_args: // args
        yylhs.value.emplace< Node * > ();
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LBRACK: // LBRACK
      case symbol_kind::S_RBRACK: // RBRACK
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_VOLATILE: // VOLATILE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_LENGTH: // LENGTH
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: global_var_list class_list entry opt_newlines "end of file"
#line 95 "parser.yy"
  {
    root = mk("Progam");
    root -> children.push_back(yystack_[4].value.as < Node * > ());
    root -> children.push_back(yystack_[3].value.as < Node * > ());
    root -> children.push_back(yystack_[2].value.as < Node * > ());
    }
#line 986 "parser.tab.cc"
    break;

  case 3: // global_var_list: %empty
#line 104 "parser.yy"
          { yylhs.value.as < Node * > () = mk("Globals"); }
#line 992 "parser.tab.cc"
    break;

  case 4: // global_var_list: global_var_list NEWLINE
#line 105 "parser.yy"
                                  { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 998 "parser.tab.cc"
    break;

  case 5: // global_var_list: global_var_list var_decl stmt_end
#line 107 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > (); yylhs.value.as < Node * > () -> children.push_back(mk1("GlobalVar", yystack_[1].value.as < Node * > ())); }
#line 1004 "parser.tab.cc"
    break;

  case 6: // opt_newlines: %empty
#line 110 "parser.yy"
                 { yylhs.value.as < Node * > () = mk("NLs"); }
#line 1010 "parser.tab.cc"
    break;

  case 7: // opt_newlines: opt_newlines NEWLINE
#line 111 "parser.yy"
                               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1016 "parser.tab.cc"
    break;

  case 8: // class_list: %empty
#line 115 "parser.yy"
               { yylhs.value.as < Node * > () = mk("Classes"); }
#line 1022 "parser.tab.cc"
    break;

  case 9: // class_list: class_list class_decl
#line 116 "parser.yy"
                                { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1028 "parser.tab.cc"
    break;

  case 10: // class_decl: CLASS ID LBRACE class_body RBRACE opt_newlines
#line 121 "parser.yy"
        {
	 yylhs.value.as < Node * > () = mk("ClassDecl");
	 yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[4].value.as < std::string > ()));
	 yylhs.value.as < Node * > () -> children.push_back(yystack_[2].value.as < Node * > ()); /* classbody */
	}
#line 1038 "parser.tab.cc"
    break;

  case 11: // class_body: class_member_list
#line 129 "parser.yy"
                            { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1044 "parser.tab.cc"
    break;

  case 12: // class_member_list: %empty
#line 133 "parser.yy"
                      { yylhs.value.as < Node * > () = mk("ClassBody"); }
#line 1050 "parser.tab.cc"
    break;

  case 13: // class_member_list: class_member_list NEWLINE
#line 134 "parser.yy"
                                    { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1056 "parser.tab.cc"
    break;

  case 14: // class_member_list: class_member_list class_member
#line 135 "parser.yy"
                                         { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1062 "parser.tab.cc"
    break;

  case 15: // class_member: ID class_member_tail
#line 140 "parser.yy"
    {
      if (yystack_[0].value.as < Node * > ()->type == "ClassVar") {
        Node* vd = yystack_[0].value.as < Node * > ()->children.front(); 

        auto it = vd->children.begin();
        ++it;                
        (*it)->value = yystack_[1].value.as < std::string > ();  
      }
      else if (yystack_[0].value.as < Node * > ()->type == "MethodDecl") {
        Node* idNode = yystack_[0].value.as < Node * > ()->children.front();
        idNode->value = yystack_[1].value.as < std::string > ();
      }

      yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();
    }
#line 1082 "parser.tab.cc"
    break;

  case 16: // class_member: VOLATILE ID COLON type opt_init stmt_end
#line 156 "parser.yy"
    {
      Node* vd = mk("VarDecl");
      vd->children.push_back(mk("Volatile","true"));
      vd->children.push_back(mk("Id", yystack_[4].value.as < std::string > ()));
      vd->children.push_back(yystack_[2].value.as < Node * > ());
      if (yystack_[1].value.as < Node * > ()) vd->children.push_back(yystack_[1].value.as < Node * > ());

      yylhs.value.as < Node * > () = mk1("ClassVar", vd);
    }
#line 1096 "parser.tab.cc"
    break;

  case 17: // class_member_tail: COLON type opt_init stmt_end
#line 169 "parser.yy"
    {
      Node* vd = mk("VarDecl");
      vd->children.push_back(mk("Volatile","false"));
      vd->children.push_back(mk("Id", ""));  /* placeholder; will be overwritten */
      vd->children.push_back(yystack_[2].value.as < Node * > ());
      if (yystack_[1].value.as < Node * > ()) vd->children.push_back(yystack_[1].value.as < Node * > ());

      yylhs.value.as < Node * > () = mk1("ClassVar", vd);
    }
#line 1110 "parser.tab.cc"
    break;

  case 18: // class_member_tail: LP param_list_opt RP COLON type stmt_block
#line 179 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("MethodDecl");
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", ""));   /* placeholder; will be overwritten */
      yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());             
      Node* rt = mk("ReturnType");
      rt->children.push_back(yystack_[1].value.as < Node * > ());            
      yylhs.value.as < Node * > ()->children.push_back(rt);
      yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());            
    }
#line 1124 "parser.tab.cc"
    break;

  case 19: // param_list_opt: %empty
#line 191 "parser.yy"
                { yylhs.value.as < Node * > () = mk("Params"); }
#line 1130 "parser.tab.cc"
    break;

  case 20: // param_list_opt: param_list
#line 192 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1136 "parser.tab.cc"
    break;

  case 21: // param_list: param
#line 196 "parser.yy"
                          { yylhs.value.as < Node * > () = mk("Params"); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1142 "parser.tab.cc"
    break;

  case 22: // param_list: param_list COMMA param
#line 197 "parser.yy"
                           { yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1148 "parser.tab.cc"
    break;

  case 23: // param: ID COLON type
#line 202 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("Param");
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[2].value.as < std::string > ()));
      yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1158 "parser.tab.cc"
    break;

  case 24: // entry: MAIN LP RP COLON INT_TYPE stmt_block
#line 212 "parser.yy"
            { yylhs.value.as < Node * > () = mk("Entry"); yylhs.value.as < Node * > ()->children.push_back(mk("ReturnType", "int")); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1164 "parser.tab.cc"
    break;

  case 25: // stmt_block: LBRACE stmt_list RBRACE
#line 217 "parser.yy"
 { yylhs.value.as < Node * > () = mk("StmtBlock"); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 1170 "parser.tab.cc"
    break;

  case 26: // stmt_list: %empty
#line 221 "parser.yy"
                           { yylhs.value.as < Node * > () = mk("Stmts"); }
#line 1176 "parser.tab.cc"
    break;

  case 27: // stmt_list: stmt_list NEWLINE
#line 222 "parser.yy"
                           { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1182 "parser.tab.cc"
    break;

  case 28: // stmt_list: stmt_list stmt
#line 223 "parser.yy"
                           { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1188 "parser.tab.cc"
    break;

  case 29: // stmt_end: NEWLINE
#line 228 "parser.yy"
            { yylhs.value.as < Node * > () = mk("StmtEnd"); }
#line 1194 "parser.tab.cc"
    break;

  case 30: // stmt: stmt_block
#line 232 "parser.yy"
               { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1200 "parser.tab.cc"
    break;

  case 31: // stmt: var_decl stmt_end
#line 233 "parser.yy"
                      { yylhs.value.as < Node * > () = mk1("VarStmt", yystack_[1].value.as < Node * > ()); }
#line 1206 "parser.tab.cc"
    break;

  case 32: // stmt: lvalue ASSIGN expr stmt_end
#line 234 "parser.yy"
                                { yylhs.value.as < Node * > () = mk3("AssignStmt", yystack_[3].value.as < Node * > (), mk("Op", ":="), yystack_[1].value.as < Node * > ()); }
#line 1212 "parser.tab.cc"
    break;

  case 33: // stmt: expr stmt_end
#line 235 "parser.yy"
                  { yylhs.value.as < Node * > () = mk1("ExprStmt", yystack_[1].value.as < Node * > ()); }
#line 1218 "parser.tab.cc"
    break;

  case 34: // stmt: IF LP expr RP stmt
#line 236 "parser.yy"
                                                     { yylhs.value.as < Node * > () = mk2("IfStmt", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1224 "parser.tab.cc"
    break;

  case 35: // stmt: IF LP expr RP stmt ELSE stmt
#line 237 "parser.yy"
                                     { yylhs.value.as < Node * > () = mk3("IfElseStmt", yystack_[4].value.as < Node * > (), yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1230 "parser.tab.cc"
    break;

  case 36: // stmt: FOR LP for_init_opt COMMA for_cond_opt COMMA lvalue ASSIGN expr RP stmt
#line 239 "parser.yy"
      {
        Node* n = mk("ForStmt");
        n->children.push_back(yystack_[8].value.as < Node * > ());   /* init */
        n->children.push_back(yystack_[6].value.as < Node * > ());   /* cond */
        n->children.push_back(mk3("Update", yystack_[4].value.as < Node * > (), mk("Op", ":="), yystack_[2].value.as < Node * > ()));
        n->children.push_back(yystack_[0].value.as < Node * > ());  /* body */
        yylhs.value.as < Node * > () = n;
      }
#line 1243 "parser.tab.cc"
    break;

  case 37: // stmt: PRINT LP expr RP stmt_end
#line 247 "parser.yy"
                              { yylhs.value.as < Node * > () = mk1("PrintStmt", yystack_[2].value.as < Node * > ()); }
#line 1249 "parser.tab.cc"
    break;

  case 38: // stmt: READ LP lvalue RP stmt_end
#line 248 "parser.yy"
                                { yylhs.value.as < Node * > () = mk1("ReadStmt", yystack_[2].value.as < Node * > ()); }
#line 1255 "parser.tab.cc"
    break;

  case 39: // stmt: RETURN expr stmt_end
#line 249 "parser.yy"
                         { yylhs.value.as < Node * > () = mk1("ReturnStmt", yystack_[1].value.as < Node * > ()); }
#line 1261 "parser.tab.cc"
    break;

  case 40: // stmt: BREAK stmt_end
#line 250 "parser.yy"
                   { yylhs.value.as < Node * > () = mk("BreakStmt"); }
#line 1267 "parser.tab.cc"
    break;

  case 41: // stmt: CONTINUE stmt_end
#line 251 "parser.yy"
                      { yylhs.value.as < Node * > () = mk("ContinueStmt"); }
#line 1273 "parser.tab.cc"
    break;

  case 42: // for_init_opt: %empty
#line 255 "parser.yy"
                { yylhs.value.as < Node * > () = mk("ForInitEmpty"); }
#line 1279 "parser.tab.cc"
    break;

  case 43: // for_init_opt: for_init
#line 256 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1285 "parser.tab.cc"
    break;

  case 44: // for_init: var_decl
#line 260 "parser.yy"
                            { yylhs.value.as < Node * > () = mk1("ForInitVar", yystack_[0].value.as < Node * > ()); }
#line 1291 "parser.tab.cc"
    break;

  case 45: // for_init: lvalue ASSIGN expr
#line 261 "parser.yy"
                            { yylhs.value.as < Node * > () = mk3("ForInitAssign", yystack_[2].value.as < Node * > (), mk("Op", ":="), yystack_[0].value.as < Node * > ()); }
#line 1297 "parser.tab.cc"
    break;

  case 46: // for_cond_opt: %empty
#line 265 "parser.yy"
                { yylhs.value.as < Node * > () = mk("ForCondEmpty"); }
#line 1303 "parser.tab.cc"
    break;

  case 47: // for_cond_opt: expr
#line 266 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1309 "parser.tab.cc"
    break;

  case 48: // var_decl: ID COLON type opt_init
#line 270 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("VarDecl");
      yylhs.value.as < Node * > ()->children.push_back(mk("Volatile","false"));
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[3].value.as < std::string > ()));
      yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
      if (yystack_[0].value.as < Node * > ()) yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1321 "parser.tab.cc"
    break;

  case 49: // var_decl: VOLATILE ID COLON type opt_init
#line 278 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("VarDecl");
      yylhs.value.as < Node * > ()->children.push_back(mk("Volatile","true"));
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[3].value.as < std::string > ()));
      yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
      if (yystack_[0].value.as < Node * > ()) yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1333 "parser.tab.cc"
    break;

  case 50: // opt_init: %empty
#line 289 "parser.yy"
                { yylhs.value.as < Node * > () = nullptr; }
#line 1339 "parser.tab.cc"
    break;

  case 51: // opt_init: ASSIGN expr
#line 290 "parser.yy"
                { yylhs.value.as < Node * > () = mk1("Init", yystack_[0].value.as < Node * > ()); }
#line 1345 "parser.tab.cc"
    break;

  case 52: // type: base_type array_opt
#line 294 "parser.yy"
                        { yylhs.value.as < Node * > () = mk2("Type", yystack_[1].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1351 "parser.tab.cc"
    break;

  case 53: // type: ID
#line 295 "parser.yy"
                        { yylhs.value.as < Node * > () = mk("TypeName", yystack_[0].value.as < std::string > ()); }
#line 1357 "parser.tab.cc"
    break;

  case 54: // type: VOID
#line 296 "parser.yy"
                        { yylhs.value.as < Node * > () = mk("Type", "void"); }
#line 1363 "parser.tab.cc"
    break;

  case 55: // base_type: INT_TYPE
#line 300 "parser.yy"
               { yylhs.value.as < Node * > () = mk("BaseType", "int"); }
#line 1369 "parser.tab.cc"
    break;

  case 56: // base_type: FLOAT_TYPE
#line 301 "parser.yy"
               { yylhs.value.as < Node * > () = mk("BaseType", "float"); }
#line 1375 "parser.tab.cc"
    break;

  case 57: // base_type: BOOLEAN
#line 302 "parser.yy"
               { yylhs.value.as < Node * > () = mk("BaseType", "boolean"); }
#line 1381 "parser.tab.cc"
    break;

  case 58: // array_opt: %empty
#line 306 "parser.yy"
                         { yylhs.value.as < Node * > () = mk("Array", "false"); }
#line 1387 "parser.tab.cc"
    break;

  case 59: // array_opt: LBRACK RBRACK
#line 307 "parser.yy"
                         { yylhs.value.as < Node * > () = mk("Array", "true"); }
#line 1393 "parser.tab.cc"
    break;

  case 60: // lvalue: ID lvalue_tail_list
#line 313 "parser.yy"
    { yylhs.value.as < Node * > () = mk("LValue"); yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[1].value.as < std::string > ())); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1399 "parser.tab.cc"
    break;

  case 61: // lvalue_tail_list: %empty
#line 317 "parser.yy"
                { yylhs.value.as < Node * > () = mk("LValueTails"); }
#line 1405 "parser.tab.cc"
    break;

  case 62: // lvalue_tail_list: lvalue_tail_list lvalue_tail
#line 318 "parser.yy"
                                 { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1411 "parser.tab.cc"
    break;

  case 63: // lvalue_tail: LBRACK expr RBRACK
#line 322 "parser.yy"
                       { yylhs.value.as < Node * > () = mk1("IndexTail", yystack_[1].value.as < Node * > ()); }
#line 1417 "parser.tab.cc"
    break;

  case 64: // lvalue_tail: DOT ID
#line 323 "parser.yy"
                       { yylhs.value.as < Node * > () = mk("FieldTail", yystack_[0].value.as < std::string > ()); }
#line 1423 "parser.tab.cc"
    break;

  case 65: // lvalue_tail: DOT LENGTH
#line 324 "parser.yy"
               { yylhs.value.as < Node * > ()  = mk("LengthTail"); }
#line 1429 "parser.tab.cc"
    break;

  case 66: // expr: expr_or
#line 328 "parser.yy"
               { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1435 "parser.tab.cc"
    break;

  case 67: // expr_or: expr_or OR expr_and
#line 331 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("OrExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1441 "parser.tab.cc"
    break;

  case 68: // expr_or: expr_and
#line 332 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1447 "parser.tab.cc"
    break;

  case 69: // expr_and: expr_and AND expr_cmp
#line 336 "parser.yy"
                          { yylhs.value.as < Node * > () = mk2("AndExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1453 "parser.tab.cc"
    break;

  case 70: // expr_and: expr_cmp
#line 337 "parser.yy"
                          { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1459 "parser.tab.cc"
    break;

  case 71: // expr_cmp: expr_add LT expr_add
#line 341 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("LtExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1465 "parser.tab.cc"
    break;

  case 72: // expr_cmp: expr_add GT expr_add
#line 342 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("GtExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1471 "parser.tab.cc"
    break;

  case 73: // expr_cmp: expr_add LE expr_add
#line 343 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("LeExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1477 "parser.tab.cc"
    break;

  case 74: // expr_cmp: expr_add GE expr_add
#line 344 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("GeExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1483 "parser.tab.cc"
    break;

  case 75: // expr_cmp: expr_add EQ expr_add
#line 345 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("EqExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1489 "parser.tab.cc"
    break;

  case 76: // expr_cmp: expr_add NE expr_add
#line 346 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("NeExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1495 "parser.tab.cc"
    break;

  case 77: // expr_cmp: expr_add
#line 347 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1501 "parser.tab.cc"
    break;

  case 78: // expr_add: expr_add PLUSOP expr_mul
#line 351 "parser.yy"
                              { yylhs.value.as < Node * > () = mk2("AddExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1507 "parser.tab.cc"
    break;

  case 79: // expr_add: expr_add MINUSOP expr_mul
#line 352 "parser.yy"
                              { yylhs.value.as < Node * > () = mk2("SubExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1513 "parser.tab.cc"
    break;

  case 80: // expr_add: expr_mul
#line 353 "parser.yy"
                              { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1519 "parser.tab.cc"
    break;

  case 81: // expr_mul: expr_mul MULTOP expr_pow
#line 357 "parser.yy"
                             { yylhs.value.as < Node * > () = mk2("MulExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1525 "parser.tab.cc"
    break;

  case 82: // expr_mul: expr_mul DIVOP expr_pow
#line 358 "parser.yy"
                             { yylhs.value.as < Node * > () = mk2("DivExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1531 "parser.tab.cc"
    break;

  case 83: // expr_mul: expr_pow
#line 359 "parser.yy"
                             { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1537 "parser.tab.cc"
    break;

  case 84: // expr_pow: expr_unary POWOP expr_pow
#line 363 "parser.yy"
                              { yylhs.value.as < Node * > () = mk2("PowExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1543 "parser.tab.cc"
    break;

  case 85: // expr_pow: expr_unary
#line 364 "parser.yy"
                              { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1549 "parser.tab.cc"
    break;

  case 86: // expr_unary: NOT expr_unary
#line 368 "parser.yy"
                              { yylhs.value.as < Node * > () = mk1("NotExpr", yystack_[0].value.as < Node * > ()); }
#line 1555 "parser.tab.cc"
    break;

  case 87: // expr_unary: MINUSOP expr_unary
#line 369 "parser.yy"
                                    { yylhs.value.as < Node * > () = mk1("NegExpr", yystack_[0].value.as < Node * > ()); }
#line 1561 "parser.tab.cc"
    break;

  case 88: // expr_unary: expr_postfix
#line 370 "parser.yy"
                              { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1567 "parser.tab.cc"
    break;

  case 89: // expr_postfix: expr_postfix LP args_opt RP
#line 375 "parser.yy"
    {
      Node* n = mk("CallExpr");
      n->children.push_back(yystack_[3].value.as < Node * > ());
      n->children.push_back(yystack_[1].value.as < Node * > () ? yystack_[1].value.as < Node * > () : mk("Args"));
      yylhs.value.as < Node * > () = n;
    }
#line 1578 "parser.tab.cc"
    break;

  case 90: // expr_postfix: primary
#line 382 "parser.yy"
    { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1584 "parser.tab.cc"
    break;

  case 91: // primary: INT
#line 386 "parser.yy"
           { yylhs.value.as < Node * > () = mk("Int", yystack_[0].value.as < std::string > ()); }
#line 1590 "parser.tab.cc"
    break;

  case 92: // primary: FLOAT
#line 387 "parser.yy"
           { yylhs.value.as < Node * > () = mk("Float", yystack_[0].value.as < std::string > ()); }
#line 1596 "parser.tab.cc"
    break;

  case 93: // primary: TRUE
#line 388 "parser.yy"
           { yylhs.value.as < Node * > () = mk("Bool", "true"); }
#line 1602 "parser.tab.cc"
    break;

  case 94: // primary: FALSE
#line 389 "parser.yy"
           { yylhs.value.as < Node * > () = mk("Bool", "false"); }
#line 1608 "parser.tab.cc"
    break;

  case 95: // primary: lvalue
#line 390 "parser.yy"
           { yylhs.value.as < Node * > () = mk1("LValueExpr", yystack_[0].value.as < Node * > ()); }
#line 1614 "parser.tab.cc"
    break;

  case 96: // primary: base_type LBRACK args RBRACK
#line 392 "parser.yy"
    {
      Node* n = mk("ArrayLiteral");
      n->children.push_back(yystack_[3].value.as < Node * > ());                       
      n->children.push_back(yystack_[1].value.as < Node * > ());
      yylhs.value.as < Node * > () = n;
    }
#line 1625 "parser.tab.cc"
    break;

  case 97: // primary: LP expr RP
#line 399 "parser.yy"
               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1631 "parser.tab.cc"
    break;

  case 98: // args_opt: %empty
#line 407 "parser.yy"
                { yylhs.value.as < Node * > () = nullptr; }
#line 1637 "parser.tab.cc"
    break;

  case 99: // args_opt: args
#line 408 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1643 "parser.tab.cc"
    break;

  case 100: // args: expr
#line 412 "parser.yy"
                         { yylhs.value.as < Node * > () = mk("Args"); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1649 "parser.tab.cc"
    break;

  case 101: // args: args COMMA expr
#line 413 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1655 "parser.tab.cc"
    break;


#line 1659 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short parser::yypact_ninf_ = -160;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -160,    22,    21,  -160,    -4,  -160,    26,   -22,    33,     8,
      19,    55,    38,  -160,  -160,  -160,  -160,  -160,  -160,  -160,
    -160,  -160,    58,    56,     8,    64,    67,    20,    29,  -160,
      74,  -160,    58,  -160,    75,  -160,  -160,  -160,  -160,  -160,
      29,    29,    29,  -160,  -160,    76,  -160,  -160,    86,    89,
    -160,    79,    57,  -160,    99,    98,  -160,  -160,  -160,    96,
      41,    78,    35,  -160,  -160,   101,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,  -160,   -10,  -160,   119,  -160,   102,    29,     5,  -160,
    -160,  -160,    51,    89,  -160,    57,    57,    73,    73,    73,
      73,    73,    73,  -160,  -160,  -160,   105,    97,   123,   128,
       8,  -160,   104,  -160,  -160,   107,  -160,  -160,  -160,    29,
    -160,   108,   113,   114,  -160,    58,     8,   135,  -160,  -160,
       8,   116,   128,    33,    58,    -4,  -160,  -160,   124,   125,
      29,    33,    33,   126,   127,  -160,  -160,    33,   140,    33,
    -160,     8,  -160,  -160,    33,    29,    10,    33,  -160,  -160,
      29,   150,  -160,    29,  -160,   102,  -160,   131,   130,  -160,
    -160,   149,  -160,   139,   141,    33,  -160,   180,    29,    29,
      33,    33,  -160,   133,   138,  -160,  -160,  -160,  -160,   180,
     150,  -160,   151,    29,   144,   180,  -160
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     8,     1,     0,     4,     0,     0,     0,     0,
       0,     0,     0,     9,     6,    29,     5,    53,    55,    56,
      57,    54,    50,    58,     0,     0,     0,     0,     0,    48,
       0,    52,    50,    12,     0,     2,     7,    61,    91,    92,
       0,     0,     0,    93,    94,     0,    95,    51,    66,    68,
      70,    77,    80,    83,    85,    88,    90,    59,    49,     0,
      11,     0,    60,    87,    86,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      98,     6,     0,    13,     0,    14,     0,     0,     0,    62,
      97,   100,     0,    67,    69,    78,    79,    71,    72,    73,
      74,    75,    76,    81,    82,    84,     0,    99,    10,    19,
       0,    15,     0,    26,    24,     0,    64,    65,    96,     0,
      89,     0,     0,    20,    21,    50,     0,     0,    63,   101,
       0,     0,     0,     0,    50,    61,    27,    25,     0,     0,
       0,     0,     0,     0,     0,    30,    28,     0,    95,     0,
      23,     0,    22,    17,     0,     0,    42,     0,    40,    41,
       0,     0,    31,     0,    33,     0,    16,     0,     0,    43,
      44,     0,    39,     0,     0,     0,    18,     0,    46,     0,
       0,     0,    32,    34,     0,    47,    45,    37,    38,     0,
       0,    35,     0,     0,     0,     0,    36
  };

  const short
  parser::yypgoto_[] =
  {
    -160,  -160,  -160,    93,  -160,  -160,  -160,  -160,  -160,  -160,
    -160,  -160,    54,  -160,   -82,  -160,  -126,  -159,  -160,  -160,
    -160,    -1,   -27,   -21,    -7,  -160,  -121,  -160,  -160,   -28,
    -160,   120,   121,    42,    15,    -6,    59,  -160,  -160,  -160,
     110
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,    27,     7,    13,    59,    60,    85,   111,
     122,   123,   124,    14,   145,   127,    16,   146,   168,   169,
     184,   147,    29,    22,    45,    31,    46,    62,    89,   149,
      48,    49,    50,    51,    52,    53,    54,    55,    56,   106,
      92
  };

  const unsigned char
  parser::yytable_[] =
  {
      47,     8,    23,    32,   114,    58,   148,   153,   116,    11,
      12,    17,   109,   135,    65,   158,   159,    23,   183,   110,
      35,   162,     3,   164,     4,     9,    36,     5,   166,    10,
     191,   172,    37,    38,    39,   171,   196,    40,    91,    15,
     174,    18,    19,    20,    82,    21,     6,    83,    24,   182,
      41,    42,    91,   117,   187,   188,   148,     6,    25,   115,
      26,    87,    18,    19,    20,    88,    77,    78,   148,   192,
      28,   103,   104,   105,   148,    43,    44,    84,   118,   119,
      69,    70,    30,   176,    95,    96,    69,    70,    33,   125,
      34,   129,    71,    72,    73,    74,    75,    76,   133,    63,
      64,    57,    66,    23,    61,   134,    67,   154,    68,   150,
      79,    86,   157,    97,    98,    99,   100,   101,   102,    23,
      80,    81,   112,    23,    90,   119,   113,   167,   120,    36,
     165,   121,   173,   126,   128,   175,   131,   130,   135,    38,
      39,   136,   132,    40,    23,   151,   155,   156,   160,   161,
     185,   186,   163,    37,   177,   170,    41,    42,   178,   113,
     137,   179,   180,   193,   181,   194,   190,   195,    18,    19,
      20,     6,   189,   138,   108,   139,   140,   141,   142,   143,
     144,    43,    44,   135,    38,    39,   152,    93,    40,    94,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    42,     0,   113,     0,     0,     0,     0,     0,
       0,     0,     0,    18,    19,    20,     6,     0,   138,     0,
     139,   140,   141,   142,   143,   144,    43,    44
  };

  const short
  parser::yycheck_[] =
  {
      28,     2,     9,    24,    86,    32,   127,   133,     3,    31,
      32,     3,    22,     3,    42,   141,   142,    24,   177,    29,
       0,   147,     0,   149,     3,    29,     6,     6,   154,     3,
     189,   157,     3,     4,     5,   156,   195,     8,    66,     6,
     161,    33,    34,    35,     3,    37,    36,     6,    29,   175,
      21,    22,    80,    48,   180,   181,   177,    36,     3,    87,
      22,    26,    33,    34,    35,    30,     9,    10,   189,   190,
      12,    77,    78,    79,   195,    46,    47,    36,    27,    28,
       7,     8,    26,   165,    69,    70,     7,     8,    24,   110,
      23,   119,    13,    14,    15,    16,    17,    18,   125,    40,
      41,    27,    26,   110,    29,   126,    20,   134,    19,   130,
      11,    33,   140,    71,    72,    73,    74,    75,    76,   126,
      22,    25,     3,   130,    23,    28,    24,   155,    23,     6,
     151,     3,   160,    29,    27,   163,    23,    29,     3,     4,
       5,     6,    28,     8,   151,    29,    22,    22,    22,    22,
     178,   179,    12,     3,    23,   156,    21,    22,    28,    24,
      25,    12,    23,    12,    23,   193,    28,    23,    33,    34,
      35,    36,    39,    38,    81,    40,    41,    42,    43,    44,
      45,    46,    47,     3,     4,     5,   132,    67,     8,    68,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    -1,    38,    -1,
      40,    41,    42,    43,    44,    45,    46,    47
  };

  const signed char
  parser::yystos_[] =
  {
       0,    52,    53,     0,     3,     6,    36,    55,    72,    29,
       3,    31,    32,    56,    64,     6,    67,     3,    33,    34,
      35,    37,    74,    75,    29,     3,    22,    54,    12,    73,
      26,    76,    74,    24,    23,     0,     6,     3,     4,     5,
       8,    21,    22,    46,    47,    75,    77,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    27,    73,    57,
      58,    29,    78,    87,    87,    80,    26,    20,    19,     7,
       8,    13,    14,    15,    16,    17,    18,     9,    10,    11,
      22,    25,     3,     6,    36,    59,    33,    26,    30,    79,
      23,    80,    91,    82,    83,    85,    85,    84,    84,    84,
      84,    84,    84,    86,    86,    86,    90,    91,    54,    22,
      29,    60,     3,    24,    65,    80,     3,    48,    27,    28,
      23,     3,    61,    62,    63,    74,    29,    66,    27,    80,
      29,    23,    28,    73,    74,     3,     6,    25,    38,    40,
      41,    42,    43,    44,    45,    65,    68,    72,    77,    80,
      74,    29,    63,    67,    73,    22,    22,    80,    67,    67,
      22,    22,    67,    12,    67,    74,    67,    80,    69,    70,
      72,    77,    67,    80,    77,    80,    65,    23,    28,    12,
      23,    23,    67,    68,    71,    80,    80,    67,    67,    39,
      28,    68,    77,    12,    80,    23,    68
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    51,    52,    53,    53,    53,    54,    54,    55,    55,
      56,    57,    58,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    64,    65,    66,    66,    66,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    70,    70,    71,    71,    72,    72,
      73,    73,    74,    74,    74,    75,    75,    75,    76,    76,
      77,    78,    78,    79,    79,    79,    80,    81,    81,    82,
      82,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      84,    85,    85,    85,    86,    86,    87,    87,    87,    88,
      88,    89,    89,    89,    89,    89,    89,    89,    90,    90,
      91,    91
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     5,     0,     2,     3,     0,     2,     0,     2,
       6,     1,     0,     2,     2,     2,     6,     4,     6,     0,
       1,     1,     3,     3,     6,     3,     0,     2,     2,     1,
       1,     2,     4,     2,     5,     7,    11,     5,     5,     3,
       2,     2,     0,     1,     1,     3,     0,     1,     4,     5,
       0,     2,     2,     1,     1,     1,     1,     1,     0,     2,
       2,     0,     2,     3,     2,     2,     1,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     1,     2,     2,     1,     4,
       1,     1,     1,     1,     1,     1,     4,     3,     0,     1,
       1,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INT", "FLOAT",
  "NEWLINE", "PLUSOP", "MINUSOP", "MULTOP", "DIVOP", "POWOP", "ASSIGN",
  "LT", "GT", "LE", "GE", "EQ", "NE", "AND", "OR", "NOT", "LP", "RP",
  "LBRACE", "RBRACE", "LBRACK", "RBRACK", "COMMA", "COLON", "DOT", "CLASS",
  "MAIN", "INT_TYPE", "FLOAT_TYPE", "BOOLEAN", "VOLATILE", "VOID", "IF",
  "ELSE", "FOR", "RETURN", "BREAK", "CONTINUE", "PRINT", "READ", "TRUE",
  "FALSE", "LENGTH", "IF_NO_ELSE", "UMINUS", "$accept", "program",
  "global_var_list", "opt_newlines", "class_list", "class_decl",
  "class_body", "class_member_list", "class_member", "class_member_tail",
  "param_list_opt", "param_list", "param", "entry", "stmt_block",
  "stmt_list", "stmt_end", "stmt", "for_init_opt", "for_init",
  "for_cond_opt", "var_decl", "opt_init", "type", "base_type", "array_opt",
  "lvalue", "lvalue_tail_list", "lvalue_tail", "expr", "expr_or",
  "expr_and", "expr_cmp", "expr_add", "expr_mul", "expr_pow", "expr_unary",
  "expr_postfix", "primary", "args_opt", "args", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    94,    94,   104,   105,   106,   110,   111,   115,   116,
     120,   129,   133,   134,   135,   139,   155,   168,   178,   191,
     192,   196,   197,   201,   211,   216,   221,   222,   223,   228,
     232,   233,   234,   235,   236,   237,   238,   247,   248,   249,
     250,   251,   255,   256,   260,   261,   265,   266,   269,   277,
     289,   290,   294,   295,   296,   300,   301,   302,   306,   307,
     312,   317,   318,   322,   323,   324,   328,   331,   332,   336,
     337,   341,   342,   343,   344,   345,   346,   347,   351,   352,
     353,   357,   358,   359,   363,   364,   368,   369,   370,   374,
     381,   386,   387,   388,   389,   390,   391,   399,   407,   408,
     412,   413
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2266 "parser.tab.cc"

#line 416 "parser.yy"

