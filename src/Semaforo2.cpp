#include <iostream>
#include "Sistema.cpp"
using namespace std;

int main() {
	int stop_interval;
	int simulation_time;
	cout << "Seja bem vindo a simulação de semáforos." << endl;
	cout << "Digite o tempo de intervalo dos semaforos e pressione enter:";
	cin >> stop_interval;
	cout << "Digite a duração da simulação e pressione enter: " << endl;
	cin >> simulation_time;

	cout << "Iniciando, aguarde;" << endl;
		cout << "------------------------------------" << endl;

	Sistema* system = new Sistema(stop_interval, simulation_time);
	system->StartSimulation();
	return 0;
}
