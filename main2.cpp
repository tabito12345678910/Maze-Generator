
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>
#include <vector>
#include <random>

#include "../RoseHack_Maze_Solver/node.h"

Node* maze(int w, int h){ //initialize the maze
    int height = h;
    int width = w;
    Node* start = new Node();
    Node* curr = new Node(1,0);

   
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(x==0&&y==0){
                
            }
            else if(x==1&&y==0){
                start->set_maze(curr);
            }
            else{
                Node* cell = new Node(x, y);
                curr -> set_maze(cell);
                curr = cell;
            }
        }
    }
    return start;
}


int rand_direction(int w, int h, Node* curr, Node* first){
  int north = 0;
  int west = 1;
  int east = 2;
  int south = 3;
  int none = 4; //no directions that you can go
  int direction;
  vector<int> unvisited;
  //if statements push possible directions into vector to later randomly select;
  if(curr->can_go_north(curr, first)==true){
    unvisited.push_back(north);
    //cout<<"Can go north"<<endl;
    //cout<<"---"<<endl;
  }
  if(curr->can_go_west(curr, first)==true){
    unvisited.push_back(west);
    //cout<<"Can go west"<<endl;
    //cout<<"---"<<endl;
  }
  if(curr->can_go_east(w, curr, first)==true){
    unvisited.push_back(east);
    //cout<<"Can go east"<<endl;
    //cout<<"---"<<endl;
  }
  if(curr->can_go_south(h, curr, first)==true){
    unvisited.push_back(south);
    //cout<<"Can go south"<<endl;
    //cout<<"---"<<endl;
  }
  if(!unvisited.empty()){

    int visit_next = rand()% unvisited.size();
    direction = unvisited.at(visit_next);
  }
  else{
    direction = none;
  }
  return direction;
}

//creates paths uses can_go_NEWS() and randomly picks a path. use stack and utilize next and prev
Node* generate_maze(int w, int h, Node* first){
  int height = h;
  int width = w;
  int COUNT_SIZE = height*width;
  int count = 0;
  int direction;


  Node* curr = first;
  curr->set_visited();


  //cout<<"starting point: curr = 0,0"<<endl;
    cout<<"Enter seed value"<<endl;
    int seed;
    cin>>seed;
    srand(seed);
    cout<<"Randomly generating maze"<<endl;

  while(count<COUNT_SIZE){
      //randomly generate direction here
      direction = rand_direction(width, height, curr, first);
      //set next to the correct direction and change curr to that, and set prev to previous node
      if(direction == 0){
        Node* temp = curr;
        curr->set_north(curr->find_north(curr, first));
        curr->set_next(curr->get_north());
        curr = curr->get_north();
        curr->set_prev(temp);
        curr->set_visited();
        //cout<<"curr changed to "<<curr->get_x()<<","<<curr->get_y()<<endl;
        if(count==COUNT_SIZE-1){
            //cout<<"found last cell "<<curr->get_x()<<","<<curr->get_y()<<endl;
            curr->set_goal();
        }
        //cout<<"count "<<count<<endl;
        count += 1;
      }
      else if(direction == 1){
        Node* temp = curr;
        curr->set_west(curr->find_west(curr, first));
        curr->set_next(curr->get_west());
        curr = curr->get_west();
        curr->set_prev(temp);
        curr->set_visited();
        //cout<<"curr changed to "<<curr->get_x()<<","<<curr->get_y()<<endl;
        if(count==COUNT_SIZE-1){
            //cout<<"found last cell "<<curr->get_x()<<","<<curr->get_y()<<endl;
            curr->set_goal();
        }
        //cout<<"count "<<count<<endl;
        count += 1;
      }
      else if(direction == 2){
        Node* temp = curr;
        curr->set_east(curr->find_east(curr, first));
        curr->set_next(curr->get_east());
        curr = curr->get_east();
        curr->set_prev(temp);
        curr->set_visited();
        //cout<<"curr changed to "<<curr->get_x()<<","<<curr->get_y()<<endl;
        if(count==COUNT_SIZE-1){
            //cout<<"found last cell "<<curr->get_x()<<","<<curr->get_y()<<endl;
            curr->set_goal();
        }
        //cout<<"count "<<count<<endl;
        count += 1;
      }
      else if(direction == 3){
        Node* temp = curr;
        curr->set_south(curr->find_south(curr, first));
        curr->set_next(curr->get_south());
        curr = curr->get_south();
        curr->set_prev(temp);
        curr->set_visited();
        //cout<<"curr changed to "<<curr->get_x()<<","<<curr->get_y()<<endl;
        if(count==COUNT_SIZE-1){
            //cout<<"found last cell "<<curr->get_x()<<","<<curr->get_y()<<endl;
            curr->set_goal();
        }
        //cout<<"count "<<count<<endl;
        count += 1;
      }
      else if(direction == 4){
        if(curr == first){
          cout<<"code says there are no directions available even though its on the starting cell"<<endl;
        }
        else{
          //cout<<"All directions are visited or on border from this cell"<<endl;
          if(count!=COUNT_SIZE-1){
            curr = curr->get_prev();
            curr->set_next(nullptr);
            //cout<<"going back to cell "<<curr->get_x()<<","<<curr->get_y()<<endl;
          }
          else{
            //cout<<"found last cell "<<curr->get_x()<<","<<curr->get_y()<<endl;
            curr->set_goal();
            //cout<<"count "<<count<<endl;
            count += 1;
          }
        }
      }
  } 

  
 


  //prints maze
  
  for(int x = 0; x<width; x++){ //top wall generation
        if(x==0){
            cout<<"+";
        }
        if(x!=width-1){
            cout<<"----";
        }
        else{
            cout<<"---+"<<endl;
        }
  }
  curr = first;

    for(int y = 0; y<height; ++y){
        for(int x = 0; x<width; ++x){
            curr = curr->iterate(x,y,first);
            if(curr->get_x()==0){ // left wall generation
                cout<<"| ";
            }
            if(curr->get_x()==0&&curr->get_y()==0){ // generates start cell
                cout<<"S";
            }
            else if (curr->get_goal() == true){ //generates goal cell
                cout<<"G";
            }
            else{
                cout<<" "; //path generation
            }
            if(curr->get_x()!=width-1){
                if(curr->get_east()!=nullptr||(curr->find_east(curr, first))->get_west()!=nullptr){
                    cout<<"   ";
                }
                else{
                    cout<<" | "; //change to "   " if path exists there
                }
            }
            if(curr->get_x()==width-1){ 
               cout<<" |"; //right wall generation
            }
        }
        if(y!=height-1){
            cout<<endl;
            for(int xx = 0; xx<width; ++xx){
                curr = curr->iterate(xx,y,first);
                if(xx==0){
                    cout<<"|";// left wall generation
                }
                if(xx!=width-1){
                    if(curr->get_south()!=nullptr||(curr->find_south(curr, first))->get_north()!=nullptr){
                        cout<<"   +";
                    }
                    else{
                        cout<<"---+";// change to "   +"if path exists there
                    }
                }     
                else{
                    if(curr->get_south()!=nullptr||(curr->find_south(curr, first))->get_north()!=nullptr){
                        cout<<"   |"<<endl;
                    }
                    else{
                        cout<<"---|"<<endl; //right wall generation change to "   |" if path exists there
                    }
                }
            }
        }

    }

    cout<<endl;
  
    for(int x = 0; x<width; x++){ //bottom row generation
      if(x==0){
          cout<<"+";
      }
      if(x!=width-1){
          cout<<"----";
      }
      else{
          cout<<"---+"<<endl;
      }
    }
    return first;
}

