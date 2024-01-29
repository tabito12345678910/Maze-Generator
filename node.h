#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

using namespace std;

class Node {
 public:
 //constructors

  Node() : x(0), y(0), v(false), g(false), north(nullptr), west(nullptr), east(nullptr), south(nullptr), next(nullptr), prev(nullptr), maze_gen(nullptr){} 
  Node(int xx, int yy) : x(xx), y(yy), v(false), g(false), north(nullptr), west(nullptr), east(nullptr), south(nullptr), next(nullptr), prev(nullptr), maze_gen(nullptr){} 
  //set and get coordinates of cells
  void set_x(int xx) { x = xx; }
  void set_y(int yy) { y = yy; }
  int get_x() const { return x; }
  int get_y() const { return y; }

  //set and get next/prev for correct path
  void set_next(Node* n){next = n;}
  void set_prev(Node* p){prev = p;}
  Node* get_next() { return next; }
  Node* get_prev() { return prev; }

  void set_north(Node* no){north = no;}
  void set_west(Node* w){west = w;}
  void set_east(Node* e){east = e;}
  void set_south(Node* s){south = s;}

  Node* get_north(){return north;}
  Node* get_west(){return west;}
  Node* get_east(){return east;}
  Node* get_south(){return south;}
  /*
  iterate through linked list of maze_gen from start till you find node with coordinates assosicated 
  with NEWS of current node and returns it
  */
  Node* iterate(int xx, int yy, Node* first);
  Node* find_north(Node*& curr, Node* first);
  Node* find_west(Node*& curr, Node* first); 
  Node* find_east(Node*& curr, Node* first); 
  Node* find_south(Node*& curr, Node* first);

  //uses get_NEWS() to check if NEWS is a possible route by checking if it is in bounds of maze and if it is already visited or not
  bool can_go_north(Node*& curr, Node* first);
  bool can_go_south(int h, Node*& curr, Node* first); //needs height in case it is on bottom row
  bool can_go_east(int w, Node*& curr, Node* first); //needs width in case it is right most column
  bool can_go_west(Node*& curr, Node* first);


  void set_maze(Node* m){maze_gen = m;}
  Node* get_maze(){return maze_gen;}

  bool get_visited() {return v; }
  void set_visited(){v=true; }

  bool get_goal() {return g; }
  void set_goal(){g=true; }




 private:
  int x;  // x value
  int y;  // y value
  bool v; // visited
  bool g;
  Node* next;// for printing route separate from stack which is used to create maze
  Node* prev;//for printing route separate from stack which is used to create maze
  Node* north;
  Node* west;
  Node* east;
  Node* south;
  Node* maze_gen; //creates links to next cell to generate maze

  
};






#endif  
