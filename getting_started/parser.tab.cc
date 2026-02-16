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

#line 68 "parser.tab.cc"


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
#line 141 "parser.tab.cc"

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
      case symbol_kind::S_stmt_body: // stmt_body
      case symbol_kind::S_stmt_nb: // stmt_nb
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
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
      case symbol_kind::S_stmt_body: // stmt_body
      case symbol_kind::S_stmt_nb: // stmt_nb
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
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
      case symbol_kind::S_stmt_body: // stmt_body
      case symbol_kind::S_stmt_nb: // stmt_nb
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
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
      case symbol_kind::S_stmt_body: // stmt_body
      case symbol_kind::S_stmt_nb: // stmt_nb
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
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
      case symbol_kind::S_stmt_body: // stmt_body
      case symbol_kind::S_stmt_nb: // stmt_nb
      case symbol_kind::S_for_init_opt: // for_init_opt
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond_opt: // for_cond_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_opt_init: // opt_init
      case symbol_kind::S_type: // type
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_array_opt: // array_opt
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
    root = mk("Program");
    root -> children.push_back(yystack_[4].value.as < Node * > ());
    root -> children.push_back(yystack_[3].value.as < Node * > ());
    root -> children.push_back(yystack_[2].value.as < Node * > ());
    }
#line 982 "parser.tab.cc"
    break;

  case 3: // program: stmt_block opt_newlines "end of file"
#line 102 "parser.yy"
  {
    root = mk("Program");
    root->children.push_back(mk("Globals"));
    root->children.push_back(mk("Classes"));
    Node* e = mk("Entry");
    e->children.push_back(mk("ReturnType","int"));
    e->children.push_back(yystack_[2].value.as < Node * > ());
    root->children.push_back(e);
  }
#line 996 "parser.tab.cc"
    break;

  case 4: // global_var_list: %empty
#line 114 "parser.yy"
          { yylhs.value.as < Node * > () = mk("Globals"); }
#line 1002 "parser.tab.cc"
    break;

  case 5: // global_var_list: global_var_list NEWLINE
#line 115 "parser.yy"
                                  { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1008 "parser.tab.cc"
    break;

  case 6: // global_var_list: global_var_list var_decl stmt_end
#line 117 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > (); yylhs.value.as < Node * > () -> children.push_back(mk1("GlobalVar", yystack_[1].value.as < Node * > ())); }
#line 1014 "parser.tab.cc"
    break;

  case 7: // opt_newlines: %empty
#line 120 "parser.yy"
                 { yylhs.value.as < Node * > () = mk("NLs"); }
#line 1020 "parser.tab.cc"
    break;

  case 8: // opt_newlines: opt_newlines NEWLINE
#line 121 "parser.yy"
                               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1026 "parser.tab.cc"
    break;

  case 9: // class_list: %empty
#line 125 "parser.yy"
               { yylhs.value.as < Node * > () = mk("Classes"); }
#line 1032 "parser.tab.cc"
    break;

  case 10: // class_list: class_list class_decl
#line 126 "parser.yy"
                                { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1038 "parser.tab.cc"
    break;

  case 11: // class_decl: CLASS ID LBRACE class_body RBRACE opt_newlines
#line 131 "parser.yy"
        {
	 yylhs.value.as < Node * > () = mk("ClassDecl");
	 yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[4].value.as < std::string > ()));
	 yylhs.value.as < Node * > () -> children.push_back(yystack_[2].value.as < Node * > ()); /* classbody */
	}
#line 1048 "parser.tab.cc"
    break;

  case 12: // class_body: class_member_list
