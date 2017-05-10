#include <iostream>
#include <fstream>
#include <assert.h>
#include <random>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <time.h>
#include <math.h>
#include <list>
#include <algorithm>

using namespace std;

#define JSRand (double)rand()/RAND_MAX
#define num_angles 180
#define time_periods 12
#define pop_size 10
#define iterations 100


class Policy{
	public:
    int calc_fitness(list<int>);

    void generate_population();
    void binary_elim();
    void mutate(list<int>&);
    void run();
    void initialize_light();
    void print_light();
    void print_fitness();
    Policy();

    private:
    list<int> population[pop_size];
    int light_intensity [time_periods][num_angles];
};

Policy::Policy(){
	initialize_light();
	cout << "Light intensity grid" << endl;
	print_light();
	run();
}

void Policy :: initialize_light(){
	for (int i=0; i < time_periods; i++){
		int offset = i;
		
		for(int j = 0; j < num_angles; j++){
			light_intensity[i][j] = num_angles + offset - j;
			
		}
	}

	for(int i = 0; i < time_periods; i++){
		for(int j = 0; j < num_angles; j++){
			if(light_intensity[i][j] > num_angles){
				int difference = light_intensity[i][j] - num_angles;
				light_intensity[i][j] = num_angles - difference;
			}
		}
	}
}

int Policy :: calc_fitness(list<int> summation){
	int fitness = 0;
	list<int>::const_iterator iterator = summation.begin();
	for(int i=0; i < time_periods; i++){
		fitness += light_intensity[i][*iterator];
		++iterator;
	}

	return fitness;
}


// Generates lists of numbers ranging 0-num_angles index into light array
void Policy :: generate_population(){
	srand(time(NULL));
	for (int i=0; i < pop_size; i++){
		list<int> temp;
		for (int i=0; i< time_periods; i++){
			temp.push_back(rand()%num_angles);
		}
		population[i] = temp;
	}
    for(int i = 0; i < pop_size; i++){
        list<int> temp = population[i];
        list<int>::const_iterator index;
    }

}

void Policy::binary_elim(){
    random_shuffle(std::begin(population),std::end(population));
    for (int i=0; i < pop_size; i = i+2){
        double fitness_a = calc_fitness(population[i]);
        double fitness_b = calc_fitness(population[i+1]);
        if (fitness_a > fitness_b){
            population[i+1] = population [i];
            mutate(population[i+1]);
        }
        else {
            population[i] = population [i+1];
            mutate(population[i]);  
        }
    }
    random_shuffle(std::begin(population),std::end(population));
}



void Policy::mutate(list<int>& path){
    int path_a = 1 + rand()%time_periods;
    int path_b = 1 + rand()%time_periods;

    auto first = next(path.begin(), path_a);
    auto second = next(path.begin(), path_b);

    iter_swap(first, second);
}

void Policy :: print_light(){
	for(int i = 0; i < time_periods; i++){
		for(int j = 0; j < num_angles; j++){
			cout << light_intensity[i][j] << " ";
		}
		cout << endl;
	}
	cout << "  " << endl;
}

void Policy :: print_fitness(){
	cout << "Fitness values ";
	for(int i=0; i< pop_size;i++){
		cout << calc_fitness(population[i]) << " ";
	}
	cout<<endl;
}

void Policy :: run(){
	generate_population();
	for (int i = 0; i < iterations; i++){
		print_fitness();
		binary_elim();

	}
}


int main(){
	Policy my_policy;
	return 0;
}
