#include "../RoseHack_Maze_Solver/node.h"

#include <iostream>



Node* Node::iterate(int xx, int yy, Node* first){
    Node* curr = first;
    //cout<<"Iterating through maze to check if cell is already visited"<<endl;
    while(curr!=nullptr){
        //cout<<curr->get_x()<<","<<curr->get_y()<<endl;
        if(curr->get_x()==xx&&curr->get_y()==yy){
            return curr;
        }
        curr = curr->get_maze();
    }
    //cout<<"Error, iterated through whole maze and could not find target cell"<<endl;
    return curr;

}


Node* Node::find_north(Node*& curr, Node* first){
    return curr->iterate(curr->get_x(), curr->get_y()-1, first);
}

Node* Node::find_west(Node*& curr, Node* first){
    return curr->iterate(curr->get_x()-1, curr->get_y(), first);
}

Node* Node::find_east(Node*& curr, Node* first){
    return curr->iterate(curr->get_x()+1, curr->get_y(), first);
}

Node* Node::find_south(Node*& curr, Node* first){
    return curr->iterate(curr->get_x(), curr->get_y()+1, first);
}

bool Node::can_go_north(Node*& curr, Node* first){ 
    if(curr->get_y()<=0){//checks if its not at the top edge of maze
        //cout<<"cannot go north as curr is on north border"<<endl;
        //cout<<"---"<<endl;
        return false;
    }
    else{
        if((curr->find_north(curr, first))->get_visited()==true){
            //cout<<"cannot go north as northern cell is already visited"<<endl;
            //cout<<"---"<<endl;
            return false;
        }
    }

    return true;
}


bool Node::can_go_south(int h, Node*& curr, Node* first){
    if(curr->get_y()>=h-1){
        //cout<<"cannot go south as curr is on south border"<<endl;
        //cout<<"---"<<endl;
        return false;
    }
    else{
        if((curr->find_south(curr, first))->get_visited()==true){
            //cout<<"cannot go south as southern cell is already visited"<<endl;
            //cout<<"---"<<endl;
            return false;
        }
    }

    return true;
}

bool Node::can_go_west(Node*& curr, Node* first){
    if(curr->get_x()<=0){
        //cout<<"cannot go west as curr is on west border"<<endl;
        //cout<<"---"<<endl;
        return false;
    }
    else{
        if((curr->find_west(curr, first))->get_visited()==true){
            //cout<<"cannot go west as western cell is already visited"<<endl;
            //cout<<"---"<<endl;
            return false;
        }
    }
    return true;
}

bool Node::can_go_east(int w, Node*& curr, Node* first){
    if(curr->get_x()>= w-1){
        //cout<<"cannot go east as curr is on east border"<<endl;
        //cout<<"---"<<endl;
        return false;
    }
    else{
        if((curr->find_east(curr, first))->get_visited()==true){
            //cout<<"cannot go east as eastern cell is already visited"<<endl;
            //cout<<"---"<<endl;
            return false;
        }
    }
    return true;
}





