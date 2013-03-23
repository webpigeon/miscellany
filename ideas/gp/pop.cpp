#define GENE_LENGTH 50
#define POP_SIZE 5000

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


class Indi2 {
	int data[GENE_LENGTH];

	public:
		void set(int n, int i) {
			data[n] = i;
		}

		int get(int n) {
			return data[n];
		}

		int score() {
			int score = 0;
			for (int i=0; i<GENE_LENGTH; i++) {
				score += data[i];
			}

			return abs(500 - score) * -1;
		}

		string print() {
			ostringstream os;

			for (int i=0; i<GENE_LENGTH; i++) {
				os << data[i];
				if (i != GENE_LENGTH-1) {
					os << ",";
				}
			}	
			os << " (" << score() << ")";
			return os.str();
		}
};

Indi2* generate() {
	Indi2* indi = new Indi2();

	for (int i=0; i<GENE_LENGTH; i++) {
		indi->set(i, rand() % 1000 );
	}

	return indi;
}

Indi2* copy(Indi2* indi) {
	Indi2* indi2 = new Indi2();
	for (int i=0; i<GENE_LENGTH; i++) {
		indi2->set(i, indi->get(i));
	}
	return indi2;
}

Indi2* crossover(Indi2* p1, Indi2* p2) {
	Indi2* c = new Indi2();
	int n = rand() % GENE_LENGTH;
	for (int i=0; i<n; i++){
		c->set(i, p1->get(i));
	}

	for (int i=n; i<GENE_LENGTH; i++) {
		c->set(i, p2->get(i));
	}
	return c;
}

Indi2* select(Indi2** population) {
	int p1 = rand() % POP_SIZE;
	int p2 = rand() % POP_SIZE;

	Indi2* can1 = population[ p1 ];
	Indi2* can2 = population[ p2 ];

	if ( can1->score() > can2->score() ) {
		return can1;
	} else {
		return can2;
	}

}

int main() {

	srand (time(NULL));

	Indi2** pop = new Indi2*[POP_SIZE];
	for (int i=0; i<POP_SIZE; i++) {
		pop[i] = generate();
	}
	
	for (int run=0; run<10000; run++) {
		cout << "Generation " << run << endl;

		int worst = 0;
		int best = 0;
		int worstScore = 0;
		int bestScore = 0;
		for (int i=0; i<POP_SIZE; i++) {
			int score = pop[i]->score();

			if (score > bestScore) {
				best = i;
				bestScore = score;
			}

			if (score < worstScore) {
				worst = i;
				worstScore = score;
			}
		}
		cout << "Best: " << pop[best]->print() << endl;
		cout << "worst: " << pop[worst]->print() << endl;


		Indi2** pop2 = new Indi2*[POP_SIZE];
		for (int i=0; i<POP_SIZE; i++) {
			int type = rand() % 10;
			if (type < 2) {
				Indi2* parent = select(pop);
				pop2[i] = copy(parent);
			} else if (type < 8) {
				Indi2* p1 = select(pop);
				Indi2* p2 = select(pop);
				pop2[i] = crossover(p1, p2);
			} else {
				pop2[i] = generate();
			}
		}

		delete pop;
		pop = pop2;
	}


	delete pop;

	return 0;	
}

