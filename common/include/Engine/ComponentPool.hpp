/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ComponentPool
*/

#pragma once

#include "Miscellaneous/Variables.hpp"

#include <vector>
#include <cstddef>
#include <optional>
#include <algorithm>

namespace Engine {
    /**
     * @class ComponentPool
     *
     * @brief A template class that implements a component pool.
     */
    template <typename ComponentType>
    class ComponentPool {
        public:

            /**
             * @brief Add a component to the pool.
             *
             * @param id The id of the component.
             * @param component The component to add.
             */
            void Add(std::size_t id, ComponentType& component) {
                _denseArray.push_back(component);

                if (RType::PAGINATION_IDX(id) >= _sparseArray.size()) {
                    _sparseArray.resize(RType::PAGINATION_IDX(id) + 1);
                }
                if (_sparseArray[RType::PAGINATION_IDX(id)].size() < RType::PAGINATION_SIZE) {
                    _sparseArray[RType::PAGINATION_IDX(id)].resize(RType::PAGINATION_SIZE, std::nullopt);
                }
                _sparseArray[RType::PAGINATION_IDX(id)][RType::IDX_IN_PAGINATION(id)] = _denseArray.size() - 1;
            };

            /**
             * @brief Get a component from the pool.
             *
             * @param id The id of the component.
             * @return The component.
             */
            ComponentType *Get(std::size_t id) {
                if (RType::PAGINATION_IDX(id) >= _sparseArray.size()) {
                    return nullptr;
                }
                if (RType::IDX_IN_PAGINATION(id) >= _sparseArray[RType::PAGINATION_IDX(id)].size()) {
                    return nullptr;
                }

                std::optional<std::size_t> index =
                    _sparseArray[RType::PAGINATION_IDX(id)][RType::IDX_IN_PAGINATION(id)];
                if (!index.has_value()) {
                    return nullptr;
                }
                return &_denseArray[index.value()];
            }

            /**
             * @brief Delete a component from the pool.
             *
             * @param id The id of the component.
             */
            void Delete(std::size_t id) {
                std::optional<std::size_t> index = _sparseArray[RType::PAGINATION_IDX(id)][RType::IDX_IN_PAGINATION(id)];
                std::optional<std::pair<std::size_t, std::size_t>> backIndex = getIndexOfSparseArrayFromValue(_denseArray.size() - 1);

                if (!index.has_value() || !backIndex.has_value()) {
                    return;
                }

                std::swap(_denseArray[index.value()], _denseArray.back());

                _sparseArray[RType::PAGINATION_IDX(id)][RType::IDX_IN_PAGINATION(id)] = std::nullopt;
                _sparseArray[backIndex.value().first][backIndex.value().second] = index;

                _denseArray.pop_back();
            }

        private:
            /**
             * @brief Get the index of a sparse array from a value.
             *
             * @param value The value to get the index of.
             * @return The index of the sparse array.
             */
            std::optional<std::pair<std::size_t, std::size_t>> getIndexOfSparseArrayFromValue(std::size_t value) {
                std::size_t paginationIdx = 0;
                std::size_t inPaginationIdx = 0;

                for (const auto& pagination : _sparseArray) {
                    for (const auto& tabValue : pagination) {
                        if (tabValue == value) {
                            return std::make_pair(paginationIdx, inPaginationIdx);
                        }
                        inPaginationIdx++;
                    }
                    paginationIdx++;
                }
                return std::nullopt;
            }

            std::vector<std::vector<std::optional<std::size_t>>> _sparseArray; /*!> The sparse array. */
            std::vector<ComponentType> _denseArray; /*!> The dense array. */
    };
}
