//
//  main.cpp
//  yaml-test
//
//  Created by steve on 7/15/11.
//  Copyright 2011 Rieman Consulting. All rights reserved.
//

#include "yaml-cpp/yaml.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "boost/multi_array.hpp"

void STLContainers(YAML::Emitter& out);
void BoostContainers(YAML::Emitter& out);
void GetStlContainer();

int main (int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";

    //YAML::Emitter out;

    std::ofstream ofstr("test2.yaml");
    YAML::Emitter out;

    STLContainers(out);
    
    //std::cout << "Here's the output YAML:\n" << out.c_str();

    ofstr << out.c_str() << std::endl;

    GetStlContainer();
    
    return 0;
}

void GetStlContainer()
{
    std::vector< std::vector<int> > v(10,10);
    
    // Set up sizes. (HEIGHT x WIDTH)
    v.resize(10);
    for (int i = 0; i < 10; ++i)
    {
        v[i].resize(10);
    }

    std::ifstream fin("test.yaml");
    YAML::Parser parser(fin);
    
    YAML::Node doc;
    //while(parser.GetNextDocument(doc))
    parser.GetNextDocument(doc);
    {
        doc["fred"] >> v;
    }
    std::string a;
    
    doc["val1"] >> a;
//    doc[0] >> a;
    std::cout << a << std::endl;
    
    std::cout << v[3][1] << std::endl;
    
}

void STLContainers(YAML::Emitter& out)
{
    std::vector< std::vector<int> > v(10,10);

    // Set up sizes. (HEIGHT x WIDTH)
    v.resize(10);
    for (int i = 0; i < 10; ++i)
    {
        v[i].resize(10);
    }
    
    std::vector< std::vector<int> >::iterator row_it = v.begin();
    std::vector< std::vector<int> >::iterator row_end = v.end();

#if 0    
    for ( int i = 0; i < 10; ++i)
    {
        v.push_back(std::vector<int>());
        
        for ( int j = 0; j < 10; ++j)
        {
            v[i].push_back(i + j);
        }
    }
#endif
    
#if 1
    for (int count = 0 ; row_it != row_end; ++row_it )
    {
        std::vector<int>::iterator col_it = row_it->begin();
        std::vector<int>::iterator col_end = row_it->end();
        
        for ( ; col_it != col_end; ++col_it )
        {
            *col_it = count++;
        }
    }
#endif
    std::vector<int> primes;
    primes.push_back(2);
    primes.push_back(3);
    primes.push_back(5);
    primes.push_back(7);
    primes.push_back(11);
    primes.push_back(13);

    out << YAML::BeginSeq;
    //out << YAML::Flow << primes;
    out << YAML::Flow << v;
    out << YAML::EndSeq;
}

void BoostContainers(YAML::Emitter& out)
{
    // Create a 3D array that is 3 x 4 x 2
    typedef boost::multi_array<double, 3> array_type;
    typedef array_type::index index;
    array_type A(boost::extents[3][4][2]);
    
    // Assign values to the elements
    int values = 0;
    for(index i = 0; i != 3; ++i) 
        for(index j = 0; j != 4; ++j)
            for(index k = 0; k != 2; ++k)
                A[i][j][k] = values++;
    
    // Verify values
    int verify = 0;
    for(index i = 0; i != 3; ++i) 
        for(index j = 0; j != 4; ++j)
            for(index k = 0; k != 2; ++k)
                assert(A[i][j][k] == verify++);

    out << YAML::BeginSeq;
    //out << YAML::Flow << A;
    out << YAML::EndSeq;
}
