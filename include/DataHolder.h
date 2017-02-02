/**
 *  @autor tekatod
 *  @date 1/30/17
 */
#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "mapbox/variant.hpp"

namespace DM {
    template<class... Classes>
    class DataHolder {
    public:
        typedef mapbox::util::variant<std::shared_ptr<Classes>...> Field;

        DataHolder() = default;

        template<typename T>
        void set(const std::string &name, T &&data) {
            dictionary.insert({name, Field(std::make_shared<T>(data))});
        }

        template<typename T>
        void set(const std::string &name, T &data) {
            dictionary.insert({name, Field(std::make_shared<T>(data))});
        }

        Field getField(const std::string &name) {
            return dictionary[name];
        }

        template<class T>
        std::shared_ptr<T> getPointer(const std::string& name) {
            return dictionary[name].template get<std::shared_ptr<T>>();
        }

        template<class T>
        T getData(const std::string& name) {
            return *getPointer<T>(name);
        }

        virtual void update() = 0;

    private:
        std::unordered_map<std::string, Field> dictionary;
    };
}

