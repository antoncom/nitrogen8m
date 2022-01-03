#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STRUCTURE_LOADED 1

typedef struct Source
{
  char type[10];
  union {
    struct {
      char name[64];
      char method[64];
      char param[64];
      char ubus_response[256];
    };
    struct {
      char config[64];
      char section[64];
      char option[64];
      char uci_response[64];
    };
  } x;
} Source;

typedef enum { INTEGER, STRING, REAL } Type;

// Good explanation of Union:
// https://stackoverflow.com/questions/724617/examples-of-union-in-c
typedef struct Value
{
  Type type;
  union
  {
    char *string;
    int integer;
    float real;
  } x;
} Value;

typedef struct Cache {
  struct Source source;
  struct Value value;
  struct Cache *next;
} Cache;

extern Cache global_cache;


typedef struct Variable
{
  char name[64];
  struct Source source;
  struct Value input;
  struct Value subtotal;
  struct Value output;
  struct Variable *next;
} Variable;

typedef struct Rule
{
  char title[128];
  struct Rule *next;
  struct Variable *stack_of_vars;
} Rule;

typedef struct Module
{
  char title[128];
  struct Rule *stack_of_rules;
  struct Cache *cache;

} Module;


//------------------------

struct Source *create_source(char *model, char *array[])
{
  Source *src;
  src = (Source *)malloc(sizeof(Source));
  if(strcmp(model, "uci") == 0)
  {
    strcpy(src->type, "uci");
    strcpy(src->x.config, array[0]);
    strcpy(src->x.section, array[1]);
    strcpy(src->x.option, array[2]);
    strcpy(src->x.uci_response, "");
  }
  else if(strcmp(model, "ubus") == 0)
  {
    strcpy(src->type, "ubus");
    strcpy(src->x.name, array[0]);
    strcpy(src->x.method, array[1]);
    strcpy(src->x.param, array[2]);
    strcpy(src->x.ubus_response, "");
  }
  else if(strcmp(model, "constant") == 0); // don nothing
  return src;
}

struct Rule *create_rule(Rule *r, char *title, Module *module)
{
  Rule *rule;
  rule = (Rule *)malloc(sizeof(Rule));
  rule->next = r;
  rule->stack_of_vars = NULL;
  strcpy(rule->title, title);

  module->stack_of_rules = rule;
  return rule;
}

struct Variable *create_variable(Variable *v, char *name, Source *src, Rule *rule)
{
  Variable *var;
  var = (Variable *)malloc(sizeof(Variable));
  var->source = *src;
  var->next = v;
  strcpy(var->name, name);
  rule->stack_of_vars = var;
  return var;
}

struct Module *create_module(char *title)
{
  Module *module;
  module = (Module *)malloc(sizeof(Module));
  strcpy(module->title, title);
  module->stack_of_rules = NULL;
  module->cache = NULL;
  return module;
}

struct Cache *create_cache_item(Cache *c, Variable *v)
{
  Cache *cache;
  cache = (Cache *)malloc(sizeof(Cache));
  cache->source = v->source;
  cache->value = v->input;
  cache->next = c;
  return cache;
}

void add_to_cache(Variable *v, Module *m)
{
  Cache *cache;
  // If cache is empty
  if(m->cache == NULL)
  {
    cache = NULL;
    cache = create_cache_item(cache, v);
    m->cache = cache;
  }
  else
  {
    cache = m->cache;
    cache = create_cache_item(cache, v);
    m->cache = cache;
  }

}

int total_items_in_cache(Cache *p){
    int t = 0;
    // пока не конец стека
    while (p != NULL) {
      // продвижение по списку
      p = p->next;
      t++;
    }
    return t;
}

int is_in_cache(Variable *var, Module *module)
{
  Cache *cache;
  while(cache != NULL)
  {
    cache = cache->next;
  }
  return 0;
}
