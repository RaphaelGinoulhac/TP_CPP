#include <Imagine/Graphics.h>
#include <algorithm>
#include <iostream>
#include "../quadtree/quadtree.h"

using namespace Imagine;
using namespace std;

#ifndef srcPath
#define srcPath(s) ("./" s)
#endif


//Variables globales : feuille blanche et noire
auto black = new QuadLeaf<byte>(0);
auto white = new QuadLeaf<byte>(255);
template<>
bool QuadTree<byte>::protect_leaves_from_destruction = true;
//compte le nombre de feuilles de type "white" dans construct_quaddag_grey pour correctement compter le nombre de feuilles en memoire
int n_leaves_dag = 0;


QuadTree<byte> *construct_quadtree(byte *image, int line, int col, int W, int width) {
    /// la sous-image consideree est de taille carree width*width
    /// line, col designe la position du coin superieur gauche de cette sous-image dans l'image originale
    /// W designe une dimension de l'image originale
    //l'image en entree est de taille 1x1
    //mettre protect_leaves_from_destruction=false si on veut utiliser cette fonction

    if (width == 1) {
        return new QuadLeaf<byte>(image[line * W + col]);
    }
    auto son_NW = construct_quadtree(image, line, col, W, width / 2);
    auto son_NE = construct_quadtree(image, line, col + width / 2, W, width / 2);
    auto son_SE = construct_quadtree(image, line + width / 2, col + width / 2, W, width / 2);
    auto son_SW = construct_quadtree(image, line + width / 2, col, W, width / 2);

    //tous les fils sont des feuilles
    if (son_NW->isLeaf() && son_NE->isLeaf() && son_SE->isLeaf() && son_SW->isLeaf()) {
        //s'ils sont tous de la meme couleur on renvoie une seule feuille de cette couleur
        if ((son_NW->value() == son_NE->value()) && (son_NW->value() == son_SE->value()) &&
            (son_NW->value() == son_SW->value())) {
            //inutile de creer une nouvelle feuille on en reutilise une
            delete son_NE;
            delete son_SE;
            delete son_SW;
            return son_NW;
        }
            //sinon, on renvoie un quadnode avec ces 4 feuilles en fils
        else {
            return new QuadNode<byte>(son_NW, son_NE, son_SE, son_SW);
        }
    } else {
        return new QuadNode<byte>(son_NW, son_NE, son_SE, son_SW);
    }
}

QuadTree<byte> *
construct_quaddag(byte *image, int line, int col, int W, int width) {
    //on n'utilise que les deux QuadLeaf black et white deja construits
    if (width == 1) {
        if (image[line * W + col] == 0)
            return black;
        else return white;
    }
    auto son_NW = construct_quaddag(image, line, col, W, width / 2);
    auto son_NE = construct_quaddag(image, line, col + width / 2, W, width / 2);
    auto son_SE = construct_quaddag(image, line + width / 2, col + width / 2, W, width / 2);
    auto son_SW = construct_quaddag(image, line + width / 2, col, W, width / 2);

    //tous les fils sont des feuilles
    if (son_NW->isLeaf() && son_NE->isLeaf() && son_SE->isLeaf() && son_SW->isLeaf()) {
        //s'ils sont tous de la meme couleur on renvoie une seule feuille de cette couleur
        if ((son_NW->value() == son_NE->value()) && (son_NW->value() == son_SE->value()) &&
            (son_NW->value() == son_SW->value())) {

            if (son_NW->value() == 0)
                return black;
            else return white;
        }
            //sinon, on renvoie un quadnode avec ces 4 feuilles en fils
        else {
            return new QuadNode<byte>(son_NW, son_NE, son_SE, son_SW);
        }
    } else {
        return new QuadNode<byte>(son_NW, son_NE, son_SE, son_SW);
    }

}

