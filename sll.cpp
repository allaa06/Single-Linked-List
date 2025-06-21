#include "sll.h"
#include <stdexcept>

template <typename T>
SLL<T>::SLL() : head(nullptr) {}

template <typename T>
SLL<T>::SLL(typename SLL<T>::size_type count, typename SLL<T>::value_type val)  {
   if(count > 0 ) {
   head = new Node{val, nullptr};
   Node* curr = head;
   --count;
   while(count) {
      curr->next = new Node{val, nullptr};
      curr = curr->next;
      --count;
   }
   }
   else if(count == 0) { head = nullptr; }
}

template <typename T>
SLL<T>::SLL(const SLL<T>& other) {
   if(other.head == nullptr) {
      head = nullptr;
   }
   else {
      head = new Node{other.head->val, nullptr};
      Node* curr1 = head;
      Node* curr2 = other.head;
      while(curr2->next) {
         curr1->next = new Node{curr2->next->val, nullptr};
         curr2 = curr2->next;
         curr1 = curr1->next;
      }
   }
}

template <typename T>
SLL<T>::SLL(SLL<T>&& other) {
   if(other.head != nullptr) {
      head = other.head;
      other.head = nullptr;
   }
   else { head = nullptr; }
}

template <typename T>
SLL<T>::SLL(Node* ptr) : head(ptr) {}

template <typename T>
SLL<T>::~SLL() {
   clear();
}

template <typename T>
bool SLL<T>::empty() const {
   return head == nullptr;
}

template <typename T>
void SLL<T>::clear() noexcept {
 
   Node* curr = head;
   Node* next;
   while(curr)
   {
      next = curr->next;
      delete curr;
      curr = next;
   }
   head = nullptr;
}

template <typename T>
typename SLL<T>::size_type SLL<T>::size() const {
   size_type count = 0;
   Node* curr = head;
   while(curr)
   {
      ++count;
      curr = curr->next;
   }
   return count;
}

template <typename T>
void SLL<T>::assign(const size_type count, value_type val) {

   clear();

    if (count == 0) {
        head = nullptr;
        return;
    }

    head = new Node{val, nullptr};
    Node* curr = head;

    for (size_type i = 1; i < count; ++i) {
        curr->next = new Node{val, nullptr};
        curr = curr->next;
    }
}


template <typename T>
void SLL<T>::assign(iterator first, iterator last) {
   clear();
   head = new Node{*first, nullptr};
   ++first;
   Node* curr =  head;
   while(first != last) {
      curr->next = new Node{*first, nullptr};
      curr = curr->next;
      ++first;
   }
   curr->next = new Node{*last, nullptr};

}

template <typename T>
void SLL<T>::assign(std::initializer_list<T> ilist) {
   clear();
   auto it = ilist.begin();
   head = new Node{*it , nullptr};
   Node* curr = head;
   ++it;

   for( it; it != ilist.end(); ++it) {
      curr->next = new Node{*it , nullptr};
      curr = curr->next;

   }
}


template <typename T>
typename SLL<T>::reference SLL<T>::front() {
   if(!head) {
      throw std::runtime_error("List is empty");
   }
   return head->val;
}

template <typename T>
typename SLL<T>::const_reference SLL<T>::front() const {
   if(!head) {
      throw std::runtime_error("List is empty");
   }
   return head->val;
}

template <typename T>
typename SLL<T>::iterator SLL<T>::insert_after(SLL<T>::const_iterator pos, SLL<T>::const_reference value) 
{
   Node* tmp = new Node{value, nullptr};
   Node* curr = head;
   SLL<T>::const_iterator pos_next(head);
   SLL<T>::iterator res(head);
   while(pos_next != pos) {
      ++pos_next;
      ++res;
      curr = curr->next;
   }
   Node* next = curr->next;
   curr->next = tmp;
   tmp->next = next;
   return res;

}


template <typename T>
typename SLL<T>::iterator SLL<T>::erase_after(SLL<T>::const_iterator pos) 
{
   if(!head || !head->next) { return iterator(nullptr); }
   Node* curr = head->next;
   Node* prev = head;
   const_iterator it(head);
   while(it != pos  && curr){
      ++it;
      prev = curr;
      curr = curr->next;
   }
   if(!curr) { throw std::invalid_argument("Unknow position"); }
   prev->next = curr->next;
   delete curr;

   return iterator(prev);

}

template <typename T>
typename SLL<T>::iterator SLL<T>::erase_after(typename SLL<T>::const_iterator first, typename SLL<T>::const_iterator last) {
   iterator it(head);
   const_iterator pos = first;
   ++pos;
   while(pos != last)
   {
      it = erase_after(first);
      pos = first;
      ++pos;
      
   }
   return it;
}

template <typename T>
void SLL<T>::push_front(typename SLL<T>::const_reference value) {
   Node* curr = new Node{value,head};
   head = curr;
}

template <typename T>
void SLL<T>::pop_front() {
   if(!head) { throw std::runtime_error("List is empty"); }
   if(!head->next) { delete head; }
   Node* old_head = head;
   head = head->next; 
   delete old_head;
}


template <typename T>
void SLL<T>::swap(SLL<T>& other) {

   Node* tmp = head;
   head = other.head;
   other.head = tmp;
}

