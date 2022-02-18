#include"CPickHandler.h"
#include<iostream>

#include"OsgContainer.h"
#include"DrawXXX.h"
#include<osgEarthAnnotation/FeatureNode>
#include<osgEarth/Picker>
#include<osgEarth/IntersectionPicker>
#include<NodeUndoCommand.h>
CPickHandler::CPickHandler(osgViewer::Viewer *viewer) : mViewer(viewer)
{
	mMyConv.setViewer(viewer);
	m_oc = dynamic_cast<OsgContainer*>(mViewer);
	
	//connect(m_oc->m_undoAction, &QAction::triggered, this, &CPickHandler::slotMenuAction);
	
}
bool CPickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
	{
		
		int button = ea.getButton();
		if (button == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			//判断选择绘制类型
			if (mSelected==SelectedDraw::NONE)
			{
				pick(ea.getX(), ea.getY());
				if (m_oc->mViewerMode != OsgContainer::ViewerMode::STAND_ALONE)
				{
					m_oc->mOperaPacket._operaType = 0;
					m_oc->mOperaPacket._lonLatAltX = ea.getX();
					m_oc->mOperaPacket._lonLatAltY = ea.getY();

					m_oc->mOperaPacket._buttonState = 1;
					m_oc->mOperaPacket._isPressed = 1;
					
					_oldSceenX = ea.getX();
					_oldSceenY = ea.getY();

				}
			}
			else if (mSelected == SelectedDraw::DOT)
			{
				pick(ea.getX(), ea.getY());
				if(mIsPickObject)
				{ 
					drawDot(mLonLatAlt.x(), mLonLatAlt.y());

					if (m_oc->mViewerMode != OsgContainer::ViewerMode::STAND_ALONE)
					{
						m_oc->mOperaPacket._operaType = 1;
						m_oc->mOperaPacket._lonLatAltX = ea.getX();
						m_oc->mOperaPacket._lonLatAltY = ea.getY();
					}
					
				}
			}
			else if (mSelected==SelectedDraw::LINE)
			{ 
				
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{
					//oldDrawLine();

					if (mLineN >= 2)
					{
						mLineN = 1;
						mLineVec->push_back(mLonLatAlt);
						
						Geometry* geom = new osgEarth::Annotation::Polygon();
						for (int i = 0; i < mLineVec->size(); i++)
						{
							geom->push_back(mLineVec->at(i).x(), mLineVec->at(i).y());
						}
						mLineVec->clear();

						Style geomStyle;

						osgEarth::Annotation::Feature* feature = new osgEarth::Annotation::Feature(geom, m_oc->getMapNode()->getMapSRS());
						//feature->geoInterp() = GEOINTERP_RHUMB_LINE;

						geomStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::Lime;
						geomStyle.getOrCreate<LineSymbol>()->stroke()->width() = 7.0f;
						geomStyle.getOrCreate<LineSymbol>()->tessellationSize() = 75000;

						geomStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
						//geomStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

						osgEarth::Annotation::FeatureNode* gnode = new osgEarth::Annotation::FeatureNode(feature, geomStyle);

						osgEarth::Annotation::FeatureEditor* editor = new osgEarth::Annotation::FeatureEditor(gnode);

						m_oc->getMapNode()->addChild(editor);
						m_oc->getMapNode()->addChild(gnode);
						m_kv.insert(editor, gnode);
						m_oc->getUndoStack()->push(new AddNodeCommand(&m_oc, editor,gnode));
	
					}
					else
					{
						mLineVec->push_back(mLonLatAlt);
						mLineN++;
					}
				}
			}
			else if(mSelected == SelectedDraw::TRIANGLES)
			{
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{
					//oldDrawTriangles();


					if (mLineN>=3)
					{
						mLineN = 1;
						mLineVec->push_back(mLonLatAlt);

						Geometry* geom = new osgEarth::Annotation::Polygon();
						for (int i = 0; i < mLineVec->size(); i++)
						{
							geom->push_back(mLineVec->at(i).x(), mLineVec->at(i).y());
						}
						mLineVec->clear();

						Style geomStyle;
						osgEarth::Annotation::Feature* feature = new osgEarth::Annotation::Feature(geom, m_oc->getMapNode()->getMapSRS());
						//feature->geoInterp() = GEOINTERP_RHUMB_LINE;

						geomStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::Lime;
						geomStyle.getOrCreate<LineSymbol>()->stroke()->width() = 3.0f;
						geomStyle.getOrCreate<LineSymbol>()->tessellationSize() = 75000;
						geomStyle.getOrCreate<PolygonSymbol>()->fill()->color() = Color(Color::Red);
						geomStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
						//geomStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

						osgEarth::Annotation::FeatureNode* gnode = new osgEarth::Annotation::FeatureNode(feature, geomStyle);

						osgEarth::Annotation::FeatureEditor* editor = new osgEarth::Annotation::FeatureEditor(gnode);

						m_oc->getMapNode()->addChild(editor);
						m_oc->getMapNode()->addChild(gnode);
						m_kv.insert(editor, gnode);
						m_oc->getUndoStack()->push(new AddNodeCommand(&m_oc, editor, gnode));
				
					}
					else
					{
						mLineVec->push_back(mLonLatAlt);
						mLineN++;
					}
					
				}
			}
			else if (mSelected == SelectedDraw::PARALLELOGRAM)
			{
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{
					//oldDrawParallelogram();
					if (mLineN >= 4)
					{
						mLineN = 1;
						mLineVec->push_back(mLonLatAlt);

						Geometry* geom = new osgEarth::Annotation::Polygon();
						for (int i = 0; i < mLineVec->size(); i++)
						{
							geom->push_back(mLineVec->at(i).x(), mLineVec->at(i).y());
						}
						mLineVec->clear();

						Style geomStyle;
						osgEarth::Annotation::Feature* feature = new osgEarth::Annotation::Feature(geom, m_oc->getMapNode()->getMapSRS());
						//feature->geoInterp() = GEOINTERP_RHUMB_LINE;

						geomStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::Lime;
						geomStyle.getOrCreate<LineSymbol>()->stroke()->width() = 3.0f;
						geomStyle.getOrCreate<LineSymbol>()->tessellationSize() = 75000;
						geomStyle.getOrCreate<PolygonSymbol>()->fill()->color() = Color(Color::Red);
						geomStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
						//geomStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

						osgEarth::Annotation::FeatureNode* gnode = new osgEarth::Annotation::FeatureNode(feature, geomStyle);

						osgEarth::Annotation::FeatureEditor* editor = new osgEarth::Annotation::FeatureEditor(gnode);

						m_oc->getMapNode()->addChild(editor);
						m_oc->getMapNode()->addChild(gnode);
						m_kv.insert(editor, gnode);
						m_oc->getUndoStack()->push(new AddNodeCommand(&m_oc, editor, gnode));

					}
					else
					{
						mLineVec->push_back(mLonLatAlt);
						mLineN++;
					}
				}
			}
			else //无选择时
			{
				return false;
			}
			
		}
		else if (button == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
	
			reDrawXXX();
			pick(ea.getX(), ea.getY());

			//pick1(ea.getX(), ea.getY());
			
			
		}
		return false;
	}
	case osgGA::GUIEventAdapter::DRAG:
	{
		/*int button = ea.getButton();
		if (button == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{*/
			

			if (!((abs(_oldSceenX - ea.getX()) <= 1.0) && (abs(_oldSceenY - ea.getY()) <= 1.0)))
			{
				m_oc->mOperaPacket._buttonState = 2;
				m_oc->mOperaPacket._oldScreenX = _oldSceenX;
				m_oc->mOperaPacket._oldScreenY = _oldSceenY;

				m_oc->mOperaPacket._lonLatAltX = ea.getX();
				m_oc->mOperaPacket._lonLatAltY = ea.getY();

				_oldSceenX = ea.getX();
				_oldSceenY = ea.getY();
			}
			else
			{

				m_oc->mOperaPacket._buttonState = 0;
				m_oc->mOperaPacket._oldScreenX = ea.getX();
				m_oc->mOperaPacket._oldScreenY = ea.getY();
				m_oc->mOperaPacket._lonLatAltX = ea.getX();
				m_oc->mOperaPacket._lonLatAltY = ea.getY();
			}
		/*}*/
			
	}
	case osgGA::GUIEventAdapter::RELEASE:
	{
		int button = ea.getButton();
		if (button == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			m_oc->mOperaPacket._buttonState = 3;
			m_oc->mOperaPacket._isPressed = 0;
			m_oc->mOperaPacket._lonLatAltX = ea.getX();
			m_oc->mOperaPacket._lonLatAltY = ea.getY();
		}
		ispickededitor = false;
	}
	default:
		return false;
	}

}

