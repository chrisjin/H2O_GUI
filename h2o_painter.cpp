#include "h2o_painter.h"
using namespace ColdWater;
void Painter::addTile(Tile* tile)
{
    preaddTile(tile);
    m_Tiles.push_back(tile);
    tile->setPainter(this);
}
void Painter::updateAllTile()
{
    for(int i=0;i<m_Tiles.size();i++)
    {
        m_Tiles[i]->handleAllChildrenChange();

    }
}
void Painter::renderView()
{
    updateAllTile();
    paint();

}
void Painter::preaddTile(Tile* tile){}
void Painter::init(){}
void Painter::paint(){}
void Painter::onCreate(){}
