#include <iostream>
#include <fstream>
using namespace std;

#include "avl.h"


// METHODES NOEUD
// --------------


/* Constructeur d'une instance noeud */
noeud::noeud(int x){

	cle = x;
    // N = vide;
    // d = vide;
    // h = vide;
	fg = fd = pere = NULL;
 
}
/* Destructeur d'une instance noeud */
noeud::~noeud(){

    if (fg){
        delete(fg);
    }
    if (fd){
        delete(fd);
    }


}



//-------------------------------------------------------------------------


// METHODES AVL (arbre)
// --------------------


/* Destructeur d'une instance arbre */
AVL::~AVL()
{
    if (r){
		delete(r);
    }
}

AVL::AVL(char* filename, bool option){
ifstream file;
	char c;
	bool stop;
	bool fin;
	  file.open(filename, std::ifstream::in);
    	file >> c;
        file.close();


}

noeud* AVL::root(){
 return (this->r);  
}