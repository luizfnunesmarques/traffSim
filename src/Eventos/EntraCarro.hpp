/*
 * EntraCarro.hpp
 *
 *  Created on: 27/04/2015
 *      Author: LuizF
 */

#ifndef ENTRACARRO_HPP_
#define ENTRACARRO_HPP_
using namespace std;
#include "EventoDePista.hpp"
#include "CarroChegouFim.hpp"
#include "../Pista/Pista.hpp"
#include "../Relogio.hpp"
#include <tuple>

class EntraCarro: public EventoDePista {
public:
	EntraCarro(int tempoExecucao, Relogio* relogio,
			Pista* pista) :
			EventoDePista(tempoExecucao, relogio, pista) {
	}
	;

	Evento* Executar() {
		try {
			std::pair<int, int> resultAddCarro;
			resultAddCarro = pista->AdicionarCarro();

			relogio->AdicionaEvento(
					new EntraCarro(resultAddCarro.second + nTempoExecucao,relogio, this->pista));

			return new CarroChegouFim(nTempoExecucao + resultAddCarro.first, relogio, this->pista);
		} catch (int excecao) {
			return NULL;
		}
	}
	;
};

#endif /* ENTRACARRO_HPP_ */
