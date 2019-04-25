#include <QCoreApplication>
#include <imghandler.hpp>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QString name="C:\\offlineMap\\offlineMap\\maps\\osm_100-l-3-8-455-202.png";
	ImgHandler *handler=new ImgHandler(name, 36.013812, 139.500248, 12, 4320, 540);
	handler->crop();
	handler->save();
	delete handler;
	return a.exec();
}
