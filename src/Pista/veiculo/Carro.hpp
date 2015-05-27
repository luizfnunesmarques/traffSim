//============================================================================
// Name        : Carro.hpp
// Author      : Luizf
// Version     :
// Copyright   : 
//============================================================================

#ifndef CARRO_HPP_
#define CARRO_HPP_
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;


class Carro {

private:
	int nProbDirecao;
	int nTamanho;

public:
	Carro(){
		nTamanho = (2 + (rand() % (int) (6 - 2 + 1))) + 3;
		nProbDirecao = (rand() % 10);
	}

	int Probabilidade() const {
		return nProbDirecao;
	}

	int Tamanho() const {
		return nTamanho;
	}


};

#endif

