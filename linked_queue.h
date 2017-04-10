// Copyright [2016] <Leonardo de Oliveira da Silva>
#include <cstdint>
#include <stdexcept>

namespace structures {


template<typename T>
//! Fila
/*!
    Fila
*/
class LinkedQueue {
 public:
    //! Construtor
    /*!
        Construtor
    */
    LinkedQueue() {
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }

    //! Destrutor
    /*!
        Destroi
    */
    ~LinkedQueue() {
        clear();
    }

    //! Limpa
    /*!
        Limpa
    */
    void clear() {
        Node *atual, *anterior;
        atual = head;
        head = nullptr;
        while (atual != nullptr) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
        }

        size_ = 0;
    }

    //! Insere
    /*!
        \param data Dado a ser inserido
    */
    void enqueue(const T& data) {
        Node *newone = new Node(data, nullptr);
        if (newone == nullptr) {
            throw std::out_of_range("Erro de alocação");
        } else if (empty()) {
            head = newone;
            tail = newone;
            ++size_;
        } else {
            tail->next(newone);
            tail = newone;
            ++size_;
        }
    }

    //! Retira
    /*!
        \return O elemento da primeira posição
    */
    T dequeue() {
        if (empty())
            throw std::out_of_range("Lista vazia");
        Node *n;
        n = head;
        T ret = n->data();
        head = n->next();
        --size_;
        delete n;
        return ret;
    }

    //! Front
    /*!
        \return elemento
    */
    T& front() const {
        if (empty())
            throw std::out_of_range("Lista vazia");
        return head->data();
    }

    //! Back
    /*!
        \return elemento
    */
    T& back() const {
        if (empty())
            throw std::out_of_range("Lista vazia");
        return tail->data();
    }

    //! Vazia
    /*!
        \return true se a lista estiver vazia
    */
    bool empty() const {
        return(size_ == 0);
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

    Node* head;
    Node* tail;
    std::size_t size_;
};

}  // namespace structures