void CPickHandler::pick(float x, float y)
{

	osgUtil::LineSegmentIntersector::Intersections intersections;

	if (mViewer->computeIntersections(x, y, intersections))
	{
		osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
		osg::NodePath getNodePath = hitr->nodePath;

		//std::cout<<hitr->matrix.valid();

		for (int i = getNodePath.size() - 1; i >=0; --i)
		{
			
			
			osgEarth::Annotation::FeatureEditor *mt = dynamic_cast<osgEarth::Annotation::FeatureEditor*>(getNodePath[i]);
			osg::MatrixTransform* mt1 = dynamic_cast<osg::MatrixTransform*>(getNodePath[i]);
			osgEarth::Annotation::FeatureNode *mt2= dynamic_cast<osgEarth::Annotation::FeatureNode*>(getNodePath[i]);
			if (mt1 != NULL || mt != NULL||mt2!=NULL)
			{
				mIsPickObject = true;
			}

			if (mt == NULL)
			{
				continue;
			}
			else
			{
				
				picked = mt;

				ispickededitor = true;
				//pickednode = mt2;
				//break;
			}
						
		}
						
		mWorld = hitr->getWorldIntersectPoint();
		
		//std::cout << "世界坐标:" << vec1.x() << " " << vec1.y() << " " << vec1.z() << std::endl;
		mLonLatAlt = mMyConv.WorldToLonLatAlt(mWorld);
		mLonLatAlt.z() = 900;
		//emit signShowLonLatAlt(mLonLatAlt);
		/*mLonLatAlt.x() = x;
		mLonLatAlt.y() = y;*/
		emit signShowLonLatAlt(mLonLatAlt);
		//std::cout << "经纬度:" << mLonLatAlt.x() << " " << mLonLatAlt.y() << " " << mLonLatAlt.z() << std::endl;
	}
	else
	{
		mIsPickObject = false;
	}
}

