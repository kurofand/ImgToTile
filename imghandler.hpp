#ifndef IMGHANDLER_HPP
#define IMGHANDLER_HPP
#include <QImage>
#include <QList>

class ImgHandler
{
public:
	//need first of new images latlon from create names
	ImgHandler(QString &imgName, double startLat, double startLon, uint8_t zoomLvl, uint32_t size, uint32_t newSize);
	void crop();
	void save();
	~ImgHandler();
private:
	QImage *img;
	QList<QImage*> *resultList;
	//x at 0, y at 1
	QList<int> firstCoordinates;
	QList<QList<int>> tilesCoordinates;
	uint8_t z;
	uint32_t s, nS;
	double lat, lon;
};

#endif // IMGHANDLER_HPP
