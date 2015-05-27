/*
 * Central.hpp
 *
 *  Created on: 27/04/2015
 *      Author: LuizF
 */

#ifndef CENTRAL_HPP_
#define CENTRAL_HPP_

#include "../core/Lista.hpp"
#include "../Pista/Pista.hpp"

class Central: public Lista<Semaforo*> {
public:
	~Central();
	Central() :
			Lista(4) {
		this->posicaoSemaforoAtual = 0;
	}

	Semaforo* giraSemaforo() {
		mostra(posicaoSemaforoAtual)->fecharSinal();

		if (posicaoSemaforoAtual == 3) {
			posicaoSemaforoAtual = 0;
		} else {
			posicaoSemaforoAtual++;
		}

		mostra(posicaoSemaforoAtual)->abrirSinal();
		return mostra(posicaoSemaforoAtual);
	}

	void abrirPrimeiroSinal() {
		this->mostra(0)->abrirSinal();
	}
	void inserirCaos(){
		this->mostra(0)->abrirSinal();
		this->mostra(1)->abrirSinal();
		this->mostra(2)->abrirSinal();
		this->mostra(3)->abrirSinal();
	}
	;

private:
	int posicaoSemaforoAtual;
};

#endif /* CENTRAL_HPP_ */
