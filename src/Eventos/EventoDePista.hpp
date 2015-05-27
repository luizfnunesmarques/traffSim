/*
 * EventoDePista.hpp
 *
 *  Created on: 27/04/2015
 *      Author: LuizF
 */

#ifndef EVENTODEPISTA_HPP_
#define EVENTODEPISTA_HPP_

#include "Evento.hpp"
#include "../Relogio.hpp"

class EventoDePista: public Evento {
protected:
	Relogio* relogio;
	Pista* pista;
public:
	EventoDePista(int tempoExecucao, Relogio* relogio,
			Pista* pista) :
			Evento(tempoExecucao) {
		this->relogio = relogio;
		this->pista = pista;
	}

	Pista* getPista() {
		return this->pista;
	}
};

#endif /* EVENTODEPISTA_HPP_ */

