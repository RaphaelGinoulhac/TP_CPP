#include "IntTree.h"

//Raphael GINOULHAC
//Pour les dernieres fonctions de Tree T, j'ai une erreur, il faut rajouter template devant vector sans doute
//Il n'y a pas beaucoup d'erreur a gerer
//Il faut recopier toutes les fonctions de inttree pour tree si on veut s'en servir en pratique
//Les parcours en bonus consistent juste en changer l'ordre dans lequel on affiche le noeud courant et on parcourt les fils
//En largeur, il suffit d'importer <queue>



int main(){
    IntTree* root = new IntTree(12);
    root->addAsLastSon((new IntTree(8)));
    root->getSon(0)->addAsLastSon(new IntTree(4));
    root->getSon(0)->addAsLastSon(new IntTree(9));
    root->addAsLastSon((new IntTree(23)));
    root->getSon(1)->addAsLastSon(new IntTree(17));
    root->getSon(1)-> getSon(0)-> addAsLastSon(new IntTree(15));

    root->display("* ");

    //IntTree* root2 = new IntTree(12);
    //root2->removeLastSon();


	return 0;
}
