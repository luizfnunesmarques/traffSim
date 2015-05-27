/*
 * Relogio.hpp
 *
 *  Created on: 22/04/2015
 *      Author: LuizF
 */

#ifndef RELOGIO_HPP_
#define RELOGIO_HPP_
#include "Eventos/Evento.hpp"

class Relogio: private ListaEnc<Evento*> {
public:
	void AdicionaEvento(Evento* ev){
		this->adicionaEmOrdem(ev);
	}

	Evento* proximoEvento(){
		return retiraDoInicio();
	};
	virtual ~Relogio(){

	}

	virtual bool menor(Evento* dado1, Evento* dado2){
		return dado1->getTempoExecucao() < dado2->getTempoExecucao();
	}
private:
	Evento* eventoAtual;
};

#endif
