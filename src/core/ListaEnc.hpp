/* Copyright [2014] <Luiz Marques>
 * TestePilha.cpp
 */

#ifndef LISTAENC_HPP_
#define LISTAENC_HPP_
#define ERROLISTAVAZIA -2;
#define ERROPOSICAO -3;
#define ERROLISTACHEIA -1;
#include <cstdio>
#include <exception>
#include "Elemento.hpp"

template<typename T>
class ListaEnc {
	public:
		ListaEnc();
		~ListaEnc();
		// inicio
		void adicionaNoInicio(const T& dado);
		T retiraDoInicio();
		void eliminaDoInicio();
		// posicao
		void adicionaNaPosicao(const T& dado, int pos);
		int posicao(const T& dado) const;
		T* posicaoMem(const T& dado) const;
		bool contem(const T& dado);
		T retiraDaPosicao(int pos);
		void adiciona(const T& dado);
		T retira();
		// especifico
		T retiraEspecifico(const T& dado);
		void adicionaEmOrdem(const T& data);
		bool listaVazia() const;
		bool igual(T dado1, T dado2);
		bool maior(T dado1, T dado2);
		virtual bool menor(T dado1, T dado2);
		void destroiLista();

		T mostrarElemento(int pos) {
			Elemento<T> *get = head;
			for (int i = 0; i < pos; ++i) {
				get = get->getProximo();
			}

			return get->getInfo();
		}
	protected:
		Elemento<T>* head;
		int size;
		T pegaCabecaLista();
		T pegaCaudaLista(){
			Elemento<T> *deleted = head;
			for (int i = 0; i < size ; ++i) {
				if (deleted->getProximo() == NULL)
					break;

				deleted = deleted->getProximo();
			}
			return deleted->getInfo();
		};

	private:
		void validarPosicaoParaInsercao(int pos);
};

template<typename T>
ListaEnc<T>::ListaEnc() {
	size = 0;
	head = NULL;
}

template<typename T>
ListaEnc<T>::~ListaEnc() {
	destroiLista();
}

template<typename T>
void ListaEnc<T>::adicionaNoInicio(const T& dado) {
	validarPosicaoParaInsercao(0);
	Elemento<T> *novo = new Elemento<T>(dado, head);
	if (novo == NULL)
		throw ERROLISTACHEIA;

	head = novo;
	size++;
}

template<typename T>
T ListaEnc<T>::retiraDoInicio() {
	if (listaVazia())
		throw ERROLISTAVAZIA;

	Elemento<T> *deleted;
	T dadoRetirado;
	deleted = head;
	dadoRetirado = deleted->getInfo();
	head = deleted->getProximo();
	delete (deleted);
	size--;
	return dadoRetirado;
}

template<typename T>
void ListaEnc<T>::eliminaDoInicio() {
	if (listaVazia())
		throw ERROLISTAVAZIA;
	Elemento<T> *deleted = head;
	head = deleted->getProximo();
	delete (deleted);
	size--;
}

template<typename T>
void ListaEnc<T>::adicionaNaPosicao(const T& dado, int pos) {
	validarPosicaoParaInsercao(pos);

	if (pos == 0)
		return adicionaNoInicio(dado);

	Elemento<T> *novo;
	Elemento<T> *anterior;

	novo = new Elemento<T>(dado, NULL);
	anterior = head;

	for (int i = 0; i < pos - 1; i++) {
		anterior = anterior->getProximo();
	}
	novo->setProximo(anterior->getProximo());
	anterior->setProximo(novo);
	size++;
}

template<typename T>
void ListaEnc<T>::validarPosicaoParaInsercao(int pos) {
	if (pos == 0)
		return;

	if ((pos > size) || pos < 0)
		throw ERROPOSICAO;
}

template<typename T>
int ListaEnc<T>::posicao(const T& dado) const {
	if (listaVazia())
		throw ERROLISTAVAZIA;

	int i = 0;
	Elemento<T> *walker = head;
	while (i < size) {
		if (walker->getInfo() == dado)
			return i;
		walker = walker->getProximo();
		i++;
	}
	throw ERROPOSICAO;
}

template<typename T>
T* ListaEnc<T>::posicaoMem(const T& dado) const {
}

template<typename T>
bool ListaEnc<T>::contem(const T& dado) {
	try {
		posicao(dado);
		return true;
	} catch (int e) {
		return false;
	}
}

template<typename T>
T ListaEnc<T>::retiraDaPosicao(int pos) {
	if (listaVazia())
		throw ERROLISTAVAZIA;

	if (pos > (size-1))
		throw ERROPOSICAO;

	if (pos == 0)
		return retiraDoInicio();

	Elemento<T> *walkingDead = head;
	Elemento<T> *anterior;
	for (int i = 0; i < pos; ++i) {
		anterior = walkingDead;
		walkingDead = walkingDead->getProximo();
	}
	anterior->setProximo(walkingDead->getProximo());
	T retorno = walkingDead->getInfo();
	delete(walkingDead);
	size--;
	return retorno;
}

template<typename T>
void ListaEnc<T>::adiciona(const T& dado) {
	return adicionaNaPosicao(dado, size);
}

template<typename T>
T ListaEnc<T>::retira() {
	if (listaVazia())
		throw ERROLISTAVAZIA;
	Elemento<T> *anterior = NULL;
	Elemento<T> *retirado = head;
	T retorno;
	while(!(retirado->getProximo() == NULL)) {
		anterior = retirado;
		retirado = retirado->getProximo();
	}

	if (!(anterior == NULL))
		anterior->setProximo(NULL);
	retorno = retirado->getInfo();
	delete(retirado);
	size--;
	return retorno;
}
template<typename T>
T ListaEnc<T>::retiraEspecifico(const T& dado) {
	if (listaVazia())
		throw ERROLISTAVAZIA;

	int pos = posicao(dado);
	return retiraDaPosicao(pos);
}
template<typename T>
void ListaEnc<T>::adicionaEmOrdem(const T& data) {
	if (listaVazia()) {
		adicionaNoInicio(data);
		return;
	}

	if (this->menor(data, head->getInfo())) {
		adicionaNoInicio(data);
		return;
	}

	Elemento<T> *walker = head;
	for (int i = 0; i < size; ++i) {
		if (this->menor(data, walker->getInfo())) {
			adicionaNaPosicao(data, i);
			return;
		}
		walker = walker->getProximo();
	}
	adiciona(data);
}

template<typename T>
bool ListaEnc<T>::listaVazia() const {
	return this->size == 0;
}
template<typename T>
bool ListaEnc<T>::igual(T dado1, T dado2) {
	return dado1 == dado2;
}

template<typename T>
bool ListaEnc<T>::maior(T dado1, T dado2) {
	return dado1 >= dado2;
}

template<typename T>
bool ListaEnc<T>::menor(T dado1, T dado2) {
	return dado1 <= dado2;
}

template<typename T>
void ListaEnc<T>::destroiLista() {
	if (head == NULL)
		return;

	Elemento<T> *next, *walkingdead;
	walkingdead = head;
	for (int i = 1; i <= size; ++i) {
		next = walkingdead->getProximo();
		delete (walkingdead);
		walkingdead = next;
	}
	size = 0;
}
template<typename T>
T ListaEnc<T>::pegaCabecaLista() {
	return head->getInfo();
}

#endif
