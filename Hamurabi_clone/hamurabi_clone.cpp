//Lets create Hamurabi clone in c++
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

class Hamurabi{
    int population;
    int land_price;
    int bushels;
    int acres;
    int year;
    int starved;
    int immigrants;
    const int bushel_requirement_per_person=20;
    int total_starved=0;
    std::mt19937 gen;

    public:

    Hamurabi(): gen(std::random_device{}()) {void update_land_price();}
    Hamurabi(int p, int b, int a, int y, int s, int i){
        cout<<"Welcome to Hamurabi!"<<endl;
        population=p;
        bushels=b;
        acres=a;
        year=y;
        starved=s;
        immigrants=i;
    }

    int get_population(){return population;}
    int get_bushels(){return bushels;}
    int get_acres(){return acres;}
    int get_year(){return year;}
    int get_starved(){return starved;}
    int get_immigrants(){return immigrants;}
    void set_population(int p){population=p;}
    void set_bushels(int b){bushels=b;}
    void set_acres(int a){acres=a;}
    void set_year(int y){year=y;}
    void set_starved(int s){starved=s;}
    void set_immigrants(int i){immigrants=i;}
    int get_price(){return land_price;}


    //logic to update land price ar random each year
    void update_land_price(){
        std::uniform_int_distribution<> dis(17, 26);
        int land_price = dis(gen);
        cout<<"The price of land this year is "<<land_price<<" bushels per acre."<<endl;
    }

    //logic to check for plague
    bool check_plague(){
        std::bernoulli_distribution plague_dist(0.15);
        if(plague_dist(gen)){
            population/=2;
            cout<<"A plague has struck! Your population has been halved!"<<endl;
            return true;
        }
        return false;
    }

    //logic to feed people
    bool feed_people(int bushels_to_feed){}

    //year increment logic
    void next_year(){}

    //logic for evaluation
    void evaluate(){}

    
    
    //logic of game_over
    bool gameover(){}

};
  
void Hamurabi::next_year(){
    year++;
}

bool Hamurabi::feed_people(int bushels_to_feed){
    if(bushels_to_feed>bushels){
        cout<<"Not enough bushels to feed people!"<<endl;
        return false;
    }
    int people_fed=bushels_to_feed/bushel_requirement_per_person;
    if(people_fed>=population){
        starved=0;
        population-=starved;    
    }
    else{
        starved=population-people_fed;
        population-=starved;
    }
    bushels-=bushels_to_feed;
    return true;
}

void Hamurabi::evaluate(){
 int average_starvation = total_starved / 10;
 int acres_per_person = acres / population;
 cout<<"Average Starvation: "<<average_starvation<<endl;
 cout<<"Acres per person: "<<acres_per_person<<endl;

}

bool Hamurabi::gameover(){
    if(population<=0){
        cout<<"Game Over! All your people have starved!"<<endl;
        return true;
    }
    if (acres<=0){
        cout<<"Game Over! You have no land left!"<<endl;
        return true;
    }
    if (bushels<=0){
        cout<<"Game Over! You have no bushels left!"<<endl;
        return true;
    }
    if (year==10){
        cout<<"Congratulations! You have successfully ruled for 10 years!"<<endl;
        return true;
    }
    if (starved>population/2){
        cout<<"Game Over! More than half of your population has starved! Your People are Revolting!"<<endl;
        return true;
    }

    return false;
}

int main() {
    Hamurabi game(100, 2800, 1000, 1, 0, 0);
    int y=game.get_year();
    int p=game.get_population();
    int b=game.get_bushels();
    int a=game.get_acres();
    int s=game.get_starved();
    int i=game.get_immigrants();

    cout<<"In year "<<y<<", population is "<<p<<", bushels is "<<b<<", acres is "<<a<<", starved is "<<s<<", immigrants is "<<i<<" ."<<endl;

    return 0;
}