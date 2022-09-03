课程设计项目文件说明：
1.词法分析器文件夹：
Lexer.cpp文件为任务1所要求的词法分析器的C++源码
Lexer.exe文件为上述cpp文件的可执行文件
lexer_grammar.txt文件为词法分析器的文法
lexer_source.txt文件为源代码
lexer_out.txt文件为词法分析结果，即三元式token序列

2.语法分析器文件夹：
Parser.cpp文件为任务2所要求的语法分析器的C++源码
Parser.exe文件为上述cpp文件的可执行文件
parser_grammar.txt文件为语法分析器的文法
lexer_out.txt文件为词法分析结果，即三元式token序列
action_goto.txt文件为分析过程中生成的ACTION GOTO表
project_set.txt文件为分析过程中生成的项目集表
parser_out.txt文件为语法分析器的分析结果输出

3.语义分析器文件夹：
Analyzer.cpp文件为任务3所要求的语义分析器的C++源码
Analyzer.exe文件为上述cpp文件的可执行文件
lexer_out.txt文件为词法分析结果，即三元式token序列
input_source.txt文件为源代码文件
out.txt为语义分析器的分析结果输出

4.QT图形化界面包装
此文件包含使用Qt进行图形化包装所用的所有.h头文件、.cpp源文件、.ui界面设计文件