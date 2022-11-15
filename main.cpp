#include <iostream>
#include <stdlib.h>
#include "avl.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 2)
		cout << "Nombre d'arguments insuffisants" << endl;
	else
	{
		int choixOption;
		bool optionCreationArbre(false);
		do
		{
			cout << endl
					 << endl;

			cout << "\t[0] -> Arbre en feuille" << endl;
			cout << "\t[1] -> Arbre en racine" << endl;
			cout << "Saisir votre choix? ";
			cin >> choixOption;
		} while (choixOption > 1);

		// Si option == True alors insertion en feuille (choixOption=0)
		// Si option == False alors insertion en racine (choixOption=1)
		if (choixOption == 0)
			optionCreationArbre = true;

		AVL creationObjetArbre = AVL(argv[1], optionCreationArbre);

		creationObjetArbre.prefixe(creationObjetArbre.root());
	}

	return -1;
}

// Appels terminal
/*
g++ main.cpp avl.cpp  -o avl.exe

*/