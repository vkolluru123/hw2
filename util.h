#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{

  // establish intersection set
  std::set<T> myIntersection;
  // create iterators for each set
  typename std::set<T>::iterator iteratorForSet1 = s1.begin();
  typename std::set<T>::iterator iteratorForSet2 = s2.begin();

  // iterate through both sets at once
  // making sure they're ordered using conditions
  while ((iteratorForSet1 != s1.end()) && (iteratorForSet2 != s2.end())) {
    
    if (*iteratorForSet1 < *iteratorForSet2) {
      // move iterator 1 forward so it comes before 2 cuz 1 is less
      iteratorForSet1++;
    }

    else if (*iteratorForSet2 < *iteratorForSet1) {
      // move iterator 2 forward so it comes before 1 cuz 2 is less
      iteratorForSet2++;
    }

    else if (*iteratorForSet1 == *iteratorForSet2) {
      // add one of them to result if they're same
      // move iterator 1 forward so it comes before 2 cuz 1 is less
      myIntersection.insert(*iteratorForSet2);
      iteratorForSet1++;
      iteratorForSet2++;
    }

  }
  
  // return intersection set
  return myIntersection;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

  // establish union set
  std::set<T> myUnion;
  
  // add both sets to it
  myUnion.insert(s1.begin(),s1.end());
  myUnion.insert(s2.begin(),s2.end());

  return myUnion;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
