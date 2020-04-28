#include <fstream>
#include <iostream>
enum COLOR{RED, BLACK};
std::ifstream in("abce.in");
std::ofstream out("abce.out");

struct Node{
    COLOR color;
    int key;
    Node *left, *right, *p;

    Node(COLOR _color, int _key, Node* _left, Node* _right, Node* _p){
        color = _color;
        key = _key;
        left = _left;
        right = _right;
        p = _p;
    }
};
typedef struct Node* Nod;

class RBT{
private:
    Nod root;
    Nod NIL;

    Nod TreeMinimum(Nod x);
    Nod TreeMaximum(Nod x);
    Nod SearchNode(int val);
    void LeftRotate(Nod x);
    void RightRotate(Nod x);
    void InsertNode(Nod z);
    void InsertFixup(Nod z);
    void Replace(Nod u, Nod v);
    void DeleteNode(Nod z);
    void DeleteFixup(Nod x);

public:
    RBT(){
        NIL = new Node(BLACK, 0, nullptr, nullptr, nullptr);
        root = NIL;
    }
    int Minimum();
    int Maximum();
    int Search(int val);
    void Insert(int val);
    void Delete(int val);
    int Successor(int val);
    int Predecessor(int val);
    void Sort(int l, int r);
};

Nod RBT::TreeMinimum(Nod x){
    while(x -> left != NIL)
        x = x -> left;
    return x;
}
Nod RBT::TreeMaximum(Nod x){
    while(x -> right != NIL)
        x = x -> right;
    return x;
}
int RBT::Minimum(){
    return TreeMinimum(root) -> key;
}
int RBT::Maximum(){
    return TreeMaximum(root) -> key;
}
Nod RBT::SearchNode(int val){
    Nod x = root;
    while(x != NIL && x -> key != val){
        if(val < x -> key)
            x = x -> left;
        else
            x = x -> right;
    }
    return x;
}
int RBT::Search(int val){
    return SearchNode(val) != NIL;
}
void RBT::LeftRotate(Nod x){
    Nod y = x -> right;
    x -> right = y -> left;
    if(y -> left != NIL)
        y -> left -> p = x;
    y -> p = x -> p;
    if(x -> p == NIL)
        root = y;
    else if(x == x -> p -> left)
        x -> p -> left = y;
    else
        x -> p -> right = y;
    y -> left = x;
    x -> p = y;
}
void RBT::RightRotate(Nod x){
    Nod y = x -> left;
    x -> left = y -> right;
    if(y -> right != NIL)
        y -> right -> p = x;
    y -> p = x -> p;
    if(x -> p == NIL)
        root = y;
    else if(x == x -> p -> right)
        x -> p -> right = y;
    else
        x -> p -> left = y;
    y -> right = x;
    x -> p = y;
}
void RBT::InsertNode(Nod z){
    Nod y = NIL;
    Nod x = root;
    while(x != NIL){
        y = x;
        if(z -> key < x -> key)
            x = x -> left;
        else
            x = x -> right;
    }
    z -> p = y;
    if(y == NIL)
        root = z;
    else if(z -> key < y -> key)
        y -> left = z;
    else
        y -> right = z;
    z -> left = NIL;
    z -> right = NIL;
    z -> color = RED;
    InsertFixup(z);
}
void RBT::InsertFixup(Nod z){
    while(z -> p -> color == RED)
        if(z -> p == z -> p -> p -> left){
            Nod y = z -> p -> p -> right;
            if(y -> color == RED){
                z -> p -> color = BLACK;
                y -> color = BLACK;
                z -> p -> p -> color = RED;
                z = z -> p -> p;
            }
            else{
                if(z == z -> p -> right){
                    z = z -> p;
                    LeftRotate(z);
                }
                z -> p -> color = BLACK;
                z -> p -> p -> color = RED;
                RightRotate(z -> p -> p);
            }
        }
        else{
            Nod y = z -> p -> p -> left;
            if(y -> color == RED){
                z -> p -> color = BLACK;
                y -> color = BLACK;
                z -> p -> p -> color = RED;
                z = z -> p -> p;
            }
            else{
                if(z == z -> p -> left){
                    z = z -> p;
                    RightRotate(z);
                }
                z -> p -> color = BLACK;
                z -> p -> p -> color = RED;
                LeftRotate(z -> p -> p);
            }
        }
    root->color = BLACK;
}
void RBT::Insert(int val){
    Nod z = new Node(RED, val, NIL, NIL, NIL);
    InsertNode(z);
}
void RBT::Replace(Nod u, Nod v){
    if(u -> p == NIL)
        root = v;
    else if(u == u -> p -> left)
        u -> p -> left = v;
    else
        u -> p -> right = v;
    v -> p = u -> p;
}
void RBT::DeleteNode(Nod z){
    Nod x, y = z;
    COLOR yOriginalColor = y -> color;
    if(z -> left == NIL){
        x = z -> right;
        Replace(z, z -> right);
    }
    else if(z -> right == NIL){
        x = z -> left;
        Replace(z, z -> left);
    }
    else{
        y = TreeMinimum(z -> right);
        yOriginalColor = y -> color;
        x = y -> right;
        if(y -> p == z)
            x -> p = y;
        else{
            Replace(y, y -> right);
            y -> right = z -> right;
            y -> right -> p = y;
        }
        Replace(z, y);
        y -> left = z -> left;
        y -> left -> p = y;
        y -> color = z -> color;
    }
    delete z;
    if(yOriginalColor == BLACK)
        DeleteFixup(x);
}
void RBT::DeleteFixup(Nod x){
    while(x != root && x -> color == BLACK){
        if(x == x -> p -> left){
            Nod w = x -> p -> right;
            if(w -> color == RED){
                w -> color = BLACK;
                x -> p -> color = RED;
                LeftRotate(x -> p);
                w = x -> p -> right;
            }
            if(w -> left -> color == BLACK && w -> right -> color == BLACK){
                w -> color = RED;
                x = x -> p;
            }
            else{
                if(w -> right -> color == BLACK){
                    w -> left -> color = BLACK;
                    w -> color = RED;
                    RightRotate(w);
                    w = x -> p -> right;
                }
                w -> color = x -> p -> color;
                x -> p -> color = BLACK;
                w -> right -> color = BLACK;
                LeftRotate(x -> p);
                x = root;
            }
        }
        else{
            Nod w = x -> p -> left;
            if(w -> color == RED){
                w -> color = BLACK;
                x -> p -> color = RED;
                RightRotate(x -> p);
                w = x -> p -> left;
            }
            if(w -> left -> color == BLACK && w -> right -> color == BLACK){
                w -> color = RED;
                x = x -> p;
            }
            else{
                if(w -> left -> color == BLACK){
                    w -> right -> color = BLACK;
                    w -> color = RED;
                    LeftRotate(w);
                    w = x -> p -> left;
                }
                w -> color = x -> p -> color;
                x -> p -> color = BLACK;
                w -> left -> color = BLACK;
                RightRotate(x -> p);
                x = root;
            }
        }
    }
    x -> color = BLACK;
}
void RBT::Delete(int val){
    Nod x = SearchNode(val);
    if(x != NIL)
        DeleteNode(x);
}
int RBT::Successor(int val){
    Nod x = root;
    int ans;
    while(x != NIL){
        if(x -> key == val)
            return x -> key;
        if(x -> key < val)
            x = x -> right;
        else{
            ans = x -> key;
            x = x -> left;
        }
    }
    return ans;
}
int RBT::Predecessor(int val){
    Nod x = root;
    int ans;
    while(x != NIL){
        if(x -> key == val)
            return x -> key;
        if(x -> key > val)
            x = x -> left;
        else{
            ans = x -> key;
            x = x -> right;
        }
    }
    return ans;
}
void RBT::Sort(int l, int r){
    int next = Successor(l);
    while(next <= r){
        out << next << " ";
        next = Successor(next + 1);
    }
}

int main(){
    RBT *T = new RBT();
    int q; //numarul de cerinte
    in>>q;
    for (int i=0; i<q; i++)
    {
        int type, x, y;
        in>>type;
        if (type == 1)
        {
            in>>x;
            T->Insert(x);
        }
        if (type == 2)
        {
            in>>x;
            T->Delete(x);
        }
        if (type == 3)
        {
            in>>x;
            out<<T->Search(x)<<"\n";
        }
        if (type == 4)
        {
            in>>x;
            out<<T->Predecessor(x)<<"\n";
        }
        if (type == 5)
        {
            in>>x;
            out<<T->Successor(x)<<"\n";
        }
        if (type == 6)
        {
            in>>x>>y;
            T->Sort(x, y);
            out<<"\n";
        }

    }
    return 0;
}
