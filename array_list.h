#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

template<typename T>
class ArrayList {
public:
    //! Construtor
    /*!
        \param max tamanho máximo da lista [opcional]
    */
    ArrayList(std::size_t max_size = DEFAULT_MAX){
        contents = new T[max_size];
        size_ = 0;
        max_size_ = max_size;
    }

    //! Destrutor
    /*!
        Destroi
    */
    ~ArrayList(){
        delete[] contents;
    }

    void clear(){
        size_ = 0;
    }

    //! Insere na última posição
    /*!
        \param data Dado a ser inserido
    */
    void push_back(const T& data){
        insert(data, size_);
    }

    //! Insere na primeira posição
    /*!
        \param data Dado a ser inserido
    */
    void push_front(const T& data){
        insert(data, 0);
    }
    
    //! Insere
    /*!
        \param data Dado a ser inserido
        \param index Local a ser inserido
    */
    void insert(const T& data, std::size_t index){
        if(full())
            throw std::out_of_range("fila cheia");
        else if(index > size_ || index < 0)
            throw std::out_of_range("posição invalida"); 

        for(int i = size_; i > index; i--){
            contents[i] = contents[i-1];
        }

        size_++;
        contents[index] = data;
    }

    //! Insere ordenado
    /*!
        \param data a ser inserido
    */
    void insert_sorted(const T& data){
        if(full())
            throw std::out_of_range("lista cheia");

        std::size_t t = 0;
        while(t < size_ && data > contents[t])
            t++;
        insert(data, t);
    }

    //! Retira na posição
    /*!
        \param index posição
        \return O elemento na posição
    */
    T pop(std::size_t index){
        if(empty())
            throw std::out_of_range("lista vazia");
        
        if(size_ <= index || index < 0)
            throw std::out_of_range("posicação inválida");

        T ret_data = contents[index];
        for(int i = index; i < size_; ++i){
            contents[i] = contents[i+1];
        }
        size_--;
        return ret_data;
    }

    //! Retira do fim
    /*!
        \return O elemento da última posição
    */
    T pop_back(){
        return pop(size_-1);
    }

    //! Retira do início
    /*!
        \return O elemento da primeira posição
    */
    T pop_front(){
        return pop(0);
    }

    //! Remover
    /*!
        \param data Elemento a ser removido
    */
    void remove(const T& data){
        for(int i = 0; i < size_ - 1; ++i){
            if(contents[i] == data){
                size_--;
                for(int k = i; k < size_; ++k){
                    contents[k] = contents[k+1];
                }
            }
        }
    }

    //! Cheia
    /*!
        \return true se a lista estiver cheia
    */
    bool full() const{
        return (size_ == max_size_);
    }

    //! Vazia
    /*!
        \return true se a lista estiver vazia
    */
    bool empty() const{
        return (size_ == 0);
    }

    //! Contém
    /*!
        \param data elemento a ser encontrado
        \return true se a lista contém data
    */
    bool contains(const T& data) const{
        for (int i = 0; i < size_; ++i){
            if(contents[i] == data){
                return true;
            }
        }
        return false;
    }

    //! Encontrar
    /*!
        \param data elemento a ser encontrado
        \return posição do data
    */
    std::size_t find(const T& data) const{
        std::size_t place = -1;
        for (int i = 0; i < size_; ++i){
            if(contents[i] == data){
                place = i;
            }
        }

        if(place == -1)
            return size_;
        else
            return place;
    }

    //! Tamanho
    /*!
        \return tamanho da lista
    */
    std::size_t size() const{
        return size_;
    }

    //! Tamanho máximo
    /*!
        \return tamanho máximo da lista
    */
    std::size_t max_size() const{
        return max_size_;
    }

    //! At (com checagem)
    /*!
        \param index Posição do elemento
        \return Elemento na posição index
    */
    T& at(std::size_t index){
        if(empty())
            throw std::out_of_range("lista vazia");
        else if(index > size_ || index < 0)
            throw std::out_of_range("posição inválida");
        else
            return contents[index];
    }

    //! Operator (sem checagem)
    /*!
        \param index Posição do elemento
        \return Elemento na posição index
    */
    T& operator[](std::size_t index){
        return contents[index];
    }

    //! At (com checagem, e sem mexer no objeto)
    /*!
        \param index Posição do elemento
        \return Elemento na posição index
    */
    const T& at(std::size_t index) const{
        if(empty())
            throw std::out_of_range("lista vazia");
        else if(index > size_ || index < 0)
            throw std::out_of_range("posição inválida");
        else
            return contents[index];
    }

    //! Operator (sem checagem e sem mexer no objeto)
    /*!
        \param index Posição do elemento
        \return Elemento na posição index
    */
    const T& operator[](std::size_t index) const{
        return contents[index];
    }

private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    const static auto DEFAULT_MAX = 10u;
};

}

#endif
