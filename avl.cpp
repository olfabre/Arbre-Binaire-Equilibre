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
    bool debut(true);
    int cleInsertion(0);
    // Lecture du nombre
    f = fopen(filename, "rt");
    while ((c = fgetc(f)) != EOF)
    {

        if (((int(c) != 10) && (int(c) != 32)) && lectureClefNoeud == true) // Fin de lecture de la première ligne
        {
            if (option == true)
            {
                cleInsertion = c - 48;

                if (debut)
                {
                    cout << cleInsertion << " ";
                    insertionFeuille(NULL, new noeud(cleInsertion));
                    debut = false;
                }
                else
                {
                    cout << cleInsertion << " ";
                    insertionFeuille(root(), new noeud(cleInsertion));
                }
            }
            if (option == false)
            {
                cleInsertion = c - 48;

                if (debut)
                {
                    cout << cleInsertion << " ";
                    insertionRacine(NULL, new noeud(cleInsertion));
                    debut = false;
                }
                else
                {
                    cout << cleInsertion << " ";
                    insertionRacine(root(), new noeud(cleInsertion));
                }
            }
        }

        if (lectureClefNoeud == false)
        {
            nbrNoeud = c - 48;
            lectureClefNoeud = true;
            cout << "\n> CREATION ARBRE " << (option ? "EN FEUILLE <" : "EN RACINE <") << endl;
            cout << "Nbr de noeud à créer: " << nbrNoeud << endl;
            cout << "Lecture fichier et insertion des clés suivantes: ";
        }
    }

    cout << endl;

    fclose(f);
}

void AVL::Infixe(noeud *x)
{
    if (x)
    {
        Infixe(x->fg);
        cout << " " << x->cle;
        Infixe(x->fd);
    }
    else
    {
        cout << "Pas d'instance d'arbre";
    }
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
    else
    {
        cout << "0/0" << endl;
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

void AVL::insertionFeuille(noeud *x, noeud *y)
{
    // Selon Algo enseignant correction TD 2 ENT
    noeud *Noeud = x;
    noeud *pere = NULL;

    while (Noeud != NULL)
    {
        pere = Noeud;
        if (y->cle <= Noeud->cle)
        {
            Noeud = Noeud->fg;
        }
        else
        {
            Noeud = Noeud->fd;
        }
    }

    y->pere = pere;

    if (y->pere == 0)
    {
        x = y;
    }
    else
    {
        if (y->cle <= y->pere->cle)
        {

            y->pere->fg = y;
        }
        else
        {
            y->pere->fd = y;
        }
    }
}

void AVL::insertionRacine(noeud *x, noeud *y)
{
    // Algo source: https://e-uapv2022.univ-avignon.fr/pluginfile.php/64132/mod_resource/content/24/TD-L2-S3-arbres-binaires-2022-2023-corr.pdf

    if (x == NULL)
    {
        x = y;
    }
    else
    {
        if (y->cle < x->cle)
        {
            if (x->fg == NULL)
            {
                x->fg = y;
            }
            else
            {
                insertionRacine(x->fg, y);
            }
            rotationDroite(x);
        }
        else
        {
            if (x->fd == NULL)
            {
                x->fd = y;
            }
            else
            {
                insertionRacine(x->fd, y);
            }
            rotationGauche(x);
        }
    }
}

noeud *AVL::partition(noeud *x, int k)
{
    // Algo source: https://e-uapv2022.univ-avignon.fr/pluginfile.php/64132/mod_resource/content/24/TD-L2-S3-arbres-binaires-2022-2023-corr.pdf
    int temp;
    noeud *resultat = NULL;

    if (x != NULL)
    {
        temp = 0;

        if (x->fg)
        {
            temp = x->fg->N;
        }

        if (temp == (k - 1))
        {
            resultat = x;
        }
    }
    else
    {
        if (temp > (k - 1))
        {
            resultat = partition(x->fg, k);
            rotationDroite(x);
        }
        else
        {
            resultat = partition(x->fd, (k - temp - 1));
            rotationGauche(x);
        }
    }
    return resultat;
}

void AVL::desequilibres(noeud *x)
{
    if (x)
        x->d = hauteur(x->fg) - hauteur(x->fd);
    else
        x->d = -1;
}

void AVL::equilibre(noeud *x)
{
    int N;
    int k;
    if (x && (x->N > 1))
    {
        N = x->N;
        k = (N / 2);
        partition(x, k);
        equilibre(x->fg);
        equilibre(x->fd);
    }
}
