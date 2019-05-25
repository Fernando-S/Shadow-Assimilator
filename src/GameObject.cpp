#include "GameObject.h"

GameObject::GameObject() {
	this->isDead = false;
	this->box.x = 0;
	this->box.y = 0;
	this->box.w = 0;
	this->box.h = 0;
	this->angleDeg = 0;
	this->started = false;
}

GameObject::~GameObject() {
	// Reset nos elementos do vetor de components
	for (auto it = this->components.rbegin(); it != this->components.rend(); it++) {
		it->reset();					// Reset em cada component
	}
	this->components.clear();			// Clear nos components
}

void GameObject::Update(float dt) {
	for (auto &component : this->components) {
		component->Update(dt);			// Update em cada component
	}
}

void GameObject::Render() {
	for (auto &component : this->components) {
		component->Render();			// Renderiza cada component
	}
}

bool GameObject::IsDead() {
	return isDead;
}

void GameObject::RequestDelete() {
	isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
	this->components.emplace_back(cpt);

	if (started)
		cpt->Start();				// Chama Start dos components adicionados se stared = true
}

void GameObject::RemoveComponent(Component* cpt) {
	unsigned i;
	std::shared_ptr<Component>& component = *(new std::shared_ptr<Component>(cpt));

	for (i = 0; i < this->components.size(); i++) {						// Percorre o vetor de components ate achar o desejado
		if (this->components[i] == component)							// Verifica se o component atual eh o desejado
			this->components.erase(this->components.begin() + i);		// Remove o component desejado
	}
}


Component* GameObject::GetComponent(std::string type) {
	for (auto it = this->components.begin(); it != this->components.end(); it++) {
		if ( (*it)->Is(type) )
			return (*it).get();				// Retorna o component do tipo desejado caso exista
	}
	return nullptr;							// Retorna um ponteiro nulo caso nao exista
}


void GameObject::Start() {
	for (auto &component : components) {
		component->Start();					// Chama Start() de cada component
	}

	started = true;							// started se torna true
}


void GameObject::NotifyCollision(GameObject& other) {
	for (auto &component : components) {
		component->NotifyCollision(other);
	}
}