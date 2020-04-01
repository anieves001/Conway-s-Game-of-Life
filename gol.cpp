/*
 * CSc103 Project 3: Game of Life
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 
 */
#include <iostream>
#include <cstdio>
#include <stdlib.h> // for exit();
#include <getopt.h> // to parse long arguments.
#include <unistd.h> // sleep
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::cout;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */
vector<vector<bool> > world;
/* NOTE: you don't have to write these functions -- this is just how
 * I chose to organize my code. */
int nbrCount(size_t i,size_t j);  //count neighbors of cell i,j on grid g.
void update();  //transform the old version of the world into the new one.
void initFromFile(const string& fname); /* read initial state into vectors. */
void mainLoop();  //update state, write state, sleep, repeat...
void dumpState(FILE* f);  //write the state to a file

/* NOTE: you can use a *boolean* as an index into the following array
 * to translate from bool to the right characters: */
char text[3] = ".O";

int main(int argc, char *argv[]) {
	// define long options
	static struct option long_opts[] = {
		{"seed",    required_argument, 0, 's'},
		{"world",   required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'},
		{"help",    no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case 's':
				initfilename = optarg;
				break;
			case 'w':
				wfilename = optarg;
				break;
			case 'f':
				max_gen = atoi(optarg);
				break;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	/* NOTE: at this point wfilename initfilename and max_gen
	 * are all set according to the command line: */
//	printf("input file:  %s\n",initfilename.c_str());
//	printf("output file: %s\n",wfilename.c_str());
//	printf("fast forward to generation: %lu\n",max_gen);
	/* TODO: comment out 3 lines above once you see what's in them. */
	/* NOTE: if wfilename == "-" you should write to stdout, not a file
	 * named "-"! */

	/* If you wrote the initFromFile function, call it here: */
	initFromFile(initfilename);
	mainLoop();
	return 0;
}

void mainLoop() {
	/* TODO: write this */
	/* update, write, sleep */
  FILE* fworld=fopen(wfilename.c_str(),"wb");
	if (max_gen == 0) {
		/* make one generation update per second */
    while(true){
      dumpState(fworld);
      update();
      sleep(1);
    }
	} else {
		/* go through generations as fast as you can until
		 * max_gen is reached... */
    while(max_gen){
      update();
      max_gen--;
    }
    for(size_t row=0;row<world.size();row++){
      for(size_t col=0;col<world[row].size();col++){
        cout<<text[world[row][col]];
      }
      cout<<"\n";
    }
	}
  fclose(fworld);
}
void initFromFile(const string& fname){
//read initial state from file.

  FILE* f=fopen(fname.c_str(),"rb");
  world.push_back(vector<bool>());
  size_t rows=0;
  char c;
  while(fread(&c,1,1,f)){
    if(c=='\n'){
      rows++;
      world.push_back(vector<bool>());
    }
    else if(c=='.'){
      world[rows].push_back(false);
    }
    else{
      world[rows].push_back(true);
    }
  }
  fclose(f);
world.erase(world.end()); //delete empty row.
}
void dumpState(FILE* f){

  char c;
  for(size_t row=0;row<world.size();row++){
    for(size_t col=0;col<world[row].size();col++){
      c=text[world[row][col]];
      fwrite(&c,1,1,f);
      if(col==world[row].size()-1){
        c='\n';
        fwrite(&c,1,1,f);
      }
    }
  }
rewind(f);
}
void update(){
  int neighbors=0;
  vector<int> indices;  //save indices where we need to make changes.
  for(size_t i=0;i<world.size();i++){
    for(size_t j=0;j<world[i].size();j++){
      neighbors=nbrCount(i,j);
      if((world[i][j])&&(neighbors<2||neighbors>3)){
        indices.push_back(i);
        indices.push_back(j);
      }
      else if((!world[i][j])&&(neighbors==3)){
        indices.push_back(i);
        indices.push_back(j);
      }
    }
  }
  for(size_t i=0;i<indices.size();i+=2){
    world[indices[i]][indices[i+1]]=!world[indices[i]][indices[i+1]];
  }
}
int nbrCount(size_t i,size_t j){

  int count=0;
  if(i>0&&j>0&&i<world.size()-1&&j<world[i].size()-1){  //Non-perimeter cell. Check all sides directly.
    if(world[i][j+1])
      count++;
    if(world[i-1][j+1])
      count++;
    if(world[i-1][j])
      count++;
    if(world[i-1][j-1])
      count++;
    if(world[i][j-1])
      count++;
    if(world[i+1][j-1])
      count++;
    if(world[i+1][j])
      count++;
    if(world[i+1][j+1])
      count++;
  }
  else{ //Perimeter cell.  Check opposite ends of grid.
    if(i==0&&j==0){ //top left corner
      if(world[i][j+1])
        count++;
      if(world[world.size()-1][j+1])
        count++;
      if(world[world.size()-1][j])
        count++;
      if(world[world.size()-1][world[0].size()-1])
        count++;
      if(world[i][world[0].size()-1])
        count++;
      if(world[i+1][world[0].size()-1])
        count++;
      if(world[i+1][j])
        count++;
      if(world[i+1][j+1])
        count++;
    }
    if((i==0&&j>0)&&(j<world[0].size()-1)){//topmost center line of grid
      if(world[i][j+1])
        count++;
      if(world[world.size()-1][j+1])
        count++;
      if(world[world.size()-1][j])
        count++;
      if(world[world.size()-1][j-1])
        count++;
      if(world[i][j-1])
        count++;
      if(world[i+1][j-1])
        count++;
      if(world[i+1][j])
        count++;
      if(world[i+1][j+1])
        count++;
    }
    if((i>0&&j==0)&&(i<world.size()-1)){//leftmost center line of grid
      if(world[i][j+1])
        count++;
      if(world[i-1][j+1])
        count++;
      if(world[i-1][j])
        count++;
      if(world[i-1][world[0].size()-1])
        count++;
      if(world[i][world[0].size()-1])
        count++;
      if(world[i+1][world[0].size()-1])
        count++;
      if(world[i+1][j])
        count++;
      if(world[i+1][j+1])
        count++;
    }
    if(i==world.size()-1&&j==0){//bottom left corner
      if(world[i][j+1])
        count++;
      if(world[i-1][j+1])
        count++;
      if(world[i-1][j])
        count++;
      if(world[i-1][world[0].size()-1])
        count++;
      if(world[i][world[0].size()-1])
        count++;
      if(world[0][world[0].size()-1])
        count++;
      if(world[0][0])
        count++;
      if(world[0][1])
        count++;
    }
    if((i==world.size()-1)&&(j>0)&&(j<world[0].size()-1)){//bottom center line of grid
      if(world[i][j+1])
        count++;
      if(world[i-1][j+1])
        count++;
      if(world[i-1][j])
        count++;
      if(world[i-1][j-1])
        count++;
      if(world[i][j-1])
        count++;
      if(world[0][j-1])
        count++;
      if(world[0][j])
        count++;
      if(world[0][j+1])
        count++;
    }
    if((i==0)&&(j==world[0].size()-1)){//top right corner
      if(world[0][0])
        count++;
      if(world[world.size()-1][0])
        count++;
      if(world[world.size()-1][world[0].size()-1])
        count++;
      if(world[world.size()-1][j-1])
        count++;
      if(world[i][j-1])
        count++;
      if(world[i+1][j-1])
        count++;
      if(world[i+1][j])
        count++;
      if(world[i+1][0])
        count++;
    }
    if((i>0)&&(j==world[0].size()-1)&&(i<world.size()-1)){ //right center line of grid
      if(world[i][0])
        count++;
      if(world[i-1][0])
        count++;
      if(world[i-1][j])
        count++;
      if(world[i-1][j-1])
        count++;
      if(world[i][j-1])
        count++;
      if(world[i+1][j-1])
        count++;
      if(world[i+1][j])
        count++;
      if(world[i+1][0])
        count++;
    }
    if(i==world.size()-1&&j==world[0].size()-1){//bottom right corner
      if(world[i][0])
        count++;
      if(world[i-1][0])
        count++;
      if(world[i-1][j])
        count++;
      if(world[i-1][j-1])
        count++;
      if(world[i][j-1])
        count++;
      if(world[0][j-1])
        count++;
      if(world[0][j])
        count++;
      if(world[0][0])
        count++;
    }
  }
  return count;
}
