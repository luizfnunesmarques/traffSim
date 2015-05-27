//============================================================================
// Name        : Semaforo2.cpp
// Author      : Luizf - Rafael
// Version     :
// Copyright   : 2015 GNU
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Sistema.hpp"
using namespace std;

int main() {
	int interacao1;
	int interacao2;
	cout << "Seja bem vindo a simulação de semáforos." << endl;
	cout << "Digite o tempo de intervalo dos semaforos e pressione enter:";
	cin >> interacao1;
	cout << "Digite a duração da simulação e pressione enter: " << endl;
	cin >> interacao2;

	cout << "Iniciando, aguarde;" << endl;
		cout << "------------------------------------" << endl;

	Sistema* sis = new Sistema(interacao1, interacao2);
	sis->iniciarSimulacao();
	return 0;
}
