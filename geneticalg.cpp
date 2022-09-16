#include <cstdint>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>     
#include <malloc.h>
#include <string.h>

int pop=50;
char gen[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', ' '};
int tgen = 27;
int siz;//= 19;
char* target;// = "senjougahara hitagi";
int gener=0;
int aleat;

struct Population{
    char** chr;
    int* score;
};

class Genetic{
    public:
        char chromo(){
            char chr = char(gen[rand()%tgen]);
            return chr;
        }
        char* multation(char* chr){
            for(int i=0;i<siz;i++){
                //if(rand()%20==0)
                if(rand()%aleat==0)
                chr[i] = char(gen[rand()%tgen]);
            }
            return chr;
        }
        int score(char** chr, Population* population){
            char* best = (char*)malloc(sizeof(char)*siz);
            int* scores = (int*) malloc(sizeof(int)*pop);
            int8_t scorem;
            int8_t scoreb;
            for(int i=0;i<pop;i++){
                scorem=0;
                for(int j=0;j<siz;j++){
                    if(chr[i][j]==target[j]){
                        scorem++;
                    }
                }
                //scores[i] = scorem;
                population->score[i]=scorem;
                //std::cout << scores[i] << std::endl;
                if(scorem>scoreb){ 
                    scoreb = scorem;
                    for(int k=0;k<siz;k++) best[k] = chr[i][k];
                }
            }
            //population->score = scores;
            std::cout << "Melhor prole: " << best << std::endl;
            //std::cout << best << std::endl;
            free(scores);
            free(best);
            if(scoreb==siz){
                std::cout << "PEGA PORRA" << std::endl;
                std::exit;
            }
            return scoreb;
        }
        void ord(Population* population)
        {
            std::cout << "****************TABELA ORDENADA!************************" << std::endl;
            for(int i=0; i<pop; i++){
                for(int j=0;j<pop-i;j++){
                    if(population->score[j]>population->score[j+1]){ 
                        int tempi = 0;                        //char* tempc = (char*)malloc(sizeof(char)*siz);
                        tempi=population->score[j+1];
                        char* tempc = (char*)malloc(sizeof(char)*siz);
                        tempc=population->chr[j+1];
                        population->score[j+1]=population->score[j];
                        population->chr[j+1]=population->chr[j];
                        population->chr[j]=tempc;
                        population->score[j]=tempi;
                        //free(tempc);
                    }
                }
           }
           tab(population);
        }
        void kill(Population* population)
        {
            int kil = int(pop/10);
            for(int i=0; i<kil; i++)
            {
                for(int j=0;j<siz;j++){
                    population->chr[i][j]= ' ';
                }
                population->score[i]=0;
            }
        }
        void cruz(Population* population)
        {
            int str = int(9*pop/10);
            int rnd = rand()%(pop-str);
            for(int i=0;i<int(pop/10);i++){
                int ind1, ind2;
                ind1=rnd+str;
                int rnd1 = rand()%(pop-str);
                ind2 = rnd1+str;
                int k=0, l=0;
                for(int j=0;j<siz;j++){
                    int rnd3=rand()%2;
                    if(k<=siz/2 && l<=siz/2){
                        if(rnd3==0){
                        population->chr[i][j]=population->chr[ind1][j];
                        k++;
                        }
                        else{
                        population->chr[i][j]=population->chr[ind2][j];
                        l++;    
                        }
                    }
                    else if(k>siz/2){
                        population->chr[i][j]=population->chr[ind2][j];
                        l++;  
                    }
                    else{
                        population->chr[i][j]=population->chr[ind1][j];
                        k++;
                    }
                }
            }
        }
        void tab(Population* population)
        {
            std::cout << "****************TABELA!************************" << std::endl;
            for(int i=0;i<pop;i++){
                std::cout << population->chr[i] << ": " << population->score[i] << "." << std::endl;
            }
        }
};
int main(){
    std::string sla;
    std::cout << "Bem vindo ao meu programa basico de algoritmo genetico. Preencha as variaveis:" << std::endl;
    std::cout << "String alvo:" << std::endl;
    target = (char*)malloc(sizeof(char)*20);
    std::cin >> target;
    siz=strlen(target);
    /*std::cout << "Tamanho da populacao:" << std::endl;
    std::cin >> pop;*/
    std::cout << "Aleatoriedade da mutacao:" << std::endl;
    std::cin >> aleat;
    srand (time(NULL));
    Population *population = (Population*)malloc(sizeof(Population));
    population->score = (int*) malloc(sizeof(int)*pop);
    population->chr = (char**)malloc(sizeof(char*)*pop);
    Genetic *genetic  = (Genetic*)malloc(sizeof(Genetic));
    /*while(true){*/
    for(int i=0; i<pop; i++){
        population->chr[i] = (char*)malloc(sizeof(char)*siz);
        for(int j=0; j<siz; j++){
        population->chr[i][j] = genetic->chromo();
        //std::cout << population->chr[i][j];
        }
        //std::cout << std::endl;
    }
    std::cout << genetic->score(population->chr, population) << std::endl;
    while(genetic->score(population->chr,population)!=siz){
        genetic->tab(population);
        genetic->ord(population);
        genetic->kill(population);
        genetic->cruz(population);
        for(int i=0;i<pop;i++){
            population->chr[i] = genetic->multation(population->chr[i]);
        }
        std::cout << genetic->score(population->chr, population) << std::endl;
        gener++;
    }
    std::cout << "gen:" << gener << std::endl;
    //}
}