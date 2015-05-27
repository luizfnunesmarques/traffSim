/*
 * Sumidouro.hpp
 *
 *  Created on: 26/04/2015
 *      Author: LuizF
 */

#ifndef SUMIDOURO_HPP_
#define SUMIDOURO_HPP_

#include "Pista.hpp"
#include "../core/FilaEnc.hpp"
#include "Sumidouro.hpp"
#include "veiculo/Carro.hpp"

class Sumidouro: public Pista {
public:
	Sumidouro(int velocidade, int Tamanho) {
		this->velocidadeMS = velocidade;
		this->comprimento = Tamanho;
		utilizado = 0;
	};


	RetornoRetiraCarro* RetiraCarro(){
		Carro* carroQueSaiuDoSistema = this->retira();
		this->utilizado = utilizado-carroQueSaiuDoSistema->Tamanho();
		delete carroQueSaiuDoSistema;
		qtdSairam++;
		return NULL;
	};

	int QuantidadeCarrosSairam(){
		return qtdSairam;
	}
private:
	int qtdSairam = 0;
};

#endif

