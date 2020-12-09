#include "node.h"
#include "iterator.h"
#include "null_iterator.h"

#include <string>
#include <iostream>
#include <list>

Node::Node(std::string id, std::string name, double size){
    _id = id;
    _name = name;
    _size = size;
}

std::string Node::id() const{
    return _id;
} 

std::string Node::name() const{
    return _name;
}

std::string Node::route() const{
    return _path+"/"+_name;
} // the "virtual" of this funtion is optional.

double Node::size() const{
    return _size;
}

void Node::updatePath(std::string path){
    _path = path;
}

void Node::addNode(Node* node){
    throw (std::string) "only folder can add node.";
}

void Node::addNodes(std::list<Node*> nodes){
    throw (std::string) "only folder can add nodes.";
}

Node* Node::getNodeById(std::string id) const{
    throw (std::string)"only folder can get node.";
}

void Node::deleteNodeById(std::string id){
    throw (std::string) "only folder can delete node.";
}

Iterator* Node::createIterator() const{
    return new NullIterator();
}