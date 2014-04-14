/*
 * object.h
 *
 *  Created on: 14 Apr 2014
 *      Author: sam
 */

#ifndef OBJECT_H_
#define OBJECT_H_

class ObjectView;

class Object {
	friend class ObjectView;
private:
	double m_x, m_y, m_z;
	double m_length, m_width, m_height;
public:
	Object(double x, double y, double z,
			double length, double width, double height);

};

class ObjectView {
public:
	void Render(Object* obj);
};



#endif /* OBJECT_H_ */
