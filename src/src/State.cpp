#include "State.h"

State::State() {
	popRequested = false;
	quitRequested = false;
	started = false;
}

State::~State()  {
	objectArray.clear();				// Esvazia o vetor de objetos
}

std::weak_ptr<GameObject> State::AddObject(GameObject* object)  {
	std::shared_ptr<GameObject> sharedGO(object);
	objectArray.push_back(sharedGO);
	if (started)
		object->Start();				// Chama Start do gameObject adicionado se started = true 

	return std::weak_ptr<GameObject>(sharedGO);		// Retorna o ponteiro para o gameObject recem adicionado
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object)  {
	for (auto& it : objectArray) {
		if (it.get() == object)
			return std::weak_ptr<GameObject>(it);		// Retorna o ponteiro para o gameObject se o encontra
	}

	return std::weak_ptr<GameObject>();		// Retorna um ponteiro vazio caso nao encontre o gameObject
}

bool State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::StartArray() {
	unsigned i;
	
	for (i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get())
			objectArray[i]->Start();			// Chama Start de cada gameObject no vetor caso seja encontrado
		else
			std::cout << " ERROR: null pointer to a GameObject in objectArray!" << std::endl;		// Mostra uma msg de erro caso nao haja objetos no vetor
	}

	started = true;
}

void State::UpdateArray(float dt) {
	for (unsigned i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);				// Chama Update de cada gameObjeto no vetor
	}
}

void State::RenderArray() {
	for (auto &gameObjects : objectArray) {
		gameObjects->Render();					// Chama Render de cada gameObject no vetor
	}
}

