#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//Raphael GINOULHAC



int distance_levenshtein_1(const string& s1, const string& s2)
{
    const std::size_t len1 = s1.size(), len2 = s2.size();
    vector<vector<int> > d(len1 + 1, vector<int>(len2 + 1));

    //initialisation
    d[0][0] = 0;
    for(int i = 1; i <= len1; ++i) d[i][0] = i;
    for(int j = 1; j <= len2; ++j) d[0][j] = j;

    //On remplit la matrice d
    for(int i = 1; i <= len1; ++i){
        for(int j = 1; j <= len2; ++j){
                      d[i][j] = min(min( d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
        }
    }
    return d[len1][len2];
}

int distance_levenshtein_damarau(const string& s1, const string& s2)
{
    const std::size_t len1 = s1.size(), len2 = s2.size();
    vector<vector<int> > d(len1 + 1, vector<int>(len2 + 1));

    //initialisation
    d[0][0] = 0;
    for(int i = 1; i <= len1; ++i) d[i][0] = i;
    for(int j = 1; j <= len2; ++j) d[0][j] = j;

    //On remplit la matrice d
    for(int i = 1; i <= len1; ++i) {
        for(int j = 1; j <= len2; ++j){
                      d[i][j] = min(min( d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
                      //seule différence avec levenshtein
                      if (i>1 && j>1 && s1[i]==s2[j-1] && s1[i-1]==s2[j]){
                          d[i][j]=min(d[i][j], d[i-2][j-2] + (s1[i] == s2[j] ? 0 : 1));
                      }
        }
    }
    return d[len1][len2];
}

int main(){
    string s1 = "dualite";
    string s2 = "durabilite" ;
    int d = distance_levenshtein_1(s1,s2);
    cout << "Distance de Levenshtein : " << d << endl;
    int dd=distance_levenshtein_damarau(s1,s2);
    cout << "Distance de Damerau-Levenshtein : " << dd << endl;

	return 0;
}