template <typename T>
void SLL<T>::merge(SLL<T>& other) {
   iterator it1(head);
   iterator it2(other.head);
   SLL<T> res(new Node{0,nullptr});
   Node* tail = res.head;
   
   while(it1 != end() && it2 != end() ){
      if(*it1 <= *it2)
      {
         tail->next = new Node{*it1, nullptr};
         ++it1;
      }
      else
      {
         tail->next = new Node{*it2, nullptr};
         ++it2;
      }
      tail = tail->next;
   }

   while(it1 != end())
   {
      tail->next = new Node{*it1, nullptr};
      ++it1;
      tail  = tail->next;
   }
   while(it2 != end())
   {
      tail->next = new Node{*it2, nullptr};
      ++it2; 
      tail = tail->next;
   }
   res.pop_front();
   swap(res);
}

template <typename T>
void SLL<T>::splice_after(typename SLL<T>::const_iterator pos, SLL<T>& other) {
   if(!other.head) { return; }
   Node* curr = head;
   const_iterator it(head);
   
   Node* first = other.head;
   Node* last = other.head;
   while(last->next) {
      last = last->next;
   }

   while(it != pos && curr){
      curr = curr->next;
      ++it;
   }

   if(!curr) { throw std::invalid_argument("Unknow position"); }

   last->next = curr->next;
   curr->next = first;
   other.head = nullptr;
}
   


template <typename T>
void SLL<T>::remove(typename SLL<T>::const_reference value) {
   if(!head){return;} 
   while(head->val == value) {
      pop_front();
      if(!head){return;}
    }

   iterator it(head->next);
   iterator animast(nullptr);
   const_iterator prev(head); 
      while(it != end()){
         if(*it == value) {
            ++it;
           animast = erase_after(prev);
         }
         else{
         ++it;
         ++prev;
         }
      }
}


template <typename T>
void SLL<T>::reverse() noexcept {
   if(!head || !head->next) { return; }

   Node* prev = nullptr;
   Node* curr = head;
   Node* next;

   while(curr)
   {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
   }

   head = prev;

}

template <typename T>
void SLL<T>::unique() {
   if(!head || !head->next) { return; }
   
   iterator cycle(head);
   const_iterator it(head->next);
   const_iterator prev(head);
   value_type value = *prev;
   while(cycle != end()) {
      if(*it == value)
      {
         ++it;
         cycle = erase_after(prev);
      }
      else
      {
         value = *it;
         prev = it;
         ++it;

      }
      ++cycle;

}
}

template<typename T>
void SLL<T>::sort() {
     if (!head || !head->next) 
        return;

    Node dummy{T(), head};
    Node* last_sorted = head;     
    Node* curr        = head->next;  

    while (curr) {
        if (curr->val >= last_sorted->val) {
            last_sorted = curr;
        }
        else {
            Node* prev = &dummy;
            while (prev->next->val <= curr->val) {
                prev = prev->next;
            }
            last_sorted->next = curr->next;
            curr->next = prev->next;
            prev->next = curr;
        }
        curr = last_sorted->next;
    }

    head = dummy.next;
}




template <typename T>
void SLL<T>::print() const {
   Node* curr = head;
   while(curr) {
      std::cout << curr->val << " ";
      curr = curr->next;
   }
   std::cout << "\n";
}

template <typename T>
SLL<T>::iterator::iterator(Node* ptr) : curr(ptr) {}

template <typename T>
typename SLL<T>::reference SLL<T>::iterator::operator*() {
   return curr->val; 
}

template <typename T>
typename SLL<T>::iterator& SLL<T>::iterator::operator++() {
   curr = curr->next;
   return *this;
}

template <typename T>
bool SLL<T>::iterator::operator==(const SLL<T>::iterator& it) const {
   return curr == it.curr;
}

template <typename T>
bool SLL<T>::iterator::operator!=(const SLL<T>::iterator& it) const {
   return curr != it.curr;
}



template <typename T>
SLL<T>::const_iterator::const_iterator(const Node* ptr) : curr(ptr) {}

template <typename T>
typename SLL<T>::const_reference SLL<T>::const_iterator::operator*() const {
   return curr->val; 
}

template <typename T>
typename SLL<T>::const_iterator& SLL<T>::const_iterator::operator++() {
   curr = curr->next;
   return *this;
}

template <typename T>
bool SLL<T>::const_iterator::operator==(const SLL<T>::const_iterator& it) const {
   return curr == it.curr;
}

template <typename T>
bool SLL<T>::const_iterator::operator!=(const SLL<T>::const_iterator& it) const {
   return curr != it.curr;
}

template <typename T>
typename SLL<T>::iterator SLL<T>::begin() {
   iterator it(head);
   return it;
}

template <typename T>
typename SLL<T>::iterator SLL<T>::end() {
   Node* curr = head;
   while(curr){
      curr = curr->next;
   }
   iterator it(curr);
   return it;
}

template <typename T>
typename SLL<T>::const_iterator SLL<T>::cbegin() const {
   const_iterator it(head);
   return it;
}

template <typename T>
typename SLL<T>::const_iterator SLL<T>::cend() const {
   Node* curr = head;
   while(!curr) {
      curr = curr->next;
   }
   const_iterator it(curr);
   return it;
}






















