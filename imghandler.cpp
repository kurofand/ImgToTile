#include "imghandler.hpp"
#include <math.h>
#include <QDebug>

ImgHandler::ImgHandler(QString &imgName, double startLat, double startLon, uint8_t zoomLvl, uint32_t size, uint32_t newSize)
{
	img=new QImage(imgName);
	resultList=new QList<QImage*>;
	z=zoomLvl;
	lat=startLat;
	lon=startLon;
	s=size;
	nS=newSize;
	auto tilex=(int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
	auto tiley=(int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z)));
	firstCoordinates={tilex, tiley};
	//tilesCoordinates.append(QList<int>({tilex, tiley}));
}

void ImgHandler::crop()
{
	uint16_t i=0, j=0;
	for(uint32_t x=0;x<s;x=x+nS)
	{
		j=0;
		for(uint32_t y=0;y<s;y=y+nS)
		{
			j++;
			resultList->append(new QImage(img->copy(x, y, nS, nS)));
			//tilesCoordinates.append(QList<int>({tilesCoordinates.at(0).at(0)+i, tilesCoordinates.at(0).at(1)+j}));
			qDebug()<<"Created from "<<x<<" to "<<x+nS<<"x, from "<<y<<" to "<<y+nS<<"y image";
		}
		i++;
	}
	for(int i=0;i<s/nS;i++)
		for(int j=0;j<s/nS;j++)
			tilesCoordinates.append(QList<int>({firstCoordinates.at(0)+i, firstCoordinates.at(1)+j}));
	qDebug()<<"Image crop complete!";
}

void ImgHandler::save()
{
	qDebug()<<"Start saving";
	for(unsigned int i=0;i<resultList->length();i++)
	{
		QString name="osm_100-l-3-"+QString::number(z)+"-"+QString::number(tilesCoordinates.at(i).at(0))+"-"+QString::number(tilesCoordinates.at(i).at(1))+".png";
		if(resultList->at(i)->save(name,"png"))
			qDebug()<<name<<" saved successfully";
		else
			qDebug()<<"An error occured on "<<name<<" saving!";
	}
	qDebug()<<"Saving complete!";
}

ImgHandler::~ImgHandler()
{
	for(QList<QImage*>::iterator it=resultList->begin();it!=resultList->end();it++)
		delete *it;
	delete resultList;
	delete img;
}
