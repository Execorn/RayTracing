#pragma once

#include <iostream>
#include <cassert>
#include <cstdint>

// ----------------------------------------------------------------

namespace DataTypes {

    template <class Type>
    void destroy(Type& element) {
        element.~Type();
    }

    template <int>
    void destroy(int& element) {}

    template <class Type, size_t array_size>
    class TArray_ {
        public:
            TArray_() {
                TArray_(0);
            }

            TArray_(const Type& fill_value) {
                for (size_t current_index = 0; current_index < array_size; ++current_index) {
                    this->data_[current_index] = fill_value;
                }
            }

            TArray_(const TArray_& array) {
                *this = array;
            }

            size_t size() const {
                return this->size_;
            }

            Type& operator[](size_t index) {
                return this->data_[index];
            }

            TArray_& operator=(const TArray_& array_to_assign) {
                for (size_t current_index = 0; current_index < array_size; ++current_index) {
                    this->data_[current_index] = array_to_assign.data_[current_index];
                }

                return *this;
            }

            void* operator new(size_t size) {
                std::cout << "Array: call new" << std::endl;

                void* new_pointer = calloc(size, 1);
                assert(new_pointer != nullptr && "Array allocation Error. Calloc failed.");

                return new_pointer;
            }

            void* operator new[](size_t size) {
                std::cout << "Array: call new[]" << std::endl;

                void* new_pointer = calloc(size, 1);
                assert(new_pointer != nullptr && "Array allocation Error. Calloc failed.");

                return new_pointer;
            }

            void operator delete(void* pointer) {
                std::cout << "Array: call delete" << std::endl;

                free(pointer);
            }

            void operator delete[](void* pointer) {
                std::cout << "Array: call delete[]" << std::endl;

                free(pointer);
            }

            ~TArray_() {
                for (size_t current_index = 0; current_index < array_size; ++current_index) {
                    destroy(this->data_[current_index]);
                }
            }

        private:    
            Type     data_[array_size];
            size_t size_ = array_size;    
    };

// ----------------------------------------------------------------

    const size_t VECTOR_STARTUP_CAPACITY     = 16;
    const size_t VECTOR_CAPACITY_RATE        = 2;

// ----------------------------------------------------------------

    template <class Type>
    class TVector_ {

        public:

            TVector_() {
                TVector_(0);
            }
            
            // disables implicit conversion using this constructor
            explicit TVector_(const size_t size):
                data_(nullptr), size_(size), capacity_(VECTOR_STARTUP_CAPACITY) {
                this->capacity_ = 1 << (63 - __builtin_clzll(this->size_) + 1);

                try {
                    data_ = new char[this->capacity_ * sizeof(Type)];
                }
                catch (std::bad_alloc& broken_alloc) {
                    std::cerr << "Vector: Allocation Error - not enough memory" << std::endl;

                    this->size_     = 0;
                    this->capacity_ = 0;

                    throw std::bad_alloc();
                }
                
                initialize(this->data_, 0, this->size_);
            }

            size_t size() const {
                return this->size_;
            }

            size_t capacity() const {
                return this->capacity_;
            }

            Type& operator[](const size_t index) const {
                if (index >= this->size_) {
                    throw std::range_error("Vector: Index out of range");
                }

                size_t index_for_char_array = index * sizeof(Type);
                return *((Type*) (this->data_ + index_for_char_array));
            }

            void initialize(char* pointer, size_t start, size_t end) {
                for (size_t current_index = start; current_index < end; ++current_index) {
                    new (pointer + current_index * sizeof(Type)) Type();
                }
            }

            void initialize(char* pointer, size_t start, size_t end, TVector_& vector) {
                for (size_t current_index = start; current_index < end; ++current_index) {
                    new (pointer + current_index * sizeof(Type)) Type(vector[current_index]);
                }
            }    

            bool change_size(size_t new_size) {
                // destroy
                if (new_size <= this->size_) {
                    for (size_t current_index = new_size; current_index < size_; current_index++) {
                        (*this)[current_index].~Type();
                    }

                    this->size_ = new_size;
                    return 0;
                }

                if (new_size <= this->capacity_) {
                    initialize(this->data_, new_size, this->size_);

                    this->size_ = new_size;
                    return 0;
                }

                size_t new_capacity = this->capacity_;
                
                new_capacity = 1 << (63 - __builtin_clzll(new_capacity) + 1);

                while (new_capacity < new_size) {
                    new_capacity *= VECTOR_CAPACITY_RATE;
                }

                char* new_pointer = nullptr;
                try {
                    new_pointer = new char[new_capacity * sizeof(Type)]();
                }
                catch (std::bad_alloc&) {
                    std::cerr << "Vector: Increase Error - lack of memory" << std::endl;

                    throw;
                }

                initialize(new_pointer, 0, this->size_, *this);

                initialize(new_pointer, this->size_, new_size);

                delete[] this->data_;

                this->data_     =  new_pointer;
                this->capacity_ = new_capacity;
                this->size_     =     new_size;

                return 0;
            }

            bool push_back(const Type& element) {
                try { 
                    this->change_size(this->size_ + 1); 
                }
                catch (std::bad_alloc& broken_alloc) {
                    std::cerr << "Vector: Push_back Error while pushing " << element << " - not enough memory" << std::endl;
                    return 1; // error
                }
                
                (*this)[this->size_ - 1] = element;
                return 0;
            }

            TVector_& operator=(const TVector_& vector) {
                //TODO: check this == vector

                this->change_size(vector.size());

                for (size_t current_index = 0; current_index < this->size_; ++current_index) {
                    (*this)[current_index] = vector[current_index];
                }

                return *this;
            }

            TVector_(const TVector_& vector) :
                data_(new char[vector.capacity() * sizeof(Type)]),
                size_(vector.size()), 
                capacity_(vector.capacity())
            {
                initialize(this->data_, 0, this->size_, const_cast<TVector_&> (vector));
            }

            void* operator new(size_t new_size) {
                std::cout << "Vector: call new" << std::endl;

                void* new_pointer = calloc(new_size, 1);
                if (new_pointer == nullptr) throw std::bad_alloc();

                return new_pointer;
            }

            void* operator new[](size_t new_size) {
                std::cout << "Vector: call new[]" << std::endl;

                void* new_pointer = calloc(new_size, 1);
                if (new_pointer == nullptr) {
                    throw std::bad_alloc();
                }

                return new_pointer;
            }

            void operator delete(void* pointer) {
                std::cout << "Vector: call delete" << std::endl;

                free(pointer);
            }

            void operator delete[](void* pointer) {
                std::cout << "Vector: call delete[]" << std::endl;

                free(pointer);
            }

            ~TVector_() {
                change_size(0);
            }

        private:
            char*  data_;

            size_t size_;
            size_t capacity_;
    
    };

    template <class Type>
    std::ostream& operator<<(std::ostream& stream, TVector_<Type> vector) {
        for (size_t current_index = 0; current_index < vector.size(); ++current_index) {
            stream << vector[current_index] << " ";
        }

        return stream;
    }

    template <class Type, size_t array_size>
    std::ostream& operator<<(std::ostream& stream, TArray_<Type, array_size> array) {
        for (size_t current_index = 0; current_index < array_size; ++current_index) {
            stream << array[current_index] << " ";
        }

        return stream;
    }
};

// ----------------------------------------------------------------