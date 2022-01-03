#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Source
{
  char model[64];
  char method[64];
  char param[64];
} Source;

typedef struct Variable
{
  char name[64];
  struct Source source;
  char input[256];
  char output[256];
  struct Variable *next;
} Variable;

typedef struct Rule
{
  char title[128];
  struct Rule *next;
  struct Variable *first_var_in_list;
} Rule;

typedef struct Module
{
  char title[128];
  struct Rule *first_rule_in_list;

} Module;

//------------------------

struct Source *create_source(char *model, char *method, char *param)
{
  Source *src;
  src = (Source *)malloc(sizeof(Source));

  strcpy(src->model, model);
  strcpy(src->method, method);
  strcpy(src->param, param);
  return src;
}

struct Variable *create_variable(Variable *v, char *name, Source src, char *input, char *output)
{
  Variable *var;
  var = (Variable *)malloc(sizeof(Variable));
  var->source = src;
  var->next = v;
  strcpy(var->name, name);
  strcpy(var->input, input);
  strcpy(var->output, output);
  return var;
}

struct Rule *create_rule(Rule *r, char *title, Variable *first_var)
{
  Rule *rule;
  rule = (Rule *)malloc(sizeof(Rule));
  rule->next = r;
  rule->first_var_in_list = first_var;
  strcpy(rule->title, title);
  return rule;
}

struct Module *create_module(char *title, Rule *first_rule)
{
  Module *module;
  module = (Module *)malloc(sizeof(Module));
  strcpy(module->title, title);
  module->first_rule_in_list = first_rule;
  return module;
}
