#ifndef BST_HPP
#define BST_HPP

#include <cstddef>

namespace utec {
    template <typename T>
    struct bst {
    private:
        struct Node {
            T data;
            Node* right = nullptr;
            Node* left = nullptr;
            Node* padre = nullptr;
            Node (const T& val): data(val) {}
        };
        Node* root = nullptr;
        size_t sz = 0;

    public:
        bst () {}
        bst (const T& x){
            insert(x);
        }
        ~bst () {
            clear();
        }

        T* search (const T& k) {
            Node* ans = search(k, root);
            return (ans == nullptr) ? nullptr : &ans->data;
        }

        T* successor (const T& k) {
            Node* current = search(k, root);
            if (current == nullptr) return nullptr;
            if (current->right != nullptr) return &min_node(current->right)->data;
            Node* padre = current->padre;
            while (padre != nullptr and current == padre->right) {
                current = padre;
                padre = padre->padre;
            }
            return (padre == nullptr) ? nullptr : &padre->data;
        }

        T* predeccessor (const T& k) {
            Node* current = search(k, root);
            if (current == nullptr) return nullptr;
            if (current->left != nullptr) return &max_node(current->left)->data;
            Node* padre = current->padre;
            while (padre != nullptr and current == padre->left) {
                current = padre;
                padre = padre->padre;
            }
            return (padre == nullptr) ? nullptr : &padre->data;
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
            Node* current = root;
            Node* parent = nullptr;

            while (current != nullptr) {
                parent = current;
                if (k < current->data) current = current->left;
                else if (current->data < k) current = current->right;
                else return;
            }

            Node* new_node = new Node(k);
            new_node->padre = parent;

            if (parent == nullptr) root = new_node;
            else if (k < parent->data) parent->left = new_node;
            else parent->right = new_node;

            sz++;
        }

        void remove(const T& k) {
            Node* z = search(k, root);
            if (z == nullptr) return;

            if (z->left == nullptr) {
                transplant(z, z->right);
            } else if (z->right == nullptr) {
                transplant(z, z->left);
            } else {
                Node* y = min_node(z->right);
                if (y->padre != z) {
                    transplant(y, y->right);
                    y->right = z->right;
                    if (y->right) y->right->padre = y;
                }
                transplant(z, y);
                y->left = z->left;
                if (y->left) y->left->padre = y;
            }
            delete z;
            sz--;
        }

        void clear () {
            clear_node(root);
            root = nullptr;
            sz = 0;
        }

        size_t size() const { return sz; }
        bool empty() const { return sz == 0; }

    private:
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

        void transplant (Node* u, Node* v) {
            if (u->padre == nullptr) root = v;
            else if (u == u->padre->left) u->padre->left = v;
            else u->padre->right = v;
            if (v != nullptr) v->padre = u->padre;
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
