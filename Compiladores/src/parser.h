/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SMCL = 258,
    INTLIT = 259,
    BOOL = 260,
    FLTLIT = 261,
    ID = 262,
    STRING = 263,
    VAR_TYPE = 264,
    DEF = 265,
    IF = 266,
    ELSE = 267,
    THEN = 268,
    RETURN = 269,
    WHILE = 270,
    DO = 271,
    BREAK = 272,
    NEXT = 273,
    CLN = 274,
    ASSIGN = 275,
    OR = 276,
    AND = 277,
    NOT = 278,
    EQUALS = 279,
    LESS = 280,
    LESSEQUALS = 281,
    BIGGER = 282,
    BIGGEREQUALS = 283,
    DIF = 284,
    SUB = 285,
    ADD = 286,
    MUL = 287,
    DIV = 288,
    MOD = 289,
    EXPO = 290,
    NEG = 291,
    LPAR = 292,
    RPAR = 293,
    COMMA = 294,
    LBRK = 295,
    RBRK = 296
  };
#endif
/* Tokens.  */
#define SMCL 258
#define INTLIT 259
#define BOOL 260
#define FLTLIT 261
#define ID 262
#define STRING 263
#define VAR_TYPE 264
#define DEF 265
#define IF 266
#define ELSE 267
#define THEN 268
#define RETURN 269
#define WHILE 270
#define DO 271
#define BREAK 272
#define NEXT 273
#define CLN 274
#define ASSIGN 275
#define OR 276
#define AND 277
#define NOT 278
#define EQUALS 279
#define LESS 280
#define LESSEQUALS 281
#define BIGGER 282
#define BIGGEREQUALS 283
#define DIF 284
#define SUB 285
#define ADD 286
#define MUL 287
#define DIV 288
#define MOD 289
#define EXPO 290
#define NEG 291
#define LPAR 292
#define RPAR 293
#define COMMA 294
#define LBRK 295
#define RBRK 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "ya.y" /* yacc.c:1909  */

    int intlit;
    double fltlit;
    char *str;
    declist declist;
    decl decl;
    stmlist stmlist;
    stm stm;
    explist explist;
    expr expr;
    arglist arglist;
    arg arg;
    idlist idlist;
    type type;

#line 152 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
