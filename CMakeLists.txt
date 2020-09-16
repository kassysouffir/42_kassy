cmake_minimum_required(VERSION 3.0)
project(42sh LANGUAGES C)

add_compile_options(-Wall -Werror -Wextra -pedantic -std=c99 -g)
include_directories(
	${CMAKE_SOURCE_DIR}/src/lexer/
	${CMAKE_SOURCE_DIR}/src/option/
	${CMAKE_SOURCE_DIR}/src/prompt/
	${CMAKE_SOURCE_DIR}/src/execution/
	${CMAKE_SOURCE_DIR}/src/ast/
	${CMAKE_SOURCE_DIR}/src/grammar/
	${CMAKE_SOURCE_DIR}/src/structures/
	${CMAKE_SOURCE_DIR}/src/read/
	${CMAKE_SOURCE_DIR}/src/tools/
	${CMAKE_SOURCE_DIR}/src/variable/
	${CMAKE_SOURCE_DIR}/src/builtin/
)

set(cfiles
src/grammar/rule_shell_command.c
src/grammar/rule_funcdec.c
src/grammar/rule_compound.c
src/grammar/rule_prefix.c
src/grammar/rule_for.c
src/grammar/rule_command.c
src/grammar/rule_while.c
src/grammar/rule_pipeline.c
src/grammar/rule_else.c
src/grammar/rule_until.c
src/grammar/rule_list.c
src/grammar/rule_element.c
src/grammar/rule_and_or.c
src/grammar/rule_simple_command.c
src/grammar/rule_if.c
src/grammar/rule_do_group.c
src/grammar/rule_redir.c

src/variable/variable.c

src/tools/tools.c

src/structures/structures.c

src/read/read.c
src/ast/ast.c

src/option/option.c

src/prompt/prompt.c

src/execution/execution.c

src/lexer/lexer.c
src/lexer/token.c
src/main.c

src/builtin/builtin.c

)

add_custom_target(doc 
	COMMAND doxygen ${CMAKE_SOURCE_DIR}/doc/Doxyfile
	DEPENDS 42sh
)

add_executable(42sh ${cfiles})
target_link_libraries(42sh -lreadline)

add_custom_target(check
    COMMAND python3 ${CMAKE_SOURCE_DIR}/tests/test.py
    DEPENDS 42sh
)