QuadTree<byte> *
construct_quaddag_rectangle(byte *image, int line, int col, int W_square, int W, int H, int width) {
    /// W_square : taille d'un des cotes du carre dans lequel on plonge l'image (de taille 2^N donc)
    /// W et H sont la largeur et la hauteur de l'image originale
    /// On complete de maniere implicite par du blanc
    if (width == 1) {
        if (line >= H || col >= W || image[line * W + col] == 255)
            return white;
        else return black;
    }
    auto son_NW = construct_quaddag_rectangle(image, line, col, W_square, W, H, width / 2);
    auto son_NE = construct_quaddag_rectangle(image, line, col + width / 2, W_square, W, H, width / 2);
    auto son_SE = construct_quaddag_rectangle(image, line + width / 2, col + width / 2, W_square, W, H, width / 2);
    auto son_SW = construct_quaddag_rectangle(image, line + width / 2, col, W_square, W, H, width / 2);

    //tous les fils sont des feuilles
    if (son_NW->isLeaf() && son_NE->isLeaf() && son_SE->isLeaf() && son_SW->isLeaf()) {
        //s'ils sont tous de la meme couleur on renvoie une seule feuille de cette couleur
        if ((son_NW->value() == son_NE->value()) && (son_NW->value() == son_SE->value()) &&
            (son_NW->value() == son_SW->value())) {

            if (son_NW->value() == 0)
                return black;
            else return white;
        }
            //sinon, on renvoie un quadnode avec ces 4 feuilles en fils
        else {
            return new QuadNode<byte>(son_NW, son_NE, son_SE, son_SW);
        }
    } else {
        return new QuadNode<byte>(son_NW, son_NE, son_SE, son_SW);
    }

}


void decode(QuadTree<byte> *q, byte *decoded_image, int line, int col, int W, int width, bool draw_borders) {

    if (q->isLeaf()) {
        for (int l = 0; l < width; l++) {
            for (int c = 0; c < width; c++) {
                decoded_image[(line + l) * W + (col + c)] = q->value();
            }
        }
        if (draw_borders)
            drawRect(IntPoint2(col, line), width, width, Color(255, 0, 0));

    } else {
        decode(q->son(NW), decoded_image, line, col, W, width / 2, draw_borders);
        decode(q->son(NE), decoded_image, line, col + width / 2, W, width / 2, draw_borders);
        decode(q->son(SE), decoded_image, line + width / 2, col + width / 2, W, width / 2, draw_borders);
        decode(q->son(SW), decoded_image, line + width / 2, col, W, width / 2, draw_borders);
    }

}


void
decode_rect(QuadTree<byte> *q, byte *decoded_image, int line, int col, int W, int H, int width, bool draw_borders) {

    if (q->isLeaf()) {
        //si on sort de l'image, on ne remplit pas le tableau. Enlever cette condition pour afficher tous les carres (meme ceux qui sortent de l'image)
        if (line + width - 1 < H && col + width - 1 < W) {
            for (int l = 0; l < width; l++) {
                for (int c = 0; c < width; c++) {
                    decoded_image[(line + l) * W + (col + c)] = q->value();
                }
            }
            if (draw_borders)
                //En rouge pour pouvoir voir les carres meme sur du noir
                drawRect(IntPoint2(col, line), width, width, Color(255, 0, 0));
        }

    } else {
        decode_rect(q->son(NW), decoded_image, line, col, W, H, width / 2, draw_borders);
        decode_rect(q->son(NE), decoded_image, line, col + width / 2, W, H, width / 2, draw_borders);
        decode_rect(q->son(SE), decoded_image, line + width / 2, col + width / 2, W, H, width / 2, draw_borders);
        decode_rect(q->son(SW), decoded_image, line + width / 2, col, W, H, width / 2, draw_borders);
    }
    //Pour observer le dessin du quadtree plus lentement
    //milliSleep(1);

}


