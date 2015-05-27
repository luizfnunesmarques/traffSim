/* Copyright [2015] <Luiz Marques>
 * TestePilha.cpp
 */
#include "ListaEnc.hpp"
#include "Elemento.hpp"
#ifndef LISTACIRC_HPP_
#define LISTACIRC_HPP_
#define PILHAVAZIA -1
#define ERROPILHACHEIA -999
#define ERROPILHAVAZIA -998
#define ERROTAMPILHAINVALIDO -997

template<typename T>
class ListaCirc : public ListaEnc<T> {
 private:
  void adicionaElementoInicial(const T& dado) {
    Elemento<T> *novo = new Elemento<T>(dado, ListaEnc<T>::head);
    if (novo == NULL)
      throw ERROLISTACHEIA;
    this->head->setProximo(novo);
    novo->setProximo(this->head);
    this->size++;
  }

  void adicionaNaCauda(const T& dado) {
    Elemento<T> *cauda = this->head->getProximo();

    for (int i = 1; i < this->size; ++i) {
      cauda = cauda->getProximo();
    }

    Elemento<T> *novo = new Elemento<T>(dado, this->head);
    cauda->setProximo(novo);
    this->size++;
  }

  virtual Elemento<T>* pegarCabeca() {
    return this->head->getProximo();
  }
  ;

 protected:
  void inicializaCabecaLista() {
    this->head = new Elemento<T>((T) NULL, NULL);
  }

  void ZerarTamanhoLista() {
    this->size = 0;
  }

 public:
  ListaCirc<T>() {
    this->size = 0;
    inicializaCabecaLista();
  }

  virtual bool contem(const T& dado) {
    try {
      this->posicao(dado);
      return true;
    } catch (int e) {
      return false;
    }
    return false;
  }
  void destroiLista() {
    if ((this->head == NULL))
      return;

    Elemento<T> *next, *walkingdead;
    walkingdead = this->head;
    walkingdead = walkingdead->getProximo();
    for (int i = 0; i < this->size; ++i) {
      next = walkingdead->getProximo();
      delete (walkingdead);
      walkingdead = next;
    }
    this->ZerarTamanhoLista();
  }

  int posicao(const T& dado) {
    if (this->listaVazia())
      throw ERROLISTAVAZIA;

    int i = 0;
    Elemento<T> *walker = this->head;
    walker = walker->getProximo();
    while (i < this->size) {
      if (walker->getInfo() == dado)
        return i;
      walker = walker->getProximo();
      i++;
    }
    throw ERROPOSICAO;
  }
  ;

  virtual void adicionaNoInicio(const T& dado) {
    if (this->listaVazia()) {
      adicionaElementoInicial(dado);
      return;
    }
    Elemento<T> *novo = new Elemento<T>(dado, ListaEnc<T>::head);
    if (novo == NULL)
      throw ERROLISTACHEIA;
    Elemento<T> *temp = this->head->getProximo();
    this->head->setProximo(novo);
    novo->setProximo(temp);
    this->size++;
  }
  ;
  void adicionaNaPosicao(const T& dado, int pos) {
    if (pos < 0 || pos > this->size)
      throw ERROPOSICAO;

    if (this->listaVazia() || pos == 0) {
      adicionaElementoInicial(dado);
      return;
    }

    if (pos == this->size) {
      adicionaNaCauda(dado);
      return;
    }

    Elemento<T> *novo = new Elemento<T>(dado, NULL);
    Elemento<T> *anterior = this->head->getProximo();

    for (int i = 0; i < pos - 1; ++i) {
      novo->setProximo(anterior->getProximo());
      anterior->setProximo(novo);
    }
  }
  void adiciona(const T& dado) {
    if (this->size == 0) {
      this->adicionaNoInicio(dado);
      return;
    };
    this->adicionaNaCauda(dado);
  }

  T retira() {
    return this->retiraDaPosicao(this->size - 1);
  }

  virtual T retiraDaPosicao(int pos) {
    if (pos < 0)
      throw ERROPOSICAO;

    if (pos >= this->size)
      throw ERROPOSICAO;

    if (pos == 0)
      this->retiraDoInicio();

    Elemento<T> *anterior = this->head->getProximo();

    for (int i = 0; i < pos - 1; i++) {
      anterior = anterior->getProximo();
    }

    Elemento<T> *deletado = anterior->getProximo();
    anterior->setProximo(deletado->getProximo());
    T dadoRetornado = deletado->getInfo();

    delete deletado;
    this->size--;

    return dadoRetornado;
  }

  virtual T retiraDoInicio() {
    if (this->listaVazia())
      throw ERROLISTAVAZIA;

    Elemento<T> *deletado = this->head->getProximo();
    this->head->setProximo(deletado->getProximo());
    T dadoExcluido = deletado->getInfo();

    delete deletado;
    this->size--;
    return dadoExcluido;
  }

  T* posicaoMem(const T& dado) const {
      if (this->listaVazia()) {
          throw ERROLISTAVAZIA;
      }
      int posicao = posicao(dado);

      Elemento<T>* atual = this->head;
      for (int i = 0; i < posicao; i++) {
          atual = atual->getProximo();
      }
      return atual->getInfo();
  }
}
;
#endif
