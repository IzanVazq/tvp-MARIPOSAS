#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include <fstream>

#include <limits>

#include "texture.h"

#include "rectangle.h"

#include "Bow.h"

#include <random>

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";
constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"bow.png", 1, 2},
	{"arrow.png"},
	{"balloons.png", 7, 6}
};

Game::Game()
	: randomGenerator(std::random_device{}()),
	  xSpawn(200, 700),
	  colorBalloon(0, 6),
	  velocityBalloon(75.0f, 250.0f),
	  exit(false)
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw "SDL_Init: "s + SDL_GetError();

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
	                                 WINDOW_WIDTH, WINDOW_HEIGHT,
	                                 0, &window, &renderer))
		throw "window or renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	try {
		textures.fill(nullptr);
		string imgRoot = IMAGE_ROOT;

		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols);
		}
	}
	catch (...) {
		// TODO: liberar la memoria reservada
		throw; // relanza la excepción
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// TODO: crear los objetos del juego
	
	//ARCO
	Rectangle bowRect(Point2D<>(0, 230.0f), 125.0f, 125.0f);
	Rectangle arrowRect(Point2D<>(0, 230.0f), 125.0f, 25.0f);
	bow = new Bow(getTexture(BOW), bowRect);

	loadLevel();
}

void 
Game::loadLevel()
{
	ifstream file(string(LEVEL_ROOT) + "1.txt");

	string key;

	while (file >> key) {

		if (key == "arrows") {
			int n;
			file >> n;
			bow->setArrowsLeft(n);
		}
		else if (key == "baldelay") {
			int t;
			file >> t;
			balloonInverval = t / 1000.0f;
		}
		else if (key == "balpoints") {
			int p;
			file >> p;
			balPuntos = p;
		}
		else {
			file.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	file.close();
}

Game::~Game()
{
	// TODO: liberar la memoria reservada por la clase
}

void
Game::render() const
{
	SDL_SetRenderDrawColor(renderer, 0, 140, 0, 255);
	SDL_RenderClear(renderer);
	// TODO
	bow->render(); //Renderiza arco
	for (int i = 0; i < arrows.size(); i++) arrows[i]->render();
	for (int i = 0; i < balloons.size(); i++) balloons[i]->render(); //Renderiza todos los globos

	//Renderiza el texto de los puntos
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	string puntuacion = "Puntos: " + to_string(puntos);
	SDL_RenderDebugText(renderer, 25, 25, puntuacion.c_str());

	//Renderiza el texto de las flechas restantes
	string flechas = "Flechas: " + to_string(bow->getArrowsLeft());
	SDL_RenderDebugText(renderer, 695, 25, flechas.c_str());

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	float delta = 1.0f / FRAME_RATE;
	// TODO
	timer += delta;
	//Crea globo cada _balloonInverval segundos
	if (timer > balloonInverval) { 
		timer = 0.0f;
		Rectangle ballonRectAux(Point2D<>(xSpawn(randomGenerator), 600.0f), 125.0f, 125.0f);
		balloon* balloonAux = new balloon(getTexture(BALLOONS), ballonRectAux, velocityBalloon(randomGenerator), colorBalloon(randomGenerator));
		balloons.push_back(balloonAux);
	}
	//Update de globos y los Destruye los globos y elimina su puntero al salir de la pantalla
	for (int i = 0; i < balloons.size(); i++) { 
		if (!balloons[i]->update(delta)) {
			delete balloons[i];
			balloons.erase(balloons.begin() + i);
		}
	}
	//
	for (int i = 0; i < arrows.size(); i++) {
		if (!arrows[i]->update(delta)) {
			delete arrows[i];
			arrows.erase(arrows.begin() + i);
		}
	}

	//Carga 
	bow->update(delta);
	if (bow->hasShot()) {
		Point2D<> bowPos = bow->getPos() + Point2D<>(0, 55); 
		Rectangle arrowRect1(bowPos, 125.0f, 25.0f);
		Arrow* arrowAux = new Arrow(getTexture(ARROW), arrowRect1, this);
		arrows.push_back(arrowAux);
	}

	if (bow->getArrowsLeft() == 0 && arrows.empty()) {
		delete bow;
		exit = true;
	}
}

void
Game::run()
{
	while (!exit) {
		// TODO: implementar bucle del juego
		Uint64 start = SDL_GetTicks();

		handleEvents();
		update();
		render();

		Uint64 elapsed = SDL_GetTicks() - start;

		if (elapsed < FRAME_PERIOD) {
			SDL_Delay(FRAME_PERIOD - elapsed);
		}
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		// TODO
		bow->handleEvent(event);
	}
}

bool //colisiones revisador
Game::checkCollision(const Rectangle& rect)
{
	for (int i = 0; i < balloons.size(); i++) {
		if (balloons[i]->hit(rect)) {
			puntos += balPuntos;
			return true;
		}
	}
	return false;
}
