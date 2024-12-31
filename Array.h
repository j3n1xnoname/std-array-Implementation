#ifndef ARRAY_H
#define ARRAY_H
#include <cstddef>
#include <initializer_list>
#include <bits/streambuf_iterator.h>


template <typename T, std::size_t N>
class Array {
    T* m_arr;
    std::size_t m_size;
public:
    Array() : m_arr(new T[N]), m_size(N) {}
    ~Array();

    Array(std::initializer_list<T> list) : m_arr(new T[N]), m_size(N) {
        std::copy(list.begin(), list.end(), m_arr);
    }

    Array(const Array& other) : m_arr(new T[other.m_size]), m_size(other.m_size) {
        std::copy(other.m_arr, other.m_arr + other.m_size, m_arr);
    }

    Array& operator=(const Array& other);
    Array& operator[](const std::size_t index) {return m_arr[index];}
    const Array& operator[](const std::size_t index) const {return m_arr[index];}
    T* begin() const {return m_arr;}
    T* end() const {return m_arr + m_size;}

    bool empty() const {return m_size == 0;}
    std::size_t size() const {return m_size;}
    static std::size_t max_size() {return N;}

    void fill(const T& value) {
        std::fill(m_arr, m_arr + m_size, value);
    }

    void swap(const Array& other);
};

template <typename T, std::size_t N>
void Array<T, N>::swap(const Array& other) {
    if (m_size == other.m_size) {
        for (std::size_t i = 0; i < m_size; ++i) {
            std::swap(m_arr[i], other.m_arr[i]);
        }
    }
}

template <typename T, std::size_t N>
Array<T, N>::~Array() {
    delete[] m_arr;
}

template <typename T, std::size_t N>
Array<T, N>& Array<T, N>::operator=(const Array& other) {
    if (this == &other) {
        return *this;
    }

    if (m_size != other.m_size) {
        delete[] m_arr;
        m_size = other.m_size;
        m_arr = new T[m_size];
    }

    std::copy(other.m_arr, other.m_arr + other.m_size, m_arr);

    return *this;
}


#endif //ARRAY_H