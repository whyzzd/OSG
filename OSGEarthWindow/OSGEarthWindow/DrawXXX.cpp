#include "DrawXXX.h"
#include <osgFX/Scribe>

DrawXXX::DrawXXX()
{
	em=new osg::EllipsoidModel;;
}
DrawXXX::~DrawXXX()
{

}

osg::Node* DrawXXX::createLine(osg::Vec3d start, osg::Vec3d end)
{
	osg::Geode* line_gnode = new osg::Geode;
	osg::ref_ptr<osg::Vec3Array>vectex = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array>color = new osg::Vec4Array;
	osg::ref_ptr<osg::Geometry>gemo = new osg::Geometry;

	//上一个点
	osg::Vec3d FirstPoint, SecondPoint;
	//第一个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(start.y()), osg::DegreesToRadians(start.x()), start.z(), FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	vectex->push_back(FirstPoint);
	//第二个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(end.y()), osg::DegreesToRadians(end.x()), end.z(), SecondPoint.x(), SecondPoint.y(), SecondPoint.z());
	vectex->push_back(SecondPoint);

	//红色
	color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	//画线
	gemo->setVertexArray(vectex);
	gemo->setColorArray(color);
	//此句影响绘制效率
	//gemo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);   
	gemo->setColorBinding(osg::Geometry::BIND_OVERALL);
	gemo->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, vectex->size()));
	//灯光
	gemo->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::ON);
	gemo->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	line_gnode->addDrawable(gemo);

	return line_gnode;
}