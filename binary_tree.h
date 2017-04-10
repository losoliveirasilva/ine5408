// Copyright [2016] <Leonardo de Oliveira da Silva>
#include "array_list.h"


namespace structures {

template<typename T>
    //! Lista Encadeada
    /*!
        Lista encadeada
    */
    class BinaryTree {
        public:
            //! Destrutor
            /*!
                Destroi
            */
            ~BinaryTree() {

            }

            //! Insere elemento na arvore
            /*!
                \param data Dado a ser inserido
            */    
            void insert(const T& data) {
            }

            //! Remove elemento da arvore
            /*!
                \param data Dado a ser removido
            */    
            void remove(const T& data) {
            }

            //! Contém
            /*!
                \param data elemento a ser encontrado
                \return true se a arvore contém data
            */
            bool contains(const T& data) const {
            }

            //! Vazia
            /*!
                \return true se a fila estiver vazia
            */
            bool empty() const {
            }

            //! Tamanho
            /*!
                \return tamanho da arvore
            */
            std::size_t size() const {
            }

            //! Tree traversal, in Pre-order.
            /*!
                Returns and array list of the tree in pre-order.
            */
            ArrayList<T> pre_order() const {
            }

            //! Tree traversal, In-order.
            /*!
                Returns and array list of the tree in-order.
            */
            ArrayList<T> in_order() const {
            }

            //! Tree traversal, in Post-order.
            /*!
                Returns and array list of the tree in post-order.
            */
            ArrayList<T> post_order() const {
            }

        private:
            struct Node {
                Node(const T& data) {
                }

                T data;
                Node* left;
                Node* right;

                void insert(const T& data_) {
                }

                bool remove(const T& data_) {
                }

                bool contains(const T& data_) const {
                }

                void pre_order(ArrayList<T>& v) const {
                }

                void in_order(ArrayList<T>& v) const {
                }

                void post_order(ArrayList<T>& v) const {
                }
            };

            Node* root;
            std::size_t size_;
    };

}
