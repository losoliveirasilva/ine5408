// Copyright [2016] <Leonardo de Oliveira da Silva>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures  {

template<typename T>
//! Lista Circular
/*!
    Lista Circular
*/
class CircularList  {
 public:
    //! Construtor
    /*!
        Construtor
    */
    CircularList() {
        head = new Node(0);
        head->next(head);
        size_ = 0;
    }

    //! Destrutor
    /*!
        Destroi
    */
    ~CircularList() {
        clear();
        // delete head->next();
    }

    //! Limpa
    /*!
        Limpa
    */
    void clear() {
        while (size_ != 0) {
            pop_front();
        }
    }

    //! Insere na última posição
    /*!
        \param data Dado a ser inserido
    */    
    void push_back(const T& data) {
        insert(data, size_);
    }

    //! Insere na primeira posição
    /*!
        \param data Dado a ser inserido
    */
    void push_front(const T& data) {
        Node *newone = new Node(data);
        if (newone == nullptr) {
            throw std::out_of_range("Erro de alocação");
        } else {
            Node *first = head->next();
            newone->next(first);
            head->next(newone);
            ++size_;
        }
    }

    //! Insere
    /*!
        \param data Dado a ser inserido
        \param index Local a ser inserido
    */
    void insert(const T& data, std::size_t index) {
        Node *prev, *newone;
        if (index > size_) {
            throw std::out_of_range("Posição inválida");
        } else if (index == 0) {
            push_front(data);
        } else {
            newone = new Node(data);
            if (newone == nullptr) {
                throw std::out_of_range("Erro de alocação");
            } else {
                prev = head->next();
                for (int i = 0; i < index -1; ++i) {
                    prev = prev->next();
                }
                newone->next(prev->next());
                prev->next(newone);
                ++size_;
            }
        }
    }

    //! Insere ordenado
    /*!
        \param data a ser inserido
    */
    void insert_sorted(const T& data) {
        Node *node;
        int pos = 0;
        if (empty())
            return(push_front(data));
        node = head->next();
        while (node->next() != head && data > node->data()) {
            node = node->next();
            ++pos;
        }

        if (data > node->data())
            return(insert(data, pos+1));
        return(insert(data, pos));
    }

    //! At
    /*!
        \param index Posição do elemento
        \return Elemento na posição index
    */
    T& at(std::size_t index) {
        if (index < 0)
            throw std::out_of_range("Posição inválida");

        Node *ret = head->next();
        for (int i = 0; i < index; ++i) {
            if (ret->next() == head)
                throw std::out_of_range("Posição inválida");
            ret = ret->next();
        }
        return ret->data();
    }

    //! At const
    /*!
        \param index Posição do elemento
        \return Elemento na posição index
    */
    const T& at(std::size_t index) const {
        Node *ret = head->next();
        for (int i = 0; i < index; ++i) {
            ret = ret->next();
        }
        return ret->data();
    }

    //! Retira na posição
    /*!
        \param index posição
        \return O elemento na posição
    */
    T pop(std::size_t index) {
        if (empty())
            throw std::out_of_range("Lista vazia");
        if (index >= size_)
            throw std::out_of_range("Indice inválido");
        if (index == 0)
            return pop_front();

        Node *n = head->next();
        Node *exit;
        for (int i = 0; i < index - 1; ++i) {
            n = n->next();
        }
        exit = n->next();
        n->next(exit->next());
        T data = exit->data();
        --size_;
        delete exit;
        return data;
    }

    //! Retira do fim
    /*!
        \return O elemento da última posição
    */
    T pop_back() {
        return pop(size_ - 1);
    }

    //! Retira do início
    /*!
        \return O elemento da primeira posição
    */
    T pop_front() {
        if (empty())
            throw std::out_of_range("Lista vazia");
        /* if (size_ == 1) {
            Node *m = head->next();
            T mret = m->data();
            head->next(head->next());
            delete m;
            return mret;
        } */

        Node *n = head->next();
        T ret = n->data();
        head->next(n->next());
        --size_;
        delete n;
        return ret;
    }

    //! Remover
    /*!
        \param data Elemento a ser removido
    */
    void remove(const T& data) {
        pop(find(data));
    }

    //! Vazia
    /*!
        \return true se a lista estiver vazia
    */
    bool empty() const {
        return(size_ == 0);
    }

    //! Contém
    /*!
        \param data elemento a ser encontrado
        \return true se a lista contém data
    */
    bool contains(const T& data) const {
        Node *n = head->next();
        while (n != head) {
            if (n->data() == data)
                return true;
            n = n->next();
        }
        return false;
    }

    //! Encontrar
    /*!
        \param data elemento a ser encontrado
        \return posição do data
    */
    std::size_t find(const T& data) const {
        if (empty())
            return -1;

        Node *n = head->next();
        std::size_t p = 0;
        while (n->data() != data && n != head) {
            n = n->next();
            ++p;
            if (n == head)
                return p;
        }
        return p;
    }

    //! Tamanho
    /*!
        \return tamanho da lista
    */
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
