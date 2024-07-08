

#ifndef STACK_H_INCLUDEDk
#define STACK_H_INCLUDED

#include<iostream>
#include<queue>
using namespace std;

#define T int   
class BST { 
   struct Node {
      T date ; 
      Node*left ; 
      Node*right ; 
      Node(T val){
         date = val ;
         left = right = nullptr ; 
      }
   } ; 
   Node* root = 0 ; 
   //#################################################################
   void addItrative(T val) {
      // creat new node 
      Node* newNode = new Node(val) ; 
      if(this->empty()){
         this->root = newNode ; 
      }else {
         Node* go = this->root , *back; 

         while(go) {
            back = go ; 
            go = go->date >= val ? go->left : go->right ;
         }
         back->date >= val ? back->left = newNode : back->right = newNode ; 
      }
   }
   void addRecursive(Node*r , int val) {
      Node* newNode = new Node(val) ; 
      if(!r) this->root = newNode ;
      else {
         if(r->date <= val){ // go left 
            if (!r->left) {
               r->left = newNode ;
               return ;   
            }
            addRecursive(r->left , val); 
         }
         else{  // go right 
            if(!r->right) {
               r->right = newNode ;
               return ; 
            }
            addRecursive(r->right , val); 
         }
      }
   }
   T getMin(Node*go) { 
      return !go->right ? go->date : getMin(go->right) ; 
   }
   T getMax(Node*go){
      return !go->left ? go->date : getMax(go->left) ; 
   }
   int getHight(Node*root) { 
      return !root ? -1 : max( getHight(root->left)+1 , getHight(root->right)+1) ; 
   }
   void traversingPreOrder(Node*go) {
      if(!go) return ;
      cout << go->date << " " ; 
      traversingPreOrder(go->right) ; 
      traversingPreOrder(go->left) ; 
       
   }
   Node* remove(Node*r , const int &val) {
      if(!r) return 0 ;
      else if(r->date > val ) 
         r->right = remove(r->right , val) ; 
      else if(r->date < val){
         r->left = remove(r->left , val) ; 
      }else { // found it 
         if(!r->left) {
            Node* ret = r->right ; 
            delete r ; 
            return ret ; 
         }
         else if(!r->right) {
            Node* ret = r->left ; 
            delete r ; 
            return ret ; 
         }else {
            r->date = this->getMax(r->left) ;
            r->left = remove(r->left , r->date) ;  
         }
      }

      return r ;      
   }
   Node* deleteNode(Node*root , const T&val) {
      if(!root) return 0 ; 
      if(val > root->date ) 
         root->left = deleteNode( root->left , val); 
      else if(val < root->date)
         root->right = deleteNode( root->left , val);
      else { 
         if(!root->left){
            Node* temp = root->right ;
            delete root ;
            return temp;  
         }else if(!root->right) {
            Node* temp = root->left ;
            delete root ;
            return temp;  
         }
         else {
            T mx = this->getMax(root);
            root->date = mx ; 
            root->right = deleteNode(root->right , mx); 
         }
      }
      return root; 
   }
   
public:
   bool empty()const{ return !root ; }
   void add(T val) { addRecursive( root , val) ;}

   T getMin() { if(!empty()) return getMin(root); }
   T getMax(){ 
      if(!empty()) return getMax(root) ; 
   }
   int getHight() { return getHight(root)+1 ; }

   void traverseLevelOrder_BFS() {
      if(this->empty()) return ; 
      
      queue<Node*>Q;
      Q.push(this->root); 
      
      while(!Q.empty()) {
         Node* curr = Q.front();
         Q.pop(); 
         cout << curr->date << ' ' ; 
         if(curr->right) Q.push(curr->right);
         if(curr->left) Q.push(curr->left);
      }

   }
   // Traversing bridth first 
   void traversingPreOrder() { traversingPreOrder(this->root);}
   void remove(const T& val ) { this->root = this->remove(this->root , val); }
   void deleteNode(const T&val) { this->root = deleteNode(this->root , val) ; }
} ; 

#endif // STACK_H_INCLUDED



