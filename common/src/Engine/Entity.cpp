/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Entity
 */

#include "Engine/Entity.hpp"

Engine::Entity::Entity(std::string name): _name(name)
{
    static std::size_t id = 1;

    _id = id++;
}
