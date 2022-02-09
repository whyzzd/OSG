#include "DrawXXX.h"
#include <osgFX/Scribe>
#include<iostream>
DrawXXX::DrawXXX()
{
	em=new osg::EllipsoidModel;
}
DrawXXX::DrawXXX(float wid) :mLineWidth(wid)
{
	em = new osg::EllipsoidModel;
}
DrawXXX::~DrawXXX()
{

}

osg::Node* DrawXXX::createLine(osg::ref_ptr<osg::Vec3Array> vec)
{
	osg::Geode* line_gnode = new osg::Geode;
	osg::ref_ptr<osg::Vec3Array>vectex = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array>color = new osg::Vec4Array;
	osg::ref_ptr<osg::Geometry>gemo = new osg::Geometry;
	
	//上一个点
	osg::Vec3d FirstPoint, SecondPoint;
	//第一个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(0).y()), osg::DegreesToRadians(vec->at(0).x()), vec->at(0).z(), FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	vectex->push_back(FirstPoint);
	//第二个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(1).y()), osg::DegreesToRadians(vec->at(1).x()), vec->at(1).z(), SecondPoint.x(), SecondPoint.y(), SecondPoint.z());
	vectex->push_back(SecondPoint);

	//红色
	//color->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	//画线
	gemo->setVertexArray(vectex);
	gemo->setColorArray(color);
	//此句影响绘制效率
	//gemo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);   
	gemo->setColorBinding(osg::Geometry::BIND_OVERALL);
	gemo->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, vectex->size()));
	//灯光
	gemo->getOrCreateStateSet()->setAttribute(new osg::LineWidth(mLineWidth), osg::StateAttribute::ON);
	gemo->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	line_gnode->addDrawable(gemo);

	return line_gnode;
}

osg::Node* DrawXXX::createTrinangle(osg::ref_ptr<osg::Vec3Array> vec)
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array>vectex = new osg::Vec3Array;
	//上一个点
	osg::Vec3d FirstPoint, SecondPoint, ThirdPoint, ForthPoint;
	//第一个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(0).y()), osg::DegreesToRadians(vec->at(0).x()), vec->at(0).z(), FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	vectex->push_back(FirstPoint);
	//第二个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(1).y()), osg::DegreesToRadians(vec->at(1).x()), vec->at(1).z(), SecondPoint.x(), SecondPoint.y(), SecondPoint.z());
	vectex->push_back(SecondPoint);
	//第三个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(2).y()), osg::DegreesToRadians(vec->at(2).x()), vec->at(2).z(), ThirdPoint.x(), ThirdPoint.y(), ThirdPoint.z());
	vectex->push_back(ThirdPoint);
	geom->setVertexArray(vectex);

	//定义颜色数组
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	//geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	//设置定点关联方式
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));
	//手动定义法线
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	//n->push_back(osg::Vec3(-2.f, -1.f, 10.f));
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));


	//灯光
	//geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::OFF);
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::Geode *geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode;
}
osg::Node* DrawXXX::createParallelogram(osg::ref_ptr<osg::Vec3Array> vec)
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array>vectex = new osg::Vec3Array;
	//上一个点
	osg::Vec3d FirstPoint, SecondPoint,ThirdPoint,ForthPoint;
	//第一个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(0).y()), osg::DegreesToRadians(vec->at(0).x()), vec->at(0).z(), FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	vectex->push_back(FirstPoint);
	//第二个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(1).y()), osg::DegreesToRadians(vec->at(1).x()), vec->at(1).z(), SecondPoint.x(), SecondPoint.y(), SecondPoint.z());
	vectex->push_back(SecondPoint);
	//第三个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(vec->at(2).y()), osg::DegreesToRadians(vec->at(2).x()), vec->at(2).z(), ThirdPoint.x(), ThirdPoint.y(), ThirdPoint.z());
	//ThirdPoint.x() = -ThirdPoint.x();
	//ThirdPoint.y() = -ThirdPoint.y();
	//ThirdPoint.z() = -ThirdPoint.z();
	vectex->push_back(ThirdPoint);
	//第四个点经纬高转世界坐标  单位度
	ForthPoint.x() =- SecondPoint.x() + FirstPoint.x() + ThirdPoint.x();
	ForthPoint.y() =- SecondPoint.y() + FirstPoint.y() + ThirdPoint.y();
	ForthPoint.z() =- SecondPoint.z() + FirstPoint.z() + ThirdPoint.z();
	vectex->push_back(ForthPoint);
	geom->setVertexArray(vectex);

	//定义颜色数组
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	//geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	/*c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));*/
	//设置定点关联方式
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	//geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 4));
	//方法一
	//手动定义法线
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	//n->push_back(osg::Vec3(-2.f, -1.f, 10.f));
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));
	//方法二
	//自动生成法线
	//osgUtil::SmoothingVisitor::smooth(*(geom.get()));//自动生成法线

	//灯光
	//geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::OFF);
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::Geode *geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode;
}

