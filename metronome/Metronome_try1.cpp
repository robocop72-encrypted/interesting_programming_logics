#include <iostream>
#include<chrono>
#include<thread>
#include<functional>
#include<atomic>
#include<SFML/Audio.hpp>
using namespace std::chrono;
using namespace std::chrono_literals;

std::atomic<bool> running(true);

sf::SoundBuffer highBuffer, lowBuffer;


void initSound() {
    if (!highBuffer.loadFromFile("tick_high.wav") ||  // relative path
        !lowBuffer.loadFromFile("tick_low.wav")) {
        std::cout << "Error loading sound files!\n";
        exit(1);
    }
}

void playTick(bool downbeat) {
    static std::vector<sf::Sound> sounds;
    static size_t index = 0;

    if (sounds.empty()) {
        for (int i = 0; i < 16; i++) {
            sounds.emplace_back(highBuffer); // temp buffer
        }
    }

    sf::Sound& sound = sounds[index];
    index = (index + 1) % sounds.size();

    sound.setBuffer(downbeat ? highBuffer : lowBuffer);
    sound.play();
}


void metronome(milliseconds interval ,  std::function<void(int)>callback){
    auto start =  steady_clock::now();
    int i =0;
    while(running){
        std::this_thread::sleep_until(start+(i+1)*interval);
        if(!running) break;
        callback(i+1);
        i++;
    }
}
int main() {
    initSound();
    std::cout<<"Enter how many beats per minute do you want?\n";
    int bpm;
    std::cin>>bpm;
    auto interval = std::chrono::milliseconds(
    static_cast<int>(60000.0 / bpm)
);
    int beatsPerBar=4;
    std::thread metronomeThread([&](){
    metronome(interval, [beatsPerBar](int beat) {
    if (beat % beatsPerBar == 1) {
        std::cout << "TICK\n" << std::flush;  // downbeat
    } else {
        std::cout << "tick\n" << std::flush;  // normal beat
    }
    playTick(beat % beatsPerBar == 1);
});
});

std::cout<<"Press 'q' to stop the metronome...\n";
    char input;
    
    while(true){
        std::cin>>input;
        if(input=='q'||input=='Q'){
            running = false;
            break;
        }
        }
    
    metronomeThread.join();
    std::cout<<"Metronome stopped.\n";
    return 0;
}