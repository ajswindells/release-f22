
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in MP3.1
    ListNode* position_;
    ListNode* end;

  public:
    ListIterator() : position_(NULL), end(NULL) { }
    ListIterator(ListNode* x) : position_(x), end(NULL) { }
    ListIterator(ListNode* x, ListNode* end_) : position_(x), end(end_) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP3.1
        ListNode* temp = position_;
        if (position_ == NULL) {
            position_ = end;
        } else {
        position_ = position_->next;
        }
        return ListIterator(temp);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        if (position_ == head_) {
            return *this;
        }
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
        ListNode* temp = position_;
        if (position_ == NULL) {
            position_ = end;
        } else {
        position_ = position_->prev;
        }
        return ListIterator(temp);
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP3.1
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return position_ == rhs.position_;
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
