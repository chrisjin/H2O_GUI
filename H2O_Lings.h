#ifndef H2O_LINGS_H
#define H2O_LINGS_H
#include"h2o_tile.h"
namespace ColdWater
{
	class Size2D :public Object
	{
	public:
		int Width;
		int Height;
		Size2D(){}
		Size2D(int a, int b) :Width(a), Height(b){}

	};
	class Point2D :public Object
	{
	public:
		int X;
		int Y;
		Point2D(){}
		Point2D(int a, int b) :X(a), Y(b){}

	};
	class Rect2D
	{
	public:
		Rect2D(){}
		Point2D Pos1;
		Point2D Pos2;
		Size2D  Size;
		Rect2D(const Point2D pos, const Size2D size)
		{
			Pos1 = pos;
			Size = size;
			Pos2.X = Pos1.X + Size.Width;
			Pos2.Y = Pos1.Y + Size.Height;
		}
		Rect2D(const Point2D pos1, const Point2D pos2)
		{
			Pos1 = pos1;
			Pos2 = pos2;
			Size.Width = Pos2.X - Pos1.X;
			Size.Height = Pos2.Y - Pos1.Y;
		}
		bool IsIn(const Point2D pos)
		{
			int x = pos.X;
			int y = pos.Y;
			if (x >= Pos1.X&&x < Pos2.X&&y >= Pos1.Y&&y < Pos2.Y)
				return true;
			else
				return false;
		}
		void setPos1(Point2D pos)
		{
			Pos1 = pos;
			Pos2.X = pos.X + Size.Width;
			Pos2.Y = pos.Y + Size.Height;
		}
		void setSize(Size2D size)
		{
			Size = size;
			Pos2.X = Pos1.X + Size.Width;
			Pos2.Y = Pos1.Y + Size.Height;
		}


	};


	template<typename T>
	class Buffer2D :public Object
	{
	public:
		T *Buffer;
		Size2D Size;
		Buffer2D(){ Buffer = 0; }
		int getWidth(){ return Size.Width; }
		int getHeight(){ return Size.Height; }
		void setBuffer(T *pbuff)
		{
			if (pbuff)
				Buffer = pbuff;
		}
		T *getBuffer()
		{
			return Buffer;
		}
		int getCellCount()
		{
			return Size.Width*Size.Height;
		}
		void Alloc(int width, int height)
		{
			Buffer = (T *)malloc(width*height*sizeof(T));
			Size.Width = width;
			Size.Height = height;
		}
		void ReAlloc(int width, int height)
		{
			if (Buffer)
			{
				free(Buffer);
				Buffer = 0;
			}
			Buffer = (T *)malloc(width*height*sizeof(T));
			Size.Width = width;
			Size.Height = height;
		}

		void Alloc(const Size2D size)
		{
			Buffer = (T *)malloc(size.Width*size.Height*sizeof(T));
			Size = size;
		}

		void ReAlloc(const Size2D size)
		{
			if (Buffer)
			{
				free(Buffer);
				Buffer = 0;
			}
			Buffer = (T *)malloc(size.Width*size.Height*sizeof(T));
			Size = size;
		}
		T *get(int x, int y)
		{
			if (x >= Size.Width || y >= Size.Height || x < 0 || y < 0)
				return 0;
			return  &(Buffer[y*Size.Width + x]);
		}
		T *get()
		{
			return Buffer;
		}
		void fill(const T ele)
		{
			T* pt = Buffer;
			for (int i = 0; i < getCellCount(); i++)
			{
				memcpy(pt, &ele, sizeof(T));
				pt += 1;
			}
		}
		void fillLine(const T ele,int index)
		{
			T* linebegin = this->get(0,index);
			for (int i = 0; i < getWidth(); i++)
			{
				*linebegin = ele;
				linebegin++;
			}

		}
		void fill(Buffer2D<T>& ele, const Rect2D region)
		{
			T* pt;
			T* pt1;
			for (int i = 0; i < region.Size.Width; i++)
				for (int j = 0; j < region.Size.Height; j++)
				{
				pt = get(i + region.Pos1.X, j + region.Pos1.Y);
				pt1 = ele.get(i, j);
				if (pt&&pt1)
					memcpy(pt, pt1, sizeof(T));

				}
		}
		void fill(const T ele, const Rect2D region)
		{
			T* pt;
			for (int i = region.Pos1.X; i < region.Size.Width; i++)
				for (int j = region.Pos1.Y; j < region.Size.Height; j++)
				{
				pt = get(i, j);
				if (pt)
					memcpy(pt, &ele, sizeof(T));

				}
		}
		void copy(Buffer2D& buff)
		{
			T* pt;
			T* pt1;
			for (int i = 0; i < Size.Width; i++)
				for (int j = 0; j < Size.Height; j++)
				{
				pt = get(i, j);
				pt1 = buff.get(i, j);
				if (pt&&pt1)
					memcpy(pt, pt1, sizeof(T));
				}
		}
		void destroy()
		{
			if (Buffer)
				free(Buffer);
			Buffer = 0;
		}
	};
	struct RGBPixel
	{
		union 
		{
			struct
			{
				unsigned char c1, c2, c3, c4;
			};
			int C;
		};
		operator int()
		{
			return C;
		}
		typedef unsigned char uchar;
		//  RGBPixel(uchar a1,uchar a2,uchar a3,uchar a4=0):c1(a1),c2(a2),c3(a3),c4(a4){}
		RGBPixel(uchar a1, uchar a2, uchar a3) :c1(a1), c2(a2), c3(a3){}

	};
	enum EVENT
	{
		EVT_LBUTTONDOWN,
		EVT_LBUTTONUP,
		EVT_RBUTTONDOWN,
		EVT_RBUTTONUP,
		EVT_MOUSEMOVE,
		EVT_MOUSEENTER,
		EVT_MOUSELEAVE,
		EVT_MOUSECROSS,
		EVT_MOUSEHOVER,
		EVT_TIMER,
		EVT_CREATE,
		EVT_LOSEFOCUS,
		EVT_GRABFOCUS,
		EVT_CHAR,
		EVT_KEYDOWN,
		EVT_KEYUP,
		EVT_IME_ENDCOMPOSITION,
		EVT_IME_CHAR,
		EVT_DESTROY
	};

	enum TIMERID
	{
		TMID_DRAGTILE,
		TMID_GIFPLAYER,
		TMID_TEXTEDIT

	};
}//namespace
#endif // H2O_LINGS_H
