/* Copyright [2014] <Luiz Marques>
 * TestePilha.cpp
 */

#ifndef FILAENC_HPP_
#define FILAENC_HPP_
#include "ListaEnc.hpp"
#define PILHAVAZIA -1
#define ERROPILHACHEIA -999
#define ERROPILHAVAZIA -998
#define ERROTAMPILHAINVALIDO -997

template<typename T>
class FilaEnc: private ListaEnc<T> {
public:
	FilaEnc<T>() {
	}
	~FilaEnc() {
		ListaEnc<T>::destroiLista();
	}
	void inclui(const T& dado){
		ListaEnc<T>::adiciona(dado);
	}
	T retira(){
		return ListaEnc<T>::retiraDoInicio();
	}
	T ultimo(){
		return ListaEnc<T>::pegaCaudaLista();
	}
	T primeiro(){
		if (ListaEnc<T>::listaVazia())
			throw ERROLISTAVAZIA;

		return ListaEnc<T>::pegaCabecaLista();
	}
	bool filaVazia(){
		return ListaEnc<T>::listaVazia();
	}
	void limparFila(){
		ListaEnc<T>::destroiLista();
	}
};
#endif
