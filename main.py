from parglare import Parser, Grammar

# sys.setrecursionlimit(2000)

# grammar = Grammar.from_file("fleaux_grammar.pg")
grammar = Grammar.from_string('''
program:
  statement_list?;

statement_list:
  statement+;

statement:
  (let_statement | expression_statement) ';';

let_statement:
  LET identifier '(' parameter_decl_list ')' ':' type LET_EXPR_SEPARATOR expression;

expression_statement:
  expression;

parameter_decl_list:
  parameter+[COMMA];

parameter:
  identifier ':' type;

tuple_type:
  type_list;

type_list:
  type+[COMMA];

type:
  NUMBER | STRING | BOOL | NULL | ANY | identifier | '(' type_list ')';

expression:
  constant |
  identifier |
  '(' expression ')' |
  expression PIPELINE_OPERATOR expression {left, 10} |
  expression PLUS_OPERATOR expression {left, 5} |
  expression MINUS_OPERATOR expression {left, 5} |
  expression DIVIDE_OPERATOR expression {left, 6} |
  expression MULTIPLY_OPERATOR expression {left, 6} |
  expression MODULUS_OPERATOR expression {left, 6} |
  expression EXPONENT_OPERATOR expression {right, 7} |
  expression EQ_OPERATOR expression {left, 4} |
  expression NE_OPERATOR expression {left, 4} |
  expression LT_OPERATOR expression {left, 4} |
  expression GT_OPERATOR expression {left, 4} |
  expression GE_OPERATOR expression {left, 4} |
  expression LE_OPERATOR expression {left, 4} |
  expression OR_OPERATOR expression {left, 1} |
  expression AND_OPERATOR expression {left, 2} |
  expression COMMA expression {left, 1} |
  NOT_OPERATOR expression {right, 3} |
  PLUS_OPERATOR expression {right, 1} |
  MINUS_OPERATOR expression {right, 1};

identifier:
  ID;

constant:
  NUMERICAL_CONSTANT | STRING_LITERAL | TRUE | FALSE | NULL;

LAYOUT: LayoutItem | LAYOUT LayoutItem | EMPTY;
LayoutItem: WS | Comment;

terminals
NUMERICAL_CONSTANT:
  /-?\d+(\.\d+)?(e|E[-+]?\d+)?/;

STRING_LITERAL: /"((\\")|[^"])*"/;
ID: /[a-zA-Z_][a-zA-Z_0-9]*/;

PIPELINE_OPERATOR: "->";
LE_OPERATOR: "<=";
GE_OPERATOR: ">=";
EQ_OPERATOR: "==";
NE_OPERATOR: "!=";
LT_OPERATOR: "<";
GT_OPERATOR: ">";
AND_OPERATOR: "&&";
OR_OPERATOR: "||";

PLUS_OPERATOR: "+";
MINUS_OPERATOR: "-";
DIVIDE_OPERATOR: "/";
MULTIPLY_OPERATOR: "*";
MODULUS_OPERATOR: "%";
EXPONENT_OPERATOR: "^";

NOT_OPERATOR: "!";

LET_EXPR_SEPARATOR: "::";

LET: "let";
NUMBER: "Number";
STRING: "String";
BOOL: "Bool";
NULL: "Null";
TRUE: "True";
FALSE: "False";
ANY: "Any";
COMMA: ',';

WS: /\s+/;
Comment: /\/\/.*/;
''')

actions = {
    "program": lambda _, nodes: nodes[1]
}

parser = Parser(grammar, build_tree=True, debug=True, actions=actions)

result = parser.parse('''
let Multiply2(x : Number) : Number :: (x) -> Multiply -> Println; 
let AddPrint(x : Number, y: Number) : Number :: (x, y) -> Add -> Println;

// y = 4x^7 - x^5
let Polynomial(x : Number) : Number :: ((((4, x) -> Multiply, 7) -> Pow, x) -> Subtract, 5) -> Pow;
let Polynomial2(x : Number) : Number :: ((4*x)^7) - (x^5);
(1, 2) -> AddPrint;
// COMMENT

("Hello, World!") -> Println;
''')

# print(result.to_str())
# for statement in result:
#     print(statement)

