/*
 * Graphe.cpp
 */

#include "Graphe.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>


#include <limits>


using namespace std;



Graphe::Graphe( void )
{

}


Graphe::~Graphe( void )
{
    // Puisque _adjacences n'est pas un pointeur il est automatiquement desalloue.
    // Le destructeur de vector s'occupe d'appeler les destructeurs sur chacun de
    // ses elements.
    // Il n'est donc pas utile de desallouer les elements.
}


void
Graphe::ajouterArcs( int a_sommet1, int a_sommet2, int a_longueur, string a_nom )
{
    int tailleMinimum = a_sommet1 < a_sommet2 ? a_sommet2 : a_sommet1;
    while( _adjacences.size() <= tailleMinimum )
    {
        _adjacences.push_back( new vector< Arc * >() );
    }

    assert( 0 <= a_sommet1 && a_sommet1 < _adjacences.size() );
    assert( nullptr != _adjacences[a_sommet1] );
    _adjacences[a_sommet1]->push_back( new Arc( a_sommet2, a_longueur, a_nom ) );

    assert( 0 <= a_sommet2 && a_sommet2 < _adjacences.size() );
    assert( nullptr != _adjacences[a_sommet2] );
    _adjacences[a_sommet2]->push_back( new Arc( a_sommet1, a_longueur, a_nom ) );
}


