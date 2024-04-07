%{

#include "Data_File.h"
#include "Parser.tab.h"
int start_line;
const char *operations[] = {
    "==",
    "!=",
    "<=",
    ">=",
    "<",
    ">",
    "+",
    "-",
    "/",
    "*",
    "||",
    "&&",
    "!",
};

/*
    Refering to the return statements: definitions of terminals (capital letters), relational operations,
    addition and subtraction (addop), multiplication and division (mulop), logical operations,
    identifiers and numbers.
    NOTE: id names, a number's type and value and some of the operations are forwarded from here to the nodes of the parse tree (that represent non-terminals or terminals) 
    fields as defined in Parser.y.
*/

%}

%x comment
%%

"/*"         start_line = yylineno; BEGIN(comment);

<comment>[^*\n]*        ;
<comment>"*"+[^*/\n]*   ;
<comment>\n             yylineno++;
<comment>"*/"           BEGIN(INITIAL);
<comment><<EOF>>        output_Error_Msg(INCOMPLETE_COMMENT); return  0; /* Examines wheter a comment is complete */


"break"  {return BREAK;}

"case" {return CASE;}

"default" {return DEFAULT;}

"else" {return ELSE;}

"float" {yylval.en.idtype = DOUBLE; return FLOAT;}

"if" {return IF;}

"input" {return INPUT;}

"int" {yylval.en.idtype = INTEGER; return INT;}

"output" {return OUTPUT;}

"switch" {return SWITCH;}

"while" {return WHILE;}



"(" {return  '('; }

")" {return  ')'; }

"{" {return  '{'; }

"}" {return  '}'; }

"," {return  ','; }

":" {return  ':'; }

";" {return  ';'; }

"=" {return  '='; }


"==" |
"!=" |
"<=" |
">=" |
"<" |
">"  {yylval.op = select_OP(yytext); return RELOP;}


"+" |
"-" {yylval.op = select_OP(yytext); return ADDOP;}

"/" | 
"*" {yylval.op = select_OP(yytext); return MULOP;}


"||" {yylval.op = OR_GATE; return OR;}

"&&" {yylval.op = AND_GATE; return AND;}

"!" {yylval.op = NOT_GATE; return NOT;}



"static_cast<int>"   {yylval.en.idtype = INTEGER; return CAST;}
"static_cast<float>" {yylval.en.idtype = DOUBLE; return CAST;}



[+-]?[0-9]+ {
    
    if (integer_Errors())  
    { 
        yylval.en.idtype = INTEGER;
        strcpy(yylval.en.id, yytext); 
        return  NUM;
    }
}

[+-]?[0-9]+[.][0-9]+ {
    
    if (float_Errors()) 
    {
        yylval.en.idtype = DOUBLE; 
        strcpy(yylval.en.id, yytext); 
        return  NUM;
    }
}

[a-zA-Z0-9]+ {if (id_Errors()) {strcpy(yylval.en.id, yytext); return  ID;}}


[\n] {yylineno++;}


. {examine_Error();} 

%%

int yywrap()
{
    return 1;
}
