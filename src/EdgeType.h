#ifndef _EDGETYPE_H
#define _EDGETYPE_H

/*
 * Yes i know it's pointless to specially sign integer values
 * SEE:
 * #define UNDIRECTED 0
 * #define DIRECTED 1
 * */
enum class EdgeType{
    twoWay = 0, oneWay = 1
};

#endif //_EDGETYPE_H
