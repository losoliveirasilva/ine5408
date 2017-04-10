// Copyright [2016] <Leonardo de Oliveira da Silva>
namespace structures {

template<typename T>
//! Lista Circular
/*!
    Lista Circular
*/
class DoublyCircularList {
 public:
    //! Construtor
    /*!
        Construtor
    */  
    DoublyLinkedList() {
        head = new Node(0);
        head->next(head);
        head->prev(head);
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
        while (size_ != 0)
            pop_front();
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
        ++size_;
        if (empty()) {
            head->next(new Node(data, head, head));
            return;
        }
        head->next(new Node(data, head, head->next()));
    }

    //! Insere
    /*!
        \param data Dado a ser inserido
        \param index Local a ser inserido
    */
    void insert(const T& data, std::size_t index) {
        if (index > size_)
            throw std::out_of_range("Posição inválida"); 

        if(index == 0) {
            push_front(data);
        } else{
            Node *prev;
            prev = head->next();
            for (int i = 0; i < index -1; ++i) {
                prev = prev->next();
            }
            prev->next(new Node(data, prev->prev(), prev->next()));
            ++size_;
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
        n->prev(exit->prev());
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
        return pop(size_ -1);
    }
    
    //! Retira do início
    /*!
        \return O elemento da primeira posição
    */
    T pop_front() {
        if (empty())
            throw std::out_of_range("Lista vazia");
        Node *n;
        n = head->next();
        T ret = n->data();
        head->next(n->next());
        head->next()->prev(head);
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
        if (empty())
                throw std::out_of_range("Lista vazia");

        Node *n = head->next();
        while (n != head) {
            if (n->data() == data)
                return true;
            n = n->next();
        }
        return false;
    }

    //! At
    /*!
        \param index Posição do elemento
        \return Elemento na posição index
    */
    T& at(std::size_t index) {
        if (index > size_)
            throw std::out_of_range("Posição inválida.");

        if (empty())
            throw std::out_of_range("Lista vazia!");

        Node *n = head->next();

        for (int i = 0; i < index; ++i)
            n = n->next();

        return n->data();
    }

    //! At const
    /*!
        \param index Posição do elemento
        \return Elemento na posição index
    */
    const T& at(std::size_t index) const {
        Node *n = head->next();

        for (int i = 0; i < index; ++i)
            n = n->next();

        return n->data();
    }

    //! Encontrar
    /*!
        \param data elemento a ser encontrado
        \return posição do data
    */
    std::size_t find(const T& data) const {
        Node *n = head->next();
        for (int i = 0; i < size_; ++i) {

            if (n->data() == data)
                return i;

            n = n->next();
        }

        return size_;
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

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
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
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace
