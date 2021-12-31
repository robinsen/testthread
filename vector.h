#pragma once

#include <memory>
#include <iostream>
#include <string>

template<typename T>
class CVector {
public:
    CVector():
    _start(nullptr),
    _end(nullptr),
    _endofStorage(nullptr)
    {

    }
    CVector(size_t n) {
        _start = _alloc.allocate(n);
        _end = _start+n;
        memset(static_cast<void*>(_start), 0, n);
        _endofStorage = _end;
    }
    CVector(size_t n, const T& value) {
        _start = _alloc.allocate(n);
        _end = _start+n;
        _endofStorage = _end;
        std::uninitialized_fill(_start, _start+n, value);
    }
    CVector(const CVector& value) {
        size_t n = value.capacity();
        _start = _alloc.allocate(n);
        _endofStorage = _start+n;;
        _end = std::uninitialized_copy(value.beging(), value.beging()+value.size(), _start);
    }

    T* beging() {
        return _start;
    }

    T* end() {
        return _end;
    }

    T& front() {
        return *beging();
    }

    T& back() {
        return *(end()-1);
    }

    T& operator[](size_t n) {
        return *(beging()+n);
    }

    size_t size() {
        if (_end >= _start)
            return _end - _start;
        return 0;
    }

    size_t capacity() {
        if (_endofStorage >= _start)
            return _endofStorage - _start;
        return 0;
    }
    void destroy() {
        if (_start)
        {
            while (_end != _start)
            {
                _alloc.destroy(--_end);
            }
        }
        _alloc.deallocate(_start, _endofStorage - _start);
        _start = _end = _endofStorage = nullptr;
    }

    void push_back(const T& t);

private:
    T*    _start=nullptr;
    T*    _end=nullptr;
    T*    _endofStorage=nullptr;
    std::allocator<T> _alloc;
};

template<typename T>
void CVector<T>::push_back(const T& value)
{
    if (_end != _endofStorage)
    {
        _alloc.construct(_end, value);
        ++_end;
    }
    else
    {
        //内存不够要重新分配内存
        size_t n = capacity();
        T* _p = _alloc.allocate(2*n);
        T* _newEnd = std::uninitialized_copy(_start, _end, _p);
        _alloc.construct(_newEnd, value);
        ++_newEnd;
        destroy();
        _start = _p;
        _end = _newEnd;
        _endofStorage = _p + 2*n;
    }
}