QuadTree<byte> *
construct_quaddag_grey(byte *image, int line, int col, int W_square, int W, int H, int width, int threshold,
                       int threshold_per_depth) {
    /// Fonction prenant en argument une image de niveau de gris, possiblement rectangulaire
    /// W_square : taille d'un des cotes du carre dans lequel on plonge l'image (de taille 2^N donc)
    /// W et H sont la largeur et la hauteur de l'image originale
    /// On complete de maniere implicite par du blanc
    if (width == 1) {
        if (line >= H || col >= W || image[line * W + col] == 255) {
            n_leaves_dag++;
            return white;
        } else return new QuadLeaf<byte>(image[line * W + col]);;
    }
    //on appelle les fils avec un threshold plus grand de threshold_per_depth (quand la taille de la region diminue)
    auto son_NW = construct_quaddag_grey(image, line, col, W_square, W, H, width / 2, threshold + threshold_per_depth,
                                         threshold_per_depth);
    auto son_NE = construct_quaddag_grey(image, line, col + width / 2, W_square, W, H, width / 2,
                                         threshold + threshold_per_depth, threshold_per_depth);
    auto son_SE = construct_quaddag_grey(image, line + width / 2, col + width / 2, W_square, W, H, width / 2,
                                         threshold + threshold_per_depth, threshold_per_depth);
    auto son_SW = construct_quaddag_grey(image, line + width / 2, col, W_square, W, H, width / 2,
                                         threshold + threshold_per_depth, threshold_per_depth);

    //tous les fils sont des feuilles
    if (son_NW->isLeaf() && son_NE->isLeaf() && son_SE->isLeaf() && son_SW->isLeaf()) {
        //s'ils sont tous d'intensite voisine on renvoie une feuille d'intensite moyenne.
        byte v_nw = son_NW->value();
        byte v_ne = son_NE->value();
        byte v_se = son_SE->value();
        byte v_sw = son_SW->value();
        if ((abs(v_nw - v_ne) < threshold) && (abs(v_nw - v_se) < threshold) &&
            (abs(v_nw - v_sw) < threshold) && (abs(v_ne - v_se) < threshold) && (abs(v_ne - v_sw)) < threshold) {
            byte mean = byte((v_nw + v_ne + v_se + v_sw) / 4);

            int nw_dag = v_nw == 255;
            int ne_dag = v_ne == 255;
            int se_dag = v_se == 255;
            int sw_dag = v_sw == 255;
            int sum_dag = nw_dag + ne_dag + se_dag + sw_dag;

            if (mean == 255) {
                n_leaves_dag += 1 - sum_dag;
                return white;
            } else {
                n_leaves_dag -= sum_dag;
                return new QuadLeaf<byte>(mean);
            }
        }
            //sinon, on renvoie un quadnode avec ces 4 feuilles en fils
        else {
            return new QuadNode<byte>(son_NW, son_NE, son_SE, son_SW);
        }
    } else {
        return new QuadNode<byte>(son_NW, son_NE, son_SE, son_SW);
    }

}


void compression(QuadTree<byte> *q, int width, int height, bool blackwhite) {
    //blackwhite : indique si l'image est en noir et blanc ou non

    cout << "Nombre de noeuds dans le quadtree : " << q->nTrees() << endl;
    auto a = new QuadNode<byte>(0, 0, 0, 0);
    auto b = new QuadLeaf<byte>(0);

    int image_size = sizeof(byte[width * height]);
    //nombre de feuilles en memoire
    int effective_n_leaves;
    if (blackwhite)
        effective_n_leaves = 2;
    else effective_n_leaves = q->nLeaves() - n_leaves_dag + 1;

    int quadtree_size = q->nNodes() * sizeof(*a) + effective_n_leaves * sizeof(*b);
    //cout << "Nombre de feuilles dag : " << n_leaves_dag << endl;
    cout << "Taille de l'image en octets : " << image_size << " et taille du quadtree : " << quadtree_size << endl;
    cout << "Taux de compression : " << 1.0 * quadtree_size / image_size << endl;

    delete a;
    delete b;
}


int smallest_power_2(int width, int height) {
    int W_square = 1;
    while (W_square < max(width, height)) {
        W_square *= 2;
    }
    cout << "Plus petite puissance de 2 superieure a la hauteur et a la largeur de l'image : " << W_square << endl;
    return W_square;
}

