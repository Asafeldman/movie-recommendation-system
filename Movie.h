
#ifndef INC_23B_C_C__EX5_MOVIE_H
#define INC_23B_C_C__EX5_MOVIE_H

#include <iostream>
#include <vector>
#include <memory>

#define HASH_START 17

class Movie;

typedef std::shared_ptr<Movie> sp_movie;

/**
 * those declartions and typedefs are given to you and should be used in the ex
 */
typedef std::size_t (*hash_func) (const sp_movie &movie);
typedef bool (*equal_func) (const sp_movie &m1, const sp_movie &m2);
std::size_t sp_movie_hash (const sp_movie &movie);
bool sp_movie_equal (const sp_movie &m1, const sp_movie &m2);

class Movie
{

 public:
  /**
   * Constructor.
   * @param name: Name of the movie.
   * @param year: Year the movie was made.
   */
  Movie (const std::string &name, int year);

  /**
   * Returns the name of the movie.
   * @return Const reference to the name of the movie.
   */
  const std::string &get_name () const { return _name; }

  /**
   * Returns the year the movie was made.
   * @return Year the movie was made.
   */
  int get_year () const { return _year; }

  /**
   * Less-than operator for comparing two movies.
   * @param rhs: Right-hand side movie.
   * @param lhs: Left-hand side movie.
   * @return Returns true if (lhs.year) < rhs.year or
   * (rhs.year == lhs.year & lhs.name < rhs.name), false otherwise.
   */
  friend bool operator< (const Movie &lhs, const Movie &rhs);

  /**
   * Output stream operator for printing a movie.
   * @param os: Output stream to write to.
   * @param movie: Movie to be printed.
   */
  friend std::ostream &operator<< (std::ostream &os, const Movie &movie);

 private:
  std::string _name;
  int _year;
};

#endif //INC_23B_C_C__EX5_MOVIE_H
