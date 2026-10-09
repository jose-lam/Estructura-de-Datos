#ifndef AVL_HPP
#define AVL_HPP

#include <cstddef>

namespace utec {
    template <typename T>
    struct avl {
    private:
        struct Node {
            T data;
            int altura;
            Node* right = nullptr;
            Node* left = nullptr;
            Node (const T& val): data(val), altura(0) {}
        };
        Node* root = nullptr;
        size_t sz = 0;

    public:
        avl () {}
        avl (const T& x){
            insert(x);
        }
        ~avl () {
            clear();
        }

        T* search (const T& k) {
            Node* ans = search(k, root);
            return (ans == nullptr) ? nullptr : &ans->data;
        }

        T* min() {
            Node* m = min_node(root);
            return m ? &m->data : nullptr;
        }

        T* max() {
            Node* m = max_node(root);
            return m ? &m->data : nullptr;
        }

        void insert (const T& k) {
            root = insert(root, k);
        }

        void remove(const T& k) {
            root = remove(root, k);
        }

        void clear () {
            clear_node(root);
            root = nullptr;
            sz = 0;
        }

        size_t size() const { return sz; }
        bool empty() const { return sz == 0; }

    private:

        int h (Node* current) {
            if (current == nullptr) return -1;
            return current->altura;
        }

        void actualizar (Node* current) {
            if (current == nullptr) return;
            int izq = h(current->left);
            int der = h(current->right);
            current->altura = 1 + (izq > der ? izq : der);
        }

        int fb (Node* current) {
            return h(current->left) - h(current->right);
        }

        Node* right_rotation (Node* current) {
            Node* x = current->left;
            current->left = x->right;
            x->right = current;
            actualizar(current);
            actualizar(x);
            return x;
        }

        Node* left_rotation (Node* current) {
            Node* x = current->right;
            current->right = x->left;
            x->left = current;
            actualizar(current);
            actualizar(x);
            return x;
        }

        Node* rebalancear (Node* current) {
            actualizar(current);
            if (fb(current) > 1) {
                if (fb(current->left) < 0) current->left = left_rotation(current->left);
                return right_rotation(current);
            }
            if (fb(current) < -1) {
                if (fb(current->right) > 0) current->right = right_rotation(current->right);
                return left_rotation(current);
            }
            return current;
        }

        Node* insert (Node* current, const T& k) {
            if (current == nullptr) {
                ++sz;
                return new Node(k);
            }
            if (k < current->data) current->left = insert(current->left, k);
            else if (current->data < k) current->right = insert(current->right, k);
            return rebalancear(current);
        }

        Node* remove (Node* current, const T& k) {
            if (current == nullptr) return nullptr;
            if (k < current->data) current->left = remove(current->left, k);
            else if (current->data < k) current->right = remove(current->right, k);
            else {
                if (current->left == nullptr || current->right == nullptr) {
                    Node* hijo = (current->left != nullptr) ? current->left : current->right;
                    delete current;
                    --sz;
                    return hijo;
                }
                Node* s = min_node(current->right);
                current->data = s->data;
                current->right = remove(current->right, current->data);
            }
            return rebalancear(current);
        }

        Node* search (const T& k, Node* current) {
            while (current != nullptr) {
                if (k < current->data) current = current->left;
                else if (current->data < k) current = current->right;
                else return current;
            }
            return nullptr;
        }

        void clear_node (Node* current) {
            if (current == nullptr) return;
            clear_node(current->right);
            clear_node(current->left);
            delete current;
        }

        Node* min_node(Node* current) const {
            if (current == nullptr) return nullptr;
            while (current->left != nullptr) current = current->left;
            return current;
        }

        Node* max_node(Node* current) const {
            if (current == nullptr) return nullptr;
            while (current->right != nullptr) current = current->right;
            return current;
        }
    };
}

#endif
