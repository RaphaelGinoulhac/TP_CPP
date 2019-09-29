#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <time.h>

using namespace std;

//Raphael GINOULHAC


void affiche_modifications(const vector<vector<int> > &d, const string &s1, const string &s2, bool damerau = false) {
    //minimum entre les differentes valeurs en haut, a gauche, et en haut a gauche
    // valeur actuelle de d[i][j]; et position dans la matrice
    int mini, current_value, current_i = d.size() - 1, current_j = d[0].size() - 1;
    //On utilise une pile pour stocker les operations a effectuer quand on remonte le chemin dans la matrice
    stack<string> pile;


    while (current_i != 0 || current_j != 0) {
        current_value = d[current_i][current_j];
        //On est sur la premiere ligne, on ne peut qu'aller a gauche
        if (current_i == 0) {
            if (current_value != d[current_i][current_j - 1]) pile.push("insertion " + string(1, s2[current_j - 1]));
            current_j--;
            //On est sur la premiere colonne, on ne peut qu'aller en haut
        } else if (current_j == 0) {
            if (current_value != d[current_i - 1][current_j]) pile.push("effacement " + string(1, s1[current_i - 1]));
            current_i--;

        } else {
            //On regarde quelle direction va minimiser la distance, pour continuer le chemin
            mini = min(min(d[current_i - 1][current_j], d[current_i][current_j - 1]), d[current_i - 1][current_j - 1]);

            if (damerau && current_i > 1 && current_j > 1 && s1[current_i - 1] == s2[current_j - 2] &&
                s1[current_i - 2] == s2[current_j - 1])
                mini = min(mini, d[current_i - 2][current_j - 2]);


            if (mini == d[current_i - 1][current_j - 1]) {
                if (current_value != d[current_i - 1][current_j - 1])
                    pile.push("substitution " + string(1, s1[current_i - 1]) + " en " + string(1, s2[current_j - 1]));
                current_i--;
                current_j--;

            } else if (mini == d[current_i - 1][current_j]) {
                if (current_value != d[current_i - 1][current_j])
                    pile.push("effacement " + string(1, s1[current_i - 1]));
                current_i--;

            } else if (mini == d[current_i][current_j - 1]) {
                if (current_value != d[current_i][current_j - 1])
                    pile.push("insertion " + string(1, s2[current_j - 1]));
                current_j--;
            }
                //la condition est redondante vu que c'est le dernier cas possible mais on la laisse par souci de clarte
            else if (damerau && current_i > 1 && current_j > 1) {
                if (mini == d[current_i - 2][current_j - 2]) {
                    if (current_value != d[current_i - 2][current_j - 2]) {
                        pile.push("transposition " + string(1, s1[current_i - 1]) + " et " +
                                  string(1, s1[current_i - 2]));
                    }
                    current_i -= 2;
                    current_j -= 2;
                    continue;
                }
            }
        }
    }
    while (!pile.empty()) {
        cout << pile.top();
        pile.pop();
        if (!pile.empty()) cout << ", ";
    }
    cout << endl;
}


void affiche_matrice(const vector<vector<int> > &d) {
    cout << "Matrice des distances entre prefixes :" << endl;
    for (int i = 0; i < d.size(); i++) {
        for (int j = 0; j < d[0].size(); j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
}


void distance_levenshtein(const string &s1, const string &s2, bool affichage = true) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    vector<vector<int> > d(len1 + 1, vector<int>(len2 + 1));

    //initialisation
    d[0][0] = 0;
    for (int i = 1; i <= len1; ++i) d[i][0] = i;
    for (int j = 1; j <= len2; ++j) d[0][j] = j;

    //On remplit la matrice d
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
        }
    }

    cout << "Distance de Levenshtein : " << d[len1][len2] << endl;
    if (affichage) {
        affiche_matrice(d);
        affiche_modifications(d, s1, s2);
    }

}

void distance_levenshtein_damerau(const string &s1, const string &s2) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    vector<vector<int> > d(len1 + 1, vector<int>(len2 + 1));

    //initialisation
    d[0][0] = 0;
    for (int i = 1; i <= len1; ++i) d[i][0] = i;
    for (int j = 1; j <= len2; ++j) d[0][j] = j;

    //On remplit la matrice d
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
            //seule différence avec levenshtein
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
            }
        }
    }

    cout << "Distance de Damerau-Levenshtein : " << d[len1][len2] << endl;
    affiche_matrice(d);
    affiche_modifications(d, s1, s2, true);

}

