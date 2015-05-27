/*
 * Fonte.hpp
 *
 *  Created on: 26/04/2015
 *      Author: LuizF
 */

#ifndef FONTE_HPP_
#define FONTE_HPP_

#include "Pista.hpp"
#include "Fonte.hpp"
#include <stdlib.h>
#include <tuple>

class Fonte: public Pista {
private:
	int QtdEngarrafados = 0;
	int QtdEntraram = 0;
public:
	Fonte(Pista* con1, int prob1, Pista* con2, int prob2, Pista* con3,
			int prob3, int velocidadeMediaMS, int comprimento,Semaforo* semaforo ,int frequencia, int variacao) :
			Pista(con1, prob1, con2, prob2, con3, prob3, velocidadeMediaMS,
					comprimento, semaforo) {
		this->frequencia = frequencia;
		this->variacao = variacao;
	}

	int PegarQtdCarrosEntraramPista(){
		return QtdEntraram;
	}

	int TempoEntradaNovoCarro(){
		int frequenciaMinima = frequencia - variacao;
		return frequenciaMinima + (rand() % (int) (variacao*2));
	}

	std::pair<int, int> AdicionarCarro() {
		Carro* novoCarro = new Carro();
		if (!(this->cabeMaisUm(novoCarro->Tamanho()))) {
			delete (novoCarro);
			throw -900;
		}
		this->inclui(novoCarro);
		this->utilizado = utilizado + novoCarro->Tamanho();
		int tempoChegada = CalcularTempoCarroDemoraPercorrerPista(novoCarro);
		QtdEntraram++;
		return make_pair(tempoChegada, TempoEntradaNovoCarro());
	}


private:
	int frequencia;
	int variacao;

};

#endif /* FONTE_HPP_ */

