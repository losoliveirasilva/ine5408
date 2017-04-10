// Copyright [2016] <Leonardo de Oliveira da Silva>
#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Pilha Encadeada
/*!
     Pilha encadeada
*/
class LinkedStack {
 public:
    //! Construtor
    /*!
        Construtor
    */
    LinkedStack() {
        top_ = nullptr;
        size_ = 0;
    }

    //! Destrutor
    /*!
        Destroi
    */
    ~LinkedStack() {
        clear();
    }

    //! Limpa
    /*!
        Limpa
    */
    void clear() {
        Node *atual, *anterior;
        atual = top_;
        top_ = nullptr;

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
    void push(const T& data) {
        Node *newone;
        newone = new Node(data);
        if (newone == nullptr) {
            throw std::out_of_range("Erro de alocação");
        } else {
            newone->next(top_);
            top_ = newone;
            ++size_;
        }
    }

    //! Retira do início
    /*!
        \return O elemento da primeira posição
    */
    T pop() {
        if (empty())
            throw std::out_of_range("Lista vazia");
        Node *n;
        n = top_;
        T ret = n->data();
        top_ = n->next();
        --size_;
        delete n;
        return ret;
    }

    //! Retira
    /*!
        \return O elemento da primeira posição
    */
    T& top() const {
        if (empty())
            throw std::out_of_range("Lista vazia");
        return top_->data();
    }

    //! Vazia
    /*!
        \return true se a lista estiver vazia
    */
    bool empty() const {
        return (size_ == 0);
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

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