#line 139 "parser.yy"
                            { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1054 "parser.tab.cc"
    break;

  case 13: // class_member_list: %empty
#line 143 "parser.yy"
                      { yylhs.value.as < Node * > () = mk("ClassBody"); }
#line 1060 "parser.tab.cc"
    break;

  case 14: // class_member_list: class_member_list NEWLINE
#line 144 "parser.yy"
                                    { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1066 "parser.tab.cc"
    break;

  case 15: // class_member_list: class_member_list class_member
#line 145 "parser.yy"
                                         { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1072 "parser.tab.cc"
    break;

  case 16: // class_member: ID class_member_tail
#line 151 "parser.yy"
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
#line 1090 "parser.tab.cc"
    break;

  case 17: // class_member: VOLATILE ID COLON type opt_init stmt_end
#line 165 "parser.yy"
    {
      Node* vd = mk("VarDecl");
      vd->children.push_back(mk("Volatile","true"));
      vd->children.push_back(mk("Id", yystack_[4].value.as < std::string > ()));
      vd->children.push_back(yystack_[2].value.as < Node * > ());
      if (yystack_[1].value.as < Node * > ()) vd->children.push_back(yystack_[1].value.as < Node * > ());
      yylhs.value.as < Node * > () = mk1("ClassVar", vd);
    }
#line 1103 "parser.tab.cc"
    break;

  case 18: // class_member: type ID LP param_list_opt RP stmt_block
#line 175 "parser.yy"
    {
      /* Allow type-first method declarations inside classes so semantic tests parse:
         e.g. int aFunc() { ... } */
      yylhs.value.as < Node * > () = mk("MethodDecl");
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[4].value.as < std::string > ()));
      yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
      Node* rt = mk("ReturnType");
      rt->children.push_back(yystack_[5].value.as < Node * > ());
      yylhs.value.as < Node * > ()->children.push_back(rt);
      yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1119 "parser.tab.cc"
    break;

  case 19: // class_member_tail: COLON type opt_init stmt_end
#line 190 "parser.yy"
    {
      Node* vd = mk("VarDecl");
      vd->children.push_back(mk("Volatile","false"));
      vd->children.push_back(mk("Id", ""));  /* placeholder; will be overwritten */
      vd->children.push_back(yystack_[2].value.as < Node * > ());
      if (yystack_[1].value.as < Node * > ()) vd->children.push_back(yystack_[1].value.as < Node * > ());
      yylhs.value.as < Node * > () = mk1("ClassVar", vd);
    }
#line 1132 "parser.tab.cc"
    break;

  case 20: // class_member_tail: COLON type LP param_list_opt RP stmt_block
#line 200 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("MethodDecl");
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", ""));   /* placeholder; will be overwritten */
      yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
      Node* rt = mk("ReturnType");
      rt->children.push_back(yystack_[4].value.as < Node * > ());
      yylhs.value.as < Node * > ()->children.push_back(rt);
      yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1146 "parser.tab.cc"
    break;

  case 21: // class_member_tail: LP param_list_opt RP COLON type stmt_block
#line 211 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("MethodDecl");
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", ""));   /* placeholder; will be overwritten */
      yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
      Node* rt = mk("ReturnType");
      rt->children.push_back(yystack_[1].value.as < Node * > ());
      yylhs.value.as < Node * > ()->children.push_back(rt);
      yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1160 "parser.tab.cc"
    break;

  case 22: // param_list_opt: %empty
#line 224 "parser.yy"
                { yylhs.value.as < Node * > () = mk("Params"); }
#line 1166 "parser.tab.cc"
    break;

  case 23: // param_list_opt: param_list
#line 225 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1172 "parser.tab.cc"
    break;

  case 24: // param_list: param
#line 229 "parser.yy"
                          { yylhs.value.as < Node * > () = mk("Params"); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1178 "parser.tab.cc"
    break;

  case 25: // param_list: param_list COMMA param
#line 230 "parser.yy"
                           { yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1184 "parser.tab.cc"
    break;

  case 26: // param: ID COLON type
#line 235 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("Param");
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[2].value.as < std::string > ()));
      yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1194 "parser.tab.cc"
    break;

  case 27: // entry: MAIN LP RP COLON INT_TYPE stmt_block
#line 245 "parser.yy"
            { yylhs.value.as < Node * > () = mk("Entry"); yylhs.value.as < Node * > ()->children.push_back(mk("ReturnType", "int")); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1200 "parser.tab.cc"
    break;

  case 28: // stmt_block: LBRACE stmt_list RBRACE
#line 250 "parser.yy"
 { yylhs.value.as < Node * > () = mk("StmtBlock"); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 1206 "parser.tab.cc"
    break;

  case 29: // stmt_list: %empty
#line 254 "parser.yy"
                           { yylhs.value.as < Node * > () = mk("Stmts"); }
#line 1212 "parser.tab.cc"
    break;

  case 30: // stmt_list: stmt_list NEWLINE
#line 255 "parser.yy"
                           { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1218 "parser.tab.cc"
    break;

  case 31: // stmt_list: stmt_list stmt
#line 256 "parser.yy"
                           { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1224 "parser.tab.cc"
    break;

  case 32: // stmt_end: NEWLINE
#line 261 "parser.yy"
            { yylhs.value.as < Node * > () = mk("StmtEnd"); }
#line 1230 "parser.tab.cc"
    break;

  case 33: // stmt: stmt_block stmt_end
#line 265 "parser.yy"
                        { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1236 "parser.tab.cc"
    break;

  case 34: // stmt: stmt_nb
#line 266 "parser.yy"
            { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1242 "parser.tab.cc"
    break;

  case 35: // stmt_body: stmt_block
#line 270 "parser.yy"
               { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1248 "parser.tab.cc"
    break;

  case 36: // stmt_body: stmt_nb
#line 271 "parser.yy"
               { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1254 "parser.tab.cc"
    break;

  case 37: // stmt_nb: var_decl stmt_end
#line 275 "parser.yy"
                      { yylhs.value.as < Node * > () = mk1("VarStmt", yystack_[1].value.as < Node * > ()); }
#line 1260 "parser.tab.cc"
    break;

  case 38: // stmt_nb: expr ASSIGN expr stmt_end
#line 276 "parser.yy"
                              { yylhs.value.as < Node * > () = mk3("AssignStmt", yystack_[3].value.as < Node * > (), mk("Op", ":="), yystack_[1].value.as < Node * > ()); }
#line 1266 "parser.tab.cc"
    break;

  case 39: // stmt_nb: expr stmt_end
#line 277 "parser.yy"
                  { yylhs.value.as < Node * > () = mk1("ExprStmt", yystack_[1].value.as < Node * > ()); }
#line 1272 "parser.tab.cc"
    break;

  case 40: // stmt_nb: IF LP expr RP opt_newlines stmt_body
#line 279 "parser.yy"
      { yylhs.value.as < Node * > () = mk2("IfStmt", yystack_[3].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1278 "parser.tab.cc"
    break;

  case 41: // stmt_nb: IF LP expr RP opt_newlines stmt_body ELSE opt_newlines stmt_body
#line 281 "parser.yy"
      { yylhs.value.as < Node * > () = mk3("IfElseStmt", yystack_[6].value.as < Node * > (), yystack_[3].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1284 "parser.tab.cc"
    break;

  case 42: // stmt_nb: FOR LP for_init_opt COMMA for_cond_opt COMMA expr ASSIGN expr RP opt_newlines stmt_body
#line 283 "parser.yy"
      {
        Node* n = mk("ForStmt");
        n->children.push_back(yystack_[9].value.as < Node * > ());   /* init */
        n->children.push_back(yystack_[7].value.as < Node * > ());   /* cond */
        n->children.push_back(mk3("Update", yystack_[5].value.as < Node * > (), mk("Op", ":="), yystack_[3].value.as < Node * > ()));
        n->children.push_back(yystack_[0].value.as < Node * > ());  /* body */
        yylhs.value.as < Node * > () = n;
      }
#line 1297 "parser.tab.cc"
    break;

  case 43: // stmt_nb: PRINT LP expr RP stmt_end
#line 291 "parser.yy"
                              { yylhs.value.as < Node * > () = mk1("PrintStmt", yystack_[2].value.as < Node * > ()); }
#line 1303 "parser.tab.cc"
    break;

  case 44: // stmt_nb: READ LP expr RP stmt_end
#line 292 "parser.yy"
                              { yylhs.value.as < Node * > () = mk1("ReadStmt", yystack_[2].value.as < Node * > ()); }
#line 1309 "parser.tab.cc"
    break;

  case 45: // stmt_nb: RETURN expr stmt_end
#line 293 "parser.yy"
                         { yylhs.value.as < Node * > () = mk1("ReturnStmt", yystack_[1].value.as < Node * > ()); }
#line 1315 "parser.tab.cc"
    break;

  case 46: // stmt_nb: BREAK stmt_end
#line 294 "parser.yy"
                   { yylhs.value.as < Node * > () = mk("BreakStmt"); }
#line 1321 "parser.tab.cc"
    break;

  case 47: // stmt_nb: CONTINUE stmt_end
#line 295 "parser.yy"
                      { yylhs.value.as < Node * > () = mk("ContinueStmt"); }
#line 1327 "parser.tab.cc"
    break;

  case 48: // for_init_opt: %empty
#line 299 "parser.yy"
                { yylhs.value.as < Node * > () = mk("ForInitEmpty"); }
#line 1333 "parser.tab.cc"
    break;

  case 49: // for_init_opt: for_init
#line 300 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1339 "parser.tab.cc"
    break;

  case 50: // for_init: var_decl
#line 304 "parser.yy"
                            { yylhs.value.as < Node * > () = mk1("ForInitVar", yystack_[0].value.as < Node * > ()); }
#line 1345 "parser.tab.cc"
    break;

  case 51: // for_init: expr ASSIGN expr
#line 305 "parser.yy"
                          { yylhs.value.as < Node * > () = mk3("ForInitAssign", yystack_[2].value.as < Node * > (), mk("Op", ":="), yystack_[0].value.as < Node * > ()); }
#line 1351 "parser.tab.cc"
    break;

  case 52: // for_cond_opt: %empty
#line 309 "parser.yy"
                { yylhs.value.as < Node * > () = mk("ForCondEmpty"); }
#line 1357 "parser.tab.cc"
    break;

  case 53: // for_cond_opt: expr
#line 310 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1363 "parser.tab.cc"
    break;

  case 54: // var_decl: ID COLON type opt_init
#line 314 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("VarDecl");
      yylhs.value.as < Node * > ()->children.push_back(mk("Volatile","false"));
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[3].value.as < std::string > ()));
      yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
      if (yystack_[0].value.as < Node * > ()) yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1375 "parser.tab.cc"
    break;

  case 55: // var_decl: VOLATILE ID COLON type opt_init
#line 322 "parser.yy"
    {
      yylhs.value.as < Node * > () = mk("VarDecl");
      yylhs.value.as < Node * > ()->children.push_back(mk("Volatile","true"));
      yylhs.value.as < Node * > ()->children.push_back(mk("Id", yystack_[3].value.as < std::string > ()));
      yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
      if (yystack_[0].value.as < Node * > ()) yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1387 "parser.tab.cc"
    break;

  case 56: // opt_init: %empty
#line 333 "parser.yy"
                { yylhs.value.as < Node * > () = nullptr; }
#line 1393 "parser.tab.cc"
    break;

  case 57: // opt_init: ASSIGN expr
#line 334 "parser.yy"
                { yylhs.value.as < Node * > () = mk1("Init", yystack_[0].value.as < Node * > ()); }
#line 1399 "parser.tab.cc"
    break;

  case 58: // type: base_type array_opt
#line 338 "parser.yy"
                        { yylhs.value.as < Node * > () = mk2("Type", yystack_[1].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1405 "parser.tab.cc"
    break;

  case 59: // type: ID
#line 339 "parser.yy"
                        { yylhs.value.as < Node * > () = mk("TypeName", yystack_[0].value.as < std::string > ()); }
#line 1411 "parser.tab.cc"
    break;

  case 60: // type: VOID
#line 340 "parser.yy"
                        { yylhs.value.as < Node * > () = mk("Type", "void"); }
#line 1417 "parser.tab.cc"
    break;

  case 61: // base_type: INT_TYPE
#line 344 "parser.yy"
               { yylhs.value.as < Node * > () = mk("BaseType", "int"); }
#line 1423 "parser.tab.cc"
    break;

  case 62: // base_type: FLOAT_TYPE
#line 345 "parser.yy"
               { yylhs.value.as < Node * > () = mk("BaseType", "float"); }
#line 1429 "parser.tab.cc"
    break;

  case 63: // base_type: BOOLEAN
#line 346 "parser.yy"
               { yylhs.value.as < Node * > () = mk("BaseType", "boolean"); }
#line 1435 "parser.tab.cc"
    break;

  case 64: // array_opt: %empty
#line 350 "parser.yy"
                         { yylhs.value.as < Node * > () = mk("Array", "false"); }
#line 1441 "parser.tab.cc"
    break;

  case 65: // array_opt: LBRACK RBRACK
#line 351 "parser.yy"
                         { yylhs.value.as < Node * > () = mk("Array", "true"); }
#line 1447 "parser.tab.cc"
    break;

  case 66: // expr: expr_or
#line 355 "parser.yy"
               { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1453 "parser.tab.cc"
    break;

  case 67: // expr_or: expr_or OR expr_and
#line 358 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("OrExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1459 "parser.tab.cc"
    break;

  case 68: // expr_or: expr_and
#line 359 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1465 "parser.tab.cc"
    break;

  case 69: // expr_and: expr_and AND expr_cmp
#line 363 "parser.yy"
                          { yylhs.value.as < Node * > () = mk2("AndExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1471 "parser.tab.cc"
    break;

  case 70: // expr_and: expr_cmp
#line 364 "parser.yy"
                          { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1477 "parser.tab.cc"
    break;

  case 71: // expr_cmp: expr_add LT expr_add
#line 368 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("LtExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1483 "parser.tab.cc"
    break;

  case 72: // expr_cmp: expr_add GT expr_add
#line 369 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("GtExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1489 "parser.tab.cc"
    break;

  case 73: // expr_cmp: expr_add LE expr_add
#line 370 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("LeExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1495 "parser.tab.cc"
    break;

  case 74: // expr_cmp: expr_add GE expr_add
#line 371 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("GeExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1501 "parser.tab.cc"
    break;

  case 75: // expr_cmp: expr_add EQ expr_add
#line 372 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("EqExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1507 "parser.tab.cc"
    break;

  case 76: // expr_cmp: expr_add NE expr_add
#line 373 "parser.yy"
                         { yylhs.value.as < Node * > () = mk2("NeExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1513 "parser.tab.cc"
    break;

  case 77: // expr_cmp: expr_add
#line 374 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1519 "parser.tab.cc"
    break;

  case 78: // expr_add: expr_add PLUSOP expr_mul
#line 378 "parser.yy"
                              { yylhs.value.as < Node * > () = mk2("AddExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1525 "parser.tab.cc"
    break;

  case 79: // expr_add: expr_add MINUSOP expr_mul
#line 379 "parser.yy"
                              { yylhs.value.as < Node * > () = mk2("SubExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1531 "parser.tab.cc"
    break;

  case 80: // expr_add: expr_mul
#line 380 "parser.yy"
                              { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1537 "parser.tab.cc"
    break;

  case 81: // expr_mul: expr_mul MULTOP expr_pow
#line 384 "parser.yy"
                             { yylhs.value.as < Node * > () = mk2("MulExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1543 "parser.tab.cc"
    break;

  case 82: // expr_mul: expr_mul DIVOP expr_pow
#line 385 "parser.yy"
                             { yylhs.value.as < Node * > () = mk2("DivExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1549 "parser.tab.cc"
    break;

  case 83: // expr_mul: expr_pow
#line 386 "parser.yy"
                             { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1555 "parser.tab.cc"
    break;

  case 84: // expr_pow: expr_unary POWOP expr_pow
#line 390 "parser.yy"
                              { yylhs.value.as < Node * > () = mk2("PowExpr", yystack_[2].value.as < Node * > (), yystack_[0].value.as < Node * > ()); }
#line 1561 "parser.tab.cc"
    break;

  case 85: // expr_pow: expr_unary
#line 391 "parser.yy"
                              { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1567 "parser.tab.cc"
    break;

  case 86: // expr_unary: NOT expr_unary
#line 395 "parser.yy"
                              { yylhs.value.as < Node * > () = mk1("NotExpr", yystack_[0].value.as < Node * > ()); }
#line 1573 "parser.tab.cc"
    break;

  case 87: // expr_unary: MINUSOP expr_unary
#line 396 "parser.yy"
                                    { yylhs.value.as < Node * > () = mk1("NegExpr", yystack_[0].value.as < Node * > ()); }
#line 1579 "parser.tab.cc"
    break;

  case 88: // expr_unary: expr_postfix
#line 397 "parser.yy"
                 { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1585 "parser.tab.cc"
    break;

  case 89: // expr_postfix: expr_postfix LBRACK expr RBRACK
#line 402 "parser.yy"
    {
      Node* n = mk("IndexExpr");
      n->children.push_back(yystack_[3].value.as < Node * > ());
      n->children.push_back(yystack_[1].value.as < Node * > ());
      yylhs.value.as < Node * > () = n;
    }
#line 1596 "parser.tab.cc"
    break;

  case 90: // expr_postfix: expr_postfix DOT LENGTH
#line 409 "parser.yy"
    {
      Node* n = mk("LengthExpr");
      n->children.push_back(yystack_[2].value.as < Node * > ());
      yylhs.value.as < Node * > () = n;
    }
#line 1606 "parser.tab.cc"
    break;

  case 91: // expr_postfix: expr_postfix DOT ID
#line 415 "parser.yy"
    {
      Node* n = mk("FieldExpr");
      n->children.push_back(yystack_[2].value.as < Node * > ());
      n->children.push_back(mk("Id", yystack_[0].value.as < std::string > ()));
      yylhs.value.as < Node * > () = n;
    }
#line 1617 "parser.tab.cc"
    break;

  case 92: // expr_postfix: expr_postfix LP args_opt RP
#line 422 "parser.yy"
    {
      Node* n = mk("CallExpr");
      n->children.push_back(yystack_[3].value.as < Node * > ());
      n->children.push_back(yystack_[1].value.as < Node * > () ? yystack_[1].value.as < Node * > () : mk("Args"));
      yylhs.value.as < Node * > () = n;
    }
#line 1628 "parser.tab.cc"
    break;

  case 93: // expr_postfix: primary
#line 429 "parser.yy"
    { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1634 "parser.tab.cc"
    break;

  case 94: // primary: INT
#line 433 "parser.yy"
           { yylhs.value.as < Node * > () = mk("Int", yystack_[0].value.as < std::string > ()); }
#line 1640 "parser.tab.cc"
    break;

  case 95: // primary: FLOAT
#line 434 "parser.yy"
           { yylhs.value.as < Node * > () = mk("Float", yystack_[0].value.as < std::string > ()); }
#line 1646 "parser.tab.cc"
    break;

  case 96: // primary: TRUE
#line 435 "parser.yy"
           { yylhs.value.as < Node * > () = mk("Bool", "true"); }
#line 1652 "parser.tab.cc"
    break;

  case 97: // primary: FALSE
#line 436 "parser.yy"
           { yylhs.value.as < Node * > () = mk("Bool", "false"); }
#line 1658 "parser.tab.cc"
    break;

  case 98: // primary: ID
#line 437 "parser.yy"
          { yylhs.value.as < Node * > () = mk("Id", yystack_[0].value.as < std::string > ()); }
#line 1664 "parser.tab.cc"
    break;

  case 99: // primary: base_type LBRACK args RBRACK
#line 439 "parser.yy"
    {
      Node* n = mk("ArrayLiteral");
      n->children.push_back(yystack_[3].value.as < Node * > ());                       
      n->children.push_back(yystack_[1].value.as < Node * > ());
      yylhs.value.as < Node * > () = n;
    }
#line 1675 "parser.tab.cc"
    break;

  case 100: // primary: LP expr RP
#line 446 "parser.yy"
               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1681 "parser.tab.cc"
    break;

  case 101: // args_opt: %empty
#line 454 "parser.yy"
                { yylhs.value.as < Node * > () = nullptr; }
#line 1687 "parser.tab.cc"
    break;

  case 102: // args_opt: args
#line 455 "parser.yy"
                { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1693 "parser.tab.cc"
    break;

  case 103: // args: expr
#line 459 "parser.yy"
                         { yylhs.value.as < Node * > () = mk("Args"); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1699 "parser.tab.cc"
    break;

  case 104: // args: args COMMA expr
#line 460 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > (); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1705 "parser.tab.cc"
    break;


#line 1709 "parser.tab.cc"

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


  const short parser::yypact_ninf_ = -178;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       9,  -178,    40,    15,  -178,   174,  -178,    18,  -178,    39,
      -8,    84,    37,    18,  -178,  -178,  -178,    99,    99,    99,
    -178,  -178,  -178,  -178,    73,    79,    99,    84,    84,    83,
      88,  -178,  -178,    84,  -178,  -178,    84,    80,    67,    91,
      93,  -178,    12,    47,  -178,   105,    54,  -178,    11,    89,
     114,   100,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,   103,    99,    31,    84,  -178,  -178,    99,    99,  -178,
    -178,    99,    99,  -178,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    13,
    -178,  -178,   111,   104,    11,   118,   120,    81,  -178,   121,
     119,  -178,  -178,   136,  -178,   126,   127,  -178,    61,    84,
      93,  -178,    47,    47,    85,    85,    85,    85,    85,    85,
    -178,  -178,  -178,   128,   124,   137,  -178,  -178,    99,  -178,
     141,  -178,   111,  -178,   134,  -178,  -178,    99,    99,    84,
      84,  -178,    99,  -178,  -178,  -178,  -178,  -178,  -178,   130,
     125,   138,   219,   142,  -178,  -178,  -178,  -178,  -178,  -178,
      -7,  -178,   166,  -178,   169,     9,  -178,   144,  -178,    99,
     167,   172,    11,  -178,   152,   162,  -178,  -178,   173,   157,
     164,   160,  -178,    19,    11,   172,   219,    99,    11,   161,
     172,   172,    84,   111,   168,  -178,   170,  -178,    11,  -178,
     171,  -178,    84,     9,  -178,     9,     9,  -178,  -178,   219,
    -178,  -178,  -178
  };

  const signed char
  parser::yydefact_[] =
  {
       4,    29,     0,     9,     7,     0,     1,     0,     5,     0,
       0,     0,     0,    98,    94,    95,    30,     0,     0,     0,
      28,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,    96,    97,     0,    31,    34,     0,     0,     0,    66,
      68,    70,    77,    80,    83,    85,    88,    93,     0,     0,
       0,     0,    10,     7,    32,     6,     3,     8,    98,    87,
      86,     0,     0,    48,     0,    46,    47,     0,     0,    33,
      37,     0,     0,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
      59,    60,    56,    64,     0,     0,     0,     0,   100,     0,
       0,    49,    50,     0,    45,     0,     0,   103,     0,     0,
      67,    69,    78,    79,    71,    72,    73,    74,    75,    76,
      81,    82,    84,     0,   102,     0,    91,    90,     0,    54,
       0,    58,    56,    13,     0,     2,     7,    52,     0,     0,
       0,    99,     0,    38,    92,    89,    57,    65,    55,     0,
      12,     0,     0,     0,    53,    51,    43,    44,   104,     7,
      59,    14,     0,    15,     0,     0,    35,    40,    36,     0,
      11,    22,     0,    16,     0,     0,    27,     7,     0,     0,
       0,    23,    24,    56,     0,    22,     0,     0,     0,     0,
       0,    22,     0,    56,     0,    41,     0,    26,     0,    25,
       0,    19,     0,     0,     7,     0,     0,    17,    18,     0,
      21,    20,    42
  };

  const short
  parser::yypgoto_[] =
  {
    -178,  -178,  -178,   -50,  -178,  -178,  -178,  -178,  -178,  -178,
    -100,  -178,    -1,  -178,     0,  -178,   -26,  -178,  -177,   187,
    -178,  -178,  -178,     5,  -121,   -90,   -31,  -178,   -13,  -178,
     123,   129,    57,    20,   -15,    82,  -178,  -178,  -178,   113
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,    12,    10,    52,   149,   150,   163,   173,
     180,   181,   182,    53,   166,     5,    55,    34,   167,   168,
     100,   101,   153,    36,   129,    92,    37,   131,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   123,   108
  };

  const unsigned char
  parser::yytable_[] =
  {
       4,    65,    66,    97,   132,    33,    61,    69,    11,   195,
      70,   148,    73,    64,    90,   171,   126,    93,     7,    76,
      77,     8,   172,    50,    51,    78,    79,    80,    81,    82,
      83,   128,   212,     1,    13,    14,    15,    56,   104,    17,
       6,   191,    49,    57,    21,    22,    23,    48,    91,    99,
     103,     9,    18,    19,   105,   106,    84,    85,   107,   109,
     164,   127,   192,    93,    21,    22,    23,     9,   102,   120,
     121,   122,   202,    54,   107,   125,    87,    31,    32,    72,
      88,   135,   183,   143,    89,   194,   152,    57,   141,   142,
      54,   200,    76,    77,   193,    62,   112,   113,   197,    59,
      60,    63,    58,    14,    15,    67,    71,    17,   205,   170,
      68,    74,    75,   156,   157,   146,    86,    95,    94,    93,
      18,    19,    96,   128,   154,   155,    98,   186,   160,   158,
     130,   161,    21,    22,    23,   114,   115,   116,   117,   118,
     119,    93,   133,   134,   136,    31,    32,   137,   138,   139,
     140,   144,   142,    93,   209,   159,   178,    93,    21,    22,
      23,   162,    91,   151,   145,   176,   201,    93,   147,   174,
     169,   165,   175,    57,   196,   179,   207,    13,    14,    15,
      16,   184,    17,   177,   185,   187,   188,   189,   190,   199,
     198,   203,    35,   204,   206,    18,    19,   110,     1,    20,
     124,     0,     0,   208,   111,   210,   211,    21,    22,    23,
       9,     0,    24,     0,    25,    26,    27,    28,    29,    30,
      31,    32,    13,    14,    15,    57,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    19,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,     9,     0,    24,     0,    25,
      26,    27,    28,    29,    30,    31,    32
  };

  const short
  parser::yycheck_[] =
  {
       0,    27,    28,    53,    94,     5,    19,    33,     3,   186,
      36,   132,    38,    26,     3,    22,     3,    48,     3,     7,
       8,     6,    29,    31,    32,    13,    14,    15,    16,    17,
      18,    12,   209,    24,     3,     4,     5,     0,    64,     8,
       0,    22,     3,     6,    33,    34,    35,    29,    37,    62,
      63,    36,    21,    22,    67,    68,     9,    10,    71,    72,
     150,    48,   183,    94,    33,    34,    35,    36,    63,    84,
      85,    86,   193,     6,    87,    88,    22,    46,    47,    12,
      26,     0,   172,   109,    30,   185,   136,     6,    27,    28,
       6,   191,     7,     8,   184,    22,    76,    77,   188,    17,
      18,    22,     3,     4,     5,    22,    26,     8,   198,   159,
      22,    20,    19,   139,   140,   128,    11,     3,    29,   150,
      21,    22,    22,    12,   137,   138,    23,   177,     3,   142,
      26,     6,    33,    34,    35,    78,    79,    80,    81,    82,
      83,   172,    24,    23,    23,    46,    47,    28,    12,    23,
      23,    23,    28,   184,   204,    25,   169,   188,    33,    34,
      35,    36,    37,    29,    27,   165,   192,   198,    27,     3,
      28,    33,     3,     6,   187,     3,   202,     3,     4,     5,
       6,    29,     8,    39,    22,    12,    29,    23,    28,   190,
      29,    23,     5,    23,    23,    21,    22,    74,    24,    25,
      87,    -1,    -1,   203,    75,   205,   206,    33,    34,    35,
      36,    -1,    38,    -1,    40,    41,    42,    43,    44,    45,
      46,    47,     3,     4,     5,     6,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    -1,    38,    -1,    40,
      41,    42,    43,    44,    45,    46,    47
  };

  const signed char
  parser::yystos_[] =
  {
       0,    24,    52,    53,    65,    66,     0,     3,     6,    36,
      55,    74,    54,     3,     4,     5,     6,     8,    21,    22,
      25,    33,    34,    35,    38,    40,    41,    42,    43,    44,
      45,    46,    47,    65,    68,    70,    74,    77,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    29,     3,
      31,    32,    56,    64,     6,    67,     0,     6,     3,    86,
      86,    79,    22,    22,    79,    67,    67,    22,    22,    67,
      67,    26,    12,    67,    20,    19,     7,     8,    13,    14,
      15,    16,    17,    18,     9,    10,    11,    22,    26,    30,
       3,    37,    76,    77,    29,     3,    22,    54,    23,    79,
      71,    72,    74,    79,    67,    79,    79,    79,    90,    79,
      81,    82,    84,    84,    83,    83,    83,    83,    83,    83,
      85,    85,    85,    89,    90,    79,     3,    48,    12,    75,
      26,    78,    76,    24,    23,     0,    23,    28,    12,    23,
      23,    27,    28,    67,    23,    27,    79,    27,    75,    57,
      58,    29,    54,    73,    79,    79,    67,    67,    79,    25,
       3,     6,    36,    59,    76,    33,    65,    69,    70,    28,
      54,    22,    29,    60,     3,     3,    65,    39,    79,     3,
      61,    62,    63,    76,    29,    22,    54,    12,    29,    23,
      28,    22,    75,    76,    61,    69,    79,    76,    29,    63,
      61,    67,    75,    23,    23,    76,    23,    67,    65,    54,
      65,    65,    69
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    51,    52,    52,    53,    53,    53,    54,    54,    55,
      55,    56,    57,    58,    58,    58,    59,    59,    59,    60,
      60,    60,    61,    61,    62,    62,    63,    64,    65,    66,
      66,    66,    67,    68,    68,    69,    69,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    74,    74,    75,    75,    76,    76,
      76,    77,    77,    77,    78,    78,    79,    80,    80,    81,
      81,    82,    82,    82,    82,    82,    82,    82,    83,    83,
      83,    84,    84,    84,    85,    85,    86,    86,    86,    87,
      87,    87,    87,    87,    88,    88,    88,    88,    88,    88,
      88,    89,    89,    90,    90
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     5,     3,     0,     2,     3,     0,     2,     0,
       2,     6,     1,     0,     2,     2,     2,     6,     6,     4,
       6,     6,     0,     1,     1,     3,     3,     6,     3,     0,
       2,     2,     1,     2,     1,     1,     1,     2,     4,     2,
       6,     9,    12,     5,     5,     3,     2,     2,     0,     1,
       1,     3,     0,     1,     4,     5,     0,     2,     2,     1,
       1,     1,     1,     1,     0,     2,     1,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     1,     2,     2,     1,     4,
       3,     3,     4,     1,     1,     1,     1,     1,     1,     4,
       3,     0,     1,     1,     3
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
  "stmt_list", "stmt_end", "stmt", "stmt_body", "stmt_nb", "for_init_opt",
  "for_init", "for_cond_opt", "var_decl", "opt_init", "type", "base_type",
  "array_opt", "expr", "expr_or", "expr_and", "expr_cmp", "expr_add",
  "expr_mul", "expr_pow", "expr_unary", "expr_postfix", "primary",
  "args_opt", "args", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    94,    94,   101,   114,   115,   116,   120,   121,   125,
     126,   130,   139,   143,   144,   145,   150,   164,   173,   189,
     198,   209,   224,   225,   229,   230,   234,   244,   249,   254,
     255,   256,   261,   265,   266,   270,   271,   275,   276,   277,
     278,   280,   282,   291,   292,   293,   294,   295,   299,   300,
     304,   305,   309,   310,   313,   321,   333,   334,   338,   339,
     340,   344,   345,   346,   350,   351,   355,   358,   359,   363,
     364,   368,   369,   370,   371,   372,   373,   374,   378,   379,
     380,   384,   385,   386,   390,   391,   395,   396,   397,   401,
     408,   414,   421,   428,   433,   434,   435,   436,   437,   438,
     446,   454,   455,   459,   460
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
#line 2328 "parser.tab.cc"

#line 463 "parser.yy"
