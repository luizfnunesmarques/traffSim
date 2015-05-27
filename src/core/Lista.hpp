/*
 * Lista.hpp
 *
 *  Created on: 08/09/2014
 *      Author: LuizF
 */

#ifndef LISTA_HPP_
#define LISTA_HPP_
#define NUMERO_INDEFINIDO -999
#define ERROLISTACHEIA  -1;
#define ERROLISTAVAZIA  -2
#define ERROPOSICAO -3
#define POSZERO 0

#include <exception>
#include <cstdio>

template<typename T>
class Lista {
 private:
	int nMaxLista;
	int nUltElemento;
	T* dados;

	/**
	 * @brief Valida a lista para inserção de um novo elemento.
	 * @details Verifica se a lista não está cheia.
	 * Caso estiver, lança ERROLISTACHEIA
	 * 
	 */
	void ValidarListaParaInsercao();

	/**
	 * @brief Valida a lista para retirada de um elemento.
	 * @details Verifica se a lista não está vazia
	 * Caso estiver, lança ERROLISTAVAZIA.
	 */
	void ValidarListaParaRetirada();

	/**
	 * @brief Inicializa a lista.
	 *  
	 * @param pnTam Tamanho máximo da lista.
	 */
	void InicializaLista(int pnTam);

	/**
	 * @brief Valida a posição informada.
	 * @details Lança ERROPOSICAO caso a posição informada seja inválida.
	 * 
	 * @param pnPos Posição.
	 */
	void ValidarPosicaoParaInsercao(int pnPos);

 public:
 	/**
 	 * @brief Construtor genérico.
 	 */
	Lista();

	/**
	 * @brief Construtor de uma lista especializada para qualquer objeto T.
	 * 
	 * @param tam [description]
	 */
	explicit Lista(int tam);

	int getTamanho(){
		return nMaxLista+1;
	}

	/**
	 * @brief Adiciona um dado na próxima posição disponível.
	 * 
	 * @param dado Dado a ser inserido.
	 */
	void adiciona(T dado);

	/**
	 * @brief Adiciona um dado no inicio da lista.
	 * @details Adiciona um dado no inicio da lista e "empurra" os demais objetos para as posições posteriores. 
	 * @param dado [description]
	 */
	void adicionaNoInicio(T dado);

	/**
	 * @brief Adiciona um dado na posição desejada.
	 * @details [long description]
	 * 
	 * @param dado Dado a ser inserido.
	 * @param posicao Posição do dado a ser inserido.
	 */
	void adicionaNaPosicao(T dado, int posicao);

	/**
	 * @brief ADiciona um elemento ordenado. Ordenação decrescente.
	 * 
	 * @param dado Dado a ser inserido.
	 */
	void adicionaEmOrdem(T dado);

	/**
	 * @brief Retira um dado da lista.
	 * @details Retira o dado da cauda da lista.
	 * @return Dado
	 */	 
	T retira();

	/**
	 * @brief Retira o dado da posição 0.
	 * @details Retira o dado que está na ponta da lista.
	 * @return Dado Retirado.
	 */
	T retiraDoInicio();

	/**
	 * @brief Retira um dado na posição informada.
	 * @details Retira o dado que está presente na posiçao.
	 * 
	 * @param posicao Posição desejada.
	 * @return Dado retirado.
	 */
	T retiraDaPosicao(int posicao);

	/**
	 * @brief Retira um dado especídifico da lista.
	 * @details Procura o dado informado na lista, retira e devolve.
	 * 
	 * @param dado dado a ser procurado e devolvido.
	 * @return dado.
	 */
	T retiraEspecifico(T dado);

	/**
	 * @brief Devolve a posição do dado informado.
	 * @details [long description]
	 * 
	 * @param dado Dado a ser procurado.
	 * @return Posição.
	 */		
	int posicao(T dado);

	/**
	 * @brief Verifica e um determinado dado está na lista.
	 * @details [long description]
	 * 
	 * @param dado Dado a ser procurado.
	 * @return Boolean
	 */
	bool contem(T dado);

	/**
	 * @brief Verifica se um dado e igual ao outro.
	 * @details [long description]
	 * 
	 * @param dado1 dado
	 * @param dado2 dado
	 * 
	 * @return Boolean
	 */
	bool igual(T dado1, T dado2);

	/**
	 * @brief Verifica se um dado é maior que outro.
	 * @details [long description]
	 * 
	 * @param dado1 dado.
	 * @param dado2 dado.
	 * 
	 * @return boolean
	 */
	bool maior(T dado1, T dado2);

	/**
	 * @brief Verifica se um dado é menor que outro.
	 * @details [long description]
	 * 
	 * @param dado1 dado
	 * @param dado2 dado
	 * 
	 * @return boolean
	 */
	bool menor(T dado1, T dado2);

	/**
	 * @brief Testa se a lista está cheiada.
	 * @details [long description]
	 * @return Boolean
	 */
	bool listaCheia();

