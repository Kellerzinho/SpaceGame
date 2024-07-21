#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <memory>
#include <ctime>
#include <cstdlib>

class Game {

public:

    Game();

    // WINDOW   
    std::shared_ptr<sf::RenderWindow> window;

    //SONS
    sf::Music music;
    sf::SoundBuffer fire_sound, explosion_sound, gameover_sound;
    sf::Sound fire, exp, gameoverSound;

    // SHIP
    std::shared_ptr<sf::Texture> ship_texture;
    std::shared_ptr<sf::Sprite> ship;


    // ENEMY
    std::shared_ptr<sf::Texture> enemy_texture;
    std::shared_ptr<sf::Sprite> enemy;
    std::vector<sf::Sprite> enemies;
    int enemies_spawn;
    float max_enemies;

    // CHARGE
    std::shared_ptr<sf::Texture> charge_texture;
    std::shared_ptr<sf::Sprite> charge;
    std::vector<sf::Sprite> charges;
    std::vector<int> charges_to_remove;
    int shoot;
    float max_shoot, charge_speed;

    // FUNDO
    std::shared_ptr<sf::Texture> background_texture;
    std::shared_ptr<sf::Sprite> background;

    // LIFE
    std::shared_ptr<sf::Texture> life_texture;
    std::shared_ptr<sf::Sprite> life;
    int start;

    // FONTE E TEXTOS
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<sf::Text> text;
    std::shared_ptr<sf::Text> score;
    std::shared_ptr<sf::Text> score_over;
    std::shared_ptr<sf::Text> title;
    std::shared_ptr<sf::Text> aux_text;
    std::shared_ptr<sf::Text> restart_text;

    int points;

    // ANIMACAO

    //Animacao de explosao
    std::shared_ptr<sf::Texture> explosion_texture;
    std::shared_ptr<sf::Sprite> explosion;
    float frame, anim_speed;
    float count, max;
    bool show;

    //Animacao de ataque
    std::shared_ptr<sf::Texture> attack_texture;
    std::shared_ptr<sf::Sprite> attack;
    bool attacking;
    float attack_frame, attack_speed;
    float attack_count, attack_max;

    //Animacao de destruicao
    std::shared_ptr<sf::Texture> destroyed_texture;
    std::shared_ptr<sf::Sprite> destroyed;
    float destroyed_frame, destroyed_speed;
    float destroyed_count, destroyed_max;
    bool death;

    // GAME OVER
    bool game_over;

    //Pagina Inicial
    bool start_page;



    //FUNCOES

    void code_game();
    void game_over_func();
    void loop_events();
    void run_game();
    void inicial_page();

};