void print_solved_maze(int w, int h, Node* first){
    //prints maze
    int width = w;
    int height = h;
  
  for(int x = 0; x<width; x++){ //top wall generation
        if(x==0){
            cout<<"+";
        }
        if(x!=width-1){
            cout<<"----";
        }
        else{
            cout<<"---+"<<endl;
        }
  }
  Node* curr = first;

    for(int y = 0; y<height; ++y){
        for(int x = 0; x<width; ++x){
            curr = curr->iterate(x,y,first);
            if(curr->get_x()==0){ // left wall generation
                cout<<"| ";
            }
            if(curr->get_x()==0&&curr->get_y()==0){ // generates start cell
                cout<<"S";
            }
            else if (curr->get_goal() == true){ //generates goal cell
                cout<<"G";
            }
            else{
                if((curr->get_prev())->get_next()== curr){
                    cout<<"x";//solution generation
                }
                else{
                    cout<<" "; //path generation
                }
                
            }
            if(curr->get_x()!=width-1){
                if(curr->get_east()!=nullptr||(curr->find_east(curr, first))->get_west()!=nullptr){
                    cout<<"   ";
                }
                else{
                    cout<<" | "; //change to "   " if path exists there
                }
            }
            if(curr->get_x()==width-1){ 
               cout<<" |"; //right wall generation
            }
        }
        if(y!=height-1){
            cout<<endl;
            for(int xx = 0; xx<width; ++xx){
                curr = curr->iterate(xx,y,first);
                if(xx==0){
                    cout<<"|";// left wall generation
                }
                if(xx!=width-1){
                    if(curr->get_south()!=nullptr||(curr->find_south(curr, first))->get_north()!=nullptr){
                        cout<<"   +";
                    }
                    else{
                        cout<<"---+";// change to "   +"if path exists there
                    }
                }     
                else{
                    if(curr->get_south()!=nullptr||(curr->find_south(curr, first))->get_north()!=nullptr){
                        cout<<"   |"<<endl;
                    }
                    else{
                        cout<<"---|"<<endl; //right wall generation change to "   |" if path exists there
                    }
                }
            }
        }

    }

    cout<<endl;
  
    for(int x = 0; x<width; x++){ //bottom row generation
      if(x==0){
          cout<<"+";
      }
      if(x!=width-1){
          cout<<"----";
      }
      else{
          cout<<"---+"<<endl;
      }
    }
}




int main(int argc, char* argv[]) {
  int width;
  int height;
  string yn;
  cout<<"input width"<<endl;
  cin>>width;
  cout<<"input height"<<endl;
  cin>>height;
  
  Node* solution = generate_maze(width, height, maze(width, height));;//function to generate path and/or solved maze

  cout << "Answer yes if you want the solved maze to be generated as well, if not enter anything else" << endl;
  cin >> yn;
  if (yn == "yes"){
        print_solved_maze(width, height, solution);
  }




  


  return 0;
}
