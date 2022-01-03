#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef STRUCTURE_LOADED
#include "rules_structure.h"
#endif

// Loads initial data to variable 'subtotal' field.
void load_var(Variable *var, Module *module)
{
  char *response;
  double result_f;
  int result_i;

  if(strcmp(var->source.type, "uci") == 0)
  {
    // TODO get from UCI code here
    // and place to cache
    response = "150";
    strcpy(var->source.x.uci_response, response);
  }
  else if(strcmp(var->source.type, "ubus") == 0)
  {

    // TODO get from UBUS code here
    // and place to cache

    response = "205.47";
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
    result_f = strtod(response, NULL);
    if(result_f != 0)
    {
      var->input.x.real = result_f;
      var->input.type = REAL;
    }
    else
    {
      result_i = strtol(response, NULL, 10);
      if(result_i != 0)
      {
        var->input.x.integer = result_i;
        var->input.type = INTEGER;
      }
      else
      {
        var->input.x.string = response;
        var->input.type = STRING;
      }
    }

    // Check if the same value already loaded
    if(is_in_cache(var, module) == 0)
    {
      add_to_cache(var, module);
    }
  }




  printf("\nVariable [%s] was loaded. Input: %f\n", var->name, var->input.x.real);

}
