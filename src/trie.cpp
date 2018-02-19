#include "trie.h"

namespace qex
{

Trie::Trie (char c, const Trie* parent /* = parent */)
  : _c{c}, _num{0}, _parent{parent}, _children{}
{ /* nothing to do */ }

Trie::~Trie ()
{
  for (auto char_child : _children)
  { delete char_child.second; }
}

Trie* Trie::add_child (char c)
{
  /* try to find an already present child with this character */
  std::map<char, Trie*>::iterator it = _children.find(c);

  if (it != _children.end())
  {
    /* a child has been found */
    return it->second;
  }
  else
  {
    /* create a new child */
    Trie* new_child = new Trie(c, this);
    _children[c] = new_child;
    return new_child;
  }
}

bool Trie::has_child (char c) const
{ return _children.find(c) != _children.end(); }

Trie* Trie::add_string (const char* s)
{
  /* error case handling */
  if (s == nullptr || *s == 0)
  { return nullptr; }

  /* add child */
  Trie* child = add_child(*s);
  ++s;

  /* if this was the last character of the string, return it.
   *
   * NOTE: \0 \n and \r are treated as string terminator, because queries
   *  cannot contain end lines characters.
   */
  if (*s == 0 || *s == '\n' || *s == '\r')
  {
    child->increment_num();
    return child;
  }
  else
  {
    return child->add_string(s);
  }
}

} /* namespace qex */

