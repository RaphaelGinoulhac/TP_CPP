#include "IntTree.h"
#include "Tree.h"


//Raphael GINOULHAC



int main() {
    //Creation d'un IntTree
    IntTree *root = new IntTree(12);
    root->addAsLastSon((new IntTree(8)));
    root->getSon(0)->addAsLastSon(new IntTree(4));
    root->getSon(0)->addAsLastSon(new IntTree(9));
    root->addAsLastSon((new IntTree(23)));
    root->getSon(1)->addAsLastSon(new IntTree(17));
    root->getSon(1)->getSon(0)->addAsLastSon(new IntTree(15));

    cout << "Premier arbre, IntTree : " << endl;
    root->display("* ");
    cout << endl;

    //Creation d'un Tree
    Tree<float> *tree = new Tree<float>(12.7);
    tree->addAsLastSon(new Tree<float>(-5));
    tree->getSon(0)->addAsLastSon(new Tree<float>(15.2));
    tree->getSon(0)->addAsLastSon(new Tree<float>(300));
    tree->addAsLastSon(new Tree<float>(24));
    tree->getSon(1)->addAsLastSon(new Tree<float>(-10));
    tree->getSon(1)->getSon(0)->addAsLastSon(new Tree<float>(3));
    tree->getSon(1)->getSon(0)->getSon(0)->addAsLastSon(new Tree<float>(3.1));

    cout << "Deuxieme arbre, Tree<float>, qui sera utilise pour les parcours et les calculs de profondeur : " << endl;
    tree->display("* ", "  ");

    cout << "Parcours en profondeur d'abord en sortant" << endl;
    tree->depthFirstAscending();
    cout << "Parcours en profondeur d'abord en entrant " << endl;
    tree->depthFirstDescending();
    cout << "Parcours en largeur d'abord" << endl;
    tree->breadthFirst();


    cout << "Profondeur minimale : " << tree->minDepth() << endl;

    cout << "Profondeur maximale : " << tree->maxDepth() << endl;


    //les messages d'erreur peuvent s'afficher au milieu des autres affichages precedents, si on n'ajoute pas la pause
    bool testGestionErreur = true;
    if (testGestionErreur) {

        cout << "Pause dans le programme avant l'affichage de la gestion d'erreur, veuillez entrer "
                "un message (quelconque) " << endl;
        cin.ignore();

        //Test gestion d'erreur pour IntTree
        try {
            IntTree *fils = root->getSon(-1);
            delete fils;
        }
            //Si on a indique une mauvaise position ou bien si le noeud n'a aucun fils
        catch (exception const &e) {
            cerr << "Erreur : " << e.what() << ", le fils demande n'existe pas " << endl;
        }


        try {
            root->getSon(1)->getSon(0)->getSon(0)->removeLastSon();
        }
        catch (exception const &e) {
            cerr << "Erreur : " << e.what() << endl;
        }

        try {
            root->setSon(-1, new IntTree(8));

        }
        catch (exception const &e) {
            cerr << "Erreur : " << e.what() << endl;
            root->setSon(1, new IntTree(8));
        }

        //Pour Tree
        try {
            tree->addSon(-1, new Tree<float>(3.14));
        }

        catch (exception const &e) {
            cerr << "Erreur : " << e.what() << endl;
        }

        try { tree->removeSon(-1); }

        catch (exception const &e) {
            cerr << "Erreur : " << e.what() << endl;
        }

        try {
            Tree<float> *filss = tree->getSon(-1);
            delete filss;
        }
        catch (exception const &e) {
            cerr << "Erreur : " << e.what() << ", le fils demande n'existe pas" << endl;
        }

        delete root;
        delete tree;

        return 0;
    }
}
