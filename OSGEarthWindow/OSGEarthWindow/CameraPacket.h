#pragma once
#include <osgViewer/Viewer>
#include <osg/io_utils>
#include "CameraPacket.h"
const unsigned int SWAP_BYTES_COMPARE = 0x12345678;
class CameraPacket {
public:


	CameraPacket() :_masterKilled(false)
	{
		_byte_order = SWAP_BYTES_COMPARE;
	}

	void setPacket(const osg::Matrix& matrix, const osg::FrameStamp* frameStamp)
	{
		_matrix = matrix;
		if (frameStamp)
		{
			_frameStamp = *frameStamp;
		}
	}

	void getModelView(osg::Matrix& matrix, float angle_offset = 0.0f)
	{

		matrix = _matrix * osg::Matrix::rotate(osg::DegreesToRadians(angle_offset), 0.0f, 1.0f, 0.0f);
	}

	void readEventQueue(osgViewer::Viewer& viewer);

	void writeEventQueue(osgViewer::Viewer& viewer);

	void setMasterKilled(const bool flag) { _masterKilled = flag; }
	bool getMasterKilled() const { return _masterKilled; }

	unsigned int    _byte_order;
	bool            _masterKilled;
	osg::Matrix     _matrix;

	// note don't use a ref_ptr as used elsewhere for FrameStamp
	// since we don't want to copy the pointer - but the memory.
	// FrameStamp doesn't have a private destructor to allow
	// us to do this, even though its a reference counted object.
	osg::FrameStamp  _frameStamp;

	osgGA::EventQueue::Events _events;

};

class DataConverter
{
public:

	DataConverter(unsigned int numBytes) :
		_startPtr(0),
		_endPtr(0),
		_swapBytes(false),
		_currentPtr(0)
	{
		_currentPtr = _startPtr = new char[numBytes];
		_endPtr = _startPtr + numBytes;
		_numBytes = numBytes;
	}

	char* _startPtr;
	char* _endPtr;
	unsigned int _numBytes;
	bool _swapBytes;

	char* _currentPtr;

	void reset()
	{
		_currentPtr = _startPtr;
	}

	inline void write1(char* ptr)
	{
		if (_currentPtr + 1 >= _endPtr) return;

		*(_currentPtr++) = *(ptr);
	}

	inline void read1(char* ptr)
	{
		if (_currentPtr + 1 >= _endPtr) return;

		*(ptr) = *(_currentPtr++);
	}

