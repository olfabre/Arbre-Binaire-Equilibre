#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#include "avl.h"

// METHODES NOEUD
// --------------

/* Constructeur d'une instance noeud */
noeud::noeud(int x)
{

    cle = x;
    N = 0; // nbr de noeud arbre
    d = 0; // désiquilibre
    h = 0; // hauteur
    fg = NULL;
    fd = NULL;
    pere = NULL;
}
/* Destructeur d'une instance noeud */
noeud::~noeud()
{

    if (fg)
    {
        delete (fg);
    }
    if (fd)
    {
        delete (fd);
    }
}

void noeud::affiche()
{
    cout << endl
         << endl;
    cout << "NOEUD ---" << endl;
    cout << "clé:" << cle << endl;
    cout << "Nbr de noeud de l'arbre: " << N << endl;
    cout << "Désiquilibre: " << d << endl;
    cout << "Hauteur: " << h << endl;
    cout << "Père" << pere << endl;
    cout << "Fils Gauche" << fg << endl;
    cout << "Fils Droit" << fd << endl;
}

//-------------------------------------------------------------------------

// METHODES AVL (arbre)
// --------------------

/* Destructeur d'une instance arbre */
AVL::~AVL()
{
    if (r)
    {
        delete (r);
    }
}

noeud *AVL::root()
{
    return (this->r);
}

AVL::AVL(noeud *r)
{
    this->r = r;
}

AVL::AVL(char *filename, bool option)
{
    int nbrNoeud;
    bool lectureClefNoeud(false);
    FILE *f;
    char c;
    // Lecture du nombre
    f = fopen(filename, "rt");
    while ((c = fgetc(f)) != EOF)
    {

        if (((int(c) != 10) && (int(c) != 32)) && lectureClefNoeud == true) // Fin de lecture de la première ligne
        {

            cout << c - 48 << " ";
        }

        if (lectureClefNoeud == false)
        {
            nbrNoeud = c - 48;
            lectureClefNoeud = true;
            cout << "\n> CREATION ARBRE " << (option ? "EN FEUILLE:" : "EN RACINE") << endl;
            cout << "Nbr de noeud à créer: " << nbrNoeud << endl;
            cout << "Lecture et insertion des clés suivantes: ";
        }
    }

    cout << endl;
    fclose(f);
}

int AVL::hauteur(noeud *x)
{
    // Initialisation
    int hauteurFilGauche;
    int hauteurFilDroit;

    if (x == NULL)
        return (-1);

    hauteurFilGauche = hauteur(x->fg);
    hauteurFilDroit = hauteur(x->fd);
    if (hauteurFilGauche > hauteurFilDroit)
    {
        return 1 + hauteurFilGauche;
    }
    else
    {
        return 1 + hauteurFilDroit;
    }
}

int AVL::noeuds(noeud *x)
{

    // met a jour l’attribut N du noeud de l’arbre de racine x. Le contenu x− > N est renvoye.
    return (x->N + 1);
}
void AVL::prefixe(noeud *x)
{
    if (x != NULL)
    {
        x->affiche();
        prefixe(x->fg);
        prefixe(x->fd);
    }
}

void AVL::rotationGauche(noeud *x)
{
    // Selon Algo enseignant correction TD 2 ENT
    if (x)
    {
        noeud *pere = x->pere;
        noeud *noeudDroite = x->fd;
        noeudDroite->pere = x->pere;
        x->fd = noeudDroite->fg;

        if (noeudDroite->fg != NULL)
        {
            noeudDroite->fg->pere = x;
        }

        noeudDroite->fg = x;
        x->pere = noeudDroite;

        if (pere == NULL)
        {
            x = noeudDroite;
        }
        else
        {
            if (pere->fd == x)
            {
                pere->fd = noeudDroite;
            }
            else
            {
                pere->fg = noeudDroite;
            }
        }
    }
}

void AVL::rotationDroite(noeud *x)
{
    // Selon Algo enseignant correction TD 2 ENT
    if (x)
    {
        noeud *pere = x->pere;
        noeud *noeudGauche = x->fg;
        noeudGauche->pere = x->pere;
        x->fg = noeudGauche->fd;

        if (noeudGauche->fd != NULL)
        {
            noeudGauche->fd->pere = x;
        }

        noeudGauche->fd = x;
        x->pere = noeudGauche;

        if (pere == NULL)
        {
            x = noeudGauche;
        }
        else
        {
            if (pere->fg == x)
            {
                pere->fg = noeudGauche;
            }
            else
            {
                pere->fd = noeudGauche;
            }
        }
    }
}
