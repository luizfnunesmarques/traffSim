/*
 * GiraSemaforo.hpp
 *
 *  Created on: 27/04/2015
 *      Author: LuizF
 */

#ifndef EVENTOSEMAFORO_HPP_
#define EVENTOSEMAFORO_HPP_

#include "Evento.hpp"
#include "../Semaforo/Central.hpp"
#include "../Relogio.hpp"
#include "../Pista/Pista.hpp"
#include <algorithm>
#include "CarroChegouFim.hpp"

class EventoSemaforo: public Evento {
public:
	EventoSemaforo(int tempoExecucao, int intervaloSemaforo, Central* central,
			Relogio* relogio) :
			Evento(tempoExecucao) {
		this->central = central;
		this->nTempoExecucao = tempoExecucao;
		this->intervaloSemaforo = intervaloSemaforo;
		this->relogio = relogio;
	}

	Evento* Executar() {
		Semaforo* semaforoQueAbriu = this->central->giraSemaforo();

		ListaEnc<RetornoRetiraCarro*>* saidaCarrosConexaoB =
				semaforoQueAbriu->pegaConexaoB()->RemoverEngarrafamento();
		ListaEnc<RetornoRetiraCarro*>* SaidaCarrosConexaoA =
				semaforoQueAbriu->pegaConexaoA()->RemoverEngarrafamento();

		if (!(saidaCarrosConexaoB->listaVazia())) {
			RetornoRetiraCarro* retornoA = saidaCarrosConexaoB->retira();

			while (!(retornoA == NULL)) {
				relogio->AdicionaEvento(
						new CarroChegouFim(
								retornoA->getTempoChegadaPistaDestino(),
								relogio, retornoA->getPistaDestino()));

				try {
					retornoA = saidaCarrosConexaoB->retira();
				} catch (int e) {
					break;
				}
			}
		};

		if (!(SaidaCarrosConexaoA->listaVazia())) {
			RetornoRetiraCarro* retorno = SaidaCarrosConexaoA->retira();
			while (!(retorno == NULL)) {
				relogio->AdicionaEvento(
						new CarroChegouFim(
								retorno->getTempoChegadaPistaDestino(), relogio,
								retorno->getPistaDestino()));

				try {
					retorno = SaidaCarrosConexaoA->retira();
				} catch (int e) {
					break;
				}
			}
		}
		delete saidaCarrosConexaoB;
		delete SaidaCarrosConexaoA;

		return new EventoSemaforo(nTempoExecucao + intervaloSemaforo,
				intervaloSemaforo, central, this->relogio);
	}

private:
	Central* central;
	Relogio* relogio;
	int intervaloSemaforo;
};

#endif
