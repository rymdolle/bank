#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "account.hpp"

class User {

private:
    std::string name_;
    std::string password_;
    int id_;
public:
    inline static std::vector<User> userVec;

    User(std::string name, std::string password, int id) {
        name_ = name;
        password_ = password;
        id_ = id;

    }


    std::string toString() const{
        return "Name: " + name_ + "\nPin: " + getPassword() + "\nID: " + std::to_string(id_) + "\n";
    }

    bool verify(std::string& name, std::string& password) const {
        return name == name_ && password_ == password;
    }


    // Getters

    const std::string &getName() const {
        return name_;
    }

    const std::string &getPassword() const {
        return password_;
    }

    int getId() const {
        return id_;
    }

};


#endif /* USER_H */
