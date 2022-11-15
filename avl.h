#ifndef __AVL_H__
#define __AVL_H__

#include <iostream>

class noeud
{

private:
    friend class AVL;
    int cle;     // Valeur à inserer
    int N;       // nombre de noeuds de l’arbre
    int d;       // contiendra le desequilibre
    int h;       // hauteur de l'arbre
    noeud *fg;   // Pointeur du noeud fils gauche
    noeud *fd;   // pointeur du noeud fils droite
    noeud *pere; // Pointeur du noeud Pere

public:
    noeud(int x);   // constructeur
    ~noeud();       // destruction
    void affiche(); // Afficher tous les attributs du noeud
};

class AVL
{
private:
    noeud *r; // Instance d'un pointeur racine

public:
    AVL(noeud *r);                    // Creation d'un arbre à partir
    ~AVL();                           // Destruction d'un arbre
    noeud *root();                    // Retourne le pointeur du noeud racine
    AVL(char *filename, bool option); // constructeur permettant de creer un arbre binaire de recherche par insertion des donnees provenant d’un fichier “filename”. Si option == true, les insertions doivent se faire en feuille, sinon en racine.
    void prefixe(noeud *x);
    int hauteur(noeud *x);
    void rotationDroite(noeud *x);             // permet d’effectuer une rotation droite en un noeud x quelconque de l’arbre.
    void rotationGauche(noeud *x);             // permet d’effectuer une rotation gauche en un noeud x quelconque de l’arbre.
    void insertionFeuille(noeud *x, noeud *y); // permet d’inserer en feuille un nouveau noeud y dans l’arbre de racine x.
    void insertionRacine(noeud *x, noeud *y);  // permet dinserer en racine un nouveau noeud y, dans larbre de racine x.
    int noeuds(noeud *x);                      // met a jour l’attribut N de tous les noeuds de l’arbre de racine x. Le contenu x− > N est renvoye.
    void desequilibres(noeud *x);              // calcule le d´esequilibre en chaque noeud d’un arbre de racine x.
    noeud *partition(noeud *x, int k);         // partitionne l’arbre par rapport a sa k-ieme plus petite valeur et renvoie l’adresse de celle-ci (voir TD Arbres Equilibres).
    void equilibre(noeud *x);                  // equilibre l’arbre en utilisant une procedure de type “diviser pour regner” (voir TD Arbres Equlibres).
    void Infixe(noeud *x);
};

#endif