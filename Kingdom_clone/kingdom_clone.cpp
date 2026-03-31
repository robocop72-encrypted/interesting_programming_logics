//Lets create kingdom clone in C++
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>
using namespace std;

class Kingdom{
    int population;
    int land_price;
    int bushels;
    int acres;
    int year;
    int starved;
    int immigrants;
    const int bushel_requirement_per_person=20;
    int total_starved=0;
    double tax_rate=10; 
    double loyalty=50;
    int justice_spending=200;
    int migration;
    std::mt19937 gen;


    public:

    Kingdom(int p, int b, int a, int y, int s, int i) 
    : population(p), bushels(b), acres(a), year(y), starved(s), immigrants(i), total_starved(0), tax_rate(10),
      gen(std::random_device{}()) 
{
    cout << "Welcome to Kingdom!" << endl;
    update_land_price();
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
    bool check_resources();

    //logic to update land price ar random each year
    void update_land_price(){
        std::uniform_int_distribution<> dis(17, 26);
        land_price = dis(gen);
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

    //logic to update loyalty based on tax rate and conditions
    void update_loyalty();

    //logic to calculate migration
    void calculate_migration();

    //logic to check for loyalty 
    void check_loyalty();

    //logic to calculate corruption
    void calculate_corruption();

    //logic to feed people
    bool feed_people(int bushels_to_feed);

    //year increment logic
    void next_year();

    //logic to plant crops
    void plant_crops();

    //logic to calculate harvest
    void calculate_harvest(int acres_planted);

    //logic to calculate rats
    void calculate_rats();

    //logic to calculate immigrants
    void calculate_immigrants();

    //logic to update population
    void update_population();

    //logic for evaluation
    void evaluate();

    //logic to buy land
    void buy_land(int acres_to_buy);

    //logic to sell land
    void sell_land(int acres_to_sell);
    
    //logic of game_over
    bool gameover();

};

void Kingdom::calculate_migration(){
    if(loyalty<40){
        int exit_rate=(40.0-loyalty)/100.0;
       migration= static_cast<int>(population*exit_rate);
        
    }
}

void Kingdom::update_loyalty(){
   double shift=0;
   if(tax_rate>15){shift-=5;}
    else if(tax_rate<5){shift+=5;}

    if(justice_spending>300){shift+=5;}
    else if(justice_spending<100){shift-=5;}

    if(starved>population/4){shift-=10;}
    else if(starved==0){shift+=5;}

    if (bushels>3000){shift+=2;}

    loyalty+=shift;
    loyalty=max(0.0, min(100.0, loyalty));
}

void Kingdom::check_loyalty(){
    if (loyalty<30){
        cout<<"Your people are unhappy with your rule! Consider lowering taxes or improving conditions!"<<endl;
    }
    else if (loyalty>70){
        cout<<"Your people are loyal and happy with your rule!"<<endl;
    }
    else if(loyalty<10){
        cout<<"Your people are revolting! Game Over!"<<endl;
        gameover();
        exit(0);
    }
}

void Kingdom::calculate_immigrants(){
    if (starved>0){
        immigrants=0;
        return;
    }
    int base = ((20*acres+bushels)/(100*population))+1;
    std::uniform_int_distribution<> var_dist(-2, 5);
    immigrants = max(0, base + var_dist(gen));
    cout << "A group of " << immigrants << " immigrants have arrived in the city!" << endl;
}

void Kingdom::update_population(){
    immigrants=0;
    population-=starved; 
    update_loyalty();
    calculate_migration();
   if(starved==0&&loyalty>40){
    calculate_immigrants();
    population+=immigrants;
   }
    check_plague();
    population = max(0, population);
}

bool Kingdom::check_resources(){
    cout<<"You have "<<population<<" people, "<<bushels<<" bushels, and "<<acres<<" acres of land."<<endl;
    cout<<"Confirm transaction? (y/n)"<<endl;
    char choice;
    cin>>choice;
    if(choice=='y' || choice=='Y'){
        return true;
    }
    return false;
}

void Kingdom::plant_crops(){
    cout<<"PLANTING SEASON!"<<endl;
    cout<<"You currently have "<<acres<<" acres of land."<<endl;
    int to_plant;
    cout<<"How many acres do you want to plant?"<<endl;
    cin>>to_plant;
    if(to_plant>acres){

        cout<<"You don't have enough land to plant!"<<endl;
        return; 
    }
    if(to_plant>(population*10)){
        cout<<"Not enough people to plant that much land!"<<endl;
        return;
    }
    int seed_cost=(to_plant+1)/2;
    if(seed_cost>bushels){
        cout<<"Not enough bushels to buy seeds!"<<endl;
        return;
    }
    bushels-=seed_cost;
    cout << "Used " << seed_cost << " bushels for seeds. Remaining: " << bushels << endl;

    calculate_harvest(to_plant);

}

void Kingdom::calculate_harvest(int acres_planted){
    std::uniform_int_distribution<> yield_dist(1, 5);
    int yield=yield_dist(gen);
    int harvest=yield*acres_planted;
    bushels+=harvest;
    cout<<"You harvested "<<harvest<<" bushels of grain! Total: " << bushels << endl;

    calculate_rats();

}

void Kingdom::calculate_rats(){
    std::bernoulli_distribution rat_dist(0.4);
    if(rat_dist(gen)){
        std::uniform_int_distribution<> rat_eat_dist(10, 30);
        int percent_eaten=rat_eat_dist(gen);
        int eaten=(percent_eaten*bushels)/100;
        bushels-=eaten;
        cout<<"Rats have eaten "<<eaten<<" bushels of grain! Total remaining: " << bushels << endl;
    }
}

void Kingdom::buy_land(int acres_to_buy){
    cout<<"You want to buy "<<acres_to_buy<<" acres of land."<<endl;
    cout<<"The price of land is "<<land_price<<" bushels per acre."<<endl;

    int cost = acres_to_buy*land_price;
    if(cost>bushels){
        cout<<"Not enough bushels to buy land!"<<endl;
        return;
    }
    if(!check_resources()){
        return;
    }
    acres+=acres_to_buy;
    bushels-=cost;
    cout << "Purchase successful. Total Bushels: " << bushels << endl;
}

void Kingdom::sell_land(int acres_to_sell){
    cout<<"You want to sell "<<acres_to_sell<<" acres of land."<<endl;
    cout<<"The price of land is "<<land_price<<" bushels per acre."<<endl;

    if(acres_to_sell>acres){
        cout<<"Not enough land to sell!"<<endl;
        return;
    }
    if(!check_resources()){
        return;
    }
    acres-=acres_to_sell;
    bushels+=(acres_to_sell*land_price);
    cout << "Sale successful. Total Bushels: " << bushels << endl;
}
  
void Kingdom::next_year(){
    year++;
}

bool Kingdom::feed_people(int bushels_to_feed){
    if(bushels_to_feed>bushels){
        cout<<"Not enough bushels to feed people!"<<endl;
        return false;
    }
    int people_fed=bushels_to_feed/bushel_requirement_per_person;
    if(people_fed>=population){
        starved=0;    
    }
    else{
        starved=population-people_fed;
    }
    bushels-=bushels_to_feed;
    total_starved+=starved;
    cout << "Feeding complete. Remaining Bushels: " << bushels << endl;
    return true;
}

void Kingdom::evaluate() {
    int active_years = (year > 1) ? (year - 1) : 1;
    double average_starvation = static_cast<double>(total_starved) / active_years;
    double acres_per_person = (population > 0) ? (static_cast<double>(acres) / population) : 0;

    cout << "\n--- FINAL EVALUATION ---" << endl;
    cout << "Average Starvation: " << fixed << setprecision(2) << average_starvation << " people/year" << endl;
    cout << "Acres per person: " << acres_per_person << endl;
}

bool Kingdom::gameover(){
    if(population<=0){
        cout<<"Game Over! All your people have starved!"<<endl;
        return true;
    }
    if (acres<=0){
        cout<<"Game Over! You have no land left!"<<endl;
        return true;
    }
    if (bushels<=0 && year > 1 && starved > 0){
        cout<<"Game Over! You have no bushels left and people are starving!"<<endl;
        return true;
    }
    if (year > 10){
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
    // Initial stats
    Kingdom game(100, 2800, 1000, 1, 0, 0);

    while (!game.gameover()) {
        cout << "\n" << setfill('=') << setw(40) << "" << endl;
        cout << "Year " << game.get_year() << " Report:" << endl;
        cout << "Population: " << game.get_population() << endl;
        cout << "Bushels in Store: " << game.get_bushels() << endl;
        cout << "Acres Owned: " << game.get_acres() << endl;
        cout << "Current Land Price: " << game.get_price() << " bushels/acre" << endl;
        cout << setfill('=') << setw(40) << "" << endl;

        // 1. Market Phase
        int choice;
        cout << "1. Buy Land | 2. Sell Land | 3. Skip Market: ";
        cin >> choice;

        if (choice == 1) {
            int to_buy;
            cout << "How many acres? "; cin >> to_buy;
            game.buy_land(to_buy);
        } else if (choice == 2) {
            int to_sell;
            cout << "How many acres? "; cin >> to_sell;
            game.sell_land(to_sell);
        }

        // 2. Feeding Phase
        int to_feed;
        cout << "How many bushels do you wish to feed the people? ";
        cin >> to_feed;
        while(!game.feed_people(to_feed)){
            cout << "Invalid amount. Try again: ";
            cin >> to_feed;
        }

        // 3. Planting Phase (This triggers harvest and rats automatically)
        game.plant_crops();

        // 4. Year-End Processing
        game.update_population(); // Starvation, Immigrants, Plague
        game.update_land_price();
        game.next_year();
    }

    // Final Score
    game.evaluate();

    return 0;
}