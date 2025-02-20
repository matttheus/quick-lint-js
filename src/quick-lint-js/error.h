// Copyright (C) 2020  Matthew Glazar
// See end of file for extended copyright information.

#ifndef QUICK_LINT_JS_ERROR_H
#define QUICK_LINT_JS_ERROR_H

#include <quick-lint-js/char8.h>
#include <quick-lint-js/cli-location.h>
#include <quick-lint-js/language.h>
#include <quick-lint-js/lex.h>
#include <quick-lint-js/location.h>
#include <quick-lint-js/token.h>
#include <quick-lint-js/translation.h>

#define QLJS_X_ERROR_TYPES                                                     \
  QLJS_ERROR_TYPE(                                                             \
      error_assignment_before_variable_declaration, "E001",                    \
      {                                                                        \
        identifier assignment;                                                 \
        identifier declaration;                                                \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("variable assigned before its declaration"),    \
             assignment)                                                       \
          .note(QLJS_TRANSLATABLE("variable declared here"), declaration))     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_assignment_to_const_global_variable, "E002",                       \
      { identifier assignment; },                                              \
                                                                               \
      .error(QLJS_TRANSLATABLE("assignment to const global variable"),         \
             assignment))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_assignment_to_const_variable, "E003",                              \
      {                                                                        \
        identifier declaration;                                                \
        identifier assignment;                                                 \
        variable_kind var_kind;                                                \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("assignment to const variable"), assignment)    \
          .note(QLJS_TRANSLATABLE("const variable declared here"),             \
                declaration))                                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_assignment_to_const_variable_before_its_declaration, "E004",       \
      {                                                                        \
        identifier declaration;                                                \
        identifier assignment;                                                 \
        variable_kind var_kind;                                                \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "assignment to const variable before its declaration"),       \
             assignment)                                                       \
          .note(QLJS_TRANSLATABLE("const variable declared here"),             \
                declaration))                                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_assignment_to_undeclared_variable, "E059",                         \
      { identifier assignment; },                                              \
      .warning(QLJS_TRANSLATABLE("assignment to undeclared variable"),         \
               assignment))                                                    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_await_operator_outside_async, "E162",                              \
      { source_code_span await_operator; },                                    \
      .error(QLJS_TRANSLATABLE("'await' is only allowed in async functions"),  \
             await_operator))                                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_big_int_literal_contains_decimal_point, "E005",                    \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("BigInt literal contains decimal point"),       \
             where))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_big_int_literal_contains_exponent, "E006",                         \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("BigInt literal contains exponent"), where))    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_c_style_for_loop_is_missing_third_component, "E093",               \
      {                                                                        \
        source_code_span expected_last_component;                              \
        source_code_span existing_semicolon;                                   \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "C-style for loop is missing its third component"),           \
             expected_last_component))                                         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_assign_to_variable_named_async_in_for_of_loop, "E082",      \
      { identifier async_identifier; },                                        \
      .error(                                                                  \
          QLJS_TRANSLATABLE(                                                   \
              "assigning to 'async' in a for-of loop requires parentheses"),   \
          async_identifier))                                                   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_declare_await_in_async_function, "E069",                    \
      { identifier name; },                                                    \
      .error(                                                                  \
          QLJS_TRANSLATABLE("cannot declare 'await' inside async function"),   \
          name))                                                               \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_declare_class_named_let, "E007",                            \
      { source_code_span name; },                                              \
      .error(QLJS_TRANSLATABLE("classes cannot be named 'let'"), name))        \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_declare_variable_named_let_with_let, "E008",                \
      { source_code_span name; },                                              \
      .error(QLJS_TRANSLATABLE(                                                \
                 "let statement cannot declare variables named 'let'"),        \
             name))                                                            \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_declare_variable_with_keyword_name, "E124",                 \
      { source_code_span keyword; },                                           \
      .error(QLJS_TRANSLATABLE("cannot declare variable named keyword '{0}'"), \
             keyword))                                                         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_declare_yield_in_generator_function, "E071",                \
      { identifier name; },                                                    \
      .error(QLJS_TRANSLATABLE(                                                \
                 "cannot declare 'yield' inside generator function"),          \
             name))                                                            \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_export_default_variable, "E076",                            \
      { source_code_span declaring_token; },                                   \
      .error(QLJS_TRANSLATABLE(                                                \
                 "cannot declare and export variable with 'export default'"),  \
             declaring_token))                                                 \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_export_let, "E009", { source_code_span export_name; },      \
      .error(QLJS_TRANSLATABLE("cannot export variable named 'let'"),          \
             export_name))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_export_variable_named_keyword, "E144",                      \
      { identifier export_name; },                                             \
      .error(QLJS_TRANSLATABLE("cannot export variable named keyword '{0}'"),  \
             export_name))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_import_let, "E010", { source_code_span import_name; },      \
      .error(QLJS_TRANSLATABLE("cannot import 'let'"), import_name))           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_import_variable_named_keyword, "E145",                      \
      { identifier import_name; },                                             \
      .error(QLJS_TRANSLATABLE("cannot import variable named keyword '{0}'"),  \
             import_name))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_refer_to_private_variable_without_object, "E155",           \
      { identifier private_identifier; },                                      \
      .error(QLJS_TRANSLATABLE("cannot reference private variables without "   \
                               "object; use 'this.'"),                         \
             private_identifier))                                              \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_cannot_update_variable_during_declaration, "E136",                 \
      {                                                                        \
        source_code_span declaring_token;                                      \
        source_code_span updating_operator;                                    \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "cannot update variable with '{0}' while declaring it"),      \
             updating_operator)                                                \
          .note(QLJS_TRANSLATABLE(                                             \
                    "remove '{0}' to update an existing variable"),            \
                declaring_token))                                              \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_catch_without_try, "E117", { source_code_span catch_token; },      \
      .error(QLJS_TRANSLATABLE("unexpected 'catch' without 'try'"),            \
             catch_token))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_class_statement_not_allowed_in_body, "E149",                       \
      {                                                                        \
        statement_kind kind_of_statement;                                      \
        source_code_span expected_body;                                        \
        source_code_span class_keyword;                                        \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("missing body for {1:headlinese}"),             \
             expected_body, kind_of_statement)                                 \
          .note(QLJS_TRANSLATABLE("a class statement is not allowed as the "   \
                                  "body of {1:singular}"),                     \
                class_keyword, kind_of_statement))                             \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_character_disallowed_in_identifiers, "E011",                       \
      { source_code_span character; },                                         \
      .error(QLJS_TRANSLATABLE("character is not allowed in identifiers"),     \
             character))                                                       \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_comma_not_allowed_after_spread_parameter, "E070",                  \
      {                                                                        \
        source_code_span comma;                                                \
        source_code_span spread;                                               \
      },                                                                       \
      .error(                                                                  \
          QLJS_TRANSLATABLE("commas are not allowed after spread parameter"),  \
          comma))                                                              \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_else_has_no_if, "E065", { source_code_span else_token; },          \
      .error(QLJS_TRANSLATABLE("'else' has no corresponding 'if'"),            \
             else_token))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_escaped_character_disallowed_in_identifiers, "E012",               \
      { source_code_span escape_sequence; },                                   \
      .error(QLJS_TRANSLATABLE(                                                \
                 "escaped character is not allowed in identifiers"),           \
             escape_sequence))                                                 \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_escaped_code_point_in_identifier_out_of_range, "E013",             \
      { source_code_span escape_sequence; },                                   \
      .error(QLJS_TRANSLATABLE("code point out of range"), escape_sequence))   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_extra_comma_not_allowed_between_arguments, "E068",                 \
      { source_code_span comma; },                                             \
      .error(QLJS_TRANSLATABLE(                                                \
                 "extra ',' is not allowed between function call arguments"),  \
             comma))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_as_before_imported_namespace_alias, "E126",               \
      {                                                                        \
        source_code_span alias;                                                \
        source_code_span star_token;                                           \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("expected 'as' between '{1}' and '{2}'"),       \
             source_code_span(star_token.begin(), alias.end()), star_token,    \
             alias))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_comma_to_separate_object_literal_entries, "E131",         \
      { source_code_span unexpected_token; },                                  \
      .error(QLJS_TRANSLATABLE("expected ',' between object literal entries"), \
             unexpected_token))                                                \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_expression_before_newline, "E014",                        \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("expected expression before newline"), where))  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_expression_for_switch_case, "E140",                       \
      { source_code_span case_token; },                                        \
      .error(QLJS_TRANSLATABLE("expected expression after 'case'"),            \
             case_token))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_expression_before_semicolon, "E015",                      \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("expected expression before semicolon"),        \
             where))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_from_and_module_specifier, "E129",                        \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("expected 'from \"name_of_module.mjs\"'"),      \
             where))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_from_before_module_specifier, "E128",                     \
      { source_code_span module_specifier; },                                  \
      .error(QLJS_TRANSLATABLE("expected 'from' before module specifier"),     \
             module_specifier))                                                \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_hex_digits_in_unicode_escape, "E016",                     \
      { source_code_span escape_sequence; },                                   \
      .error(QLJS_TRANSLATABLE(                                                \
                 "expected hexadecimal digits in Unicode escape sequence"),    \
             escape_sequence))                                                 \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_left_curly, "E107",                                       \
      { source_code_span expected_left_curly; },                               \
      .error(QLJS_TRANSLATABLE("expected '{{'"), expected_left_curly))         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_right_paren_for_function_call, "E141",                    \
      {                                                                        \
        source_code_span expected_right_paren;                                 \
        source_code_span left_paren;                                           \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("expected ')' to close function call"),         \
             expected_right_paren)                                             \
          .note(QLJS_TRANSLATABLE("function call started here"), left_paren))  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parentheses_around_do_while_condition, "E084",            \
      { source_code_span condition; },                                         \
      .error(QLJS_TRANSLATABLE(                                                \
                 "do-while loop needs parentheses around condition"),          \
             condition))                                                       \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parenthesis_around_do_while_condition, "E085",            \
      {                                                                        \
        source_code_span where;                                                \
        char8 token;                                                           \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "do-while loop is missing '{1}' around condition"),           \
             where, string8_view(&token, 1)))                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parentheses_around_if_condition, "E017",                  \
      { source_code_span condition; },                                         \
      .error(QLJS_TRANSLATABLE(                                                \
                 "if statement needs parentheses around condition"),           \
             condition))                                                       \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parenthesis_around_if_condition, "E018",                  \
      {                                                                        \
        source_code_span where;                                                \
        char8 token;                                                           \
      },                                                                       \
      .error(                                                                  \
          QLJS_TRANSLATABLE("if statement is missing '{1}' around condition"), \
          where, string8_view(&token, 1)))                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parentheses_around_switch_condition, "E091",              \
      { source_code_span condition; },                                         \
      .error(QLJS_TRANSLATABLE(                                                \
                 "switch statement needs parentheses around condition"),       \
             condition))                                                       \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parenthesis_around_switch_condition, "E092",              \
      {                                                                        \
        source_code_span where;                                                \
        char8 token;                                                           \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "switch statement is missing '{1}' around condition"),        \
             where, string8_view(&token, 1)))                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parentheses_around_while_condition, "E087",               \
      { source_code_span condition; },                                         \
      .error(                                                                  \
          QLJS_TRANSLATABLE("while loop needs parentheses around condition"),  \
          condition))                                                          \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parenthesis_around_while_condition, "E088",               \
      {                                                                        \
        source_code_span where;                                                \
        char8 token;                                                           \
      },                                                                       \
      .error(                                                                  \
          QLJS_TRANSLATABLE("while loop is missing '{1}' around condition"),   \
          where, string8_view(&token, 1)))                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parentheses_around_with_expression, "E089",               \
      { source_code_span expression; },                                        \
      .error(QLJS_TRANSLATABLE(                                                \
                 "with statement needs parentheses around expression"),        \
             expression))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_parenthesis_around_with_expression, "E090",               \
      {                                                                        \
        source_code_span where;                                                \
        char8 token;                                                           \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "with statement is missing '{1}' around expression"),         \
             where, string8_view(&token, 1)))                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_expected_variable_name_for_catch, "E135",                          \
      { source_code_span unexpected_token; },                                  \
      .error(QLJS_TRANSLATABLE("expected variable name for 'catch'"),          \
             unexpected_token))                                                \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_exporting_requires_default, "E067",                                \
      { source_code_span expression; },                                        \
      .error(QLJS_TRANSLATABLE("exporting requires 'default'"), expression))   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_exporting_requires_curlies, "E066", { source_code_span names; },   \
      .error(QLJS_TRANSLATABLE("exporting requires '{{' and '}'"), names))     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_exporting_string_name_only_allowed_for_export_from, "E153",        \
      { source_code_span export_name; },                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "forwarding exports are only allowed in export-from"),        \
             export_name))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_finally_without_try, "E118", { source_code_span finally_token; },  \
      .error(QLJS_TRANSLATABLE("unexpected 'finally' without 'try'"),          \
             finally_token))                                                   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_function_statement_not_allowed_in_body, "E148",                    \
      {                                                                        \
        statement_kind kind_of_statement;                                      \
        source_code_span expected_body;                                        \
        source_code_span function_keywords;                                    \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("missing body for {1:headlinese}"),             \
             expected_body, kind_of_statement)                                 \
          .note(                                                               \
              QLJS_TRANSLATABLE("a function statement is not allowed as the "  \
                                "body of {1:singular}"),                       \
              function_keywords, kind_of_statement))                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_generator_function_star_belongs_before_name, "E133",               \
      {                                                                        \
        source_code_span function_name;                                        \
        source_code_span star;                                                 \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "generator function '*' belongs before function name"),       \
             star))                                                            \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_in_disallowed_in_c_style_for_loop, "E108",                         \
      { source_code_span in_token; },                                          \
      .error(QLJS_TRANSLATABLE(                                                \
                 "'in' disallowed in C-style for loop initializer"),           \
             in_token))                                                        \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_indexing_requires_expression, "E075",                              \
      { source_code_span squares; },                                           \
      .error(QLJS_TRANSLATABLE("indexing requires an expression"), squares))   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_invalid_binding_in_let_statement, "E019",                          \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("invalid binding in let statement"), where))    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_invalid_expression_left_of_assignment, "E020",                     \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("invalid expression left of assignment"),       \
             where))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_invalid_hex_escape_sequence, "E060",                               \
      { source_code_span escape_sequence; },                                   \
      .error(QLJS_TRANSLATABLE("invalid hex escape sequence: {0}"),            \
             escape_sequence))                                                 \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_invalid_lone_literal_in_object_literal, "E021",                    \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("invalid lone literal in object literal"),      \
             where))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_invalid_rhs_for_dot_operator, "E074", { source_code_span dot; },   \
      .error(QLJS_TRANSLATABLE(                                                \
                 "'.' operator needs a key name; use + to concatenate "        \
                 "strings; use [] to access with a dynamic key"),              \
             dot))                                                             \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_invalid_utf_8_sequence, "E022", { source_code_span sequence; },    \
      .error(QLJS_TRANSLATABLE("invalid UTF-8 sequence"), sequence))           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_keywords_cannot_contain_escape_sequences, "E023",                  \
      { source_code_span escape_sequence; },                                   \
      .error(QLJS_TRANSLATABLE("keywords cannot contain escape sequences"),    \
             escape_sequence))                                                 \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_legacy_octal_literal_may_not_be_big_int, "E032",                   \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("legacy octal literal may not be BigInt"),      \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_legacy_octal_literal_may_not_contain_underscores, "E152",          \
      { source_code_span underscores; },                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "legacy octal literals may not contain underscores"),         \
             underscores))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_let_with_no_bindings, "E024", { source_code_span where; },         \
      .error(QLJS_TRANSLATABLE("let with no bindings"), where))                \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_lexical_declaration_not_allowed_in_body, "E150",                   \
      {                                                                        \
        statement_kind kind_of_statement;                                      \
        source_code_span expected_body;                                        \
        source_code_span declaring_keyword;                                    \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("missing body for {1:headlinese}"),             \
             expected_body, kind_of_statement)                                 \
          .note(                                                               \
              QLJS_TRANSLATABLE("a lexical declaration is not allowed as the " \
                                "body of {1:singular}"),                       \
              declaring_keyword, kind_of_statement))                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_methods_should_not_use_function_keyword, "E072",                   \
      { source_code_span function_token; },                                    \
      .error(                                                                  \
          QLJS_TRANSLATABLE("methods should not use the 'function' keyword"),  \
          function_token))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_array_close, "E157",                                       \
      {                                                                        \
        source_code_span left_square;                                          \
        source_code_span expected_right_square;                                \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("missing end of array; expected ']'"),          \
             expected_right_square)                                            \
          .note(QLJS_TRANSLATABLE("array started here"), left_square))         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_arrow_function_parameter_list, "E105",                     \
      { source_code_span arrow; },                                             \
      .error(QLJS_TRANSLATABLE("missing parameters for arrow function"),       \
             arrow))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_catch_clause, "E119",                             \
      { source_code_span catch_token; },                                       \
      .error(QLJS_TRANSLATABLE("missing body for catch clause"), catch_token)) \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_class, "E111",                                    \
      { source_code_span class_keyword_and_name_and_heritage; },               \
      .error(QLJS_TRANSLATABLE("missing body for class"),                      \
             class_keyword_and_name_and_heritage))                             \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_do_while_statement, "E101",                       \
      { source_code_span do_token; },                                          \
      .error(QLJS_TRANSLATABLE("missing body for do-while loop"), do_token))   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_finally_clause, "E121",                           \
      { source_code_span finally_token; },                                     \
      .error(QLJS_TRANSLATABLE("missing body for finally clause"),             \
             finally_token))                                                   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_for_statement, "E094",                            \
      { source_code_span for_and_header; },                                    \
      .error(QLJS_TRANSLATABLE("missing body for 'for' loop"),                 \
             for_and_header))                                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_if_statement, "E064",                             \
      { source_code_span if_and_condition; },                                  \
      .error(QLJS_TRANSLATABLE("missing body for 'if' statement"),             \
             if_and_condition))                                                \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_switch_statement, "E106",                         \
      { source_code_span switch_and_condition; },                              \
      .error(QLJS_TRANSLATABLE("missing body for 'switch' statement"),         \
             switch_and_condition))                                            \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_try_statement, "E120",                            \
      { source_code_span try_token; },                                         \
      .error(QLJS_TRANSLATABLE("missing body for try statement"), try_token))  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_body_for_while_statement, "E104",                          \
      { source_code_span while_and_condition; },                               \
      .error(QLJS_TRANSLATABLE("missing body for while loop"),                 \
             while_and_condition))                                             \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_catch_or_finally_for_try_statement, "E122",                \
      {                                                                        \
        source_code_span expected_catch_or_finally;                            \
        source_code_span try_token;                                            \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "missing catch or finally clause for try statement"),         \
             expected_catch_or_finally)                                        \
          .note(QLJS_TRANSLATABLE("try statement starts here"), try_token))    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_catch_variable_between_parentheses, "E130",                \
      {                                                                        \
        source_code_span left_paren;                                           \
        source_code_span right_paren;                                          \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "missing catch variable name between parentheses"),           \
             source_code_span(left_paren.begin(), right_paren.end())))         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_comma_between_object_literal_entries, "E025",              \
      { source_code_span where; },                                             \
      .error(                                                                  \
          QLJS_TRANSLATABLE("missing comma between object literal entries"),   \
          where))                                                              \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_comma_between_variable_declarations, "E132",               \
      { source_code_span expected_comma; },                                    \
      .error(QLJS_TRANSLATABLE("missing ',' between variable declarations"),   \
             expected_comma))                                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_colon_in_conditional_expression, "E146",                   \
      {                                                                        \
        source_code_span expected_colon;                                       \
        source_code_span question;                                             \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("missing ':' in conditional expression"),       \
             expected_colon)                                                   \
          .note(QLJS_TRANSLATABLE("'?' creates a conditional expression"),     \
                question))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_condition_for_if_statement, "E138",                        \
      { source_code_span if_keyword; },                                        \
      .error(QLJS_TRANSLATABLE("missing condition for if statement"),          \
             if_keyword))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_condition_for_while_statement, "E139",                     \
      { source_code_span while_keyword; },                                     \
      .error(QLJS_TRANSLATABLE("missing condition for while statement"),       \
             while_keyword))                                                   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_condition_for_switch_statement, "E137",                    \
      { source_code_span switch_keyword; },                                    \
      .error(QLJS_TRANSLATABLE("missing condition for switch statement"),      \
             switch_keyword))                                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_expression_between_parentheses, "E078",                    \
      {                                                                        \
        source_code_span left_paren;                                           \
        source_code_span right_paren;                                          \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("missing expression between parentheses"),      \
             source_code_span(left_paren.begin(), right_paren.end())))         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_for_loop_header, "E125", { source_code_span for_token; },  \
      .error(QLJS_TRANSLATABLE("missing header and body for 'for' loop"),      \
             for_token))                                                       \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_for_loop_rhs_or_components_after_expression, "E097",       \
      {                                                                        \
        source_code_span header;                                               \
        source_code_span for_token;                                            \
      },                                                                       \
      .error(                                                                  \
          QLJS_TRANSLATABLE(                                                   \
              "for loop needs an iterable, or condition and update clauses"),  \
          header)                                                              \
          .note(QLJS_TRANSLATABLE(                                             \
                    "use 'while' instead to loop until a condition is false"), \
                for_token))                                                    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_for_loop_rhs_or_components_after_declaration, "E098",      \
      {                                                                        \
        source_code_span header;                                               \
        source_code_span for_token;                                            \
      },                                                                       \
      .error(                                                                  \
          QLJS_TRANSLATABLE(                                                   \
              "for loop needs an iterable, or condition and update clauses"),  \
          header))                                                             \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_function_parameter_list, "E073",                           \
      { source_code_span function_name; },                                     \
      .error(QLJS_TRANSLATABLE("missing function parameter list"),             \
             function_name))                                                   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_header_of_for_loop, "E096", { source_code_span where; },   \
      .error(QLJS_TRANSLATABLE("missing for loop header"), where))             \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_key_for_object_entry, "E154",                              \
      { source_code_span expression; },                                        \
      .error(QLJS_TRANSLATABLE(                                                \
                 "unexpected expression; missing key for object entry"),       \
             expression))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_name_in_function_statement, "E061",                        \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("missing name in function statement"), where))  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_name_in_class_statement, "E080",                           \
      { source_code_span class_keyword; },                                     \
      .error(QLJS_TRANSLATABLE("missing name of class"), class_keyword))       \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_name_of_exported_class, "E081",                            \
      { source_code_span class_keyword; },                                     \
      .error(QLJS_TRANSLATABLE("missing name of exported class"),              \
             class_keyword))                                                   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_name_of_exported_function, "E079",                         \
      { source_code_span function_keyword; },                                  \
      .error(QLJS_TRANSLATABLE("missing name of exported function"),           \
             function_keyword))                                                \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_name_or_parentheses_for_function, "E062",                  \
      {                                                                        \
        source_code_span where;                                                \
        source_code_span function;                                             \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("missing name or parentheses for function"),    \
             where))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_operand_for_operator, "E026", { source_code_span where; }, \
      .error(QLJS_TRANSLATABLE("missing operand for operator"), where))        \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_operator_between_expression_and_arrow_function, "E063",    \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE(                                                \
                 "missing operator between expression and arrow function"),    \
             where))                                                           \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_property_name_for_dot_operator, "E142",                    \
      { source_code_span dot; },                                               \
      .error(QLJS_TRANSLATABLE("missing property name after '.' operator"),    \
             dot))                                                             \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_semicolon_after_statement, "E027",                         \
      { source_code_span where; },                                             \
      .error(QLJS_TRANSLATABLE("missing semicolon after statement"), where))   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_semicolon_between_for_loop_condition_and_update, "E100",   \
      { source_code_span expected_semicolon; },                                \
      .error(QLJS_TRANSLATABLE("missing semicolon between condition and "      \
                               "update parts of for loop"),                    \
             expected_semicolon))                                              \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_semicolon_between_for_loop_init_and_condition, "E099",     \
      { source_code_span expected_semicolon; },                                \
      .error(QLJS_TRANSLATABLE("missing semicolon between init and condition " \
                               "parts of for loop"),                           \
             expected_semicolon))                                              \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_token_after_export, "E113",                                \
      { source_code_span export_token; },                                      \
      .error(QLJS_TRANSLATABLE(                                                \
                 "incomplete export; expected 'export default ...' or "        \
                 "'export {{name}' or 'export * from ...' or 'export class' "  \
                 "or 'export function' or 'export let'"),                      \
             export_token))                                                    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_value_for_object_literal_entry, "E083",                    \
      { source_code_span key; },                                               \
      .error(QLJS_TRANSLATABLE("missing value for object property"), key))     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_variable_name_in_declaration, "E123",                      \
      { source_code_span equal_token; },                                       \
      .error(QLJS_TRANSLATABLE("missing variable name"), equal_token))         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_missing_while_and_condition_for_do_while_statement, "E103",        \
      {                                                                        \
        source_code_span do_token;                                             \
        source_code_span expected_while;                                       \
      },                                                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "missing 'while (condition)' for do-while statement"),        \
             expected_while)                                                   \
          .note(QLJS_TRANSLATABLE("do-while statement starts here"),           \
                do_token))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_number_literal_contains_consecutive_underscores, "E028",           \
      { source_code_span underscores; },                                       \
      .error(QLJS_TRANSLATABLE(                                                \
                 "number literal contains consecutive underscores"),           \
             underscores))                                                     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_number_literal_contains_trailing_underscores, "E029",              \
      { source_code_span underscores; },                                       \
      .error(                                                                  \
          QLJS_TRANSLATABLE("number literal contains trailing underscore(s)"), \
          underscores))                                                        \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_octal_literal_may_not_have_exponent, "E030",                       \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("octal literal may not have exponent"),         \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_octal_literal_may_not_have_decimal, "E031",                        \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("octal literal may not have decimal"),          \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_private_properties_are_not_allowed_in_object_literals, "E156",     \
      { identifier private_identifier; },                                      \
      .error(QLJS_TRANSLATABLE(                                                \
                 "private properties are not allowed in object literals"),     \
             private_identifier))                                              \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_redeclaration_of_global_variable, "E033",                          \
      { identifier redeclaration; },                                           \
      .error(QLJS_TRANSLATABLE("redeclaration of global variable"),            \
             redeclaration))                                                   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_redeclaration_of_variable, "E034",                                 \
      {                                                                        \
        identifier redeclaration;                                              \
        identifier original_declaration;                                       \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("redeclaration of variable: {0}"),              \
             redeclaration)                                                    \
          .note(QLJS_TRANSLATABLE("variable already declared here"),           \
                original_declaration))                                         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_regexp_literal_flags_cannot_contain_unicode_escapes, "E035",       \
      { source_code_span escape_sequence; },                                   \
      .error(                                                                  \
          QLJS_TRANSLATABLE("RegExp literal cannot contain Unicode escapes"),  \
          escape_sequence))                                                    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_stray_comma_in_let_statement, "E036", { source_code_span where; }, \
      .error(QLJS_TRANSLATABLE("stray comma in let statement"), where))        \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_typescript_enum_not_implemented, "E127",                           \
      { source_code_span enum_keyword; },                                      \
      .error(QLJS_TRANSLATABLE("TypeScript's 'enum' feature is not yet "       \
                               "implemented by quick-lint-js"),                \
             enum_keyword))                                                    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unclosed_block_comment, "E037",                                    \
      { source_code_span comment_open; },                                      \
      .error(QLJS_TRANSLATABLE("unclosed block comment"), comment_open))       \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unclosed_code_block, "E134", { source_code_span block_open; },     \
      .error(QLJS_TRANSLATABLE(                                                \
                 "unclosed code block; expected '}' by end of file"),          \
             block_open))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unclosed_identifier_escape_sequence, "E038",                       \
      { source_code_span escape_sequence; },                                   \
      .error(QLJS_TRANSLATABLE("unclosed identifier escape sequence"),         \
             escape_sequence))                                                 \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unclosed_object_literal, "E161",                                   \
      {                                                                        \
        source_code_span object_open;                                          \
        source_code_span expected_object_close;                                \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("unclosed object literal; expected '}'"),       \
             expected_object_close)                                            \
          .note(QLJS_TRANSLATABLE("object literal started here"),              \
                object_open))                                                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unclosed_regexp_literal, "E039",                                   \
      { source_code_span regexp_literal; },                                    \
      .error(QLJS_TRANSLATABLE("unclosed regexp literal"), regexp_literal))    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unclosed_string_literal, "E040",                                   \
      { source_code_span string_literal; },                                    \
      .error(QLJS_TRANSLATABLE("unclosed string literal"), string_literal))    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unclosed_template, "E041",                                         \
      { source_code_span incomplete_template; },                               \
      .error(QLJS_TRANSLATABLE("unclosed template"), incomplete_template))     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_at_character, "E042", { source_code_span character; },  \
      .error(QLJS_TRANSLATABLE("unexpected '@'"), character))                  \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_arrow_after_expression, "E160",                         \
      {                                                                        \
        source_code_span arrow;                                                \
        source_code_span expression;                                           \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("unexpected '{0}'"), arrow)                     \
          .note(QLJS_TRANSLATABLE("expected parameter for arrow function, "    \
                                  "but got an expression instead"),            \
                expression))                                                   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_arrow_after_literal, "E158",                            \
      {                                                                        \
        source_code_span arrow;                                                \
        source_code_span literal_parameter;                                    \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("unexpected '{0}'"), arrow)                     \
          .note(QLJS_TRANSLATABLE("expected parameter for arrow function, "    \
                                  "but got a literal instead"),                \
                literal_parameter))                                            \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_backslash_in_identifier, "E043",                        \
      { source_code_span backslash; },                                         \
      .error(QLJS_TRANSLATABLE("unexpected '\\' in identifier"), backslash))   \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_case_outside_switch_statement, "E115",                  \
      { source_code_span case_token; },                                        \
      .error(QLJS_TRANSLATABLE("unexpected 'case' outside switch statement"),  \
             case_token))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_characters_in_number, "E044",                           \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("unexpected characters in number literal"),     \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_control_character, "E045",                              \
      { source_code_span character; },                                         \
      .error(QLJS_TRANSLATABLE("unexpected control character"), character))    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_characters_in_binary_number, "E046",                    \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("unexpected characters in binary literal"),     \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_characters_in_octal_number, "E047",                     \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("unexpected characters in octal literal"),      \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_characters_in_hex_number, "E048",                       \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("unexpected characters in hex literal"),        \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_default_outside_switch_statement, "E116",               \
      { source_code_span default_token; },                                     \
      .error(                                                                  \
          QLJS_TRANSLATABLE("unexpected 'default' outside switch statement"),  \
          default_token))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_literal_in_parameter_list, "E159",                      \
      { source_code_span literal; },                                           \
      .error(QLJS_TRANSLATABLE("unexpected literal in parameter list; "        \
                               "expected parameter name"),                     \
             literal))                                                         \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_semicolon_in_c_style_for_loop, "E102",                  \
      { source_code_span semicolon; },                                         \
      .error(QLJS_TRANSLATABLE("C-style for loops have only three "            \
                               "semicolon-separated components"),              \
             semicolon))                                                       \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_semicolon_in_for_in_loop, "E110",                       \
      { source_code_span semicolon; },                                         \
      .error(                                                                  \
          QLJS_TRANSLATABLE("for-in loop expression cannot have semicolons"),  \
          semicolon))                                                          \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_semicolon_in_for_of_loop, "E109",                       \
      { source_code_span semicolon; },                                         \
      .error(                                                                  \
          QLJS_TRANSLATABLE("for-of loop expression cannot have semicolons"),  \
          semicolon))                                                          \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_no_digits_in_binary_number, "E049",                                \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("binary number literal has no digits"),         \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_no_digits_in_hex_number, "E050", { source_code_span characters; }, \
      .error(QLJS_TRANSLATABLE("hex number literal has no digits"),            \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_no_digits_in_octal_number, "E051",                                 \
      { source_code_span characters; },                                        \
      .error(QLJS_TRANSLATABLE("octal number literal has no digits"),          \
             characters))                                                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_hash_character, "E052", { source_code_span where; },    \
      .error(QLJS_TRANSLATABLE("unexpected '#'"), where))                      \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_identifier, "E053", { source_code_span where; },        \
      .error(QLJS_TRANSLATABLE("unexpected identifier"), where))               \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_identifier_in_expression, "E147",                       \
      { identifier unexpected; },                                              \
      .error(                                                                  \
          QLJS_TRANSLATABLE(                                                   \
              "unexpected identifier in expression; missing operator before"), \
          unexpected))                                                         \
                                                                               \
  /* NOTE(strager): Try not to use this error. Find or make a more descriptive \
     and helpful error instead. */                                             \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_token, "E054", { source_code_span token; },             \
      .error(QLJS_TRANSLATABLE("unexpected token"), token))                    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_token_after_export, "E112",                             \
      { source_code_span unexpected_token; },                                  \
      .error(QLJS_TRANSLATABLE(                                                \
                 "unexpected token in export; expected 'export default ...' "  \
                 "or 'export {{name}' or 'export * from ...' or 'export "      \
                 "class' or 'export function' or 'export let'"),               \
             unexpected_token))                                                \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unexpected_token_in_variable_declaration, "E114",                  \
      { source_code_span unexpected_token; },                                  \
      .error(QLJS_TRANSLATABLE("unexpected token in variable declaration; "    \
                               "expected variable name"),                      \
             unexpected_token))                                                \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unmatched_indexing_bracket, "E055",                                \
      { source_code_span left_square; },                                       \
      .error(QLJS_TRANSLATABLE("unmatched indexing bracket"), left_square))    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unmatched_parenthesis, "E056", { source_code_span where; },        \
      .error(QLJS_TRANSLATABLE("unmatched parenthesis"), where))               \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_unmatched_right_curly, "E143", { source_code_span right_curly; },  \
      .error(QLJS_TRANSLATABLE("unmatched '}'"), right_curly))                 \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_use_of_undeclared_variable, "E057", { identifier name; },          \
      .warning(QLJS_TRANSLATABLE("use of undeclared variable: {0}"), name))    \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_variable_used_before_declaration, "E058",                          \
      {                                                                        \
        identifier use;                                                        \
        identifier declaration;                                                \
      },                                                                       \
      .error(QLJS_TRANSLATABLE("variable used before declaration: {0}"), use)  \
          .note(QLJS_TRANSLATABLE("variable declared here"), declaration))     \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_invalid_break, "E200", { source_code_span break_statement; },      \
      .error(QLJS_TRANSLATABLE(                                                \
                 "break can only be used inside of a loop or switch"),         \
             break_statement))                                                 \
                                                                               \
  QLJS_ERROR_TYPE(                                                             \
      error_invalid_continue, "E201",                                          \
      { source_code_span continue_statement; },                                \
      .error(QLJS_TRANSLATABLE("continue can only be used inside of a loop"),  \
             continue_statement))                                              \
  /* END */

namespace quick_lint_js {
#define QLJS_ERROR_TYPE(name, code, struct_body, format_call) \
  struct name struct_body;
QLJS_X_ERROR_TYPES
#undef QLJS_ERROR_TYPE

class error_reporter {
 public:
  error_reporter() noexcept = default;

  error_reporter(const error_reporter &) noexcept = default;
  error_reporter &operator=(const error_reporter &) noexcept = default;

  error_reporter(error_reporter &&) noexcept = default;
  error_reporter &operator=(error_reporter &&) noexcept = default;

  virtual ~error_reporter() = default;

#define QLJS_ERROR_TYPE(name, code, struct_body, format) \
  virtual void report(name) = 0;
  QLJS_X_ERROR_TYPES
#undef QLJS_ERROR_TYPE
};

class null_error_reporter : public error_reporter {
 public:
  static null_error_reporter instance;

#define QLJS_ERROR_TYPE(name, code, struct_body, format) \
  void report(name) override {}
  QLJS_X_ERROR_TYPES
#undef QLJS_ERROR_TYPE
};
inline null_error_reporter null_error_reporter::instance;
}

#endif

// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew Glazar
//
// This file is part of quick-lint-js.
//
// quick-lint-js is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// quick-lint-js is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
