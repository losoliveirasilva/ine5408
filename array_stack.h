#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures {

template<typename T>
//! Pilha com Vetor
/*!
    Pilha implementada utilizando vetor
*/
class ArrayStack {
public:
    //! Construtor
    /*!
        \param max tamanho máximo da pilha [opcional]
    */
    ArrayStack(std::size_t max = DEFAULT_SIZE){
        contents = new T[max];
        top_ = -1;
        max_size_ = max;
    }

    //! Destrutor
    /*!
        Destroi
    */
    ~ArrayStack(){
        delete[] contents;
    }

    //! Empilha
    /*!
        \param data tamanho máximo da pilha [opcional]
    */
    void push(const T& data){ // empilha
        if(full())
            throw std::out_of_range("pilha cheia");

        top_++;
        contents[top_] = data;
    }

    //! Desempilha
    /*!
        \return O último elemento da pilha e o desempilha
    */
    T pop(){ // desempilha
        if(empty())
            throw std::out_of_range("pilha vazia");

        top_--;
        return(contents[top_ + 1]);
    }

    //! Topo
    /*!
        \return O último elemento da pilha
    */
    T& top(){
        if(empty())
            throw std::out_of_range("pilha vazia");

        return(contents[top_]);
    }

    //! Limpar
    /*!
        Limpa a pilha
    */
    void clear(){ // limpa
        top_ = -1;
    }

    //! Tamanho
    /*!
        \return O tamanho da atual da pilha
    */
    std::size_t size(){ // tamanho
        return top_ + 1;
    }

    //! Tamanho máximo
    /*!
        \return O tamanho máximo da pilha
    */
    std::size_t max_size(){
        return max_size_;
    }

    //! Vazia
    /*!
        \return true se a pilha estiver vazia
    */
    bool empty(){ // vazia
        if(top_ == -1)
            return true;
        else
            return false;
    }

    //! Cheia
    /*!
        \return true se a pilha estiver cheia
    */
    bool full(){ // cheia
        if(top_ == max_size_ -1)
            return true;
        else
            return false;
    }

private:
    T* contents;
    int top_;
    std::size_t max_size_;

    const static auto DEFAULT_SIZE = 10u;
};

}

#endif