void CPickHandler::pick1(float x, float y)
{
	osgEarth::IntersectionPicker pick(m_oc, m_oc->getSceneData());
	osgEarth::IntersectionPicker::Hits hits;
	

	if (pick.pick(x, y, hits))
	{
		
		for (osgEarth::IntersectionPicker::Hits::iterator hit = hits.begin(); hit != hits.end(); ++hit)
		{
			//for (int i = hit->nodePath.size() - 1; i >= 0; --i)
			//{
			//	osgEarth::Annotation::FeatureNode *mt = dynamic_cast<osgEarth::Annotation::FeatureNode*>(hit->nodePath[i]);
			//	//osg::MatrixTransform* mt1 = dynamic_cast<osg::MatrixTransform*>(hit->nodePath[i]);
			//	if (mt == NULL)
			//	{
			//		continue;
			//	
			//	}
			//	else
			//	{
			//		//pickednode = mt;
			//		pickednode = mt;
			//		std::cout << "zzzzzzzzzz";
			//	}

			//}
			osgEarth::Annotation::FeatureNode* node = pick.getNode<osgEarth::Annotation::FeatureNode>(*hit);
			if (node == NULL)
			{
				continue;
					
			}
			else
			{
				//pickednode = mt;
				pickednode = node;
				std::cout << "zzzzzzzzzz";
			}
		}

	}
}
void CPickHandler::reDrawXXX()
{
	mIsPickObject = false;
	mLineN = 1;
	mTrinangleN = 1;
	mParallelogramN = 1;
	mLineVec->clear();
	mTrinangleVec->clear();
	mTrinangleVec->clear();
	emit signReDefault();
}
void CPickHandler::drawDot(float x, float y)
{
	//OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);
	const osgEarth::SpatialReference* mapSRS = m_oc->getMapNode()->getMapSRS();
	//osg::Group*geometryGroup = new osg::Group;
	osgEarth::Symbology::Style geomStyle;

	osg::ref_ptr<osgEarth::Symbology::Geometry> polygon = new osgEarth::Symbology::Polygon();
	polygon->push_back(osg::Vec3d(x,y, 0));

	osg::ref_ptr<osgEarth::Features::Feature> feature = new osgEarth::Features::Feature(polygon, mapSRS);
	osg::ref_ptr<osgEarth::Annotation::FeatureNode> featureNode = new osgEarth::Annotation::FeatureNode(feature/*, geomStyle*/);

	osgEarth::Annotation::FeatureEditor* editor = new osgEarth::Annotation::FeatureEditor(featureNode);
	m_oc->getMapNode()->addChild(editor);
	m_oc->getUndoStack()->push(new AddNodeCommand(&m_oc, editor));
}
void CPickHandler::oldDrawLine()
{
	if (mLineN >= 2)
	{
		mLineN = 1;
		//std::cout << typeid(*mViewer).name() << std::endl;//打印mViewer所指的实际类型
		//OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);

		mLineVec->push_back(mLonLatAlt);

		DrawXXX drawline(mDrawLineWid);


		m_oc->getMapNode()->addChild(drawline.createLine(mLineVec));
		//oc->getRoot()->addChild(drawline.createLine(mLineVec));
		mLineVec->clear();
		//oc->getEM()->setHomeViewpoint(osgEarth::Viewpoint("视点", (vvv[0].x()+vvv[1].x())/2, (vvv[0].y()+vvv[1].y())/2, 900, 0.0, -90, 7e3));
		//oc->getEM()->setViewpoint(osgEarth::Viewpoint("视点", (vvv[0].x() + vvv[1].x()) / 2, (vvv[0].y() + vvv[1].y()) / 2, 900, 0.0, -90, 7e3));
	}
	else
	{
		mLineVec->push_back(mLonLatAlt);
		mLineN++;
	}
}
void CPickHandler::oldDrawTriangles()
{
	if (mTrinangleN >= 3)
	{
		mTrinangleN = 1;
		//OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);

		mTrinangleVec->push_back(mLonLatAlt);

		DrawXXX drawTrinangle;
		m_oc->getMapNode()->addChild(drawTrinangle.createTrinangle(mTrinangleVec));
		//oc->getRoot()->addChild(drawTrinangle.createTrinangle(mTrinangleVec));
		mTrinangleVec->clear();

	}
	else
	{
		mTrinangleVec->push_back(mLonLatAlt);
		mTrinangleN++;
	}
}
void CPickHandler::oldDrawParallelogram()
{
	if (mParallelogramN >= 3)
	{
		mParallelogramN = 1;
		//OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);

		mParallelogramVec->push_back(mLonLatAlt);

		DrawXXX drawQuads;
		m_oc->getRoot()->addChild(drawQuads.createParallelogram(mParallelogramVec));

		mParallelogramVec->clear();

	}
	else
	{
		mParallelogramVec->push_back(mLonLatAlt);
		mParallelogramN++;
	}

}

void CPickHandler::slotGetDrawIndex(int n)
{
	mSelected = n;
}
void CPickHandler::slotDrawLineWid(float a)
{
	mDrawLineWid = a;
}
void CPickHandler::slotActionUndo(bool checked)
{
	m_oc->m_undoStack->undo();
}
void CPickHandler::slotActionRedo(bool checked )
{
	m_oc->m_undoStack->redo();
}
void CPickHandler::slotActionDel(bool checked )
{
	
	if (m_oc->getMapNode()->findMapNode(picked))
	{
		//picked->setNodeMask(0);
		m_oc->getMapNode()->removeChild(picked);
		m_oc->getUndoStack()->push(new DelNodeCommand(&m_oc, picked));

		m_oc->getMapNode()->removeChild(m_kv.value(picked));
		
		m_oc->getUndoStack()->push(new DelNodeCommand(&m_oc, picked, m_kv.value(picked)));
	}
	

}