//Meme chose pour damerau, juste un bloc if a rajouter et on utilise 3 vector
int distance_levenshtein_lineaire_aux(const string &s1, const string &s2) {
    //On suppose que la plus petite chaine est s2 (pour gagner en complexite spatiale)
    const std::size_t len1 = s1.size(), len2 = s2.size();
    vector<int> d0(len2 + 1);
    vector<int> d1(len2 + 1);

    //Initialisation de la 1ere ligne comme dans l'algo precedent
    for (int i = 0; i <= len2; ++i) {
        d0[i] = i;
    }

    for (int i = 1; i <= len1; ++i) {
        //Initialisation de la condition limite comme dans l'algo precedent
        d1[0] = i;
        // Meme formule
        for (int j = 1; j <= len2; ++j) {
            d1[j] = min(min(d0[j] + 1, d1[j - 1] + 1), d0[j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
        }
        //Swap pour mettre a jour le contenu de d0
        d0.swap(d1);
    }
    return d0[len2];
}


void distance_levenshtein_lineaire(const string &s1, const string &s2) {
    int dist;
    //permet d'avoir une complexite spatiale en O(min(m,n)) ou m, n sont les longueurs des chaines
    if (s1.size() < s2.size()) dist = distance_levenshtein_lineaire_aux(s2, s1);
    else dist = distance_levenshtein_lineaire_aux(s1, s2);

    cout << "Distance de Levenshtein (version lineaire en espace) : " << dist << endl;
}


int distance_levenshtein_rec_aux(const string &s1, const string &s2, int i, int j) {
    if (i == 0 || j == 0) return max(i, j);

    return min(
            min(distance_levenshtein_rec_aux(s1, s2, i - 1, j) + 1, distance_levenshtein_rec_aux(s1, s2, i, j - 1) + 1),
            distance_levenshtein_rec_aux(s1, s2, i - 1, j - 1) + (s1[i - 1] == s2[j - 1] ? 0 : 1));
}


void distance_levenshtein_rec(const string &s1, const string &s2) {
    cout << "Distance de Levenshtein (version recursive) : "
         << distance_levenshtein_rec_aux(s1, s2, s1.size(), s2.size()) << endl;
}


int distance_levenshtein_rec_memo_aux(const string &s1, const string &s2, int i, int j, vector<vector<int> > &memo) {
    if (memo[i][j] == -1) {
        memo[i][j] = (i == 0 || j == 0) ? max(i, j) : min(
                min(distance_levenshtein_rec_memo_aux(s1, s2, i - 1, j, memo) + 1,
                    distance_levenshtein_rec_memo_aux(s1, s2, i, j - 1, memo) + 1),
                distance_levenshtein_rec_memo_aux(s1, s2, i - 1, j - 1, memo) + (s1[i - 1] == s2[j - 1] ? 0 : 1));
    }
    return memo[i][j];
}

void distance_levenshtein_rec_memo(const string &s1, const string &s2) {
    vector<vector<int> > memo(s1.size() + 1, vector<int>(s2.size() + 1, -1));
    cout << "Distance de Levenshtein (version recursive memoisee) : "
         << distance_levenshtein_rec_memo_aux(s1, s2, s1.size(), s2.size(), memo) << endl;
    //On peut afficher la matrice de distance entre prefixes memoisee pour la comparer a la version iterative (ce sont les memes)
    //affiche_matrice(memo);
}


int main() {
    string s1 = "ecoles";
    string s2 = "eclose";

    //s1 = "testpluslong";
    //s2 = "longmottest";

    //s1 = "testvraimentpluslongcomplexe";
    //s2 = "treslongmottestcomplexite";

    cout << "Les deux mots sont : " << s1 << " et " << s2 << endl;

    clock_t t1, t2;

    t1 = clock();
    //Pour correctement comparer les temps d'execution avec la version recursive memoisee, mettre affichage=false.
    // Utiliser des mots plus longs (et commenter la version recursive naive qui prendra trop de temps)
    distance_levenshtein(s1, s2, true);
    t2 = clock();
    cout << "Execution en " << (t2 - t1) / double(CLOCKS_PER_SEC) << " secondes" << endl;

    distance_levenshtein_damerau(s1, s2);

    distance_levenshtein_lineaire(s1, s2);

    t1 = clock();
    distance_levenshtein_rec(s1, s2);
    t2 = clock();
    cout << "Execution en " << (t2 - t1) / double(CLOCKS_PER_SEC) << " secondes" << endl;

    t1 = clock();
    distance_levenshtein_rec_memo(s1, s2);
    t2 = clock();
    cout << "Execution en " << (t2 - t1) / double(CLOCKS_PER_SEC) << " secondes" << endl;

    return 0;
}
