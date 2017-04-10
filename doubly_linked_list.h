// Copyright [2016] <Leonardo de Oliveira da Silva>

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>

//! Lista
/*!
    Lista
*/
class DoublyLinkedList {
 public:
    //! Construtor
    /*!
        Construtor
    */  
    DoublyLinkedList() {
        head = nullptr;
        size_ = 0;
    }

    //! Destrutor
    /*!
        Destroi
    */
    ~DoublyLinkedList() {
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
        
        while(atual != nullptr){
            anterior = atual;
            atual = atual->next();
            delete anterior;
        }

        size_ = 0;
    }

    void push_back(const T& data) {
        insert(data, size_);
    }

    void push_front(const T& data) {
        Node *newone = new Node(data);
        if (newone == nullptr) {
            throw std::out_of_range("Erro de alocação");
        } else {
            newone->next(head);
            newone->prev(nullptr);
            head = newone;
            if (newone->next() != nullptr)
                newone->next()->prev(newone);
            ++size_;
        }
    }

    void insert(const T& data, std::size_t index) {
        Node *prev, *newone;
        if (index > size_) {
            throw std::out_of_range("Posição inválida");
        } else if(index == 0) {
            push_front(data);
        } else{
            newone = new Node(data);
            if (newone == nullptr) {
                throw std::out_of_range("Erro de alocação");
            } else {
                prev = head;
                for (int i = 0; i < index -1; ++i) {
                    prev = prev->next();
                }
                newone->next(prev->next());
                if (newone->next() != nullptr)
                    newone->next()->prev(newone);
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
        
        node = head;
        while (node->next() != nullptr && data > node->data()) {
            node = node->next();
            ++pos;
        }

        if (data > node->data())
            return(insert(data, pos+1));
        
        return(insert(data, pos));
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

        Node *n = head;
        Node *exit;
        for (int i = 0; i < index - 1; ++i) {
            n = n->next();
        }
        exit = n->next();
        n->next(exit->next());
        T data = exit->data();
        if (exit->next() != nullptr)
            exit->next()->prev(n);
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
        Node *n;
        n = head;
        T ret = n->data();
        head = n->next();
        if (head != nullptr) {
            head->prev(nullptr);
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
    bool contains(const T& data) const{
        Node *n = head;
        while (n != nullptr) {
            if (n->data() == data)
                return true;
            n = n->next();
        }
        return false;
    }

    T& at(std::size_t index) {
        if (index < 0)
            throw std::out_of_range("Posição inválida");
        if (index > size_)
            throw std::out_of_range("Posição inválida");

        Node *ret = head;
        for (int i = 0; i < index; ++i) {
            if (ret->next() == nullptr)
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
        if (index < 0)
            throw std::out_of_range("Posição inválida");

        Node *ret = head;
        for (int i = 0; i < index; ++i) {
            if (ret->next() == nullptr)
                throw std::out_of_range("Posição inválida");
            ret = ret->next();
        }
        return ret->data();
    }

    //! Encontrar
    /*!
        \param data elemento a ser encontrado
        \return posição do data
    */
    std::size_t find(const T& data) const {
        if (empty())
            return -1;

        Node *n = head;
        std::size_t p = 0;

        while (n->data() != data) {
            n = n->next();
            ++p;
            if (n == nullptr)
                return p;
        }
        return p;
    }

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

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
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
        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }
     private :
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}  // namespace structures