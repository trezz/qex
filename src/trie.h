/**
 * Trie data structure representing a set of character strings. qex uses this
 * data structure to store the input queries as characters tree with one
 * character per node.
 * The strings can be re-built by starting at the leafs and climbing up to the
 * root node one character at a time.
 */

#ifndef _QEX_TRIE_H_
#define _QEX_TRIE_H_

#include <map>

namespace qex
{

class Trie
{
  public:
    /** Constructor */
    Trie (char c, const Trie* parent = nullptr);
    /** Destructor */
    virtual ~Trie ();

    /**
     * Add a character to this node and return the child node representing this
     * character. The returned object is either created if it does not exist or
     * returned from the set of already known children.
     *
     * \param [in] c  Child character.
     */
    Trie* add_child (char c);

    /** Return true if the current node has `c` has child, false otherwise. */
    bool has_child (char c) const;

    /**
     * Insert a new string one character at a time in the Trie. The returned
     * object is either created if it does not exist or returned from the set
     * of already known children.
     *
     * if `s` is null or points to a null character, the function does nothing
     * and returns null.
     *
     * \param [in] s  String pointer pointing at the next character to add as
     *                a child node.
     */
    Trie* add_string (const char* s);

    /* Getters */
    char character () const { return _c; }
    size_t num () const { return _num; }
    const Trie* parent () const { return _parent; }
    std::map<char, Trie*>& children () { return _children; }
    const std::map<char, Trie*>& children () const { return _children; }

    /* Setters */
    void increment_num () { ++_num; }

  private:
    char _c;
      /**< character of this Trie node */
    size_t _num;
      /**< Number of character strings already inserted in the Trie tree. */
    const Trie* _parent;
      /**< Parent node. */
    std::map<char, Trie*> _children;
      /**< children nodes ordered in a set to improve the insertion speed */
};

} /* namespace qex */

#endif /* !_QEX_TRIE_H_ */
