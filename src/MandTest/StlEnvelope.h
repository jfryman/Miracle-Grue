/**
   MiracleGrue - Model Generator for toolpathing. <http://www.grue.makerbot.com>
   Copyright (C) 2011 Far McKon <Far@makerbot.com>, Hugo Boyer (hugo@makerbot.com)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

*/

#ifndef GCODE_DATA_H
#define GCODE_DATA_H

#include <string>
#include "../DataEnvelope.h"
namespace BGL {
	class Mesh3d; //#include "../BGL/Mesh3d.h"
}

class StlEnvelope: public DataEnvelope {

private:
	BGL::Mesh3d &ourMesh;

public:

	StlEnvelope(BGL::Mesh3d &mesh);
	~StlEnvelope();

	const BGL::Mesh3d& getMesh() const;
};


#endif // GCODE_DATA_H
