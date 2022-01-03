#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rules_structure.h"
#include "rules_method.h"

void list_vars(Rule *rule);
void list_rules(Module *module);
void load_var(Variable *var, Module *module);

int main()
{
  printf("-------------------------------\n");
  printf("[tsrules] service is starting..\n");


  Source *src1, *src2, *src3;
  //src = NULL;
  Variable *var, *var1, *var2, *var3;
  var = NULL;
  Rule *rule;
  rule = NULL;
  Module *module;

  module = create_module("[module] Tsmodem Rules");

  char *ubus[] = {"tsmodem.driver", "signal", "value"};
  char *uci[] = {"tsmodem", "sim_1", "name"};
  src1 = create_source("ubus", ubus);
  src2 = create_source("uci", uci);
  src3 = create_source("uci", uci);

  rule = create_rule(rule, "[rule] Switching sim card if not registered.", module);

  var1 = create_variable(var, "varname1", src1, rule);
  var2 = create_variable(var1, "varname2", src2, rule);
  var3 = create_variable(var2, "varname3", src2, rule);


  printf("First-from-the-end Var name:\t%s\n", var2->name);
  printf("Second-from-the-end Var name:\t%s\n", var2->next->name);

  printf("Rule title:\t%s\n", rule->title);
  printf("Module title\t%s\n", module->title);

  list_rules(module);
  list_vars(rule);

  load_var(var1, module);
  load_var(var2, module);
  load_var(var3, module);

  printf("TOTAL ITEMS IN CACHE: %d\n", total_items_in_cache(module->cache));

  return 0;
}

void list_vars(Rule *rule)
{
  printf("\n---- LIST OF VARS FOR [%s] ----\n", rule->title);
  Variable *v;
  v = rule->stack_of_vars;
  while(v != NULL) {
    printf("Name:\t\t%s\n", v->name);
    v = v->next;
  }
}

void list_rules(Module *module)
{
  printf("\n---- LIST OF RULES FOR [%s] ----\n", module->title);
  Rule *r;
  r = module->stack_of_rules;
  while(r != NULL) {
    printf("Rule name:\t\t%s\n", r->title);
    r = r->next;
  }
}
