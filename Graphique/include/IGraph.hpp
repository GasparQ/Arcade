//
// IGraph.hpp for IGraph in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/include
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 11:05:46 2016 Victor Gouet
// Last update Wed Mar  9 15:18:03 2016 Victor Gouet
//

#ifndef IGRAPH_HPP_
# define IGRAPH_HPP_

# include <stack>
#include "../../Commons/include/AComponent.hpp"

class	IGraph
{
public:
    virtual ~IGraph(){};
    virtual int eventManagment() = 0;
    virtual void display(std::stack<AComponent *>) = 0;
    virtual void setTitle(const std::string &title) = 0;
};

#endif
