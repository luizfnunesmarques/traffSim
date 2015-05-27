/*
 * CarroChegouFim.hpp
 *
 *  Created on: 27/04/2015
 *      Author: LuizF
 */

#ifndef CARROCHEGOUFIM_HPP_
#define CARROCHEGOUFIM_HPP_

#include "EventoDePista.hpp"
#include <tuple>

class CarroChegouFim: public EventoDePista {
public:

	CarroChegouFim(int tempoExecucao, Relogio* relogio,
			Pista* pista) :
			EventoDePista(tempoExecucao, relogio, pista) {
	}
	;

	Evento* Executar() {
		RetornoRetiraCarro* retorno = pista->RetiraCarro();

		if (retorno == NULL)
				return NULL;

		int tempoChegadaPistaDestino = retorno->getTempoChegadaPistaDestino();
		Pista* pistaDestino = retorno->getPistaDestino();
		delete retorno;
		//Novo evento para retirar o carro da pista pra qual ele foi.
		return new CarroChegouFim(nTempoExecucao + tempoChegadaPistaDestino, relogio, pistaDestino);
	};
};

#endif /* CARROCHEGOUFIM_HPP_ */