void
Graphe::plusCourtChemin( void )
{
  int maxLimite = std::numeric_limits<int>::max()/2;
  int tailleMatrice = _adjacences.size();
//  int none = -1;
  int **matriceAdjacence = initialiserMatrice(_adjacences.size()); //[_adjacences.size()][_adjacences.size()];
  int **matriceProvenence = initialiserMatrice(_adjacences.size());  //[_adjacences.size()][_adjacences.size()];

  int **matriceTempo = initialiserMatrice(_adjacences.size());  //[_adjacences.size()][_adjacences.size()];

  //initialise les matrices
  for(int i = 0; i < _adjacences.size(); ++i ){

    for(int n = 0; n < _adjacences.size(); ++n ){

      if(i == n){
        matriceAdjacence[i][n] = 0;
        matriceProvenence[i][n] = i;

        matriceTempo[i][n] = 0;
      }else{
        matriceAdjacence[i][n] = maxLimite;

        matriceProvenence[i][n] = maxLimite;
        matriceTempo[i][n] = maxLimite;

      }

    }
  }




  for(int i = 0; i < _adjacences.size(); ++i){
    vector< Arc * > *vec = _adjacences[i];

    for(int n = 0; n < vec->size(); ++n){

      Arc* arc = vec[0][n];


      matriceAdjacence[i][arc->sommetArrive] = arc->longueur;


    //cout << vec[0][n]->nom <<  "|   sommeArrive   : " << vec[0][n]->sommetArrive  << "|     longueur  :" << vec[0][n]->longueur  <<endl;

    }

  }


//---------------test du prof
tailleMatrice = 5;
int** mm = initialiserMatrice(tailleMatrice);

for(int i = 0; i < tailleMatrice; ++i ){

  for(int n = 0; n < tailleMatrice ; ++n ){

    mm[i][n] = maxLimite;
  //  cout << mm[i][n] << " | ";

  }
//  cout << endl;
}


mm[0][0] = 0; mm[1][1] = 0; mm[2][2] = 0; mm[3][3] = 0; mm[4][4] = 0;
mm[0][1] = 3; mm[0][3] = 7;
mm[1][2] = 3; mm[1][3] = 2;
mm[2][4] = 1;
mm[3][1] = 6; mm[3][2] = 9; mm[3][4] = 5;
mm[4][0] = 4; mm[4][3] = 2;






//-------------------







  int** D =  copierMatrice(mm, tailleMatrice);
  matriceProvenence = initialiserMatrice(tailleMatrice);

  matriceProvenence[0][0] = 0;
  matriceProvenence[0][1] = 0;
  matriceProvenence[0][2] = maxLimite;
  matriceProvenence[0][3] = 0;
  matriceProvenence[0][4] = maxLimite;

  matriceProvenence[1][0] = maxLimite;
  matriceProvenence[1][1] = 1;
  matriceProvenence[1][2] = 1;
  matriceProvenence[1][3] = 1;
  matriceProvenence[1][4] = maxLimite;

  matriceProvenence[2][0] = maxLimite;
  matriceProvenence[2][1] = maxLimite;
  matriceProvenence[2][2] = 2;
  matriceProvenence[2][3] = maxLimite;
  matriceProvenence[2][4] = 2;

  matriceProvenence[3][0] = maxLimite;
  matriceProvenence[3][1] = 3;
  matriceProvenence[3][2] = 3;
  matriceProvenence[3][3] = 3;
  matriceProvenence[3][4] = 3;

  matriceProvenence[4][0] = 4;
  matriceProvenence[4][1] = maxLimite;
  matriceProvenence[4][2] = maxLimite;
  matriceProvenence[4][3] = 4;
  matriceProvenence[4][4] = 4;



  int** T;
  int** P;


  for(int k = 0; k < tailleMatrice; ++k){

    T = copierMatrice(D, tailleMatrice);
    P = copierMatrice(matriceProvenence, tailleMatrice);
    D = initialiserMatrice(tailleMatrice);

    for(int i = 0; i < tailleMatrice; ++i){

      for(int j = 0; j < tailleMatrice; ++j){
        if((T[i][k] + T[k][j]) < T[i][j]){
          D[i][j] = T[i][k] + T[k][j];
          matriceProvenence[i][j] = P[k][j];
        }else{
          D[i][j] = T[i][j];
        }
      }

    }


  }




  //---------------calcule chemain

  //vector<int> *a_destinations;
  //a_destinations->push_back(4);
  //a_destinations->push_back(1);

  vector< vector< int > *> combinaisons;

  //combinaisons.push_back(new vector<int>);

  //combinaisons[0]->push_back(5);
  // cout << combinaisons[0][0][0] << endl;
  int myints[] = {1,3,7,4};
  int indexVec = 0;

  std::sort (myints,myints+4);

  std::cout << "The 3! possible permutations with 3 elements:\n";
  do {
       combinaisons.push_back(new vector<int>);
       for(int i = 0; i < 4; ++i){
         combinaisons[indexVec]->push_back(myints[i]);
        // cout << myints[i];
       }
       //cout << endl;
       indexVec++;

  //  std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2]  << ' ' << myints[3] << '\n';
  } while ( std::next_permutation(myints,myints+4) );


//cout << "size  : " << combinaisons.size() << endl;
  for(int i = 0; i < combinaisons.size(); ++i){
    vector<int>* vec = combinaisons[i];
    for(int n = 0; n < 4; ++n){
      cout << vec[0][n];

    }
    cout << endl;
  }






  //------------









//------- voir matrice


  for(int i = 0; i < tailleMatrice; ++i ){

    for(int n = 0; n < tailleMatrice ; ++n ){

  //  cout << matriceProvenence[i][n] << " | ";

    }
    cout << endl;
  }



//-------

}











int** Graphe:: initialiserMatrice(int taille){

  int **array = new int*[ taille ];

for( int i = 0; i < taille; ++i )
{
    array[ i ]  = new int[ taille ];
}

for(int i = 0; i < taille; ++i){
  for(int n = 0; n < taille; ++n){
    array[i][n] = 0;
  }
}
return array;

}


int** Graphe:: copierMatrice(int** matriceOriginale, int taille){

  int** copie = initialiserMatrice(taille);

  for(int i = 0; i < taille; ++i){

    for(int n = 0; n < taille; ++n){
      copie[i][n] = matriceOriginale[i][n];
    }
  }

  return copie;

}














//--------------------------------------------------------------

ostream &
operator <<( ostream & a_out, Graphe const & a_graphe )
{
    int i = 0;
    int j = 0;

    for( i = 0; i < a_graphe._adjacences.size(); ++ i )
    {
        a_out << i << " : ";
        for( j = 0; j < a_graphe._adjacences[i]->size(); ++ j )
        {
            if( 0 != j )
            {
                a_out << ", ";
            }
            a_out << *( a_graphe._adjacences[i]->at(j) );
        }
        a_out << endl;
    }

    return a_out;
}
