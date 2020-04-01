#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::cin;

vector<vector<bool> > world = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int main(int argc,char** argv)
{
	/* NOTE: the vector 'world' above corresponds to the contents
	 * of ../res/tests/0.  TODO: apply the rules to the vector,
	 * write the result to standard output, and compare with the
	 * contents of ../tests/1. */
  int gen=atoi(argv[1]),check=0;
  vector<int> indices;  //save indices where we need to make changes.
  while(gen>0){
    for(size_t row=0;row<world.size();row++){
      for(size_t col=0;col<world[row].size();col++){
        if((row>0&&col>0)&&(row<world.size()-1)&&(col<world[row].size()-1)){
          //Non-perimeter cell.Therefore, check all 8 sides directly.
          if(world[row][col+1])
            check++;
          if(world[row-1][col+1])
            check++;
          if(world[row-1][col])
            check++;
          if(world[row-1][col-1])
            check++;
          if(world[row][col-1])
            check++;
          if(world[row+1][col-1])
            check++;
          if(world[row+1][col])
            check++;
          if(world[row+1][col+1])
            check++;
          //Store coordinates of cells that need to be changed
          if((world[row][col])&&(check<2||check>3)){  //condition for live cell
            indices.push_back(row);
            indices.push_back(col);
          }
          else if(!world[row][col]&&check==3){  //condition for dead cell
            indices.push_back(row);
            indices.push_back(col);
          }
        }
        else{//Perimeter cell. Check opposite ends of grid.
          if(row==0&&col==0){//top left corner
            if(world[row][col+1])
              check++;
            if(world[world.size()-1][col+1])
              check++;
            if(world[world.size()-1][col])
              check++;
            if(world[world.size()-1][world[0].size()-1])
              check++;
            if(world[row][world[0].size()-1])
              check++;
            if(world[row+1][world[0].size()-1])
              check++;
            if(world[row+1][col])
              check++;
            if(world[row+1][col+1])
              check++;
          }
          if(row==0&&col>0&&col<world[0].size()-1){ //topmost center line of grid.
            if(world[row][col+1])
              check++;
            if(world[world.size()-1][col+1])
              check++;
            if(world[world.size()-1][col])
              check++;
            if(world[world.size()-1][col-1])
              check++;
            if(world[row][col-1])
              check++;
            if(world[row+1][col-1])
              check++;
            if(world[row+1][col])
              check++;
            if(world[row+1][col+1])
              check++;
          }
          if(row>0&&col==0&&row<world.size()-1){ //leftmost center line of grid
            if(world[row][col+1])
              check++;
            if(world[row-1][col+1])
              check++;
            if(world[row-1][col])
              check++;
            if(world[row-1][world[0].size()-1])
              check++;
            if(world[row][world[0].size()-1])
              check++;
            if(world[row+1][world[0].size()-1])
              check++;
            if(world[row+1][col])
              check++;
            if(world[row+1][col+1])
              check++; 
          }
          if(row==world.size()-1&&col==0){ //bottom left corner
            if(world[row][col+1])
              check++;
            if(world[row-1][col+1])
              check++;
            if(world[row-1][col])
              check++;
            if(world[row-1][world[0].size()-1])
              check++;
            if(world[row][world[0].size()-1])
              check++;
            if(world[0][world[0].size()-1])
              check++;
            if(world[0][0])
              check++;
            if(world[0][1])
              check++;
          }
          if(row==world.size()-1&&col>0&&col<world[0].size()-1){ //bottom center line of grid
            if(world[row][col+1])
              check++;
            if(world[row-1][col+1])
              check++;
            if(world[row-1][col])
              check++;
            if(world[row-1][col-1])
              check++;
            if(world[row][col-1])
              check++;
            if(world[0][col-1])
              check++;
            if(world[0][col])
              check++;
            if(world[0][col+1])
              check++;
          }
          if(row==0&&col==world[0].size()-1){ //top right corner
            if(world[0][0])
              check++;
            if(world[world.size()-1][0])
              check++;
            if(world[world.size()-1][world[0].size()-1])
              check++;
            if(world[world.size()-1][col-1])
              check++;
            if(world[row][col-1])
              check++;
            if(world[row+1][col-1])
              check++;
            if(world[row+1][col])
              check++;
            if(world[row+1][0])
              check++;
          }
          if(row>0&&col==world[0].size()-1&&row<world.size()-1){ //right center line of grid
            if(world[row][0])
              check++;
            if(world[row-1][0])
              check++;
            if(world[row-1][col])
              check++;
            if(world[row-1][col-1])
              check++;
            if(world[row][col-1])
              check++;
            if(world[row+1][col-1])
              check++;
            if(world[row+1][col])
              check++;
            if(world[row+1][0])
              check++;
          }
          if(row==world.size()-1&&col==world[0].size()-1){ //bottom right corner
            if(world[row][0])
              check++;
            if(world[row-1][0])
              check++;
            if(world[row-1][col])
              check++;
            if(world[row-1][col-1])
              check++;
            if(world[row][col-1])
              check++;
            if(world[0][col-1])
              check++;
            if(world[0][col])
              check++;
            if(world[0][0])
              check++;
          }
          if((world[row][col])&&(check<2||check>3)){
            indices.push_back(row);
            indices.push_back(col);
          }
          else if(!world[row][col]&&check==3){
            indices.push_back(row);
            indices.push_back(col);
          }
        }
        check=0;
      }
    }
    gen--;
    //go through grid and change based on coordinates
    for(size_t i=0;i<indices.size();i+=2){
      world[indices[i]][indices[i+1]]=!world[indices[i]][indices[i+1]];
    }
    indices.clear();
  }
  for(size_t row=0;row<world.size();row++){
    for(size_t col=0;col<world[row].size();col++){
      if(world[row][col])
        cout<<"O";
      else
        cout<<".";
    }
    cout<<"\n";
  }
  return 0;
}
