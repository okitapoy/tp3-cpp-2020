/*
 * Graphe.cpp
 */

#include "Graphe.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>


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
  int maxLimite = std::numeric_limits<int>::max();
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








  int** D =  copierMatrice(matriceAdjacence, _adjacences.size());
  matriceProvenence = initialiserMatrice(_adjacences.size());


  for(int k = 0; k < _adjacences.size(); ++k){

    int** T = copierMatrice(D, _adjacences.size());;
    int** P = copierMatrice(matriceProvenence, _adjacences.size());
    D = initialiserMatrice(_adjacences.size());

    for(int i = 0; i < _adjacences.size(); ++i){

      for(int j = 0; j < _adjacences.size(); ++j){

        if((T[i][k] + T[k][j]) < T[i][j]){
          D[i][j] = 1;//T[i][k] + T[k][j];
          matriceProvenence[i][j] = P[k][j];
        }else{
          D[i][j] = T[i][j];
        }
      }

    }


  }









//------- voir matrice
  for(int i = 0; i < _adjacences.size(); ++i ){

    for(int n = 0; n < _adjacences.size(); ++n ){

      cout << D[i][n] << " | ";

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
