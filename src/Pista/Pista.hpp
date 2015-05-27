/*
 * Pista.hpp
 *
 *  Created on: 22/04/2015
 *      Author: LuizF
 */

#ifndef PISTA_HPP_
#define PISTA_HPP_
#include "../core/FilaEnc.hpp"
#include "../core/Lista.hpp"
#include "veiculo/Carro.hpp"
#include <math.h>

class Pista;

class RetornoRetiraCarro {
public:
	RetornoRetiraCarro() {
	}
	;
	RetornoRetiraCarro(int tempoCarroPercorrePistaDestino,
			Pista* pistaDestino) {
		this->tempoChegadaFimPistaDestino = tempoCarroPercorrePistaDestino;
		this->pistaDestino = pistaDestino;
	}
	int getTempoChegadaPistaDestino() {
		return tempoChegadaFimPistaDestino;
	}
	Pista* getPistaDestino() {
		return pistaDestino;
	}
private:
	int tempoChegadaFimPistaDestino;
	Pista* pistaDestino;
};

class Semaforo {
private:
	bool sinalAberto;
	char nome;
	Pista* pistaConectadaA;
	Pista* pistaConectadaB;
public:
	Semaforo(char nome) {
		sinalAberto = false;
		this->nome = nome;

	}
	void definirConexaoA(Pista* pista) {
		this->pistaConectadaA = pista;
	}
	void definirConexaoB(Pista* pista) {
		this->pistaConectadaB = pista;
	}
	void fecharSinal() {
		this->sinalAberto = false;
	}
	void abrirSinal() {
		this->sinalAberto = true;
	}
	bool sinalLiberado() {
		return this->sinalAberto;
	}

	Pista* pegaConexaoA() {
		return pistaConectadaA;
	}

	Pista* pegaConexaoB() {
		return pistaConectadaB;
	}
};

class Pista: protected FilaEnc<Carro*> {
public:
	Pista() {

	}
	Pista(Pista* con1, int prob1, Pista* con2, int prob2, Pista* con3,
			int prob3, int velocidadeMediaMS, int comprimento,
			Semaforo* semaforo) {

		for (int i = 0; i < prob1; ++i) {
			conexoes[i] = con1;
		}
		int temp = prob1;

		for (int i = temp; i < (prob1 + prob2); ++i) {
			conexoes[i] = con2;
			temp = i;
		}

		for (int i = temp; i < 10; ++i) {
			conexoes[i] = con3;
		}
		this->comprimento = comprimento;
		this->velocidadeMS = velocidadeMediaMS;
		this->semaforo = semaforo;
		this->utilizado = 0;
	}
	virtual std::pair<int, int> AdicionarCarro() {
	}
	;

	Pista(int velocidade, int comprimento) {
		this->velocidadeMS = velocidade;
		this->comprimento = comprimento;

	}

	virtual int ReceberCarro(Carro* carro) {
		if (!(cabeMaisUm(carro->Tamanho())))
			throw -902;

		this->inclui(carro);
		this->utilizado = utilizado + carro->Tamanho();
		return CalcularTempoCarroDemoraPercorrerPista(carro);
	}

	ListaEnc<RetornoRetiraCarro*>* RemoverEngarrafamento() {
		ListaEnc<RetornoRetiraCarro*>* retorno = new ListaEnc<
				RetornoRetiraCarro*>;

		int nEngarrafados = qtdEngarrafados;
		for (int i = 1; i <= nEngarrafados; ++i) {
			try {
				retorno->adiciona(moverCarroDePista());
				qtdEngarrafados--;
			} catch (int e) {
				break;
			}
		}

		return retorno;
	}

	virtual RetornoRetiraCarro* RetiraCarro() {
		if (!(semaforo->sinalLiberado())) {
			qtdEngarrafados++;
			return NULL;
		}

		try {
			return moverCarroDePista();
		} catch (int e) {
			qtdEngarrafados++;
		}
		return NULL;
	}

	virtual ~Pista() {

	}

protected:
	Semaforo * semaforo;
	Pista * conexoes[10];
	int velocidadeMS, comprimento;
	int utilizado;

	int CalcularTempoCarroDemoraPercorrerPista(Carro* carro) {
		return trunc(comprimento / velocidadeMS);
	}

	bool cabeMaisUm(int tamanho) {
		return ((utilizado + tamanho) < this->comprimento);
	}
	int qtdEngarrafados = 0;

private:
	RetornoRetiraCarro* moverCarroDePista() {
		int intencaoManobra = this->primeiro()->Probabilidade();

		int nTamanhoCarroRetirado = this->primeiro()->Tamanho();
		int tempoChegadaNovoCarro = conexoes[intencaoManobra]->ReceberCarro(
				this->primeiro());

		this->retira();
		this->utilizado = utilizado - nTamanhoCarroRetirado;
		return new RetornoRetiraCarro(tempoChegadaNovoCarro,
				conexoes[intencaoManobra]);
	}
};

#endif

