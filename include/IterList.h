#ifndef ITERLIST_H
#define ITERLIST_H

#include <iostream>

/* An IterList element should contain
 * an IterListElem property called "elem"
 * in order to be used properly
 *
 * Anyway, this class was made to guarantee
 * a few things:
 *
 * > O(1) add and remove time given an element
 * > O(n) internal iterator
 *
 * Maybe I'm just a silly d00d but I don't think
 * any data structure in C++ gives me that. The
 * only cost is that I have to allocate a thing
 * in whatever I'm storing.
 */

 template <class T>
 class IterListElem;

template <class T>
class IterList
{
    public:
        IterList()
            {
                this->h = 0;
                this->t = 0;
                this->size = 0;
            };
        virtual ~IterList()
            {
                IterListElem<T>* index = this->h;
                while (index != 0) {
                    IterListElem<T>* remove_this = index;
                    index = index->next;
                    delete remove_this;
                }
            };
        void add(T* elem)
            {
                IterListElem<T>* newelem = new IterListElem<T>(elem);
                if (this->t) {
                    // no elements in the list
                    this->t->next = newelem;
                    newelem->prev = this->t;
                } else {
                    this->h = newelem;
                    this->iter = this->h;
                }

                this->t = newelem;
            };
        T* del(T* elem)
            {
                if (elem->elem == 0) {
                    return 0;
                } else {
                    IterListElem<T>* elem = elem->elem;
                    if (elem->next != 0)
                        elem->next->prev = 0;
                    if (elem->prev != 0)
                        elem->prev->next = 0;
                    if (this->h == elem)
                        this->h = elem->next;
                    if (this->t == elem)
                        this->t = elem->prev;
                    T* obj = elem->obj;
                    delete elem;
                    return obj;
                }
            };
        T* next()
            {
                if (this->iter != 0) {
                    this->iter = this->iter->next;
                    return (this->iter > 0 ? this->iter->obj : 0);
                }
                else return 0;
            };
        T* prev()
            {
                if (this->iter != 0) {
                    this->iter = this->iter->prev;
                    return (this->iter > 0 ? this->iter->obj : 0);
                }
                else return 0;
            };
        T* head()
            {
                this->iter = this->h;
                return this->iter->obj;
            };
        T* tail()
            {
                this->iter = this->t;
                return this->iter->obj;
            };
        IterListElem<T>* expose()
            {
                return this->iter;
            }

    protected:

    private:
        int size;
        IterListElem<T>* h, *t, *iter;
};

template <class T>
class IterListElem
{
    public:
        IterListElem(T* elem)
            {
                this->obj = elem;
                elem->elem = this;
                this->prev = this->next = 0;
            };
        virtual ~IterListElem()
            {
                delete this->obj;
            };
        T* obj;
        IterListElem<T>* prev;
        IterListElem<T>* next;

    private:
};

#endif // ITERLIST_H
