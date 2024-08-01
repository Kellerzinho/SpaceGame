#include "Game.h"

Game::Game() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // WINDOW
    window = std::make_shared<sf::RenderWindow>();
    window->create(sf::VideoMode(1280, 720), "Space Game", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(0, 0));
    window->setFramerateLimit(60);

    //SONS
    music.openFromFile("assets/Music.wav");
    music.setVolume(10.f);


    fire_sound.loadFromFile("assets/Fire.wav");
    explosion_sound.loadFromFile("assets/Explosion.wav");
    gameover_sound.loadFromFile("assets/Gameover.wav");
    fire.setBuffer(fire_sound);
    fire.setVolume(10.f);
    exp.setBuffer(explosion_sound);
    exp.setVolume(30.f);
    gameoverSound.setBuffer(gameover_sound);
    gameoverSound.setVolume(30.f);

    // SHIP
    ship_texture = std::make_shared<sf::Texture>();
    ship_texture->loadFromFile("assets/Ship.png");
    ship = std::make_shared<sf::Sprite>(*ship_texture);
    ship->setPosition(0, window->getSize().y / 2 - ship->getGlobalBounds().height / 2);

    // ENEMY
    enemy_texture = std::make_shared<sf::Texture>();
    enemy_texture->loadFromFile("assets/Enemy.png");
    enemy = std::make_shared<sf::Sprite>(*enemy_texture);
    enemies_spawn = 1;
    max_enemies = 100;

    // CHARGE
    charge_texture = std::make_shared<sf::Texture>();
    charge_texture->loadFromFile("assets/Charge.png");
    charge = std::make_shared<sf::Sprite>(*charge_texture);
    shoot = 20;
    max_shoot = 50;
    charge_speed = 1.5f;

    // FUNDO
    background_texture = std::make_shared<sf::Texture>();
    background_texture->loadFromFile("assets/Background.png");
    background = std::make_shared<sf::Sprite>(*background_texture);

    // LIFE
    life_texture = std::make_shared<sf::Texture>();
    life_texture->loadFromFile("assets/Life.png");
    life = std::make_shared<sf::Sprite>(*life_texture);
    life->setPosition(window->getSize().x - life_texture->getSize().x - 10.f, 10.f);
    start = 0;
    life->setTextureRect(sf::IntRect(0, start, 300, 30));

    // FONTE
    font = std::make_shared<sf::Font>();
    font->loadFromFile("assets/Font.ttf");

    //Texto de Game Over
    text = std::make_shared<sf::Text>();
    text->setFont(*font);
    text->setString("GAME OVER");
    text->setCharacterSize(100);
    text->setFillColor(sf::Color::White);
    text->setPosition((window->getSize().x / 2) - text->getGlobalBounds().width / 2, window->getSize().y / 2 - text->getGlobalBounds().height / 2 - 100);

    //Texto de Score
    score = std::make_shared<sf::Text>();
    score->setFont(*font);
    score->setString("Score: 0");
    score->setFillColor(sf::Color::White);
    score->setPosition(10.f, 10.f);
    points = 0;

    //Texto de Score no Game Over
    score_over = std::make_shared<sf::Text>();
    score_over->setFont(*font);
    score_over->setFillColor(sf::Color::White);
    score_over->setCharacterSize(50);

    //Texto do titulo
    title = std::make_shared<sf::Text>();
    title->setFont(*font);
    title->setString("Space Game");
    title->setCharacterSize(100);
    title->setFillColor(sf::Color::White);
    title->setPosition((window->getSize().x / 2) - title->getGlobalBounds().width / 2, (window->getSize().y / 2) - title->getGlobalBounds().height / 2 - 100);

    //Texto auxiliar
    aux_text = std::make_shared<sf::Text>();
    aux_text->setFont(*font);
    aux_text->setString("Press Enter to start");
    aux_text->setCharacterSize(50);
    aux_text->setFillColor(sf::Color::White);
    aux_text->setPosition((window->getSize().x / 2) - aux_text->getGlobalBounds().width / 2, (window->getSize().y / 2) - aux_text->getGlobalBounds().height / 2 + 100);

    //Texto de restart
    restart_text = std::make_shared<sf::Text>();
    restart_text->setFont(*font);
    restart_text->setString("Press Enter to restart");
    restart_text->setCharacterSize(50);
    restart_text->setFillColor(sf::Color::White);
    restart_text->setPosition((window->getSize().x / 2) - restart_text->getGlobalBounds().width / 2, (window->getSize().y / 2) - restart_text->getGlobalBounds().height / 2 + 200);

    //Pagina Inicial
    start_page = true;

    // ANIMACAO

    //Animacao de explosao
    explosion_texture = std::make_shared<sf::Texture>();
    explosion_texture->loadFromFile("assets/Explosion.png");
    explosion = std::make_shared<sf::Sprite>(*explosion_texture);
    explosion->setTextureRect(sf::IntRect(0, 0, 44, 64));
    frame = 0.f;
    anim_speed = 0.1f;
    count = 19;
    max = 0;
    show = true;

    //Animacao de ataque
    attack_texture = std::make_shared<sf::Texture>();
    attack_texture->loadFromFile("assets/Attack.png");
    attack = std::make_shared<sf::Sprite>(*attack_texture);
    attack->setTextureRect(sf::IntRect(0, 0, 98, 70));
    attacking = false;
    attack_frame = 0.f;
    attack_speed = 0.1f;
    attack_count = 4;
    attack_max = 0;

    //Animacao de destruicao
    destroyed_texture = std::make_shared<sf::Texture>();
    destroyed_texture->loadFromFile("assets/Destroyed.png");
    destroyed = std::make_shared<sf::Sprite>(*destroyed_texture);
    destroyed->setTextureRect(sf::IntRect(0, 0, 192, 192));
    destroyed->setScale(2.f, 2.f);
    destroyed->setPosition(window->getSize().x / 2 - destroyed->getGlobalBounds().width / 2, window->getSize().y / 2 - destroyed->getGlobalBounds().height / 2);
    destroyed_frame = 0.f;
    destroyed_speed = 0.09f;
    destroyed_count = 15;
    destroyed_max = 0;
    death = false;


    // GAME OVER
    game_over = false;

}

