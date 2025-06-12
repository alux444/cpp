#include <string>

struct Node
{
  char ch;
  Node *prev;
  Node *next;
  Node(char ch) : ch(ch), prev(nullptr), next(nullptr) {}
};

class TextEditor
{
  Node *start;
  Node *end;
  Node *cursor;

  std::string getLastTen()
  {
    int chars = 10;
    Node *cur = cursor;
    std::string s = "";
    while (chars > 0 && cur && cur != start)
    {
      --chars;
      s += cur->ch;
      cur = cur->prev;
    }
    std::reverse(s.begin(), s.end());
    return s;
  }

public:
  TextEditor()
  {
    start = new Node('\n');
    end = new Node('\n');
    start->next = end;
    end->prev = start;

    cursor = start;
  }

  void addText(std::string text)
  {
    for (char ch : text)
    {
      Node *chNode = new Node(ch);
      chNode->prev = cursor;
      chNode->next = cursor->next;

      cursor->next->prev = chNode;
      cursor->next = chNode;

      cursor = chNode;
    }
  }

  int deleteText(int k)
  {
    int deleted = 0;
    while (k > 0 && cursor != start)
    {
      ++deleted;
      --k;

      Node *toDelete = cursor;
      cursor = cursor->prev;

      cursor->next = toDelete->next;
      toDelete->next->prev = cursor;

      delete toDelete;
    }
    return deleted;
  }

  std::string cursorLeft(int k)
  {
    while (k > 0 && cursor != start)
    {
      --k;
      cursor = cursor->prev;
    }
    return getLastTen();
  }

  std::string cursorRight(int k)
  {
    while (k > 0 && cursor->next != end) // cant be at end
    {
      --k;
      cursor = cursor->next;
    }
    return getLastTen();
  }
};