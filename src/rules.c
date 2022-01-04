#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef STRUCTURE_LOADED
#include "rules.h"
#endif

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
  cache = module->cache;
  while(cache != NULL)
  {
    if(strcmp(var->source.hash, cache->source.hash) == 0)
        return 1;
    cache = cache->next;
  }
  return 0;
}

void clear_cache(Cache *c){
    int t = 0;
    Cache *cache;
    while (c != NULL) {
      cache = c->next;
      free(c);
      c = cache;

      t++;
    }
    printf("Cleared in cache: %d\n", t);

}

bool is_float(const char *s) {
  if (s == NULL) {
    return false;
  }
  char *endptr;
  (float) strtod(s, &endptr);
  if (s == endptr) {
    return false; // no conversion;
  }
  // Look at trailing text
  while (isspace((unsigned char ) *endptr))
    endptr++;
  return *endptr == '\0';
}

// Loads initial data to variable 'subtotal' field.
void load_var(Variable *var, Module *module)
{
  char response[256];
  long int result_i;

  if(strcmp(var->source.type, "uci") == 0)
  {
    // TODO get from UCI code here
    // and place to cache
    strcpy(response, "250.70");
    strcpy(var->source.x.uci_response, response);
  }
  else if(strcmp(var->source.type, "ubus") == 0)
  {

    // TODO get from UBUS code here
    // and place to cache

    strcpy(response, "-500.10");
    strcpy(var->source.x.ubus_response, response);
  }

  else
  {
    // for constants
    strcpy(response, var->input.x.string);
    var->input.type = STRING;
  }


  if(strlen(response) == 0)
  {
    var->input.x.string = strcpy(var->input.x.string, "");
    var->input.type = STRING;
  }
  else // convert to REAL or INTEGER or STRING
  {
      if(strcmp(response, "0") == 0)
      {
          var->input.x.integer = 0;
          var->input.type = INTEGER;
      }
      else
      {
          char *endp;
          result_i = (long int) strtol(response, &endp, 10);
          if(strlen(endp) == 0)
          {
              var->input.x.integer = result_i;
              var->input.type = INTEGER;
          }
          else
          {
              if(is_float(response))
              {
                var->input.x.real = (float) strtod(response, NULL);
                var->input.type = REAL;
              }
              else
              {
                  var->input.x.string = response;
                  var->input.type = STRING;
              }
          }
      }



    // Check if the same value already loaded

    if(is_in_cache(var, module) == 0)
    {
      add_to_cache(var, module);
    }


  }



  switch(var->input.type) {
    case STRING:
        printf("STRING\n");
        printf("\nVariable [%s] was loaded. Input: %s\n", var->name, var->input.x.string);
        break;
    case REAL:
        printf("REAL\n");
        printf("\nVariable [%s] was loaded. Input: %f\n", var->name, var->input.x.real);
        break;
    case INTEGER:
        printf("INTEGER\n");
        printf("\nVariable [%s] was loaded. Input: %ld\n", var->name, var->input.x.integer);
        break;
    default:
        printf("--- type not defined -- \n");
  }


}