	/**
	 * @brief Testa se a lista está vazia.
	 * @details [long description]
	 * @return boolean
	 */
	bool listaVazia();

	/**
	 * @brief Canela a lista virtualmente, setando a ultima pos~ição para -1;
	 * @details [long description]
	 */
	void destroiLista();

	T mostra(int pos){
		return this->dados[pos];
	}
};

template<typename T>
Lista<T>::Lista() {
}

template<typename T>
Lista<T>::Lista(int tam) {
	nUltElemento = -1;
	InicializaLista(tam);
}

template<typename T>
void Lista<T>::adiciona(T dado) {
	this->ValidarListaParaInsercao();

	nUltElemento++;
	dados[nUltElemento] = dado;
}

template<typename T>
void Lista<T>::adicionaNoInicio(T dado) {
	this->ValidarListaParaInsercao();
	nUltElemento++;
	for (int i = nUltElemento; i > 0; --i) {
		dados[i] = dados[i - 1];
	}
	dados[POSZERO] = dado;
}

template<typename T>
void Lista<T>::adicionaNaPosicao(T dado, int posicao) {
	ValidarListaParaInsercao();
	ValidarPosicaoParaInsercao(posicao);

	if ((posicao == nUltElemento) || (nUltElemento == -1))
		return adiciona(dado);

	if (posicao == 0)
		return adicionaNoInicio(dado);

	nUltElemento++;
	for (int i = nUltElemento; i > posicao; i--) {
		dados[i] = dados[i - 1];
	}

	dados[posicao] = dado;
}

template<typename T>
void Lista<T>::adicionaEmOrdem(T dado) {
	if (listaVazia()){
		adiciona(dado);
		return;
	}

	for (int i = 0; i <= nUltElemento; ++i) {
		if (dado > dados[i]) {
			adicionaNaPosicao(dado, i);
			return;
		}
	}
	adiciona(dado);
}

template<typename T>
T Lista<T>::retira() {
	ValidarListaParaRetirada();

	T dadoRetiradoTemp = dados[nUltElemento];
	nUltElemento--;
	return dadoRetiradoTemp;
}

template<typename T>
T Lista<T>::retiraDoInicio() {
	ValidarListaParaRetirada();

	if (nUltElemento == 0)
		return retira();

	T retorno = dados[0];
	for (int i = 0; i < nUltElemento; i++)
		dados[i] = dados[i + 1];
	return retorno;
}

template<typename T>
T Lista<T>::retiraDaPosicao(int posicao) {
	if (listaVazia() || (posicao < 0))
		throw ERROPOSICAO;

	if (posicao > nMaxLista - 1)
		throw ERROPOSICAO;

	if ((posicao == 0) || (posicao == nMaxLista))
		return retira();

	T temp = dados[posicao];
	for (int i = posicao; i < nUltElemento; ++i) {
		dados[i] = dados[i + 1];
	}

	return temp;
}

template<typename T>
T Lista<T>::retiraEspecifico(T dado) {
	if (listaVazia())
		throw ERROLISTAVAZIA;

	int pos = posicao(dado);
	return retiraDaPosicao(pos);
}

template<typename T>
int Lista<T>::posicao(T dado) {
	if (listaVazia())
		throw ERROLISTAVAZIA;

	for (int i = 0; i <= nUltElemento; ++i) {
		if (dado == dados[i])
			return i;
	}
	throw ERROPOSICAO;
}

template<typename T>
bool Lista<T>::contem(T dado) {
	try {
		posicao(dado);
		return true;
	} catch (int e) {
		return false;
	}
}

template<typename T>
bool Lista<T>::igual(T dado1, T dado2) {
	return dado1 == dado2;
}

template<typename T>
bool Lista<T>::maior(T dado1, T dado2) {
	return (dado1 >= dado2);
}

template<typename T>
bool Lista<T>::menor(T dado1, T dado2) {
	return dado1 < dado2;
}

template<typename T>
bool Lista<T>::listaCheia() {
	return (nUltElemento == (nMaxLista - 1));
}
template<typename T>
bool Lista<T>::listaVazia() {
	return nUltElemento == -1;
}

template<typename T>
void Lista<T>::InicializaLista(int pnTam) {
	nUltElemento = -1;
	nMaxLista = pnTam;
	dados = new T[pnTam];
}

template<typename T>
void Lista<T>::ValidarListaParaRetirada() {
	if (listaVazia())
		throw ERROLISTAVAZIA;
}

template<typename T>
void Lista<T>::ValidarPosicaoParaInsercao(int pnPos) {
	if ((pnPos) < 0)
		throw ERROPOSICAO;

	if (pnPos >= nMaxLista)
		throw ERROPOSICAO;
}

template<typename T>
void Lista<T>::destroiLista() {
	nUltElemento = -1;
}

template<typename T>
void Lista<T>::ValidarListaParaInsercao() {
	if (listaCheia()) {
		throw ERROLISTACHEIA;
	}
}

#endif /* LISTA_HPP_ */
