//
// LoadException.hpp for LoadException in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Exception
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 16:25:22 2016 Victor Gouet
// Last update Wed Mar  9 16:49:32 2016 Victor Gouet
//

#ifndef LOADEXCEPTION_HPP_
# define LOADEXCEPTION_HPP_

# include <stdexcept>

namespace arcade
{
  class LoadLibraryException : public std::runtime_error
  {
  public:
    LoadLibraryException(std::string const &file)
      : std::runtime_error("arcade: can not load " + file)
    {}

    virtual ~LoadLibraryException() throw()
    {}
  };

  class IncompleteLibraryException : public std::runtime_error
  {
  public:
    IncompleteLibraryException(std::string const &file)
      : std::runtime_error("arcade: no implemented function " + file)
    {}

    virtual ~IncompleteLibraryException() throw()
    {}
  };

  class InvalidFileFormatException : public std::invalid_argument
  {
  public:
    InvalidFileFormatException(std::string const &file)
      : std::invalid_argument("arcade: invalid file format for " + file)
    {}

    virtual ~InvalidFileFormatException() throw()
    {}
  };

};

#endif
