#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures {

template<typename T>
class ArrayQueue {
public:

    //! Construtor
    /*!
        \param max tamanho máximo da fila [opcional]
    */
    ArrayQueue(std::size_t max = DEFAULT_SIZE){
        contents = new T[max];
        size_ = -1;
        max_size_ = max;
    }

    //! Destrutor
    /*!
        Destroi
    */
    ~ArrayQueue(){
        delete[] contents;
    }

    //! Enfileira
    /*!
        \param data dado a ser enfileirado
    */
    void enqueue(const T& data){
        if(full())
            throw std::out_of_range("pilha cheia");

        size_++;
        contents[size_] = data;
    }

    //! Retira
    /*!
        \return dado retirado da fila
    */
    T dequeue(){
        if(empty())
            throw std::out_of_range("pilha vazia");

        T return_ = contents[0];

        for(int i = 0; i < size_; i++){
            contents[i] = contents[i+1];
        }

        size_--;

        return return_;
    }

    //! Back
    /*!
        \return Último elemento da fila
    */
    T& back(){
        if(empty())
            throw std::out_of_range("pilha vazia");

        return contents[size_];
    }

    //! Limpa
    /*!
        Limpa a fila
    */
    void clear(){
        size_ = -1;
    }

    //! Tamanho
    /*!
        \return o tamanho atual da fila
    */
    std::size_t size(){
        return size_ + 1;
    }

    //! Tamanho máximo
    /*!
        \return o tamanho máximo da fila
    */
    std::size_t max_size(){
        return max_size_;
    }

    //! Vazia
    /*!
        \return true se a fila estiver vazia
    */
    bool empty(){
        return (size_ == -1);
    }

    //! Cheia
    /*!
        \return true se a fila estiver cheia
    */
    bool full(){
        return (size_ + 1 == max_size_);
    }

private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    const static auto DEFAULT_SIZE = 10u;
};

}

#endif
