#ifndef SCOPE_HPP
#define SCOPE_HPP

class Scope
{
private:
  char *m_name;

public:
  Scope *m_parent;
  Scope(char *name) : m_name(name){};
};

#endif