//FUNCOES

void Game::code_game() {

    // MOVIMENTO DA NAVE
    if (!attacking) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            ship->move(10.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            ship->move(0.f, -10.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            ship->move(-10.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            ship->move(0.f, 10.f);

        // VERIFICACAO DE COLISAO COM A JANELA
        if (ship->getPosition().x < 0) {
            ship->setPosition(0, ship->getPosition().y);
        }

        if (ship->getPosition().x > window->getSize().x - ship->getGlobalBounds().width) {
            ship->setPosition(window->getSize().x - ship->getGlobalBounds().width, ship->getPosition().y);
        }

        if (ship->getPosition().y < 50) {
            ship->setPosition(ship->getPosition().x, 50);
        }

        if (ship->getPosition().y > window->getSize().y - ship->getGlobalBounds().height) {
            ship->setPosition(ship->getPosition().x, window->getSize().y - ship->getGlobalBounds().height);
        }
    }

    // MOVIMENTO DO CHARGE
    if (shoot < max_shoot) shoot++;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && shoot >= max_shoot) {
        fire.play();
        shoot = 0;
        attacking = true;
        attack_max = 0;
        attack->setPosition(ship->getPosition().x, ship->getPosition().y);
    }

    // Mover CHARGES
    std::vector<int> charges_to_remove;
    for (size_t i = 0; i < charges.size(); ++i) {
        charges[i].move(charge_speed, 0.f);

        if (charges[i].getPosition().x > window->getSize().x) {
            charges_to_remove.push_back(i);
        }

        for (int k = 0; k < enemies.size(); ++k) {
            if (charges[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds())) {
                
                //Score
                points += 10;
                score->setString("Score: " + std::to_string(points));
                explosion->setPosition(charges[i].getPosition().x, charges[i].getPosition().y);
                exp.play();
                show = false;
                max = 0;
                attack_speed += 0.01f;
                if (max_enemies > 5) max_enemies -= 1.;
                if (max_shoot > 10) max_shoot -= 0.4f;
                if (charge_speed < 35) charge_speed += 0.4f;

                charges_to_remove.push_back(i);
                enemies.erase(enemies.begin() + k);
                break;
            }
           
        }
    }

    // Remover CHARGE
    for (int i = charges_to_remove.size() - 1; i >= 0; --i) {
        charges.erase(charges.begin() + charges_to_remove[i]);
    }

    // ENEMY SPAWN
    if (enemies_spawn < max_enemies) enemies_spawn++;

    if (enemies_spawn >= max_enemies) {
        sf::Sprite enemy(*enemy_texture);
        enemy.setPosition(window->getSize().x - enemy.getGlobalBounds().width, static_cast<float>(50 + (static_cast<int>(ship->getGlobalBounds().height) / 2) - (static_cast<int>(enemy.getGlobalBounds().height) / 2) + std::rand() % (window->getSize().y - 50 - (static_cast<int>(ship->getGlobalBounds().height) / 2) - (static_cast<int>(enemy.getGlobalBounds().height) / 2))));
        enemies.push_back(enemy);
        enemies_spawn = 0;
    }

    std::vector<int> enemies_to_remove;
    for (int i = 0; i < enemies.size(); ++i) {
        enemies[i].move(-5.f, 0.f);

        if (enemies[i].getPosition().x < 0) {
            enemies_to_remove.push_back(i);
        }

        // Colisao com ENEMY
        if (ship->getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
            start += 30;
            life->setTextureRect(sf::IntRect(0, start, 300, 30));
            if (start >= 90) {
                game_over = true;
                death = true;
                gameoverSound.play();
                destroyed_frame = 0.f;
            }
            enemies_to_remove.push_back(i);
        }
    }

    // Remove ENEMY
    for (int i = enemies_to_remove.size() - 1; i >= 0; --i) {
        enemies.erase(enemies.begin() + enemies_to_remove[i]);
    }

    window->clear();
    window->draw(*background);
    window->draw(*score);

    if (!show) {
        window->draw(*explosion);
    }

    if (start < 90) window->draw(*life);

    for (int i = 0; i < charges.size(); ++i) {
        window->draw(charges[i]);
    }

    window->draw(*ship);

    if (attacking) {
        window->draw(*attack);
    }

    for (int i = 0; i < enemies.size(); ++i) {
        window->draw(enemies[i]);
    }

    window->display();

}

void Game::game_over_func() {
    if (music.getStatus() == sf::Music::Playing) {
        music.stop();
    }

    window->clear();
    window->draw(*background); 

    if (death) {
        window->draw(*destroyed);
    }

    if (!death) {
        if (music.getStatus() != sf::Music::Playing) music.play();
        window->draw(*text);
        score_over->setString("Score: " + std::to_string(points));
        score_over->setPosition((window->getSize().x / 2) - score_over->getGlobalBounds().width / 2, (window->getSize().y / 2) - score_over->getGlobalBounds().height / 2 + 50);
        window->draw(*score_over);
        window->draw(*restart_text);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
		game_over = false;
        death = false;
        destroyed_frame = 0.f;
		points = 0;
		score->setString("Score: 0");
		start = 0;
		life->setTextureRect(sf::IntRect(0, start, 300, 30));
		ship->setPosition(0, window->getSize().y / 2 - ship->getGlobalBounds().height / 2);
		enemies.clear();
		charges.clear();
		max_enemies = 100;
		max_shoot = 50;
		charge_speed = 1.5f;
		attack_speed = 0.1f;

	}

    window->display();
}

void Game::loop_events() {
    sf::Event event;

    if (music.getStatus() != sf::Music::Playing) music.play();

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
    }

    // ANIMACAO

    // Animacao de explosao
    if (!show) {
        frame += anim_speed;
        if (frame > count) {
            frame = 0.f;
            show = true;
        }
        explosion->setTextureRect(sf::IntRect(44 * static_cast<size_t>(frame), 0, 44, 64));
    }

    // Animacao de ataque
    if (attacking) {
        attack_frame += attack_speed;
        if (attack_frame > attack_count) {
            attack_frame = 0.f;
            attacking = false;

            charge->setPosition(ship->getPosition().x + ship->getGlobalBounds().width / 1.5, ship->getPosition().y + ship->getGlobalBounds().height / 2 - charge->getGlobalBounds().height / 2);
            charges.push_back(*charge);
        }
        attack->setTextureRect(sf::IntRect(98 * static_cast<size_t>(attack_frame), 0, 98, 70));
    }

    // Animacao de destruicao
    if (death && game_over) {
        destroyed_frame += destroyed_speed;
        if (destroyed_frame > destroyed_count) {
            destroyed_frame = destroyed_count;
            death = false;
        }
        destroyed->setTextureRect(sf::IntRect(192 * static_cast<size_t>(destroyed_frame), 0, 192, 192));
    }
}

void Game::inicial_page() {
    window->clear();
    window->draw(*background);
    window->draw(*title);
    window->draw(*aux_text);
    window->display();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) start_page = false;
}

void Game::run_game() {
    while (window->isOpen()) {
        this->loop_events();

        if(start_page) {
			this->inicial_page();
		}

        else{

            if(game_over){
                this->game_over_func();
            }

            else {
			this->code_game();           
            }
        }
        
    }
}

