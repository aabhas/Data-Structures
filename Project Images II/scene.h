#ifndef scene_H
#define scene_H
#include "scene.h"
#include "image.h"
#include "png.h"
#include "rgbapixel.h"

class Scene{
	public:
	Image** arr;
	int* xi;
	int* yi;
	
	int max;
	Scene(int max);
	~Scene();
	Scene(const Scene &source);
	const Scene & 	operator= (const Scene &source);
	void changemaxlayers(int newmax);
	void addpicture(const char *FileName, int index, int x, int y);
	void changelayer (int index, int newindex);
	void translate (int index, int xcoord, int ycoord);
	void deletepicture (int index);
	Image *getpicture (int index) const;
	Image drawscene () const;
	
	private:
	void clear();
	void copy(const Scene &other);
	};
#endif