	inline void write2(char* ptr)
	{
		if (_currentPtr + 2 >= _endPtr) return;

		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr);
	}

	inline void read2(char* ptr)
	{
		if (_currentPtr + 2 >= _endPtr) return;

		if (_swapBytes)
		{
			*(ptr + 1) = *(_currentPtr++);
			*(ptr) = *(_currentPtr++);
		}
		else
		{
			*(ptr++) = *(_currentPtr++);
			*(ptr) = *(_currentPtr++);
		}
	}

	inline void write4(char* ptr)
	{
		if (_currentPtr + 4 >= _endPtr) return;

		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr);
	}

	inline void read4(char* ptr)
	{
		if (_currentPtr + 4 >= _endPtr) return;

		if (_swapBytes)
		{
			*(ptr + 3) = *(_currentPtr++);
			*(ptr + 2) = *(_currentPtr++);
			*(ptr + 1) = *(_currentPtr++);
			*(ptr) = *(_currentPtr++);
		}
		else
		{
			*(ptr++) = *(_currentPtr++);
			*(ptr++) = *(_currentPtr++);
			*(ptr++) = *(_currentPtr++);
			*(ptr) = *(_currentPtr++);
		}
	}

	inline void write8(char* ptr)
	{
		if (_currentPtr + 8 >= _endPtr) return;

		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr++);

		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr++);
		*(_currentPtr++) = *(ptr);
	}

	inline void read8(char* ptr)
	{
		char* endPtr = _currentPtr + 8;
		if (endPtr >= _endPtr) return;

		if (_swapBytes)
		{
			*(ptr + 7) = *(_currentPtr++);
			*(ptr + 6) = *(_currentPtr++);
			*(ptr + 5) = *(_currentPtr++);
			*(ptr + 4) = *(_currentPtr++);

			*(ptr + 3) = *(_currentPtr++);
			*(ptr + 2) = *(_currentPtr++);
			*(ptr + 1) = *(_currentPtr++);
			*(ptr) = *(_currentPtr++);
		}
		else
		{
			*(ptr++) = *(_currentPtr++);
			*(ptr++) = *(_currentPtr++);
			*(ptr++) = *(_currentPtr++);
			*(ptr++) = *(_currentPtr++);

			*(ptr++) = *(_currentPtr++);
			*(ptr++) = *(_currentPtr++);
			*(ptr++) = *(_currentPtr++);
			*(ptr) = *(_currentPtr++);
		}
	}

	inline void writeChar(char c) { write1(&c); }
	inline void writeUChar(unsigned char c) { write1((char*)&c); }
	inline void writeShort(short c) { write2((char*)&c); }
	inline void writeUShort(unsigned short c) { write2((char*)&c); }
	inline void writeInt(int c) { write4((char*)&c); }
	inline void writeUInt(unsigned int c) { write4((char*)&c); }
	inline void writeFloat(float c) { write4((char*)&c); }
	inline void writeDouble(double c) { write8((char*)&c); }

	inline char readChar() { char c = 0; read1(&c); return c; }
	inline unsigned char readUChar() { unsigned char c = 0; read1((char*)&c); return c; }
	inline short readShort() { short c = 0; read2((char*)&c); return c; }
	inline unsigned short readUShort() { unsigned short c = 0; read2((char*)&c); return c; }
	inline int readInt() { int c = 0; read4((char*)&c); return c; }
	inline unsigned int readUInt() { unsigned int c = 0; read4((char*)&c); return c; }
	inline float readFloat() { float c = 0.0f; read4((char*)&c); return c; }
	inline double readDouble() { double c = 0.0; read8((char*)&c); return c; }

	void write(const osg::FrameStamp& fs)
	{
		osg::notify(osg::NOTICE) << "writeFramestamp = " << fs.getFrameNumber() << " " << fs.getReferenceTime() << std::endl;

		writeUInt(fs.getFrameNumber());
		writeDouble(fs.getReferenceTime());
		writeDouble(fs.getSimulationTime());
	}

	void read(osg::FrameStamp& fs)
	{
		fs.setFrameNumber(readUInt());
		fs.setReferenceTime(readDouble());
		fs.setSimulationTime(readDouble());

		osg::notify(osg::NOTICE) << "readFramestamp = " << fs.getFrameNumber() << " " << fs.getReferenceTime() << std::endl;
	}

	void write(const osg::Matrix& matrix)
	{
		writeDouble(matrix(0, 0));
		writeDouble(matrix(0, 1));
		writeDouble(matrix(0, 2));
		writeDouble(matrix(0, 3));

		writeDouble(matrix(1, 0));
		writeDouble(matrix(1, 1));
		writeDouble(matrix(1, 2));
		writeDouble(matrix(1, 3));

		writeDouble(matrix(2, 0));
		writeDouble(matrix(2, 1));
		writeDouble(matrix(2, 2));
		writeDouble(matrix(2, 3));

		writeDouble(matrix(3, 0));
		writeDouble(matrix(3, 1));
		writeDouble(matrix(3, 2));
		writeDouble(matrix(3, 3));

		osg::notify(osg::NOTICE) << "writeMatrix = " << matrix << std::endl;

	}

	void read(osg::Matrix& matrix)
	{
		matrix(0, 0) = readDouble();
		matrix(0, 1) = readDouble();
		matrix(0, 2) = readDouble();
		matrix(0, 3) = readDouble();

		matrix(1, 0) = readDouble();
		matrix(1, 1) = readDouble();
		matrix(1, 2) = readDouble();
		matrix(1, 3) = readDouble();

		matrix(2, 0) = readDouble();
		matrix(2, 1) = readDouble();
		matrix(2, 2) = readDouble();
		matrix(2, 3) = readDouble();

		matrix(3, 0) = readDouble();
		matrix(3, 1) = readDouble();
		matrix(3, 2) = readDouble();
		matrix(3, 3) = readDouble();

		osg::notify(osg::NOTICE) << "readMatrix = " << matrix << std::endl;

	}

	void write(const osgGA::GUIEventAdapter& event)
	{
		writeUInt(event.getEventType());
		writeUInt(event.getKey());
		writeUInt(event.getButton());
		writeInt(event.getWindowX());
		writeInt(event.getWindowY());
		writeUInt(event.getWindowWidth());
		writeUInt(event.getWindowHeight());
		writeFloat(event.getXmin());
		writeFloat(event.getYmin());
		writeFloat(event.getXmax());
		writeFloat(event.getYmax());
		writeFloat(event.getX());
		writeFloat(event.getY());
		writeUInt(event.getButtonMask());
		writeUInt(event.getModKeyMask());
		writeDouble(event.getTime());
	}

	void read(osgGA::GUIEventAdapter& event)
	{
		event.setEventType((osgGA::GUIEventAdapter::EventType)readUInt());
		event.setKey(readUInt());
		event.setButton(readUInt());
		int x = readInt();
		int y = readInt();
		int width = readUInt();
		int height = readUInt();
		event.setWindowRectangle(x, y, width, height);
		float xmin = readFloat();
		float ymin = readFloat();
		float xmax = readFloat();
		float ymax = readFloat();
		event.setInputRange(xmin, ymin, xmax, ymax);
		event.setX(readFloat());
		event.setY(readFloat());
		event.setButtonMask(readUInt());
		event.setModKeyMask(readUInt());
		event.setTime(readDouble());
	}

	void write(CameraPacket& cameraPacket)
	{
		writeUInt(cameraPacket._byte_order);

		writeUInt(cameraPacket._masterKilled);

		write(cameraPacket._matrix);
		write(cameraPacket._frameStamp);

		writeUInt(cameraPacket._events.size());
		for (osgGA::EventQueue::Events::iterator itr = cameraPacket._events.begin();
			itr != cameraPacket._events.end();
			++itr)
		{
			osgGA::GUIEventAdapter* event = (*itr)->asGUIEventAdapter();
			if (event) write(*event);
		}
	}

	void read(CameraPacket& cameraPacket)
	{
		cameraPacket._byte_order = readUInt();
		if (cameraPacket._byte_order != SWAP_BYTES_COMPARE)
		{
			_swapBytes = !_swapBytes;
		}

		cameraPacket._masterKilled = readUInt() != 0;

		read(cameraPacket._matrix);
		read(cameraPacket._frameStamp);

		cameraPacket._events.clear();
		unsigned int numEvents = readUInt();
		for (unsigned int i = 0; i < numEvents; ++i)
		{
			osgGA::GUIEventAdapter* event = new osgGA::GUIEventAdapter;
			read(*(event));
			cameraPacket._events.push_back(event);
		}
	}
};


