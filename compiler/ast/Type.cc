#include <string>
#include "Type.h"

std::string type_name(Type type)
{
  if(type == TYPE_INT)
    return "TYPE_INT";
  return "[UNKNOWN TYPE]";
}
