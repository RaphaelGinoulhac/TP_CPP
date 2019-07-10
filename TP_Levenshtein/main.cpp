#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//Raphael GINOULHAC


int affiche_modifications(const vector<vector<int> > &d, const string &s1, const string &s2, bool damerau = false) {
    int mini, current_value, current_i = d.size() - 1, current_j = d[0].size() - 1;
    stack<string> pile;


    while (current_i != 0 || current_j != 0) {
        current_value = d[current_i][current_j];
        if (current_i == 0) {
            if (current_value != d[current_i][current_j - 1]) pile.push("insertion");
            current_j--;

        } else if (current_j == 0) {
            if (current_value != d[current_i - 1][current_j]) pile.push("effacement");
            current_i--;

        } else {
            mini = min(min(d[current_i - 1][current_j], d[current_i][current_j - 1]), d[current_i - 1][current_j - 1]);
            if (damerau && current_i > 1 && current_j > 1 && s1[current_i] == s2[current_j - 1] &&
                s1[current_i - 1] == s2[current_j])
                mini = min(mini, d[current_i - 2][current_j - 2]);

            if (damerau && current_i > 1 && current_j > 1) {
                if (mini == d[current_i - 2][current_j - 2]) {
                    if (current_value != d[current_i - 2][current_j - 2]) pile.push("transposition");
                    current_i -= 2;
                    current_j -= 2;
                    continue;
                }
            }
            if (mini == d[current_i - 1][current_j]) {
                if (current_value != d[current_i - 1][current_j]) pile.push("effacement");
                current_i--;

            } else if (mini == d[current_i][current_j - 1]) {
                if (current_value != d[current_i][current_j - 1]) pile.push("insertion");
                current_j--;

            } else if (mini == d[current_i - 1][current_j - 1]) {
                if (current_value != d[current_i - 1][current_j - 1]) pile.push("substitution");
                current_i--;
                current_j--;

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


void distance_levenshtein(const string &s1, const string &s2) {
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
    affiche_matrice(d);
    affiche_modifications(d, s1, s2);

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
            //le cout de substitution est different
            d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i] == s2[j] ? 0 : 1));
            //seule différence avec levenshtein
            if (i > 1 && j > 1 && s1[i] == s2[j - 1] && s1[i - 1] == s2[j]) {
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + (s1[i] == s2[j] ? 0 : 1));
            }
        }
    }

    cout << "Distance de Damerau-Levenshtein : " << d[len1][len2] << endl;
    affiche_matrice(d);
    affiche_modifications(d, s1, s2, true);

}


int main() {
    string s1 = "ecoles";
    string s2 = "eclose";
    //s1 = "rp";
    //s2 = "pr";

    cout << "Les deux mots sont : " << s1 << " et " << s2 << endl;

    distance_levenshtein(s1, s2);

    distance_levenshtein_damerau(s1, s2);

    return 0;
}