int main(int argc, char **argv) {
    // Get image file (default is running horse)
    const char *image_file =
            (argc > 1) ? argv[1] : srcPath("running-horse-square.png");

    // Load image
    byte *image;
    int width, height;
    cout << "Chargement d'une image noir et blanc carree : " << image_file << endl;
    loadGreyImage(image_file, image, width, height);

    // Print statistics
    cout << "Image size: " << width << "x" << height << endl;
    cout << "Number of pixels: " << width * height << endl;

    // Display image
    Window window = openWindow(width, height);
    putGreyImage(IntPoint2(0, 0), image, width, height);

    // Pause
    click();

    //Construction du quadtree
    cout << "Encodage de l'image dans un quadtree et affichage de ce dernier" << endl;
    auto q = construct_quaddag(image, 0, 0, width, width);

    //Affichage du quadtree
    byte *decoded_image = new byte[width * height];
    decode(q, decoded_image, 0, 0, width, width, true);
    click();

    //Decodage
    cout << "Affichage de l'image decodee" << endl;
    putGreyImage(IntPoint2(0, 0), decoded_image, width, height);
    compression(q, width, height, true);
    click();

    closeWindow(window);

    /// Rectangle
    const char *image_file_rect = srcPath("running-horse-rect.png");
    int width_rect, height_rect;
    byte *image_rect;
    cout << "Chargement d'une image noir et blanc rectangulaire : " << image_file_rect << endl;

    loadGreyImage(image_file_rect, image_rect, width_rect, height_rect);
    cout << "Image size: " << width_rect << "x" << height_rect << endl;
    cout << "Number of pixels: " << width_rect * height_rect << endl;

    int W_square = smallest_power_2(width_rect, height_rect);

    Window window_rect = openWindow(width_rect, height_rect);
    putGreyImage(IntPoint2(0, 0), image_rect, width_rect, height_rect);
    click();

    cout << "Encodage de l'image dans un quadtree et affichage de ce dernier" << endl;
    auto q_rect = construct_quaddag_rectangle(image_rect, 0, 0, W_square, width_rect, height_rect, W_square);
    byte *decoded_image_rect = new byte[width_rect * height_rect];
    //initialisation de l'image decodee avec du blanc
    fill_n(decoded_image_rect, width_rect * height_rect, 255);
    decode_rect(q_rect, decoded_image_rect, 0, 0, width_rect, height_rect, W_square, true);
    click();

    cout << "Affichage de l'image decodee" << endl;
    putGreyImage(IntPoint2(0, 0), decoded_image_rect, width_rect, height_rect);
    compression(q_rect, width_rect, height_rect, true);
    click();

    closeWindow(window_rect);

    ///Niveaux de gris
    const char *image_file_grey = srcPath("lena.png");
    int width_grey, height_grey;
    byte *image_grey;
    cout << "Chargement d'une image en niveaux de gris rectangulaire : " << image_file_grey << endl;

    loadGreyImage(image_file_grey, image_grey, width_grey, height_grey);
    cout << "Image size: " << width_grey << "x" << height_grey << endl;
    cout << "Number of pixels: " << width_grey * height_grey << endl;

    W_square = smallest_power_2(width_grey, height_grey);

    Window window_grey = openWindow(width_grey, height_grey);
    putGreyImage(IntPoint2(0, 0), image_grey, width_grey, height_grey);
    click();

    cout << "Encodage de l'image dans un quadtree et affichage de ce dernier" << endl;
    auto q_grey = construct_quaddag_grey(image_grey, 0, 0, W_square, width_grey, height_grey, W_square, 20, 4);
    byte *decoded_image_grey = new byte[width_grey * height_grey];
    fill_n(decoded_image_grey, width_grey * height_grey, 255);
    decode_rect(q_grey, decoded_image_grey, 0, 0, width_grey, height_grey, W_square, true);
    click();

    cout << "Affichage de l'image decodee" << endl;
    putGreyImage(IntPoint2(0, 0), decoded_image_grey, width_grey, height_grey);
    compression(q_grey, width_grey, height_grey, false);
    click();


    delete[] image;
    delete q;
    delete[] decoded_image;
    delete[] image_rect;
    delete q_rect;
    delete[] decoded_image_rect;
    delete[] image_grey;
    delete q_grey;
    delete[] decoded_image_grey;
    delete black;
    delete white;


    // Exit
    return 0;
}
