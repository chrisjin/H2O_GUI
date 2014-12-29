#ifndef H2O_PAINTER_H
#define H2O_PAINTER_H

#include"H2O_Delegate.h"
#include"H2O_Tile.h"
/*
    virtual void preaddTile(Tile* tile); //tile�ӽ��ڲ�vectorǰ����
    virtual void init();
    virtual void paint();      //�����ڲ����ݺ�����ػ�
    virtual void onCreate();
*/
namespace ColdWater
{
    class Tile;
    class Painter:public Object
    {

        vector<Tile*> m_Tiles;
    public:
        Tile* getnTile(int index){return m_Tiles[index];}
        int   getTileNum(){return m_Tiles.size();}

        void addTile(Tile* tile);
        void updateAllTile();
        void renderView();
        virtual void preaddTile(Tile* tile);
        virtual void init();
        virtual void paint();
        virtual void onCreate();

    };
}


#endif // H2O_PAINTER_H
