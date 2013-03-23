#include <iostream>

using namespace std;

#define POPULATION_SIZE 10
#define GENOME_SIZE 5
#define MAX_GENERATIONS 5

void get_scores(int* scores, int population[POPULATION_SIZE][GENOME_SIZE], int (*fitFunc)(int*) ) {
	for (int n=0; n<POPULATION_SIZE; n++) {
		scores[n] = fitFunc(population[n]);
	}
}

int higher_is_better(int genome[]){
	int score = 0;

	for (int i=0; i<GENOME_SIZE; i++) {
		score += genome[i];
	}

	return score;
}


int main(int argc, char* argv[]){
	cout << "Genetic Algorthm Experiment" << endl;

	int population[POPULATION_SIZE][GENOME_SIZE];	

	for (int generation=0; generation < MAX_GENERATIONS; generation++) {
		// Get the scores for the current generation
		int scores[POPULATION_SIZE];
		get_scores(scores, population, higher_is_better);

		cout << "generation " << generation << " scores" << endl;
		for (int i=0; i<POPULATION_SIZE; i++) {
			cout << i << " [";
			for (int j=0; j<GENOME_SIZE; j++) {
				cout << population[i][j];
				if (j != GENOME_SIZE-1) {
					cout << ",";
				}
			}
			cout << "] " << scores[i] << endl;
		}

		// build the new population
		int population_new[POPULATION_SIZE][GENOME_SIZE];
		for (int i=0; i<POPULATION_SIZE; i++) {
			if ( rand() % 2 == 0) {
				population_new[i] = population[i];
				cout << "generating via copy" << endl;
			} else {
				population_new[i] = population[i];
				cout << "generating via xo" << endl;
			}
		}

		cout << endl;
	}

	return 0;
}
