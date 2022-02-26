#include <array>
#include <vector>
#include <iostream>

/** 
 * @brief Template for generating a Circular Buffer using a std::array container.
 * 
 * @tparam T type for the values of the circular buffer
 * @tparam Size of the circular buffer
 * 
 */ 
template<class T, std::size_t Size>
class CircularBuffer {
  public:
    typedef T value_type;
    // typedef T* pointer;
    // typedef T const* const_pointer;
    typedef T& reference;
    typedef T const& const_reference;
    typedef std::size_t size_type;
    // typedef std::ptrdiff_t difference_type;

    /**
     * @brief Circular Buffer constructor.
     *
     */
    CircularBuffer()
        : _head(0)
        , _tail(0)
        , _size(0)
    {
    }

    /**
     * @brief Front function to easily access the current head element.
     *
     * @return Reference to the head element.
     * 
     */
    reference front() {
        if(getHead()==0){
            return _buffer[size()-1];
        }
        return _buffer[getHead()-1];
    }

    /**
     * @brief Front const function to easily access the current head element.
     *
     * @return Const Reference to the head element.
     * 
     */
    const_reference front() const {
        if(getHead()==0){
            return &_buffer[size()-1];
        }
        return &_buffer[getHead()-1];
    }

    /**
     * @brief Back function to easily access the current tail element.
     *
     * @return Reference to the tail element.
     * 
     */
    reference back() {
        return _buffer[getTail()];
    }

    /**
     * @brief Back const function to easily access the current tail element.
     *
     * @return Const Reference to the tail element.
     * 
     */
    const_reference back() const {
        return &_buffer[getTail()];
    }

    /**
     * @brief [] operator to easily access a buffer element using the index.
     * 
     * @param[in] index of the element
     *
     * @return Reference to the element.
     * 
     */
    reference &operator[](size_t index) {
        std::cout << "operator[]" << std::endl;
        return _buffer[index];
    }

    /**
     * @brief [] const operator to easily access a buffer element using the index.
     * 
     * @param[in] index of the element
     *
     * @return Const Reference to the element.
     * 
     */
    const_reference &operator[](size_t index) const {
        std::cout << "const operator[]" << std::endl;
        return &_buffer[index];
    }

    /**
     * @brief helper function to get the _tail index.
     *
     * @return _tail index.
     * 
     */
    size_type getTail() const {
        return _tail;
    }

    /**
     * @brief helper function to get the _head index.
     *
     * @return _head index.
     * 
     */
    size_type getHead() const {
        return _head;
    }

    /**
     * @brief helper function to return the maximum size of the buffer.
     *
     * @return _size of buffer.
     * 
     */
    size_type size() const {
        return _size;
    }

    /**
     * @brief helper function to check if the buffer is empty.
     *
     * @return boolean, true if empty, false otherwise.
     * 
     */
    bool empty() const {
        return size() == 0;
    }

    /**
     * @brief helper function to check if the buffer is full.
     *
     * @return boolean, true if full, false otherwise.
     * 
     */
    bool full() const {
        return size() == Size;
    }

    bool getElements(std::vector<T> &values, std::size_t elements){
        // If we don't have enough elements, return false
        if(elements > size()){
            return false;
        }
        // easy loop, we don't need to do any operation
        if ( getHead() >= elements) {
            int index_calc = getHead()-1-elements;
            for (int i=getHead()-1; i>index_calc; i--) {
                values.push_back(_buffer[i]);
            }
        } 
        // complex loop, as we need to return first all the values from the head
        // to the beginning of the buffer, and then go to the end of the buffer
        // for returning some more until reaching the elements
        else {
            // Get elements from head to begin of the buffer
            for (int i=getHead()-1; i>=0; i--) {
                values.push_back(_buffer[i]);
            }
            // Get nedded elements starting from the end of the buffer
            int index_calc = elements - getHead();
            for (int i=size()-1; i>=size()-index_calc; i--) {
                values.push_back(_buffer[i]);
            }
        }
        return true;
    }

    /**
     * @brief function to read the tail element. This function removes the
     * the element from the buffer, making the tail advance.
     *
     * @return tail value of the buffer
     * 
     * @note the caller must ensure that the buffer is not empty. We could
     * force this with an assert if required.
     * 
     */
    T pop() {
        // assert(!empty());
        if (!empty()){
            value_type ret = _buffer[_tail];
            _buffer[_tail] = 0;
            --_size;
            _tail = wrapEnd(_tail);
            return ret;
        }
    }

    /**
     * @brief function to write a new element where the head points. This
     * function adds the value and advances the _head pointer.
     *
     * @param[in] value value to add to the buffer
     * 
     */
    void push(T value){
        _buffer[_head] = value;

        if (!full()){
            ++_size;
            _head = wrapEnd(_head);
        } else {
            _head = _tail = wrapEnd(_tail);
        }
    }

  private:
    /**
     * @brief helper function to do the wrap math in the end of the buffer.
     *
     * @param[in] cb_pointer one of tail/head pointers
     * 
     * @return the valid tail/head pointer after the increment.
     * 
     */
    size_type wrapEnd(const size_type cb_pointer){
        return ((cb_pointer + 1) % Size);
    }

    /**
     * @brief Pretty printing the Circular Buffer in the form of:
     * [ *1 ^0 0 ]
     * where * represents the tail and ^ represents the head
     *  
     * @param[in] os stream object to hold the pretty printing 
     * @param[in] cb CircularBuffer object to be printed.
     * 
     * @return stream with the printed buffer
     */
    template <typename U, size_type V>
    friend std::ostream& operator<<(std::ostream& os,
        CircularBuffer<U,V> const& cb);

    /**
     * @brief The array contained to hold the circular buffer data
     *
     */
    std::array<T,Size> _buffer = {};
    /**
     * @brief The _head index
     *
     */
    std::size_t _head;
    /**
     * @brief The _tail index
     *
     */
    std::size_t _tail;
    /**
     * @brief The _size of the elements in the array
     *
     */
    std::size_t _size;
};

template <typename T, std::size_t Size>
std::ostream& operator<<(std::ostream& os, CircularBuffer<T,Size> const& cb)
{
    os << "[ ";
    for (uint i = 0; i< Size; i++) {
        if (i == cb._head) {
            os << "^";
        }
        if (i == cb._tail) {
            os << "*";
        }
        os << cb._buffer[i] << " ";
    }
    os << "]";
    return os;
}