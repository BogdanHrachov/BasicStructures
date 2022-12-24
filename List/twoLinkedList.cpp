#include <iostream>

template < typename T >
struct ls_el
{
    T val;
    explicit ls_el(T data) : val(data) {}
    struct ls_el < T >*next = nullptr;
    struct ls_el < T >*prev = nullptr;
};

template <typename T>
class List
{
private:
    T data;
    struct ls_el < T >* p_beg = nullptr;
    struct ls_el < T >* p_end = nullptr;
public:
    List() = default;
    ~List()
    {
        clear();
    }
    explicit List(T data) : data(data) {}
    struct ls_el < T >* begin()
    {
        return p_beg;
    }
    struct ls_el < T >* end()
    {
        return p_end -> next;
    }
    int size()
    {
        struct ls_el < T >* p_cur = begin();
        int count = 0;
        while (p_cur != end()) {
            ++count;
            p_cur = p_cur -> next;
        }
        return count;
    }
    void pushBack(T data)
    {
        struct ls_el < T >* p_cur = new struct ls_el < T >(data);
        if (p_beg == nullptr)
            p_beg = p_cur;
        else {
            p_end -> next = p_cur;
            p_cur -> prev = p_end;
        }
        p_end = p_cur;
    }
    void pushFront(T data)
    {
        struct ls_el < T >* p_cur = new struct ls_el < T >(data);
        if (p_beg == nullptr) {
            p_end = p_cur;
            p_beg = p_cur;
        }
        else {
            p_beg -> prev = p_cur;
            p_cur -> next = p_beg;
        }
        p_beg = p_cur;
    }
    struct ls_el < T >* erase(struct ls_el < T >* el)
    {
        if (el == p_beg && el == p_end) {
            p_beg = p_end = nullptr;
            delete el;
            return nullptr;
        }
        if (el == p_beg) {
            p_beg = p_beg -> next;
            p_beg -> prev = nullptr;
            delete el;
            return p_beg;
        }
        if (el == end()) {
            p_end = p_end -> prev;
            p_end -> next = nullptr;
            delete el;
            return el;
        }
        el -> next -> prev = el -> prev;
        el -> prev -> next = el -> next;
        struct ls_el < T >* temp = el -> next;
        delete el;
        return temp;
    }
    void print()
    {
        struct ls_el < int >* pcur = begin();
        while (pcur != end()) {
            std::cout << pcur -> val << " ";
            pcur = pcur -> next;
        }
    }
    void clear()
    {
        struct ls_el < T >* p_cur = p_beg;
        while (p_cur != nullptr) {
            p_beg = p_cur;
            p_cur = p_cur -> next;
            delete p_beg;
        }
    }
};

int main()
{
    List <int> ls;
    for (int i = 0; i < 10; ++i) {
        int a;
        std::cin >> a;
        ls.pushFront(a);
    }
    ls.print();
    std::cout << std:: endl << "size of list: " << ls.size();
    ls.erase(ls.begin());
    std::cout << std::endl << "first element of the list was deleted: ";
    ls.print();
    struct ls_el < int >* p_cur = ls.begin();
    while (p_cur != ls.end() && p_cur -> val != 5) {
        p_cur = p_cur -> next;
    }
    ls.erase(p_cur);
    std::cout << std::endl << "5 was deleted: ";
    ls.print();
    ls.erase(ls.end());
    std::cout << std::endl << "last element of the list was deleted: ";
    ls.print();
    return 0;
}
