/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */

%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */

%}
%option  yylineno
%option  case-insensitive

%x  COMMENT


/*
 * Define names for regular expressions here.
 */


CLASS          ?i:class
ELSE           ?i:else
FI             ?i:fi
IF             (?i:if)
IN             ?i:in
INHERITS       ?i:inherits
LET            ?i:let
LOOP           ?i:loop
POOL           ?i:pool
THEN           ?i:then
WHILE          ?i:while
CASE           ?i:case
ESAC           ?i:esac
OF             ?i:of
DARROW          =>
NEW            ?i:new
ISVOID         ?i:isvoid
CHAR           [A-Za-z]
DIGIT          [0-9]
NOT            ?i:not
TRUE           (?-i:t)(?i:rue)
FALSE          (?-i:f)(?i:alse)
BOOL           {TRUE}|{FALSE}
NEWLINE        "\n"
%%

 /*
  *  Nested comments
  */


 /*
  *  The multiple-character operators.
  */
  
"/*"          BEGIN(COMMENT);
<COMMENT>[^*\n]* {}
<COMMENT>"*"+[^*/\n]*  {}
<COMMENT>\n     curr_lineno++;
<COMMENT>"*"+"/"  { printf("end comment!\n");  BEGIN(INITIAL);}


 
\n              {} 
{NEWLINE}       {}	
		   
		
{CLASS}         { cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno; 
				  return CLASS;
                }	
{ELSE}          { cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return ELSE;
                }				
{FI}    		{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return FI;
                }	
{IF}            { cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
                  return IF;
                }				
{IN}		   	{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return IN;
                }	
{INHERITS}		{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return INHERITS;
                }	
	
{LET}			{ cool_yylval.symbol = inttable.add_string(yytext);
                 curr_lineno = yylineno;
				  return LET;
                }
{LOOP}			{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return LOOP;
                }	
{POOL}      	{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return POOL;
                }	
{THEN}        	{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return THEN;
                }					
{WHILE}			{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return WHILE;
                }	
{CASE}			{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return CASE;
                }	
{ESAC}			{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return ESAC;
                }	
{NEW}			{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return NEW;
                }
{ISVOID}		{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return ISVOID;
                }				
{OF}			{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return OF;
                }	
{NOT}           { cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return NOT;
                }
{BOOL}			{ cool_yylval.symbol = inttable.add_string(yytext);
                  curr_lineno = yylineno;
				  return BOOL_CONST;
                }
		
{DARROW}		{ curr_lineno = yylineno;
				  return (DARROW);  
				 }					
{CHAR}+         { 
                  cool_yylval.symbol = inttable.add_string(yytext); 
                  curr_lineno = yylineno;
                  return STR_CONST;
				}
{DIGIT}+        { cool_yylval.symbol = inttable.add_string(yytext); 
                  curr_lineno = yylineno;                 
                  return INT_CONST;
				}				
 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */


%%
