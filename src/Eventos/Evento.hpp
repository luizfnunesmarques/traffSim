//============================================================================
// Name        : Evento.hpp
// Author      : Luizf
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef EVENTO_HPP_
#define EVENTO_HPP_
using namespace std;


class Evento {
public:
	virtual ~Evento(){};
	Evento(int tempoExecucao) {
		nTempoExecucao = tempoExecucao;
	}


	int getTempoExecucao() {
		return nTempoExecucao;
	}

	virtual Evento* Executar()= 0;

protected:
	int nTempoExecucao;


};

#endif

