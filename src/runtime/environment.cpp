#include "lum/runtime/environment.hpp"
#include "lum/runtime/value.hpp"
#include "lum/error/error.hpp"
#include <utility>
namespace lum{

    Environment::Environment(){
        this->values = {};
        this->enclosing = nullptr;
    }

    Environment::Environment(std::shared_ptr<Environment> enclosing){
        this->values = {};
        this->enclosing = enclosing;
    }

    void Environment::define(const std::string& name, Value value){
        this->values.insert_or_assign(name, std::move(value)); // insert or overwrite if exists
    }

    Value Environment::get(const Token& token) const{
        auto it = this->values.find(token.lexeme);
        if(it != this->values.end()){
            return it->second;
        }else if(this->enclosing != nullptr){
            return this->enclosing->get(token);
        }
        lum::Error::throw_and_return("undefined variable: " + token.lexeme, token.line, token.column);
    }

    void Environment::assign(const Token& token, Value value){
        auto it = this->values.find(token.lexeme);
        if(it != this->values.end()){
            it->second = std::move(value);
        }else if(this->enclosing != nullptr){
            this->enclosing->assign(token, std::move(value));
        }else{
            lum::Error::throw_and_return("can't assign " + token.lexeme, token.line, token.column);
        }
    }

}
